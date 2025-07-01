#!/bin/bash
# docs/main_textbook.mdから特定セクションを除外してWord文書を生成するスクリプト

# 基本ディレクトリ
BASE_DIR=$(pwd)
DOCS_DIR="../docs"
OUTPUT_DIR="../output/word"
TEMPLATE="../custom-reference-1.docx"

# 一時ファイル
TEMP_FILTERED="/tmp/filtered_textbook.md"

# 出力ファイル名
OUTPUT_FILE="${OUTPUT_DIR}/C言語プログラミング教材_メインテキスト_クリーン版.docx"

echo "docs/main_textbook.mdから特定セクションを除外してWord文書を生成します"
echo "================================================"

# docsディレクトリの存在確認
if [ ! -f "${DOCS_DIR}/main_textbook.md" ]; then
    echo "エラー: ${DOCS_DIR}/main_textbook.md が見つかりません"
    exit 1
fi

# outputディレクトリの作成
mkdir -p "$OUTPUT_DIR"

echo "フィルタリング処理を実行中..."

# フィルタリング処理
# 1. 各セクションの開始位置を検出して、次のセクションまたは章の区切りまでを削除
awk '
BEGIN {
    skip = 0
    in_code_block = 0
}

# コードブロックの開始/終了を追跡
/^```/ {
    in_code_block = !in_code_block
    if (!skip) {
        print
    }
    next
}

# 除外するセクションの検出（コードブロック内でない場合のみ）
!in_code_block && /^##+ *(次の章へ|参考資料|サンプルコード|演習課題|演習問題|コンパイル方法|規格による違い|よくある間違い|おめでとうございます)/ {
    skip = 1
    next
}

# 章の区切り（---）の処理（コードブロック内でない場合のみ）
!in_code_block && /^---$/ {
    if (skip) {
        skip = 0
    }
    print
    next
}

# 新しい章または主要セクションの開始を検出
!in_code_block && /^#+ *(第[0-9]+章|対応C規格|学習目標|概要と詳細)/ {
    skip = 0
}

# スキップ中でなければ出力（コードブロック内の---は保持）
!skip || in_code_block {
    print
}
' "${DOCS_DIR}/main_textbook.md" > "$TEMP_FILTERED"

# 連続する空行を1つに削減 (BSD sed互換)
perl -i -0pe 's/\n\n+/\n\n/g' "$TEMP_FILTERED"

# 章の終わりの不要な空行を削除
perl -i -pe 's/\n+---$/\n---/g' "$TEMP_FILTERED"

echo "pandocで変換中..."

# pandocで変換
pandoc "$TEMP_FILTERED" \
    --reference-doc="$TEMPLATE" \
    -o "$OUTPUT_FILE" \
    --from markdown+raw_attribute+pipe_tables+tex_math_dollars \
    --to docx \
    --toc \
    --toc-depth=2 \
    --standalone \
    --highlight-style=tango

if [ $? -eq 0 ]; then
    echo "✓ 作成完了: $(basename "$OUTPUT_FILE")"
    echo "  ファイルサイズ: $(ls -lh "$OUTPUT_FILE" | awk '{print $5}')"
    echo "  保存場所: $OUTPUT_FILE"
    
    # フィルタリング結果の統計を表示
    original_lines=$(wc -l < "${DOCS_DIR}/main_textbook.md")
    filtered_lines=$(wc -l < "$TEMP_FILTERED")
    removed_lines=$((original_lines - filtered_lines))
    
    echo ""
    echo "フィルタリング統計:"
    echo "  元のファイル: ${original_lines} 行"
    echo "  フィルタ後: ${filtered_lines} 行"
    echo "  削除された行数: ${removed_lines} 行"
else
    echo "✗ エラー: Word文書の作成に失敗しました"
    exit 1
fi

# 一時ファイルを削除
rm -f "$TEMP_FILTERED"

echo "================================================"
echo "除外されたセクション:"
echo "  - 次の章へ"
echo "  - 参考資料"
echo "  - サンプルコード"
echo "  - 演習課題"
echo "  - 演習問題"
echo "  - コンパイル方法"
echo "  - 規格による違い"
echo "  - よくある間違い"
echo "  - おめでとうございます"
echo "================================================"
echo "完了しました。"