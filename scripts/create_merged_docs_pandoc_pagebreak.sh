#!/bin/bash
# pandocを使用して全章を統合したメインテキストと演習問題集を作成（改ページ対応版）

# 基本ディレクトリ
BASE_DIR=$(pwd)
SRC_DIR="../src"
OUTPUT_DIR="../output/word"
TEMPLATE="../custom-reference-1.docx"

# 一時ファイル
TEMP_TEXTBOOK="/tmp/merged_textbook.md"
TEMP_EXERCISES="/tmp/merged_exercises.md"

# 改ページ用のOpenXMLコード
PAGEBREAK='```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```'

# 章情報
declare -a CHAPTERS=(
    "1:introduction:導入・環境構築"
    "2:basics-syntax:基本文法・Hello World"
    "3:data-types:データ型と変数"
    "4:operators:演算子"
    "5:control-if:制御構造（条件分岐）"
    "6:control-loop:制御構造（ループ）"
    "7:arrays:配列"
    "8:strings:文字列処理"
    "9:functions:関数"
    "10:pointers:ポインタ基礎"
    "11:structures:構造体とポインタ"
    "12:function-pointers:関数ポインタ"
    "13:advanced:複数ファイル・発展技術"
    "14:c23-features:C23の新機能（オプション）"
)

echo "pandocによる統合ファイル作成（改ページ対応版）"
echo "テンプレート: custom-reference-1.docx"
echo "================================================"

# メインテキスト用の統合Markdownファイルを作成
echo "メインテキストの統合ファイルを作成中..."

# タイトルページ
cat > "$TEMP_TEXTBOOK" << EOF
---
title: "C言語プログラミング教材"
subtitle: "メインテキスト"
author: "C言語学習教材プロジェクト"
date: "$(date '+%Y年%m月%d日')"
---

$PAGEBREAK

# 目次

EOF

# 目次を追加
for chapter_info in "${CHAPTERS[@]}"; do
    IFS=':' read -r num dir title <<< "$chapter_info"
    echo "- 第${num}章 ${title}" >> "$TEMP_TEXTBOOK"
done

# 改ページを追加
echo "" >> "$TEMP_TEXTBOOK"
echo "$PAGEBREAK" >> "$TEMP_TEXTBOOK"
echo "" >> "$TEMP_TEXTBOOK"

# 各章の内容を追加
for chapter_info in "${CHAPTERS[@]}"; do
    IFS=':' read -r num dir title <<< "$chapter_info"
    
    echo "  第${num}章を追加中..."
    
    # 章タイトル
    echo "# 第${num}章 ${title}" >> "$TEMP_TEXTBOOK"
    echo "" >> "$TEMP_TEXTBOOK"
    
    # README.mdの内容を追加（タイトル行を除く）
    CHAPTER_DIR="${SRC_DIR}/${dir}"
    if [ -f "${CHAPTER_DIR}/README.md" ]; then
        tail -n +2 "${CHAPTER_DIR}/README.md" >> "$TEMP_TEXTBOOK"
        echo "" >> "$TEMP_TEXTBOOK"
    fi
    
    # サンプルコードを追加
    if [ -d "${CHAPTER_DIR}/examples" ]; then
        echo "" >> "$TEMP_TEXTBOOK"
        echo "## サンプルコード" >> "$TEMP_TEXTBOOK"
        echo "" >> "$TEMP_TEXTBOOK"
        
        for c_file in "${CHAPTER_DIR}/examples"/*.c; do
            if [ -f "$c_file" ] && [[ ! "$c_file" =~ _c99\.c$ ]]; then
                filename=$(basename "$c_file")
                echo "### $filename" >> "$TEMP_TEXTBOOK"
                echo "" >> "$TEMP_TEXTBOOK"
                echo '```c' >> "$TEMP_TEXTBOOK"
                cat "$c_file" >> "$TEMP_TEXTBOOK"
                echo '```' >> "$TEMP_TEXTBOOK"
                echo "" >> "$TEMP_TEXTBOOK"
            fi
        done
    fi
    
    # 章の最後に改ページ（最後の章以外）
    if [ "$num" -lt 14 ]; then
        echo "" >> "$TEMP_TEXTBOOK"
        echo "$PAGEBREAK" >> "$TEMP_TEXTBOOK"
        echo "" >> "$TEMP_TEXTBOOK"
    fi
done

# 演習問題集用の統合Markdownファイルを作成
echo "演習問題集の統合ファイルを作成中..."

# タイトルページ
cat > "$TEMP_EXERCISES" << EOF
---
title: "C言語プログラミング教材"
subtitle: "演習問題集"
author: "C言語学習教材プロジェクト"
date: "$(date '+%Y年%m月%d日')"
---

$PAGEBREAK

# 目次

EOF

# 目次を追加
for chapter_info in "${CHAPTERS[@]}"; do
    IFS=':' read -r num dir title <<< "$chapter_info"
    echo "- 第${num}章 ${title}" >> "$TEMP_EXERCISES"
done

# 改ページを追加
echo "" >> "$TEMP_EXERCISES"
echo "$PAGEBREAK" >> "$TEMP_EXERCISES"
echo "" >> "$TEMP_EXERCISES"

# 各章の演習問題を追加
for chapter_info in "${CHAPTERS[@]}"; do
    IFS=':' read -r num dir title <<< "$chapter_info"
    
    echo "  第${num}章の演習問題を追加中..."
    
    # 章タイトル
    echo "# 第${num}章 ${title}" >> "$TEMP_EXERCISES"
    echo "" >> "$TEMP_EXERCISES"
    
    CHAPTER_DIR="${SRC_DIR}/${dir}"
    
    # 演習問題を追加
    if [ -f "${CHAPTER_DIR}/exercises/README.md" ]; then
        echo "## 演習問題" >> "$TEMP_EXERCISES"
        echo "" >> "$TEMP_EXERCISES"
        tail -n +2 "${CHAPTER_DIR}/exercises/README.md" >> "$TEMP_EXERCISES"
        echo "" >> "$TEMP_EXERCISES"
    fi
    
    # 解答例を追加
    if [ -d "${CHAPTER_DIR}/solutions" ]; then
        echo "" >> "$TEMP_EXERCISES"
        echo "## 解答例" >> "$TEMP_EXERCISES"
        echo "" >> "$TEMP_EXERCISES"
        
        # 解答のREADMEがあれば追加
        if [ -f "${CHAPTER_DIR}/solutions/README.md" ]; then
            tail -n +2 "${CHAPTER_DIR}/solutions/README.md" >> "$TEMP_EXERCISES"
            echo "" >> "$TEMP_EXERCISES"
        fi
        
        # 解答コードを追加
        for c_file in "${CHAPTER_DIR}/solutions"/*.c; do
            if [ -f "$c_file" ] && [[ ! "$c_file" =~ _c99\.c$ ]]; then
                filename=$(basename "$c_file")
                echo "### $filename" >> "$TEMP_EXERCISES"
                echo "" >> "$TEMP_EXERCISES"
                echo '```c' >> "$TEMP_EXERCISES"
                cat "$c_file" >> "$TEMP_EXERCISES"
                echo '```' >> "$TEMP_EXERCISES"
                echo "" >> "$TEMP_EXERCISES"
            fi
        done
    fi
    
    # 章の最後に改ページ（最後の章以外）
    if [ "$num" -lt 14 ]; then
        echo "" >> "$TEMP_EXERCISES"
        echo "$PAGEBREAK" >> "$TEMP_EXERCISES"
        echo "" >> "$TEMP_EXERCISES"
    fi
done

# pandocで変換（raw_attributeを有効化）
echo "pandocで変換中..."

# メインテキストを作成
OUTPUT_TEXTBOOK="${OUTPUT_DIR}/C言語プログラミング教材_メインテキスト.docx"
pandoc "$TEMP_TEXTBOOK" \
    --reference-doc="$TEMPLATE" \
    -o "$OUTPUT_TEXTBOOK" \
    --from markdown+raw_attribute \
    --to docx \
    --toc \
    --toc-depth=2 \
    --standalone

if [ $? -eq 0 ]; then
    echo "✓ 作成完了: C言語プログラミング教材_メインテキスト.docx"
else
    echo "✗ エラー: メインテキストの作成に失敗"
fi

# 演習問題集を作成
OUTPUT_EXERCISES="${OUTPUT_DIR}/C言語プログラミング教材_演習問題集.docx"
pandoc "$TEMP_EXERCISES" \
    --reference-doc="$TEMPLATE" \
    -o "$OUTPUT_EXERCISES" \
    --from markdown+raw_attribute \
    --to docx \
    --toc \
    --toc-depth=2 \
    --standalone

if [ $? -eq 0 ]; then
    echo "✓ 作成完了: C言語プログラミング教材_演習問題集.docx"
else
    echo "✗ エラー: 演習問題集の作成に失敗"
fi

# 一時ファイルを削除（デバッグのため一時的にコメントアウト）
# rm -f "$TEMP_TEXTBOOK" "$TEMP_EXERCISES"
echo "デバッグ用: 一時ファイルを保持しています"
echo "  メインテキスト: $TEMP_TEXTBOOK"
echo "  演習問題集: $TEMP_EXERCISES"

echo "================================================"
echo "完了しました。"