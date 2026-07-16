#!/bin/bash

# 補章のWord文書を生成するスクリプト

# 色付き出力用のカラーコード
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# ベースディレクトリ
BASE_DIR=$(cd "$(dirname "$0")/.." && pwd)
OUTPUT_DIR="$BASE_DIR/output/word"
TEMPLATE_DIR="$BASE_DIR/templates"
DOCS_DIR="$BASE_DIR/docs"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

echo -e "${YELLOW}補章のWord文書を生成中...${NC}"

# 一時ファイルを作成
TMP_FILE="$DOCS_DIR/supplementary_chapters.md"

# ヘッダーを追加
cat > "$TMP_FILE" << 'EOF'
---
title: "C言語プログラミング教材 - 補章"
subtitle: "C言語の規格と歴史・開発環境の詳細設定"
author: "プログラミング学習教材"
date: "2024年"
---

# 補章について

本書は、C言語プログラミング教材の補章として、以下の内容を扱います：

- **補章1**: C言語の規格と歴史
- **補章2**: 開発環境の詳細設定

これらの内容は、メインの学習には必須ではありませんが、より深い理解を求める方や、特定の問題に直面した際の参考資料として活用できます。

---

EOF

# 補章1の内容を追加
echo -e "\n# 補章1: C言語の規格と歴史\n" >> "$TMP_FILE"
cat "$BASE_DIR/src/c-standards/README.md" >> "$TMP_FILE"

# 区切り線を追加
echo -e "\n---\n" >> "$TMP_FILE"

# 補章2の内容を追加
echo -e "\n# 補章2: 開発環境の詳細設定\n" >> "$TMP_FILE"
cat "$BASE_DIR/src/development-environment/README.md" >> "$TMP_FILE"

# pandocでWord文書を生成
echo "Pandocでdocxファイルを生成中..."

if [ -f "$BASE_DIR/templates/custom-reference.docx" ]; then
    pandoc "$TMP_FILE" \
        -f markdown \
        -t docx \
        --filter mermaid-filter \
        --reference-doc="$BASE_DIR/templates/custom-reference.docx" \
        --dpi=300 \
        -o "$OUTPUT_DIR/C言語プログラミング教材_補章.docx"
else
    pandoc "$TMP_FILE" \
        -f markdown \
        -t docx \
        --filter mermaid-filter \
        --reference-doc="$BASE_DIR/templates/custom-reference.docx" \
        --dpi=300 \
        -o "$OUTPUT_DIR/C言語プログラミング教材_補章.docx"
fi

# 一時ファイルを削除
rm -f "$TMP_FILE"

echo -e "${GREEN}✅ 補章のWord文書が生成されました: $OUTPUT_DIR/C言語プログラミング教材_補章.docx${NC}"
echo -e "${GREEN}✅ 処理が完了しました${NC}"