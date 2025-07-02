#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 出力ディレクトリを作成
OUTPUT_DIR="$PROJECT_ROOT/output/word"
mkdir -p "$OUTPUT_DIR"

# 演習問題集を生成
echo "演習問題集のWord文書を生成中..."

# 一時ファイルのパス
TEMP_MD="$PROJECT_ROOT/temp_exercises.md"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_演習問題集.docx"

# ヘッダーを作成
cat > "$TEMP_MD" << 'EOF'
---
title: "C言語プログラミング教材 - 演習問題集"
subtitle: "基礎から応用まで段階的に学習"
author: "C言語学習教材プロジェクト"
date: "2024年"
documentclass: report
lang: ja
fontsize: 12pt
geometry: margin=1in
toc: true
toc-depth: 3
numbersections: true
---

# はじめに

本書は、C言語プログラミング教材の演習問題集です。各章の内容を理解し、実践的なプログラミング能力を身につけるための問題を収録しています。

## 問題の構成

各章の演習問題は以下の3つのレベルに分かれています：

- **基礎問題**: 基本的な文法や概念を確認する問題
- **応用問題**: 学習した内容を組み合わせて解く問題
- **チャレンジ問題**: より高度な理解と実装力が必要な問題

## 学習の進め方

1. まず教材本文で各章の内容を学習してください
2. 基礎問題から順番に取り組みましょう
3. 分からない問題があれば、教材本文に戻って復習しましょう
4. すべての問題を解き終えたら、次の章に進みましょう

---

EOF

# 章の情報
chapters=(
    "introduction:第1章 導入・環境構築"
    "basics-syntax:第2章 基本文法・Hello World"
    "data-types:第3章 データ型と変数"
    "operators:第4章 演算子"
    "control-if:第5章 制御構造（条件分岐）"
    "control-loop:第6章 制御構造（ループ）"
    "arrays-basics:第7章 配列（基本編）"
    "pointers:第8章 ポインタ基礎"
    "arrays-pointers:第9章 配列とポインタ"
    "strings:第10章 文字列処理"
    "functions:第11章 関数"
    "bit-operations:第12章 ビット操作とビットフィールド"
    "structures:第13章 構造体とポインタ"
    "function-pointers:第14章 関数ポインタ"
    "advanced:第15章 複数ファイル・発展技術"
    "c23-features:第16章 C23の新機能"
)

# 各章の演習問題を結合
for chapter_info in "${chapters[@]}"; do
    IFS=':' read -r dir_name chapter_title <<< "$chapter_info"
    
    if [ -f "$PROJECT_ROOT/src/$dir_name/exercises/README.md" ]; then
        # 章タイトルの追加（改ページ付き）
        echo "" >> "$TEMP_MD"
        echo "" >> "$TEMP_MD"
        
        # 演習問題の内容を追加
        cat "$PROJECT_ROOT/src/$dir_name/exercises/README.md" >> "$TEMP_MD"
        echo "" >> "$TEMP_MD"
    fi
done

# 終わりに
cat >> "$TEMP_MD" << 'EOF'

# 終わりに

すべての演習問題お疲れさまでした。これらの問題を通じて、C言語の基礎から応用まで幅広い知識と実践的なプログラミング能力を身につけることができたはずです。

## 今後の学習

C言語の学習を続けるために、以下のような取り組みをお勧めします：

1. **実際のプロジェクトに挑戦する**
   - 小さなツールやゲームを作ってみましょう
   - オープンソースプロジェクトに参加してみましょう

2. **より高度な内容を学習する**
   - データ構造とアルゴリズム
   - システムプログラミング
   - 組み込みプログラミング

3. **他の言語も学習する**
   - C++でオブジェクト指向を学ぶ
   - Pythonで高レベルプログラミングを学ぶ
   - Rustで安全なシステムプログラミングを学ぶ

プログラミングの学習に終わりはありません。継続的に学び、実践することで、より優れたプログラマーになることができます。

頑張ってください！
EOF

# Pandocでdocxファイルを生成
if command -v pandoc &> /dev/null; then
    echo "Pandocでdocxファイルを生成中..."
    pandoc "$TEMP_MD" \
        -o "$OUTPUT_DOCX" \
        --from markdown \
        --to docx \
        --standalone \
        --toc \
        --toc-depth=3 \
        --highlight-style=tango
    
    if [ $? -eq 0 ]; then
        echo "✅ 演習問題集が生成されました: $OUTPUT_DOCX"
        # 一時ファイルを削除
        rm -f "$TEMP_MD"
    else
        echo "❌ エラー: docxファイルの生成に失敗しました"
        rm -f "$TEMP_MD"
        exit 1
    fi
else
    echo "❌ エラー: Pandocがインストールされていません"
    echo "以下のコマンドでインストールしてください:"
    echo "  brew install pandoc  # macOS"
    echo "  sudo apt-get install pandoc  # Ubuntu/Debian"
    rm -f "$TEMP_MD"
    exit 1
fi

echo "✅ 処理が完了しました"