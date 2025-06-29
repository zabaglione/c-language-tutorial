#!/bin/bash

# 演習課題用のMarkdownファイルを作成
OUTPUT="exercises_workbook.md"

# ヘッダーを作成
cat > "$OUTPUT" << 'EOF'
---
title: "C言語プログラミング演習課題集"
author: "プログラミング学習教材"
date: "2024年"
---

# C言語プログラミング演習課題集

## 目次

1. [第1章: C言語入門 - 演習課題](#第1章-c言語入門---演習課題)
2. [第2章: 基本構文 - 演習課題](#第2章-基本構文---演習課題)
3. [第3章: データ型と変数 - 演習課題](#第3章-データ型と変数---演習課題)
4. [第4章: 演算子 - 演習課題](#第4章-演算子---演習課題)
5. [第5章: 条件分岐 - 演習課題](#第5章-条件分岐---演習課題)
6. [第6章: 繰り返し処理 - 演習課題](#第6章-繰り返し処理---演習課題)
7. [第7章: 配列 - 演習課題](#第7章-配列---演習課題)
8. [第8章: 文字列処理 - 演習課題](#第8章-文字列処理---演習課題)
9. [第9章: 関数 - 演習課題](#第9章-関数---演習課題)
10. [第10章: ポインタ - 演習課題](#第10章-ポインタ---演習課題)
11. [第11章: 構造体 - 演習課題](#第11章-構造体---演習課題)
12. [第12章: 関数ポインタ - 演習課題](#第12章-関数ポインタ---演習課題)
13. [第13章: 高度なトピック - 演習課題](#第13章-高度なトピック---演習課題)

---

EOF

# 各章の演習課題を追加する関数
add_exercises() {
    local chapter_num=$1
    local chapter_dir=$2
    local chapter_title=$3
    
    echo "" >> "$OUTPUT"
    echo "# 第${chapter_num}章: ${chapter_title} - 演習課題" >> "$OUTPUT"
    echo "" >> "$OUTPUT"
    
    # exercises/README.mdの内容を追加
    if [ -f "${chapter_dir}/exercises/README.md" ]; then
        # タイトル行をスキップして内容を追加
        tail -n +2 "${chapter_dir}/exercises/README.md" >> "$OUTPUT"
    else
        echo "この章の演習課題は準備中です。" >> "$OUTPUT"
    fi
    
    echo "" >> "$OUTPUT"
    echo "---" >> "$OUTPUT"
}

# 各章の演習課題を追加
add_exercises 1 "introduction" "C言語入門"
add_exercises 2 "basics-syntax" "基本構文"
add_exercises 3 "data-types" "データ型と変数"
add_exercises 4 "operators" "演算子"
add_exercises 5 "control-if" "条件分岐"
add_exercises 6 "control-loop" "繰り返し処理"
add_exercises 7 "arrays" "配列"
add_exercises 8 "strings" "文字列処理"
add_exercises 9 "functions" "関数"
add_exercises 10 "pointers" "ポインタ"
add_exercises 11 "structures" "構造体"
add_exercises 12 "function-pointers" "関数ポインタ"
add_exercises 13 "advanced" "高度なトピック"

echo "演習課題集の作成が完了しました: $OUTPUT"