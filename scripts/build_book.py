#!/usr/bin/env python3
# /// script
# requires-python = ">=3.11"
# dependencies = [
#   "pillow>=11,<13",
#   "pypdf>=6,<7",
#   "reportlab>=4.4,<5",
# ]
# ///
"""Build and validate the complete C tutorial PDF from canonical Markdown files."""

from __future__ import annotations

import argparse
import hashlib
import html
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any, Iterable

from pypdf import PdfReader
from reportlab import rl_config
from reportlab.lib import colors
from reportlab.lib.enums import TA_CENTER, TA_LEFT
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle, getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.pdfgen import canvas
from reportlab.platypus import (
    BaseDocTemplate,
    Flowable,
    HRFlowable,
    Image,
    Indenter,
    ListFlowable,
    ListItem,
    LongTable,
    PageBreak,
    PageTemplate,
    Paragraph,
    Spacer,
    TableStyle,
)
from reportlab.platypus.tableofcontents import TableOfContents
from reportlab.platypus.xpreformatted import XPreformatted


ROOT = Path(__file__).resolve().parents[1]
MANIFEST_PATH = ROOT / "docs" / "book.json"
TMP_ROOT = ROOT / "tmp" / "pdfs"
PANDOC = shutil.which("pandoc")
MMDC = shutil.which("mmdc")
PDFINFO = shutil.which("pdfinfo")
PDFTOPPM = shutil.which("pdftoppm")
PDFFONTS = shutil.which("pdffonts")
FC_MATCH = shutil.which("fc-match")
JAPANESE = r"[\u3040-\u30ff\u3400-\u4dbf\u4e00-\u9fff\u3005\u3006\u30f6]"
INLINE_CODE = re.compile(r"`+[^`]*`+")
SPACE_BETWEEN_SCRIPTS = re.compile(rf"(?:{JAPANESE}[ \t]+[A-Za-z0-9]|[A-Za-z0-9][ \t]+{JAPANESE})")
HALFWIDTH_PUNCTUATION = re.compile(rf"(?:{JAPANESE}[?!:;]|[?!:;]{JAPANESE})")
HEADING_SEPARATOR = re.compile(r"^#{1,6}\s+.*(?:--+|[\u2014\u2015\u2500]{2,}).*$")
PROSE_DASH = re.compile(r"[\u2014\u2015]")


def resolve_font(families: tuple[str, ...], style: str = "Regular") -> Path | None:
    if not FC_MATCH:
        return None
    for family in families:
        result = subprocess.run(
            [str(FC_MATCH), "-f", "%{family}\n%{file}", f"{family}:style={style}"],
            check=False,
            capture_output=True,
            text=True,
        )
        matched = result.stdout.splitlines()
        if len(matched) < 2 or family.casefold() not in matched[0].casefold():
            continue
        path = Path(matched[1].strip())
        if path.is_file() and path.suffix.lower() in {".ttf", ".ttc"}:
            return path
    return None


BODY_FONT = resolve_font(("FORM UDPGothic", "Noto Sans JP", "Arial Unicode MS"))
BOLD_FONT = resolve_font(("FORM UDPGothic", "Noto Sans JP", "Arial Unicode MS"), "Bold")
CODE_FONT = resolve_font(("Noto Sans Mono CJK JP", "FORM UDPGothic", "Arial Unicode MS"))

def require_tools() -> None:
    missing = []
    if not PANDOC:
        missing.append("pandoc")
    if not MMDC:
        missing.append("mmdc")
    if missing:
        raise RuntimeError("Missing required tools: " + ", ".join(missing))
    for font in (BODY_FONT, BOLD_FONT, CODE_FONT):
        if font is None or not font.exists():
            raise RuntimeError(f"Missing required font: {font}")


def load_manifest() -> dict[str, Any]:
    return json.loads(MANIFEST_PATH.read_text(encoding="utf-8"))


def audit_japanese_text(path: Path, manifest: dict[str, Any]) -> list[str]:
    findings: list[str] = []
    text = path.read_text(encoding="utf-8")
    fence: str | None = None
    in_frontmatter = text.startswith("---\n")
    for line_number, raw_line in enumerate(text.splitlines(), start=1):
        if in_frontmatter:
            if line_number > 1 and raw_line.strip() == "---":
                in_frontmatter = False
            continue
        stripped = raw_line.lstrip()
        if stripped.startswith(("```", "~~~")):
            marker = stripped[:3]
            fence = None if fence == marker else marker
            continue
        if fence is not None:
            continue
        line = INLINE_CODE.sub("", raw_line)
        if not line.strip():
            continue
        rules = (
            (PROSE_DASH.search(line), "prose dash"),
            (SPACE_BETWEEN_SCRIPTS.search(line), "script spacing"),
            (HEADING_SEPARATOR.search(line), "heading separator"),
            (HALFWIDTH_PUNCTUATION.search(line), "halfwidth punctuation"),
            (line.count("\u3002") >= 2, "multiple sentences per line"),
        )
        for matched, message in rules:
            if matched:
                findings.append(f"{path.relative_to(ROOT)}:{line_number}: {message}")
        for phrase in manifest["validation"]["forbidden_phrases"]:
            if phrase in line:
                findings.append(f"{path.relative_to(ROOT)}:{line_number}: stock phrase '{phrase}'")
        for pattern in manifest["validation"]["malformed_patterns"]:
            if re.search(pattern, line):
                findings.append(f"{path.relative_to(ROOT)}:{line_number}: malformed spelling /{pattern}/")
    return findings


def active_markdown_paths() -> list[Path]:
    paths = [ROOT / "README.md", ROOT / "scripts" / "README.md"]
    paths.extend(sorted((ROOT / "src").rglob("README.md")))
    return paths


def audit_all_markdown(manifest: dict[str, Any]) -> None:
    findings: list[str] = []
    for path in active_markdown_paths():
        findings.extend(audit_japanese_text(path, manifest))
    if findings:
        raise RuntimeError("Japanese writing audit failed:\n" + "\n".join(findings))


def strip_frontmatter(lines: list[str]) -> list[str]:
    if not lines or lines[0].strip() != "---":
        return lines
    for index in range(1, len(lines)):
        if lines[index].strip() == "---":
            return lines[index + 1 :]
    return lines


def strip_sections(lines: list[str], drop_sections: set[str]) -> list[str]:
    result: list[str] = []
    dropping = False
    drop_level = 0
    for line in lines:
        match = re.match(r"^(#{1,6})\s+(.+?)\s*$", line)
        if match:
            level = len(match.group(1))
            title = re.sub(r"\s+\{[^}]*\}\s*$", "", match.group(2)).strip()
            if title in drop_sections:
                dropping = True
                drop_level = level
                continue
            if dropping and level <= drop_level:
                dropping = False
        if not dropping:
            result.append(line)
    return result


def shift_headings(lines: list[str], title: str, css_class: str) -> list[str]:
    result: list[str] = []
    first_heading = False
    in_fence = False
    fence_marker = ""
    for line in lines:
        stripped = line.lstrip()
        if stripped.startswith(("```", "~~~")):
            marker = stripped[:3]
            if not in_fence:
                in_fence = True
                fence_marker = marker
            elif marker == fence_marker:
                in_fence = False
            result.append(line)
            continue
        if not in_fence:
            match = re.match(r"^(#{1,6})\s+(.+)$", line)
            if match:
                if not first_heading:
                    result.append(f"## {title} {{.{css_class}}}")
                    first_heading = True
                    continue
                level = min(6, len(match.group(1)) + 1)
                result.append("#" * level + " " + match.group(2))
                continue
        result.append(line)
    if not first_heading:
        result.insert(0, f"## {title} {{.{css_class}}}")
    return result


def prepare_source(path: Path, title: str, css_class: str, drop_sections: set[str]) -> str:
    text = path.read_text(encoding="utf-8")
    if "\x00" in text:
        raise RuntimeError(f"NUL byte found in {path}")
    lines = strip_frontmatter(text.replace("\r\n", "\n").splitlines())
    lines = strip_sections(lines, drop_sections)
    lines = shift_headings(lines, title, css_class)
    return "\n".join(lines).strip() + "\n"


def build_markdown(manifest: dict[str, Any], target: Path) -> list[Path]:
    used: list[Path] = []
    sections: list[str] = [
        "---",
        f'title: "{manifest["title"]}"',
        f'subtitle: "{manifest["subtitle"]}"',
        f'author: "{manifest["author"]}"',
        'lang: "ja"',
        "---",
        "",
    ]
    part_specs = (
        ("textbook", ROOT / "src" / "{id}" / "README.md", "chapter", ""),
        (
            "exercises",
            ROOT / "src" / "{id}" / "exercises" / "README.md",
            "chapter",
            manifest["labels"]["exercise_suffix"],
        ),
        (
            "solutions",
            ROOT / "src" / "{id}" / "solutions" / "README.md",
            "chapter",
            manifest["labels"]["solution_suffix"],
        ),
    )
    drop_sections = {manifest["navigation_heading"]}
    for part_key, pattern, css_class, suffix in part_specs:
        sections.extend((f'# {manifest["parts"][part_key]} {{.part}}', ""))
        for chapter in manifest["chapters"]:
            source = Path(str(pattern).format(id=chapter["id"]))
            if not source.exists():
                continue
            used.append(source)
            label = str(chapter["number"])
            template = manifest["labels"]["supplement"] if not label.isdigit() else manifest["labels"]["chapter"]
            heading = template.format(number=label, title=chapter["title"], suffix=suffix)
            sections.append(prepare_source(source, heading, css_class, drop_sections))
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text("\n".join(sections), encoding="utf-8")
    return used


def run_pandoc(source: Path) -> dict[str, Any]:
    process = subprocess.run(
        [
            str(PANDOC),
            "--from=markdown+fenced_divs+bracketed_spans+definition_lists+pipe_tables",
            "--to=json",
            str(source),
        ],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    return json.loads(process.stdout)


def register_fonts() -> None:
    assert BODY_FONT is not None
    assert BOLD_FONT is not None
    assert CODE_FONT is not None
    pdfmetrics.registerFont(TTFont("BookBody", str(BODY_FONT)))
    pdfmetrics.registerFont(TTFont("BookBodyBold", str(BOLD_FONT)))
    pdfmetrics.registerFont(TTFont("BookCode", str(CODE_FONT)))
    pdfmetrics.registerFontFamily(
        "BookBody",
        normal="BookBody",
        bold="BookBodyBold",
        italic="BookBody",
        boldItalic="BookBodyBold",
    )
    rl_config.canvas_basefontname = "BookBody"


def inline_markup(inlines: list[dict[str, Any]]) -> str:
    parts: list[str] = []
    for inline in inlines:
        kind = inline["t"]
        value = inline.get("c")
        if kind == "Str":
            parts.append(html.escape(value))
        elif kind in {"Space", "SoftBreak"}:
            parts.append(" ")
        elif kind == "LineBreak":
            parts.append("<br/>")
        elif kind == "Code":
            parts.append(f'<font name="BookCode">{html.escape(value[1])}</font>')
        elif kind == "Strong":
            parts.append("<b>" + inline_markup(value) + "</b>")
        elif kind == "Emph":
            parts.append("<i>" + inline_markup(value) + "</i>")
        elif kind == "Strikeout":
            parts.append("<strike>" + inline_markup(value) + "</strike>")
        elif kind == "Superscript":
            parts.append("<super>" + inline_markup(value) + "</super>")
        elif kind == "Subscript":
            parts.append("<sub>" + inline_markup(value) + "</sub>")
        elif kind == "Quoted":
            quote_type, content = value
            marks = ("‘", "’") if quote_type["t"] == "SingleQuote" else ("“", "”")
            parts.append(marks[0] + inline_markup(content) + marks[1])
        elif kind == "Link":
            _, content, target = value
            url = html.escape(target[0], quote=True)
            label = inline_markup(content)
            if url.startswith(("http://", "https://", "mailto:")):
                parts.append(f'<link href="{url}" color="#1955a6">{label}</link>')
            else:
                parts.append(label)
        elif kind == "Image":
            _, content, _ = value
            parts.append(inline_markup(content))
        elif kind == "Math":
            parts.append(f'<font name="BookCode">{html.escape(value[1])}</font>')
        elif kind == "Span":
            parts.append(inline_markup(value[1]))
        elif kind == "Note":
            parts.append("[Note]")
        else:
            parts.append(html.escape(str(value)) if value is not None else "")
    return "".join(parts)


def plain_text(inlines: list[dict[str, Any]]) -> str:
    return re.sub(r"<[^>]+>", "", inline_markup(inlines))


def blocks_to_markup(blocks: list[dict[str, Any]]) -> str:
    chunks: list[str] = []
    for block in blocks:
        if block["t"] in {"Para", "Plain"}:
            chunks.append(inline_markup(block["c"]))
        elif block["t"] == "CodeBlock":
            chunks.append(f'<font name="BookCode">{html.escape(block["c"][1])}</font>')
        elif block["t"] == "BulletList":
            for item in block["c"]:
                chunks.append("・" + blocks_to_markup(item))
        elif block["t"] == "OrderedList":
            for index, item in enumerate(block["c"][1], start=block["c"][0][0]):
                chunks.append(f"{index}. " + blocks_to_markup(item))
        else:
            chunks.append("")
    return "<br/>".join(chunk for chunk in chunks if chunk)


class BookDocTemplate(BaseDocTemplate):
    def __init__(self, filename: str, styles: dict[str, ParagraphStyle], **kwargs: Any) -> None:
        super().__init__(filename, **kwargs)
        self.book_styles = styles
        frame_width = self.pagesize[0] - self.leftMargin - self.rightMargin
        frame_height = self.pagesize[1] - self.topMargin - self.bottomMargin
        from reportlab.platypus import Frame

        frame = Frame(self.leftMargin, self.bottomMargin, frame_width, frame_height, id="body")
        self.addPageTemplates(PageTemplate(id="book", frames=[frame], onPage=self.draw_page))

    def draw_page(self, canvas: Any, doc: Any) -> None:
        page = canvas.getPageNumber()
        if page == 1:
            return
        canvas.saveState()
        canvas.setFont("BookBody", 8)
        canvas.setFillColor(colors.HexColor("#666666"))
        canvas.drawCentredString(A4[0] / 2, 9 * mm, str(page - 1))
        canvas.restoreState()

    def afterFlowable(self, flowable: Flowable) -> None:
        if not isinstance(flowable, Paragraph):
            return
        level = getattr(flowable, "_toc_level", None)
        bookmark = getattr(flowable, "_bookmark_name", None)
        if level is None or bookmark is None:
            return
        text = flowable.getPlainText()
        self.canv.bookmarkPage(bookmark)
        self.canv.addOutlineEntry(text, bookmark, level=level, closed=level > 0)
        self.notify("TOCEntry", (level, text, self.page, bookmark))


class EmbeddedFontCanvas(canvas.Canvas):
    def __init__(self, *args: Any, **kwargs: Any) -> None:
        kwargs["initialFontName"] = "BookBody"
        kwargs["initialFontSize"] = 9.3
        kwargs["initialLeading"] = 15
        super().__init__(*args, **kwargs)

    def setFont(self, psfontname: str, size: float, leading: float | None = None) -> None:
        if psfontname == "Helvetica":
            psfontname = "BookBody"
        super().setFont(psfontname, size, leading)


class Renderer:
    def __init__(self, styles: dict[str, ParagraphStyle], workdir: Path) -> None:
        self.styles = styles
        self.workdir = workdir
        self.heading_index = 0
        self.has_heading = False

    def heading(self, level: int, attr: list[Any], inlines: list[dict[str, Any]]) -> list[Flowable]:
        identifier, classes, _ = attr
        title = inline_markup(inlines)
        self.heading_index += 1
        bookmark = identifier or f"heading-{self.heading_index}"
        style_name = f"Heading{min(level, 6)}"
        paragraph = Paragraph(f'<a name="{html.escape(bookmark)}"/>{title}', self.styles[style_name])
        if "part" in classes:
            paragraph._toc_level = 0  # type: ignore[attr-defined]
            paragraph._bookmark_name = bookmark  # type: ignore[attr-defined]
        elif "chapter" in classes:
            paragraph._toc_level = 1  # type: ignore[attr-defined]
            paragraph._bookmark_name = bookmark  # type: ignore[attr-defined]
        flowables: list[Flowable] = []
        if self.has_heading and ("part" in classes or "chapter" in classes):
            flowables.append(PageBreak())
        self.has_heading = True
        flowables.append(paragraph)
        return flowables

    def render_mermaid(self, source: str) -> Image:
        digest = hashlib.sha256(source.encode("utf-8")).hexdigest()[:16]
        input_path = self.workdir / f"mermaid-{digest}.mmd"
        output_path = self.workdir / f"mermaid-{digest}.png"
        input_path.write_text(source, encoding="utf-8")
        if not output_path.exists():
            command = [
                str(MMDC),
                "-i",
                str(input_path),
                "-o",
                str(output_path),
                "-c",
                str(ROOT / ".mermaid-config.json"),
                "-C",
                str(ROOT / ".mermaid.css"),
                "-b",
                "white",
                "-s",
                "2",
            ]
            result = subprocess.run(command, cwd=ROOT, check=False, capture_output=True, text=True)
            if result.returncode != 0:
                raise RuntimeError("Mermaid rendering failed:\n" + (result.stderr or result.stdout))
        image = Image(str(output_path))
        max_width = A4[0] - 42 * mm
        max_height = A4[1] - 70 * mm
        scale = min(max_width / image.imageWidth, max_height / image.imageHeight, 1.0)
        image.drawWidth = image.imageWidth * scale
        image.drawHeight = image.imageHeight * scale
        image.hAlign = "CENTER"
        return image

    def list_items(self, items: list[list[dict[str, Any]]], ordered: bool, start: int = 1) -> ListFlowable:
        rendered: list[ListItem] = []
        for item in items:
            children = self.blocks(item)
            rendered.append(ListItem(children, leftIndent=7 * mm))
        options: dict[str, Any] = {
            "bulletType": "1" if ordered else "bullet",
            "leftIndent": 8 * mm,
            "bulletFontName": "BookBody",
            "bulletFontSize": 9,
            "spaceBefore": 2,
            "spaceAfter": 5,
        }
        if ordered:
            options["start"] = str(start)
        return ListFlowable(
            rendered,
            **options,
        )

    def table(self, value: list[Any]) -> LongTable:
        _, _, colspecs, head, bodies, foot = value
        rows: list[list[Paragraph]] = []
        head_rows = head[1]
        for row in head_rows:
            rows.append([Paragraph(blocks_to_markup(cell[4]), self.styles["TableHead"]) for cell in row[1]])
        for body in bodies:
            for row in body[2] + body[3]:
                rows.append([Paragraph(blocks_to_markup(cell[4]), self.styles["TableCell"]) for cell in row[1]])
        for row in foot[1]:
            rows.append([Paragraph(blocks_to_markup(cell[4]), self.styles["TableCell"]) for cell in row[1]])
        if not rows:
            rows = [[Paragraph("", self.styles["TableCell"])]]
        columns = max(len(row) for row in rows)
        for row in rows:
            row.extend(Paragraph("", self.styles["TableCell"]) for _ in range(columns - len(row)))
        available = A4[0] - 42 * mm
        specified = []
        for _, width in colspecs:
            specified.append(width if isinstance(width, (int, float)) else 0)
        if specified and sum(specified) > 0:
            total = sum(specified)
            widths = [available * width / total for width in specified]
        else:
            widths = [available / columns] * columns
        table = LongTable(rows, colWidths=widths, repeatRows=1 if head_rows else 0, hAlign="LEFT")
        commands: list[tuple[Any, ...]] = [
            ("FONTNAME", (0, 0), (-1, -1), "BookBody"),
            ("FONTSIZE", (0, 0), (-1, -1), 7.2),
            ("LEADING", (0, 0), (-1, -1), 9.2),
            ("VALIGN", (0, 0), (-1, -1), "TOP"),
            ("GRID", (0, 0), (-1, -1), 0.35, colors.HexColor("#aab2bd")),
            ("LEFTPADDING", (0, 0), (-1, -1), 4),
            ("RIGHTPADDING", (0, 0), (-1, -1), 4),
            ("TOPPADDING", (0, 0), (-1, -1), 4),
            ("BOTTOMPADDING", (0, 0), (-1, -1), 4),
        ]
        if head_rows:
            commands.extend(
                [
                    ("BACKGROUND", (0, 0), (-1, len(head_rows) - 1), colors.HexColor("#e9eef5")),
                    ("FONTNAME", (0, 0), (-1, len(head_rows) - 1), "BookBodyBold"),
                ]
            )
        table.setStyle(TableStyle(commands))
        return table

    def block(self, block: dict[str, Any]) -> list[Flowable]:
        kind = block["t"]
        value = block.get("c")
        if kind == "Header":
            return self.heading(value[0], value[1], value[2])
        if kind in {"Para", "Plain"}:
            markup = inline_markup(value)
            return [Paragraph(markup or " ", self.styles["Body"])]
        if kind == "CodeBlock":
            attr, source = value
            if "mermaid" in attr[1]:
                return [Spacer(1, 3 * mm), self.render_mermaid(source), Spacer(1, 3 * mm)]
            return [XPreformatted(html.escape(source), self.styles["Code"])]
        if kind == "BulletList":
            return [self.list_items(value, ordered=False)]
        if kind == "OrderedList":
            attrs, items = value
            return [self.list_items(items, ordered=True, start=attrs[0])]
        if kind == "DefinitionList":
            flowables: list[Flowable] = []
            for term, definitions in value:
                flowables.append(Paragraph("<b>" + inline_markup(term) + "</b>", self.styles["BodyTight"]))
                flowables.append(Indenter(left=7 * mm))
                for definition in definitions:
                    flowables.extend(self.blocks(definition))
                flowables.append(Indenter(left=-7 * mm))
            return flowables
        if kind == "BlockQuote":
            return [Indenter(left=7 * mm)] + self.blocks(value) + [Indenter(left=-7 * mm)]
        if kind == "HorizontalRule":
            return [Spacer(1, 2 * mm), HRFlowable(width="100%", thickness=0.5, color=colors.HexColor("#9aa4b2")), Spacer(1, 2 * mm)]
        if kind == "Table":
            return [Spacer(1, 2 * mm), self.table(value), Spacer(1, 3 * mm)]
        if kind == "Div":
            return self.blocks(value[1])
        if kind == "RawBlock":
            return []
        if kind == "LineBlock":
            return [Paragraph("<br/>".join(inline_markup(line) for line in value), self.styles["Body"])]
        return []

    def blocks(self, blocks: Iterable[dict[str, Any]]) -> list[Flowable]:
        flowables: list[Flowable] = []
        for block in blocks:
            flowables.extend(self.block(block))
        return flowables


def make_styles() -> dict[str, ParagraphStyle]:
    sample = getSampleStyleSheet()
    body = ParagraphStyle(
        "Body",
        parent=sample["BodyText"],
        fontName="BookBody",
        fontSize=9.3,
        leading=15,
        textColor=colors.HexColor("#20252b"),
        spaceAfter=4.5,
        splitLongWords=True,
        allowWidows=1,
        allowOrphans=1,
    )
    styles: dict[str, ParagraphStyle] = {
        "Body": body,
        "BodyTight": ParagraphStyle("BodyTight", parent=body, spaceAfter=1.5),
        "Code": ParagraphStyle(
            "Code",
            parent=body,
            fontName="BookCode",
            fontSize=6.8,
            leading=8.8,
            leftIndent=4 * mm,
            rightIndent=4 * mm,
            borderPadding=5,
            borderColor=colors.HexColor("#d8dee8"),
            borderWidth=0.5,
            borderRadius=2,
            backColor=colors.HexColor("#f5f7fa"),
            spaceBefore=3,
            spaceAfter=6,
            splitLongWords=True,
        ),
        "TableHead": ParagraphStyle("TableHead", parent=body, fontName="BookBodyBold", fontSize=7.2, leading=9.2),
        "TableCell": ParagraphStyle("TableCell", parent=body, fontSize=7.2, leading=9.2),
    }
    heading_specs = {
        1: (23, 31, "#17365d", 12, 10),
        2: (18, 25, "#17365d", 10, 8),
        3: (14, 20, "#244f7a", 8, 5),
        4: (11.5, 17, "#2d5d87", 6, 4),
        5: (10.3, 15, "#34495e", 5, 3),
        6: (9.6, 14, "#34495e", 4, 2),
    }
    for level, (size, leading, color, before, after) in heading_specs.items():
        styles[f"Heading{level}"] = ParagraphStyle(
            f"Heading{level}",
            parent=body,
            fontName="BookBodyBold",
            fontSize=size,
            leading=leading,
            textColor=colors.HexColor(color),
            spaceBefore=before,
            spaceAfter=after,
            keepWithNext=True,
        )
    return styles


def title_story(manifest: dict[str, Any], styles: dict[str, ParagraphStyle]) -> list[Flowable]:
    title_style = ParagraphStyle(
        "Title",
        parent=styles["Heading1"],
        fontSize=28,
        leading=40,
        alignment=TA_CENTER,
        textColor=colors.HexColor("#17365d"),
    )
    subtitle_style = ParagraphStyle(
        "Subtitle",
        parent=styles["Body"],
        fontSize=14,
        leading=22,
        alignment=TA_CENTER,
        textColor=colors.HexColor("#4b5f73"),
    )
    author_style = ParagraphStyle(
        "Author",
        parent=styles["Body"],
        fontSize=11,
        leading=16,
        alignment=TA_CENTER,
    )
    toc = TableOfContents()
    toc.levelStyles = [
        ParagraphStyle("TOC1", fontName="BookBodyBold", fontSize=10.5, leading=15, leftIndent=0, firstLineIndent=0, spaceBefore=4),
        ParagraphStyle("TOC2", fontName="BookBody", fontSize=9.2, leading=13, leftIndent=6 * mm, firstLineIndent=0, spaceBefore=1),
        ParagraphStyle("TOC3", fontName="BookBody", fontSize=8.5, leading=12, leftIndent=12 * mm, firstLineIndent=0),
    ]
    return [
        Spacer(1, 58 * mm),
        Paragraph(html.escape(manifest["title"]), title_style),
        Spacer(1, 8 * mm),
        Paragraph(html.escape(manifest["subtitle"]), subtitle_style),
        Spacer(1, 62 * mm),
        Paragraph(html.escape(manifest["author"]), author_style),
        PageBreak(),
        Paragraph(html.escape(manifest["toc_title"]), styles["Heading1"]),
        Spacer(1, 4 * mm),
        toc,
        PageBreak(),
    ]


def build_pdf(ast: dict[str, Any], manifest: dict[str, Any], output: Path, workdir: Path) -> None:
    register_fonts()
    styles = make_styles()
    renderer = Renderer(styles, workdir)
    story = title_story(manifest, styles) + renderer.blocks(ast["blocks"])
    output.parent.mkdir(parents=True, exist_ok=True)
    doc = BookDocTemplate(
        str(output),
        styles,
        pagesize=A4,
        leftMargin=21 * mm,
        rightMargin=21 * mm,
        topMargin=18 * mm,
        bottomMargin=18 * mm,
        title=manifest["title"],
        author=manifest["author"],
        subject=manifest["subtitle"],
    )
    doc.multiBuild(story, canvasmaker=EmbeddedFontCanvas)


def validate_sources(paths: list[Path], manifest: dict[str, Any]) -> None:
    failures: list[str] = []
    for path in paths:
        text = path.read_text(encoding="utf-8")
        if "\x00" in text:
            failures.append(f"NUL byte: {path}")
        for pattern in manifest["validation"]["malformed_patterns"]:
            if re.search(pattern, text):
                failures.append(f"Malformed spelling /{pattern}/: {path}")
        for phrase in manifest["validation"]["forbidden_phrases"]:
            if phrase in text:
                failures.append(f"Stock phrase '{phrase}': {path}")
    if failures:
        raise RuntimeError("Source validation failed:\n" + "\n".join(failures))


def validate_pdf(output: Path, manifest: dict[str, Any]) -> int:
    reader = PdfReader(str(output))
    if len(reader.pages) < 100:
        raise RuntimeError(f"Unexpected page count: {len(reader.pages)}")
    expected_width, expected_height = A4
    empty_pages: list[int] = []
    local_links: list[int] = []
    page_texts: list[str] = []
    for page_number, page in enumerate(reader.pages, start=1):
        width = float(page.mediabox.width)
        height = float(page.mediabox.height)
        if abs(width - expected_width) > 1 or abs(height - expected_height) > 1:
            raise RuntimeError(f"Non-A4 page: {page_number} ({width} x {height})")
        text = page.extract_text() or ""
        page_texts.append(text)
        if not text.strip():
            empty_pages.append(page_number)
        for annotation_ref in page.get("/Annots", []):
            annotation = annotation_ref.get_object()
            action = annotation.get("/A")
            if action and str(action.get("/URI", "")).startswith("file:"):
                local_links.append(page_number)
    if empty_pages:
        raise RuntimeError(f"Empty PDF pages: {empty_pages}")
    if local_links:
        raise RuntimeError(f"Local file links on pages: {local_links}")
    first_text = "\n".join(page_texts[:5])
    if manifest["title"] not in first_text:
        raise RuntimeError("Document title was not found in the first pages")
    all_text = "\n".join(page_texts)
    forbidden = ("ERR_FILE_NOT_FOUND", "file:///Users/", "<w:p>", "STATE_STOPPDFF")
    found = [token for token in forbidden if token in all_text]
    if found:
        raise RuntimeError("Forbidden output tokens: " + ", ".join(found))
    missing_headings: list[str] = []
    for chapter in manifest["chapters"]:
        label = str(chapter["number"])
        template = manifest["labels"]["supplement"] if not label.isdigit() else manifest["labels"]["chapter"]
        heading = template.format(number=label, title=chapter["title"], suffix="")
        if heading not in all_text:
            missing_headings.append(heading)
    if missing_headings:
        raise RuntimeError("Missing chapter headings: " + ", ".join(missing_headings))
    if PDFFONTS:
        result = subprocess.run([str(PDFFONTS), str(output)], check=True, capture_output=True, text=True)
        font_rows = [line.split() for line in result.stdout.splitlines()[2:] if line.strip()]
        not_embedded = [row[0] for row in font_rows if len(row) > 3 and row[3].lower() != "yes"]
        if not_embedded:
            raise RuntimeError("Fonts are not embedded: " + ", ".join(not_embedded))
    return len(reader.pages)


def render_preview(output: Path, preview_dir: Path, dpi: int) -> None:
    if not PDFTOPPM:
        return
    if preview_dir.exists():
        shutil.rmtree(preview_dir)
    preview_dir.mkdir(parents=True)
    subprocess.run(
        [str(PDFTOPPM), "-r", str(dpi), "-png", str(output), str(preview_dir / "page")],
        cwd=ROOT,
        check=True,
    )
    create_contact_sheets(preview_dir)


def create_contact_sheets(preview_dir: Path, columns: int = 4, rows: int = 5) -> None:
    from PIL import Image as PILImage
    from PIL import ImageDraw, ImageOps

    page_paths = sorted(
        preview_dir.glob("page-*.png"),
        key=lambda path: int(path.stem.rsplit("-", 1)[1]),
    )
    contact_dir = preview_dir / "contact-sheets"
    contact_dir.mkdir(parents=True, exist_ok=True)
    batch_size = columns * rows
    thumb_width = 220
    thumb_height = 312
    gap = 12
    label_height = 22
    for batch_index in range(0, len(page_paths), batch_size):
        batch = page_paths[batch_index : batch_index + batch_size]
        canvas = PILImage.new(
            "RGB",
            (
                columns * (thumb_width + gap) + gap,
                rows * (thumb_height + label_height + gap) + gap,
            ),
            "#d9dde3",
        )
        draw = ImageDraw.Draw(canvas)
        for index, path in enumerate(batch):
            with PILImage.open(path) as source:
                page = ImageOps.contain(source.convert("RGB"), (thumb_width, thumb_height))
            column = index % columns
            row = index // columns
            x = gap + column * (thumb_width + gap)
            y = gap + row * (thumb_height + label_height + gap)
            canvas.paste(page, (x, y))
            page_number = int(path.stem.rsplit("-", 1)[1])
            draw.text((x, y + thumb_height + 3), f"Page {page_number}", fill="#20252b")
        output = contact_dir / f"contact-{batch_index // batch_size + 1:03d}.png"
        canvas.save(output, optimize=True)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, help="Override the PDF output path")
    parser.add_argument("--render", action="store_true", help="Render every PDF page to PNG")
    parser.add_argument("--dpi", type=int, default=90, help="Preview rendering resolution")
    parser.add_argument("--keep-temp", action="store_true", help="Keep temporary Markdown and diagram files")
    parser.add_argument("--audit-only", action="store_true", help="Audit active Markdown without building a PDF")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    manifest = load_manifest()
    audit_all_markdown(manifest)
    if args.audit_only:
        print(f"Audited {len(active_markdown_paths())} Markdown files")
        return 0
    require_tools()
    output = (ROOT / args.output).resolve() if args.output else (ROOT / manifest["output"]).resolve()
    TMP_ROOT.mkdir(parents=True, exist_ok=True)
    if args.keep_temp:
        workdir = TMP_ROOT / "build"
        workdir.mkdir(parents=True, exist_ok=True)
        cleanup = None
    else:
        cleanup = tempfile.TemporaryDirectory(prefix="book-", dir=TMP_ROOT)
        workdir = Path(cleanup.name)
    try:
        source = workdir / "book.md"
        used = build_markdown(manifest, source)
        validate_sources(used, manifest)
        ast = run_pandoc(source)
        build_pdf(ast, manifest, output, workdir)
        pages = validate_pdf(output, manifest)
        if args.render:
            render_preview(output, TMP_ROOT / "rendered", args.dpi)
        print(f"Built {output.relative_to(ROOT)} ({pages} pages)")
    finally:
        if cleanup is not None:
            cleanup.cleanup()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
