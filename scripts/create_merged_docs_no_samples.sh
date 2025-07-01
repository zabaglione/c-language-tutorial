#!/bin/bash
# pandocを使用して全章を統合したメインテキストと演習問題集を作成（サンプルコード・演習課題除外版）

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

echo "pandocによる統合ファイル作成（サンプルコード・演習課題除外版）"
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
    
    # README.mdの内容を追加（タイトル行と除外セクション以降を除く）
    CHAPTER_DIR="${SRC_DIR}/${dir}"
    if [ -f "${CHAPTER_DIR}/README.md" ]; then
        # 除外するセクションの行番号を取得（最も早く現れるもの）
        sample_line=$(grep -En "^##[ 🔍]*サンプルコード" "${CHAPTER_DIR}/README.md" | head -1 | cut -d: -f1)
        exercise_line=$(grep -En "^##[ 💻]*演習" "${CHAPTER_DIR}/README.md" | head -1 | cut -d: -f1)
        answer_line=$(grep -n "^## *解答例" "${CHAPTER_DIR}/README.md" | head -1 | cut -d: -f1)
        
        # 最小の行番号を見つける（存在するものの中で）
        cutoff_line=""
        for line in $sample_line $exercise_line $answer_line; do
            if [ -n "$line" ]; then
                if [ -z "$cutoff_line" ] || [ "$line" -lt "$cutoff_line" ]; then
                    cutoff_line=$line
                fi
            fi
        done
        
        if [ -n "$cutoff_line" ]; then
            # 除外セクションの前までを抽出
            head -n $((cutoff_line - 1)) "${CHAPTER_DIR}/README.md" | tail -n +2 > /tmp/readme_content.md
        else
            # 除外セクションがない場合は全体を使用
            tail -n +2 "${CHAPTER_DIR}/README.md" > /tmp/readme_content.md
        fi
        
        # コードブロックが閉じられているか確認
        open_count=$(grep -c '^```' /tmp/readme_content.md || echo 0)
        if [ $((open_count % 2)) -eq 1 ]; then
            echo '```' >> /tmp/readme_content.md
        fi
        
        cat /tmp/readme_content.md >> "$TEMP_TEXTBOOK"
        echo "" >> "$TEMP_TEXTBOOK"
        rm -f /tmp/readme_content.md
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
        # タイトル行を除く
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
        
        # 解答コードを追加（ソート済み、C99版を除く）
        for c_file in $(ls "${CHAPTER_DIR}/solutions"/*.c 2>/dev/null | grep -v "_c99.c" | sort); do
            if [ -f "$c_file" ]; then
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
    --from markdown+raw_attribute+pipe_tables \
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
    --from markdown+raw_attribute+pipe_tables \
    --to docx \
    --toc \
    --toc-depth=2 \
    --standalone

if [ $? -eq 0 ]; then
    echo "✓ 作成完了: C言語プログラミング教材_演習問題集.docx"
else
    echo "✗ エラー: 演習問題集の作成に失敗"
fi

# 一時ファイルを削除
rm -f "$TEMP_TEXTBOOK" "$TEMP_EXERCISES"

echo "================================================"
echo "完了しました。"