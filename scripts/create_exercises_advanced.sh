#!/bin/bash

# スクリプトのディレクトリを取得
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 入力ファイルと出力ファイルのパス
INPUT_MD="$PROJECT_ROOT/docs/exercises_advanced.md"
OUTPUT_DIR="$PROJECT_ROOT/output/word"
OUTPUT_DOCX="$OUTPUT_DIR/C言語プログラミング教材_演習問題集_上級編.docx"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# 上級編用の演習問題集Markdownファイルを生成
echo "上級編の演習問題集を生成中..."

cat > "$INPUT_MD" << 'EOF'
---
title: "C言語プログラミング教材 - 演習問題集（上級編）"
subtitle: "第12章〜第16章の演習問題"
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

本書は、C言語プログラミング教材上級編の演習問題集です。ビット操作、構造体、関数ポインタなど、実務で必要となる高度な技術を実践的に習得するための問題を収録しています。

## 前提知識

上級編の演習問題に取り組む前に、以下の内容を完全に理解していることが必要です：

- ポインタと配列の関係
- 動的メモリ管理
- 関数の設計と実装
- 文字列処理

## 演習問題の特徴

上級編の演習問題は、実務で遭遇する実際の課題に基づいています：

- **システムプログラミング**: ハードウェアに近いレベルの処理
- **データ構造**: 効率的なデータ管理手法
- **設計パターン**: 再利用可能なコード設計

## チャレンジ問題

各章には「チャレンジ問題」が含まれています。これらは発展的な内容で、より深い理解と創造性が求められます。

---

EOF

# 各章の演習問題README.mdを結合（上級編：第12-16章）
chapter_names=("第12章: ビット操作とビットフィールド" "第13章: 構造体とポインタ" "第14章: 関数ポインタ" "第15章: 複数ファイル・発展技術" "第16章: C23の新機能")
chapters=(bit-operations structures function-pointers advanced c23-features)

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

# 上級編を修了して

## 習得したスキル

上級編の演習問題を通じて、以下の高度なスキルを習得しました：

### システムレベルプログラミング
- [ ] ビット操作による効率的なデータ処理
- [ ] メモリレイアウトの理解と最適化
- [ ] ハードウェア制御の基礎

### 高度なデータ構造
- [ ] 構造体を使った複雑なデータモデリング
- [ ] リンクリストやツリー構造の実装
- [ ] メモリ効率を考慮した設計

### 関数型プログラミング要素
- [ ] 関数ポインタによる高階関数
- [ ] コールバックパターンの実装
- [ ] 汎用的なアルゴリズムの設計

### プロジェクト構成
- [ ] 複数ファイルによるモジュール設計
- [ ] ヘッダファイルの適切な管理
- [ ] 再利用可能なライブラリの作成

## 実務への応用

これらのスキルは、以下のような分野で活用できます：

1. **組み込みシステム開発**
   - マイコンプログラミング
   - リアルタイムシステム

2. **システムプログラミング**
   - OS開発
   - デバイスドライバ

3. **高性能コンピューティング**
   - 数値計算
   - ゲームエンジン

## 継続的な学習

プログラミングスキルを維持・向上させるために：

1. **コードリーディング**
   - オープンソースプロジェクトのソースコードを読む
   - 優れたC言語プロジェクトから学ぶ

2. **プロジェクト実践**
   - 自分でツールやライブラリを作成
   - 既存プロジェクトへの貢献

3. **新技術の探求**
   - C標準の最新動向をフォロー
   - 関連技術（Rust、Zig等）の学習

## 最後に

C言語は、コンピュータサイエンスの基礎を学ぶ上で最適な言語です。本教材で学んだ知識は、他のプログラミング言語を学ぶ際にも必ず役立ちます。

これからも挑戦を続け、素晴らしいソフトウェアを作り出してください！

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
        echo "✅ 演習問題集（上級編）が生成されました: $OUTPUT_DOCX"
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