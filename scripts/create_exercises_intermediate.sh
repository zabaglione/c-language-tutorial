#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/exercises_intermediate.md"
OUTPUT_DIR="$PROJECT_ROOT/output/word"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_演習問題集_応用編.docx"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# 応用編用の演習問題集Markdownファイルを生成
echo "応用編の演習問題集を生成中..."

cat > "$INPUT_MD" << 'EOF'
---
title: "C言語プログラミング教材 - 演習問題集（応用編）"
subtitle: "第7章〜第11章の演習問題"
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

本書は、C言語プログラミング教材応用編の演習問題集です。配列、ポインタ、文字列、関数など、C言語の中核となる概念を実践的に習得するための問題を収録しています。

## 前提知識

応用編の演習問題に取り組む前に、基礎編の内容を十分に理解していることが必要です：

- 基本的な文法とデータ型
- 演算子の使い方
- 条件分岐とループ

## 演習問題の難易度

応用編では、より実践的な問題を扱います：

- **基礎問題**: 新しい概念の基本的な使い方
- **応用問題**: 実務で遭遇する典型的な課題
- **発展問題**: アルゴリズムとデータ構造の応用

## ポインタ学習の重要性

特に第8章〜第9章のポインタ関連の演習は、C言語習得の要となります。じっくりと時間をかけて取り組んでください。

---

EOF

# 各章の演習問題README.mdを結合（応用編：第7-11章）
chapter_names=("第7章: 配列（基本編）" "第8章: ポインタ基礎" "第9章: 配列とポインタ" "第10章: 文字列処理" "第11章: 関数")
chapters=(arrays-basics pointers arrays-pointers strings functions)

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

## 理解度の確認

応用編の演習問題を通じて、以下の点を確認してください：

### ポインタの理解
- [ ] ポインタとアドレスの関係を説明できる
- [ ] ポインタ演算を正しく使える
- [ ] 配列とポインタの関係を理解している

### 文字列処理
- [ ] 文字配列と文字列の違いを理解している
- [ ] 標準ライブラリ関数を適切に使える
- [ ] 独自の文字列処理関数を実装できる

### 関数設計
- [ ] 適切な引数と戻り値を設計できる
- [ ] ポインタ渡しと値渡しを使い分けられる
- [ ] 再帰関数の動作を理解している

## 次のステップ

応用編を修了したら、上級編に進んでください。上級編では、より高度なデータ構造とシステムプログラミングの技術を学びます。

## デバッグのヒント

応用編では、特に以下のエラーに注意してください：

1. **セグメンテーションフォルト**
   - NULLポインタへのアクセス
   - 配列の範囲外アクセス
   - 解放済みメモリへのアクセス

2. **メモリリーク**
   - mallocしたメモリのfree忘れ
   - 適切なメモリ管理

3. **文字列処理のバグ**
   - NULL終端の忘れ
   - バッファオーバーフロー

これらのエラーは、printfデバッグやデバッガを使って丁寧に調査してください。

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
        echo "✅ 演習問題集（応用編）が生成されました: $OUTPUT_DOCX"
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