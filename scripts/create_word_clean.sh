#!/bin/bash
# docs/main_textbook.mdから特定セクションを完全に除外してWord文書を生成するスクリプト

# 基本ディレクトリ
BASE_DIR=$(pwd)
DOCS_DIR="../docs"
OUTPUT_DIR="../output/word"
TEMPLATE="../custom-reference-1.docx"

# 一時ファイル
TEMP_FILTERED="/tmp/clean_textbook.md"

# 出力ファイル名
OUTPUT_FILE="${OUTPUT_DIR}/C言語プログラミング教材_メインテキスト_クリーン版.docx"

echo "docs/main_textbook.mdから特定セクションを除外してWord文書を生成します"
echo "================================================"

# docsディレクトリの存在確認
if [ ! -f "${DOCS_DIR}/main_textbook.md" ]; then
    echo "エラー: ${DOCS_DIR}/main_textbook.md が見つかりません"
    exit 1
fi

# outputディレクトリの作成
mkdir -p "$OUTPUT_DIR"

echo "フィルタリング処理を実行中..."

# Pythonスクリプトでより正確なフィルタリングを実行
python3 << 'EOF' > "$TEMP_FILTERED"
import re
import sys

with open("../docs/main_textbook.md", "r", encoding="utf-8") as f:
    content = f.read()

# 各章を個別に処理
chapters = content.split('\n# 第')
result = [chapters[0]]  # ヘッダー部分を保持

for i, chapter in enumerate(chapters[1:], 1):
    chapter = '# 第' + chapter
    
    # 除外するセクションのパターン
    exclude_patterns = [
        r'\n##\s*次の章へ.*?(?=\n#|\Z)',
        r'\n##\s*参考資料.*?(?=\n#|\Z)',
        r'\n##\s*サンプルコード.*?(?=\n#|\Z)',
        r'\n##\s*演習課題.*?(?=\n#|\Z)',
        r'\n##\s*演習問題.*?(?=\n#|\Z)',
        r'\n##\s*コンパイル方法.*?(?=\n#|\Z)',
        r'\n##\s*規格による違い.*?(?=\n#|\Z)',
        r'\n##\s*よくある間違い.*?(?=\n#|\Z)',
        r'\n##\s*おめでとうございます.*?(?=\n#|\Z)',
        r'\n##\s*🔄.*?(?=\n#|\Z)',  # 絵文字付きセクション
        r'\n##\s*💻.*?(?=\n#|\Z)',
        r'\n##\s*🔍.*?(?=\n#|\Z)',
    ]
    
    # 各パターンを適用
    for pattern in exclude_patterns:
        chapter = re.sub(pattern, '', chapter, flags=re.DOTALL)
    
    # 章の最後の余分な改行と区切り線を削除
    chapter = re.sub(r'\n\n+---\s*$', '\n\n---', chapter)
    chapter = re.sub(r'\n\n\n+', '\n\n', chapter)
    
    result.append(chapter)

# 結果を結合
output = '\n'.join(result)

# コードブロック内の---が正しく処理されているか確認
# YAMLヘッダーの後の最初の---以外で、コードブロック外の単独の---を削除
lines = output.split('\n')
in_code = False
yaml_end = False
cleaned_lines = []

for i, line in enumerate(lines):
    if i < 5 and line == '---':
        yaml_end = True
        cleaned_lines.append(line)
    elif line.startswith('```'):
        in_code = not in_code
        cleaned_lines.append(line)
    elif line == '---' and not in_code and yaml_end:
        # 章の区切りとして必要な---は保持
        if i + 1 < len(lines) and lines[i + 1].startswith('# 第'):
            cleaned_lines.append(line)
        elif i > 0 and lines[i - 1] == '':
            cleaned_lines.append(line)
    else:
        cleaned_lines.append(line)

print('\n'.join(cleaned_lines))
EOF

echo "pandocで変換中..."

# pandocで変換
pandoc "$TEMP_FILTERED" \
    --reference-doc="$TEMPLATE" \
    -o "$OUTPUT_FILE" \
    --from markdown+raw_attribute+pipe_tables+tex_math_dollars \
    --to docx \
    --toc \
    --toc-depth=2 \
    --standalone \
    --highlight-style=tango

if [ $? -eq 0 ]; then
    echo "✓ 作成完了: $(basename "$OUTPUT_FILE")"
    echo "  ファイルサイズ: $(ls -lh "$OUTPUT_FILE" | awk '{print $5}')"
    echo "  保存場所: $OUTPUT_FILE"
    
    # フィルタリング結果の統計を表示
    original_lines=$(wc -l < "${DOCS_DIR}/main_textbook.md")
    filtered_lines=$(wc -l < "$TEMP_FILTERED")
    removed_lines=$((original_lines - filtered_lines))
    
    echo ""
    echo "フィルタリング統計:"
    echo "  元のファイル: ${original_lines} 行"
    echo "  フィルタ後: ${filtered_lines} 行"
    echo "  削除された行数: ${removed_lines} 行"
else
    echo "✗ エラー: Word文書の作成に失敗しました"
    exit 1
fi

# 一時ファイルを削除
rm -f "$TEMP_FILTERED"

echo "================================================"
echo "除外されたセクション:"
echo "  - 次の章へ"
echo "  - 参考資料"
echo "  - サンプルコード"
echo "  - 演習課題/演習問題"
echo "  - コンパイル方法"
echo "  - 規格による違い"
echo "  - よくある間違い"
echo "  - おめでとうございます"
echo "================================================"
echo "完了しました。"