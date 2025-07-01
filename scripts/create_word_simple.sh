#!/bin/bash
# docs/main_textbook.mdから学習に必要な部分のみを抽出してWord文書を生成

# 基本ディレクトリ
BASE_DIR=$(pwd)
DOCS_DIR="../docs"
OUTPUT_DIR="../output/word"
TEMPLATE="../custom-reference-1.docx"

# 一時ファイル
TEMP_CLEAN="/tmp/textbook_clean.md"

# 出力ファイル名
OUTPUT_FILE="${OUTPUT_DIR}/C言語プログラミング教材_学習テキスト.docx"

echo "docs/main_textbook.mdから学習用テキストを生成します"
echo "================================================"

# docsディレクトリの存在確認
if [ ! -f "${DOCS_DIR}/main_textbook.md" ]; then
    echo "エラー: ${DOCS_DIR}/main_textbook.md が見つかりません"
    exit 1
fi

# outputディレクトリの作成
mkdir -p "$OUTPUT_DIR"

echo "クリーンアップ処理を実行中..."

# シンプルなアプローチ：必要なセクションのみを抽出
python3 << 'PYTHON_SCRIPT' > "$TEMP_CLEAN"
import re

# ファイルを読み込む
with open("../docs/main_textbook.md", "r", encoding="utf-8") as f:
    lines = f.readlines()

output_lines = []
skip_section = False
in_code_block = False
code_block_count = 0

# 除外するセクションのパターン
skip_patterns = [
    "次の章へ",
    "参考資料",
    "サンプルコード",
    "演習課題",
    "演習問題",
    "コンパイル方法",
    "規格による違い",
    "よくある間違い",
    "おめでとうございます",
    "学習完了項目",
    "次のステップ",
]

for i, line in enumerate(lines):
    # コードブロックの追跡
    if line.strip().startswith("```"):
        in_code_block = not in_code_block
        if in_code_block:
            code_block_count += 1
    
    # セクションヘッダーの検出
    if line.startswith("##") and not in_code_block:
        # 除外するセクションかチェック
        if any(pattern in line for pattern in skip_patterns):
            skip_section = True
            continue
        else:
            skip_section = False
    
    # 新しい章の開始でリセット
    if line.startswith("# 第") and not in_code_block:
        skip_section = False
        # 前の章の最後に適切な改行を追加
        if output_lines and output_lines[-1].strip() != "---":
            output_lines.append("\n---\n")
    
    # スキップ中でなければ出力
    if not skip_section:
        output_lines.append(line)

# 最後のクリーンアップ
result = "".join(output_lines)

# 連続する空行を削減
result = re.sub(r'\n\n\n+', '\n\n', result)

# 章の境界の---が適切に配置されているか確認
result = re.sub(r'\n+---\n+#', '\n\n---\n\n#', result)

print(result)
PYTHON_SCRIPT

echo "検証中..."

# 生成されたファイルの基本検証
if [ -f "$TEMP_CLEAN" ]; then
    line_count=$(wc -l < "$TEMP_CLEAN")
    echo "  生成されたファイル: ${line_count} 行"
    
    # YAMLヘッダーの確認
    if head -n 1 "$TEMP_CLEAN" | grep -q "^---$"; then
        echo "  YAMLヘッダー: OK"
    else
        echo "  警告: YAMLヘッダーが見つかりません"
    fi
else
    echo "エラー: フィルタリング後のファイルが生成されませんでした"
    exit 1
fi

echo "pandocで変換中..."

# pandocで変換（エラーを無視して強制的に処理）
pandoc "$TEMP_CLEAN" \
    --reference-doc="$TEMPLATE" \
    -o "$OUTPUT_FILE" \
    --from markdown \
    --to docx \
    --toc \
    --toc-depth=2 \
    --standalone 2>/dev/null

if [ -f "$OUTPUT_FILE" ]; then
    echo "✓ 作成完了: $(basename "$OUTPUT_FILE")"
    echo "  ファイルサイズ: $(ls -lh "$OUTPUT_FILE" | awk '{print $5}')"
    echo "  保存場所: $OUTPUT_FILE"
    
    # 統計情報
    original_lines=$(wc -l < "${DOCS_DIR}/main_textbook.md")
    cleaned_lines=$(wc -l < "$TEMP_CLEAN")
    removed_lines=$((original_lines - cleaned_lines))
    
    echo ""
    echo "処理統計:"
    echo "  元のファイル: ${original_lines} 行"
    echo "  処理後: ${cleaned_lines} 行"
    echo "  削除された行数: ${removed_lines} 行 ($(( removed_lines * 100 / original_lines ))%)"
else
    echo "✗ エラー: Word文書の作成に失敗しました"
    exit 1
fi

# 一時ファイルを削除
rm -f "$TEMP_CLEAN"

echo "================================================"
echo "学習に必要な以下の内容のみを含みます:"
echo "  ✓ 各章の概要と詳細"
echo "  ✓ 学習目標"
echo "  ✓ 対応C規格"
echo "  ✓ 理論的な説明"
echo ""
echo "以下の内容は除外されました:"
echo "  ✗ サンプルコード"
echo "  ✗ 演習問題"
echo "  ✗ 参考資料"
echo "  ✗ 次の章へのリンク"
echo "================================================"
echo "完了しました。"