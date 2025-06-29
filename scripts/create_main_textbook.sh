#!/bin/bash

# メインテキスト用のMarkdownファイルを作成
OUTPUT="main_textbook.md"

# ヘッダーを作成
cat > "$OUTPUT" << 'EOF'
---
title: "C言語プログラミング教材"
author: "プログラミング学習教材"
date: "2024年"
---

# C言語プログラミング教材

## 目次

1. [第1章: C言語入門](#第1章-c言語入門)
2. [第2章: 基本構文](#第2章-基本構文)
3. [第3章: データ型と変数](#第3章-データ型と変数)
4. [第4章: 演算子](#第4章-演算子)
5. [第5章: 条件分岐](#第5章-条件分岐)
6. [第6章: 繰り返し処理](#第6章-繰り返し処理)
7. [第7章: 配列](#第7章-配列)
8. [第8章: 文字列処理](#第8章-文字列処理)
9. [第9章: 関数](#第9章-関数)
10. [第10章: ポインタ](#第10章-ポインタ)
11. [第11章: 構造体](#第11章-構造体)
12. [第12章: 関数ポインタ](#第12章-関数ポインタ)
13. [第13章: 高度なトピック](#第13章-高度なトピック)

---

EOF

# 各章を追加する関数
add_chapter() {
    local chapter_num=$1
    local chapter_dir=$2
    local chapter_title=$3
    
    echo "" >> "$OUTPUT"
    echo "# 第${chapter_num}章: ${chapter_title}" >> "$OUTPUT"
    echo "" >> "$OUTPUT"
    
    # READMEの内容を追加（タイトル行をスキップ）
    if [ -f "${chapter_dir}/README.md" ]; then
        tail -n +2 "${chapter_dir}/README.md" >> "$OUTPUT"
    fi
    
    # examplesディレクトリのC90版ソースコードを追加
    if [ -d "${chapter_dir}/examples" ]; then
        echo "" >> "$OUTPUT"
        echo "## サンプルコード" >> "$OUTPUT"
        echo "" >> "$OUTPUT"
        
        for c_file in ${chapter_dir}/examples/*.c; do
            if [ -f "$c_file" ]; then
                # C99版はスキップ
                if [[ ! "$c_file" =~ _c99\.c$ ]]; then
                    filename=$(basename "$c_file")
                    echo "### ${filename}" >> "$OUTPUT"
                    echo "" >> "$OUTPUT"
                    echo '```c' >> "$OUTPUT"
                    cat "$c_file" >> "$OUTPUT"
                    echo '```' >> "$OUTPUT"
                    echo "" >> "$OUTPUT"
                    
                    # C99版が存在する場合はリンクを追加
                    c99_file="${c_file%.c}_c99.c"
                    if [ -f "$c99_file" ]; then
                        echo "> C99版は[こちら]($(basename "$c99_file"))を参照してください。" >> "$OUTPUT"
                        echo "" >> "$OUTPUT"
                    fi
                fi
            fi
        done
    fi
    
    echo "---" >> "$OUTPUT"
}

# 各章を追加
add_chapter 1 "introduction" "C言語入門"
add_chapter 2 "basics-syntax" "基本構文"
add_chapter 3 "data-types" "データ型と変数"
add_chapter 4 "operators" "演算子"
add_chapter 5 "control-if" "条件分岐"
add_chapter 6 "control-loop" "繰り返し処理"
add_chapter 7 "arrays" "配列"
add_chapter 8 "strings" "文字列処理"
add_chapter 9 "functions" "関数"
add_chapter 10 "pointers" "ポインタ"
add_chapter 11 "structures" "構造体"
add_chapter 12 "function-pointers" "関数ポインタ"
add_chapter 13 "advanced" "高度なトピック"

echo "メインテキストの作成が完了しました: $OUTPUT"