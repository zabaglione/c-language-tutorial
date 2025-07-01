#!/bin/bash
# docs/main_textbook.mdからWord文書を生成するスクリプト

# 基本ディレクトリ
BASE_DIR=$(pwd)
DOCS_DIR="../docs"
OUTPUT_DIR="../output/word"
TEMPLATE="../custom-reference-1.docx"

# 出力ファイル名
OUTPUT_FILE="${OUTPUT_DIR}/C言語プログラミング教材_メインテキスト_最新版.docx"

echo "docs/main_textbook.mdからWord文書を生成します"
echo "================================================"

# docsディレクトリの存在確認
if [ ! -f "${DOCS_DIR}/main_textbook.md" ]; then
    echo "エラー: ${DOCS_DIR}/main_textbook.md が見つかりません"
    exit 1
fi

# outputディレクトリの作成
mkdir -p "$OUTPUT_DIR"

# pandocで変換
echo "pandocで変換中..."

pandoc "${DOCS_DIR}/main_textbook.md" \
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
else
    echo "✗ エラー: Word文書の作成に失敗しました"
    exit 1
fi

echo "================================================"
echo "完了しました。"