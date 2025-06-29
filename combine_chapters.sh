#!/bin/bash

# Combined markdown file creation script
OUTPUT_FILE="complete_tutorial.md"

# Start fresh
rm -f "$OUTPUT_FILE"

# Add YAML front matter
cat metadata.yaml > "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# Add introduction
cat >> "$OUTPUT_FILE" << 'EOF'
# はじめに

本書は、C言語の基礎から応用まで、体系的に学習できる教材です。マイコン開発を見据えたビット操作も含め、実践的なプログラミングスキルを身につけることができます。

## 対応C規格

本教材は以下のC言語規格に対応しています：

- **C90** (ANSI C): 基本的な文法とライブラリ
- **C99**: bool型、可変長配列、forループ内宣言など
- **C11**: 匿名構造体、_Generic選択、_Static_assertなど  
- **C17**: C11のマイナーアップデート版

## 学習目標

### 初心者レベル完了時
- C言語の基本文法を理解
- 簡単なプログラムを作成可能
- 配列と関数を使った処理が書ける

### 中級レベル完了時  
- ポインターを理解し活用可能
- 構造体を使ったデータ管理ができる
- ビット操作でハードウェア制御が理解できる

### 発展レベル完了時
- メモリ管理を理解
- 大規模なプログラム開発の基礎を習得
- C言語の高度な機能を活用可能

## 学習方法

1. **README.md** で理論を学習
2. **examples/** でサンプルコードを確認・実行
3. **exercises/** で演習課題に挑戦
4. **solutions/** で解答例を確認

\newpage

EOF

# Define chapters in order
chapters=(
    "introduction"
    "basics-syntax" 
    "data-types"
    "operators"
    "control-if"
    "control-loop"
    "arrays"
    "strings"
    "functions"
    "pointers"
    "structures"
    "function-pointers"
    "advanced"
)

chapter_numbers=(0 1 2 3 4 5 6 7 8 9 10 11 12)

# Process each chapter
for i in "${!chapters[@]}"; do
    chapter="${chapters[$i]}"
    number="${chapter_numbers[$i]}"
    
    if [ -f "${chapter}/README.md" ]; then
        echo "Processing Chapter ${number}: ${chapter}"
        
        # Process the chapter content - Remove "第X章:" prefix from titles
        sed -e "s/^# 第[0-9]*章: \(.*\)/# \1/" \
            -e "/次の章へ/,/参考資料/{ /\[第[0-9]*章:/d; }" \
            "${chapter}/README.md" >> "$OUTPUT_FILE"
        
        echo "" >> "$OUTPUT_FILE"
        echo "\\newpage" >> "$OUTPUT_FILE"
        echo "" >> "$OUTPUT_FILE"
    else
        echo "Warning: ${chapter}/README.md not found"
    fi
done

echo "Combined file created: $OUTPUT_FILE"