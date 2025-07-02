#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/main_textbook_intermediate.md"
OUTPUT_DIR="$PROJECT_ROOT/output/word"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_メインテキスト_応用編.docx"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# 応用編用のMarkdownファイルを生成
echo "応用編のメインテキストを生成中..."

cat > "$INPUT_MD" << 'EOF'
---
title: "C言語プログラミング教材 - メインテキスト（応用編）"
subtitle: "第7章〜第11章：実践的なプログラミング技術"
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

本書は、C言語プログラミング教材の応用編です。基礎編を修了した学習者を対象に、より実践的なプログラミング技術を習得できるよう構成されています。

## 前提知識

応用編を学習する前に、以下の内容を理解していることが必要です：

- 基本的なC言語の文法
- 変数とデータ型
- 演算子の使い方
- 条件分岐とループ

## 本書の構成

応用編では以下の内容を扱います：

- 第7章: 配列（基本編）
- 第8章: ポインタ基礎
- 第9章: 配列とポインタ
- 第10章: 文字列処理
- 第11章: 関数

## 学習のポイント

応用編では、C言語の最も重要な概念であるポインタを中心に学習します。ポインタは初学者にとって難しい概念ですが、メモリの仕組みを理解しながら段階的に学習することで、必ず習得できます。

---

EOF

# 各章のREADME.mdを結合（応用編：第7-11章）
chapters=(arrays-basics pointers arrays-pointers strings functions)
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

応用編の学習お疲れさまでした。ここまでで、C言語の中核となる概念を学びました。

## 学習の成果

応用編を通じて、以下のスキルを習得しました：

- 配列を使った効率的なデータ管理
- ポインタによるメモリの直接操作
- 文字列の柔軟な処理
- 関数による構造化プログラミング

## 次のステップ

応用編を修了したら、上級編に進んでください。上級編では以下の内容を学習します：

- ビット操作とビットフィールド
- 構造体とポインタ
- 関数ポインタ
- 複数ファイルプログラミング

これらの技術を習得することで、より大規模で実践的なプログラムを作成できるようになります。

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
        echo "✅ メインテキスト（応用編）が生成されました: $OUTPUT_DOCX"
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