#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/main_textbook_advanced.md"
OUTPUT_DIR="$PROJECT_ROOT/output/word"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_メインテキスト_上級編.docx"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# 上級編用のMarkdownファイルを生成
echo "上級編のメインテキストを生成中..."

cat > "$INPUT_MD" << 'EOF'
---
title: "C言語プログラミング教材 - メインテキスト（上級編）"
subtitle: "第12章〜第16章：高度なプログラミング技術"
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

本書は、C言語プログラミング教材の上級編です。応用編を修了した学習者を対象に、実務で必要となる高度なプログラミング技術を習得できるよう構成されています。

## 前提知識

上級編を学習する前に、以下の内容を十分に理解していることが必要です：

- 配列とポインタの関係
- 文字列処理の基本
- 関数の定義と使用
- メモリの概念

## 本書の構成

上級編では以下の内容を扱います：

- 第12章: ビット操作とビットフィールド
- 第13章: 構造体とポインタ
- 第14章: 関数ポインタ
- 第15章: 複数ファイル・発展技術
- 第16章: C23の新機能（オプション）

## 学習の目標

上級編では、以下のスキルの習得を目標とします：

1. ハードウェアに近いレベルでのプログラミング
2. 複雑なデータ構造の設計と実装
3. 大規模プログラムの構成方法
4. 最新のC言語規格への対応

---

EOF

# 各章のREADME.mdを結合（上級編：第12-16章）
chapters=(bit-operations structures function-pointers advanced c23-features)
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

C言語プログラミング教材の全課程を修了おめでとうございます！

## 習得したスキル

本教材を通じて、以下のスキルを習得しました：

- C言語の基本から高度な機能まで
- メモリ管理とポインタ操作
- 構造化プログラミング
- ビット操作による効率的な処理
- 大規模プログラムの設計手法

## 今後の学習

C言語の学習はここで終わりではありません。以下のような発展的な学習をお勧めします：

1. **実践的なプロジェクト**
   - 自分でアプリケーションを作成
   - オープンソースプロジェクトへの参加

2. **関連技術の学習**
   - システムプログラミング
   - 組み込みプログラミング
   - ネットワークプログラミング

3. **他の言語への応用**
   - C++への移行
   - RustやGoなどのシステムプログラミング言語

## 最後に

プログラミングは実践が最も重要です。学んだ知識を活かして、様々なプログラムを作成してください。困ったときは、本教材を参考書として活用してください。

皆さんのプログラミング人生が実り多いものになることを願っています。

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
        echo "✅ メインテキスト（上級編）が生成されました: $OUTPUT_DOCX"
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