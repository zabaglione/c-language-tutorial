#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/exercises_basic.md"
OUTPUT_DIR="$PROJECT_ROOT/output/word"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_演習問題集_基礎編.docx"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# 基礎編用の演習問題集Markdownファイルを生成
echo "基礎編の演習問題集を生成中..."

cat > "$INPUT_MD" << 'EOF'
---
title: "C言語プログラミング教材 - 演習問題集（基礎編）"
subtitle: "第1章〜第6章の演習問題"
author: "C言語学習教材プロジェクト"
date: "2024年"
documentclass: report
lang: ja
fontsize: 12pt
geometry: margin=1in
toc: true
toc-depth: 2
numbersections: true
---

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

# はじめに

本書は、C言語プログラミング教材基礎編の演習問題集です。各章で学んだ内容を実践的に確認し、理解を深めるための問題を収録しています。

## 演習問題の構成

各章の演習問題は以下の構成になっています：

- **基礎問題**: 学習内容の基本的な理解を確認
- **応用問題**: 複数の概念を組み合わせた問題
- **発展問題**: より実践的な課題

## 学習の進め方

1. まず自分で問題を解いてみる
2. コンパイル・実行して動作を確認
3. 解答例と比較して理解を深める
4. 別解や改善点を考える

---

EOF

# 各章の演習問題README.mdを結合（基礎編：第1-6章）
chapter_names=("第1章: 導入・環境構築" "第2章: 基本文法・Hello World" "第3章: データ型と変数" "第4章: 演算子" "第5章: 制御構造（条件分岐）" "第6章: 制御構造（ループ）")
chapters=(introduction basics-syntax data-types operators control-if control-loop)

for i in "${!chapters[@]}"; do
    chapter="${chapters[$i]}"
    chapter_name="${chapter_names[$i]}"
    
    if [ -f "$PROJECT_ROOT/src/$chapter/exercises/README.md" ]; then
        # 各章の前に改ページを追加
        echo "" >> "$INPUT_MD"
        echo '```{=openxml}' >> "$INPUT_MD"
        echo '<w:p><w:r><w:br w:type="page"/></w:r></w:p>' >> "$INPUT_MD"
        echo '```' >> "$INPUT_MD"
        echo "" >> "$INPUT_MD"
        
        echo "" >> "$INPUT_MD"
        echo "# $chapter_name - 演習問題" >> "$INPUT_MD"
        echo "" >> "$INPUT_MD"
        # タイトル行をスキップしてから内容を追加
        tail -n +2 "$PROJECT_ROOT/src/$chapter/exercises/README.md" >> "$INPUT_MD"
        echo "" >> "$INPUT_MD"
    fi
done

# 終わりに
cat >> "$INPUT_MD" << 'EOF'

# 演習問題を解き終えたら

## チェックリスト

基礎編の演習問題をすべて解き終えたら、以下の点を確認してください：

- [ ] すべての問題でコンパイルエラーなく実行できた
- [ ] 期待される出力が得られた
- [ ] コードの意味を説明できる
- [ ] 別の方法での実装を考えられる

## 次のステップ

基礎編の演習を完了したら、応用編の学習に進んでください。応用編では、より複雑なデータ構造とアルゴリズムを扱います。

## 困ったときは

- メインテキストの該当章を再度確認
- サンプルコードと比較
- エラーメッセージを注意深く読む
- 段階的にデバッグ出力を追加

プログラミングは試行錯誤の連続です。エラーを恐れず、積極的に挑戦してください。

EOF

# Pandocでdocxファイルを生成
if command -v pandoc &> /dev/null; then
    echo "Pandocでdocxファイルを生成中..."
    # カスタムテンプレートを使用
    if [ -f "$PROJECT_ROOT/templates/custom-reference.docx" ]; then
        pandoc "$INPUT_MD" \
            -o "$OUTPUT_DOCX" \
            --from markdown+raw_attribute+raw_html+fenced_divs+bracketed_spans \
            --to docx+styles \
            --standalone \
            --toc \
            --reference-doc="$PROJECT_ROOT/templates/custom-reference.docx"
    else
        pandoc "$INPUT_MD" \
            -o "$OUTPUT_DOCX" \
            --from markdown+raw_attribute+raw_html+fenced_divs+bracketed_spans \
            --to docx+styles \
            --standalone \
            --toc
    fi
    
    if [ $? -eq 0 ]; then
        echo "✅ 演習問題集（基礎編）が生成されました: $OUTPUT_DOCX"
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