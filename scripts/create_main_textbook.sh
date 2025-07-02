#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 出力ディレクトリを作成
OUTPUT_DIR="$PROJECT_ROOT/output/word"
mkdir -p "$OUTPUT_DIR"

# メインテキストbook文書を生成
echo "メインテキストのWord文書を生成中..."

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/main_textbook.md"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_メインテキスト.docx"

# Pandocでdocxファイルを生成
if command -v pandoc &> /dev/null; then
    echo "Pandocでdocxファイルを生成中..."
    pandoc "$INPUT_MD" \
        -o "$OUTPUT_DOCX" \
        --from markdown \
        --to docx \
        --standalone \
        --toc \
        --toc-depth=3 \
        --highlight-style=tango
    
    if [ $? -eq 0 ]; then
        echo "✅ メインテキストが生成されました: $OUTPUT_DOCX"
    else
        echo "❌ エラー: docxファイルの生成に失敗しました"
        exit 1
    fi
else
    echo "❌ エラー: Pandocがインストールされていません"
    echo "以下のコマンドでインストールしてください:"
    echo "  brew install pandoc  # macOS"
    echo "  sudo apt-get install pandoc  # Ubuntu/Debian"
    exit 1
fi

echo "✅ 処理が完了しました"