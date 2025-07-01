#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/main_textbook_basic.md"
OUTPUT_DIR="$PROJECT_ROOT/output/word"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_メインテキスト_基礎編.docx"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# 基礎編用のMarkdownファイルを生成
echo "基礎編のメインテキストを生成中..."

cat > "$INPUT_MD" << 'EOF'
---
title: "C言語プログラミング教材 - メインテキスト（基礎編）"
subtitle: "第1章〜第6章：プログラミングの基礎を学ぶ"
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

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

# はじめに

本書は、C言語プログラミング教材の基礎編です。プログラミング初心者を対象に、C言語の基本的な概念と文法を段階的に学習できるよう構成されています。

## 本書の構成

基礎編では以下の内容を扱います：

- 第1章: 導入・環境構築
- 第2章: 基本文法・Hello World
- 第3章: データ型と変数
- 第4章: 演算子
- 第5章: 制御構造（条件分岐）
- 第6章: 制御構造（ループ）

## 学習の進め方

各章は以下の構成になっています：

1. **概念の説明**: 学習する内容の理論的な説明
2. **サンプルコード**: 実際に動作するコード例
3. **演習問題**: 理解を深めるための練習問題

サンプルコードは必ず自分で入力して実行し、動作を確認しながら学習を進めてください。

---

EOF

# 各章のREADME.mdを結合（基礎編：第1-6章）
chapters=(introduction basics-syntax data-types operators control-if control-loop)
for i in "${!chapters[@]}"; do
    chapter="${chapters[$i]}"
    if [ -f "$PROJECT_ROOT/src/$chapter/README.md" ]; then
        # 各章の前に改ページを追加
        echo "" >> "$INPUT_MD"
        echo '```{=openxml}' >> "$INPUT_MD"
        echo '<w:p><w:r><w:br w:type="page"/></w:r></w:p>' >> "$INPUT_MD"
        echo '```' >> "$INPUT_MD"
        echo "" >> "$INPUT_MD"
        
        echo "" >> "$INPUT_MD"
        cat "$PROJECT_ROOT/src/$chapter/README.md" >> "$INPUT_MD"
        echo "" >> "$INPUT_MD"
    fi
done

# 終わりに
cat >> "$INPUT_MD" << 'EOF'

# 終わりに

基礎編の学習お疲れさまでした。ここまでで、C言語の基本的な文法と制御構造を学びました。

## 次のステップ

基礎編を修了したら、応用編に進んでください。応用編では以下の内容を学習します：

- 配列とポインタ
- 文字列処理
- 関数
- ビット操作

プログラミングの学習は継続が大切です。焦らず、着実に理解を深めていきましょう。

EOF

# Pandocでdocxファイルを生成
if command -v pandoc &> /dev/null; then
    echo "Pandocでdocxファイルを生成中..."
    # カスタムテンプレートを使用
    if [ -f "$PROJECT_ROOT/templates/custom-reference.docx" ]; then
        pandoc "$INPUT_MD" \
            -o "$OUTPUT_DOCX" \
            --from markdown+raw_attribute+raw_html \
            --to docx \
            --standalone \
            --toc \
            --reference-doc="$PROJECT_ROOT/templates/custom-reference.docx"
    else
        pandoc "$INPUT_MD" \
            -o "$OUTPUT_DOCX" \
            --from markdown+raw_attribute+raw_html \
            --to docx \
            --standalone \
            --toc
    fi
    
    if [ $? -eq 0 ]; then
        echo "✅ メインテキスト（基礎編）が生成されました: $OUTPUT_DOCX"
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

# 中間ファイルを削除（オプション）
# rm -f "$INPUT_MD"

echo "✅ 処理が完了しました"