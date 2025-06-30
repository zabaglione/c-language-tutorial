#!/bin/bash
# pandocを使用してcustom-reference-1.docxをテンプレートとして章別Wordファイルを作成

# 基本ディレクトリ
BASE_DIR=$(pwd)
SRC_DIR="../src"
OUTPUT_DIR="../output/docs"
TEMPLATE="../custom-reference-1.docx"

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

echo "pandocによる章別Wordファイル生成"
echo "テンプレート: custom-reference-1.docx"
echo "出力先: $OUTPUT_DIR"
echo "================================================"

# 出力ディレクトリの確認
mkdir -p "$OUTPUT_DIR"

# 各章を処理
for chapter_info in "${CHAPTERS[@]}"; do
    IFS=':' read -r num dir title <<< "$chapter_info"
    
    echo -e "\n第${num}章: ${title}"
    
    # 章のディレクトリ
    CHAPTER_DIR="${SRC_DIR}/${dir}"
    
    # 教科書用ファイルの作成
    echo "  教科書用ファイルを作成中..."
    
    # 一時ファイルを作成（教科書用）
    TEMP_TEXTBOOK="/tmp/chapter_${num}_textbook.md"
    
    # タイトルを追加
    echo "# 第${num}章 ${title}" > "$TEMP_TEXTBOOK"
    echo "" >> "$TEMP_TEXTBOOK"
    
    # README.mdの内容を追加（タイトル行を除く）
    if [ -f "${CHAPTER_DIR}/README.md" ]; then
        tail -n +2 "${CHAPTER_DIR}/README.md" >> "$TEMP_TEXTBOOK"
        echo "" >> "$TEMP_TEXTBOOK"
    fi
    
    # サンプルコードを追加
    if [ -d "${CHAPTER_DIR}/examples" ]; then
        echo -e "\n# サンプルコード\n" >> "$TEMP_TEXTBOOK"
        
        for c_file in "${CHAPTER_DIR}/examples"/*.c; do
            if [ -f "$c_file" ] && [[ ! "$c_file" =~ _c99\.c$ ]]; then
                filename=$(basename "$c_file")
                echo "## $filename" >> "$TEMP_TEXTBOOK"
                echo "" >> "$TEMP_TEXTBOOK"
                echo '```c' >> "$TEMP_TEXTBOOK"
                cat "$c_file" >> "$TEMP_TEXTBOOK"
                echo '```' >> "$TEMP_TEXTBOOK"
                echo "" >> "$TEMP_TEXTBOOK"
            fi
        done
    fi
    
    # pandocで変換（教科書）
    OUTPUT_TEXTBOOK="${OUTPUT_DIR}/chapter_$(printf "%02d" $num)_textbook.docx"
    pandoc "$TEMP_TEXTBOOK" \
        --reference-doc="$TEMPLATE" \
        -o "$OUTPUT_TEXTBOOK" \
        --from markdown \
        --to docx \
        --standalone
    
    if [ $? -eq 0 ]; then
        echo "  ✓ 作成: $(basename "$OUTPUT_TEXTBOOK")"
    else
        echo "  ✗ エラー: 教科書ファイルの作成に失敗"
    fi
    
    # 演習問題用ファイルの作成
    echo "  演習問題用ファイルを作成中..."
    
    # 一時ファイルを作成（演習問題用）
    TEMP_EXERCISES="/tmp/chapter_${num}_exercises.md"
    
    # タイトルを追加
    echo "# 第${num}章 ${title} - 演習問題" > "$TEMP_EXERCISES"
    echo "" >> "$TEMP_EXERCISES"
    
    # 演習問題を追加
    if [ -f "${CHAPTER_DIR}/exercises/README.md" ]; then
        echo "# 演習問題" >> "$TEMP_EXERCISES"
        echo "" >> "$TEMP_EXERCISES"
        tail -n +2 "${CHAPTER_DIR}/exercises/README.md" >> "$TEMP_EXERCISES"
        echo "" >> "$TEMP_EXERCISES"
    fi
    
    # 解答例を追加
    if [ -d "${CHAPTER_DIR}/solutions" ]; then
        echo -e "\n# 解答例\n" >> "$TEMP_EXERCISES"
        
        # 解答のREADMEがあれば追加
        if [ -f "${CHAPTER_DIR}/solutions/README.md" ]; then
            tail -n +2 "${CHAPTER_DIR}/solutions/README.md" >> "$TEMP_EXERCISES"
            echo "" >> "$TEMP_EXERCISES"
        fi
        
        # 解答コードを追加
        for c_file in "${CHAPTER_DIR}/solutions"/*.c; do
            if [ -f "$c_file" ] && [[ ! "$c_file" =~ _c99\.c$ ]]; then
                filename=$(basename "$c_file")
                echo "## $filename" >> "$TEMP_EXERCISES"
                echo "" >> "$TEMP_EXERCISES"
                echo '```c' >> "$TEMP_EXERCISES"
                cat "$c_file" >> "$TEMP_EXERCISES"
                echo '```' >> "$TEMP_EXERCISES"
                echo "" >> "$TEMP_EXERCISES"
            fi
        done
    fi
    
    # pandocで変換（演習問題）
    OUTPUT_EXERCISES="${OUTPUT_DIR}/chapter_$(printf "%02d" $num)_exercises.docx"
    pandoc "$TEMP_EXERCISES" \
        --reference-doc="$TEMPLATE" \
        -o "$OUTPUT_EXERCISES" \
        --from markdown \
        --to docx \
        --standalone
    
    if [ $? -eq 0 ]; then
        echo "  ✓ 作成: $(basename "$OUTPUT_EXERCISES")"
    else
        echo "  ✗ エラー: 演習問題ファイルの作成に失敗"
    fi
    
    # 一時ファイルを削除
    rm -f "$TEMP_TEXTBOOK" "$TEMP_EXERCISES"
done

echo -e "\n================================================"
echo "完了しました。"
echo "作成されたファイルは ${OUTPUT_DIR} にあります。"