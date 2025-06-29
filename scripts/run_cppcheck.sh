#!/bin/bash
# C言語学習教材のコード品質評価スクリプト

# 出力ファイル
REPORT_FILE="../docs/cppcheck_evaluation_report.md"
TIMESTAMP=$(date +"%Y-%m-%d %H:%M:%S")

# レポートヘッダー
cat > "$REPORT_FILE" << EOF
# C言語学習教材 コード品質評価レポート

**評価ツール**: cppcheck $(cppcheck --version 2>&1 | head -n1)  
**評価日時**: $TIMESTAMP  
**評価対象**: src/ディレクトリ内の全C言語ソースコード

## 評価サマリー

本レポートは、C言語学習教材に含まれるサンプルコードおよび演習解答例の静的解析結果をまとめたものです。

### 評価基準

cppcheckは以下の項目をチェックします：
- **error**: 明確なバグ
- **warning**: 防御的プログラミングの観点からの警告
- **style**: コーディングスタイルの問題
- **performance**: パフォーマンスの問題
- **portability**: 移植性の問題
- **information**: 情報提供

---

## 章別評価結果

EOF

# 各章を検査
cd ../src

for chapter in */; do
    chapter_name=${chapter%/}
    echo "Checking $chapter_name..."
    
    # 章タイトルを追加
    echo -e "\n### $chapter_name\n" >> "$REPORT_FILE"
    
    # ファイル数をカウント
    c_files=$(find "$chapter_name" -name "*.c" | wc -l | tr -d ' ')
    echo "**検査ファイル数**: $c_files 個" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # cppcheckを実行（一時ファイルに出力）
    temp_file="/tmp/cppcheck_${chapter_name}.txt"
    cppcheck --enable=all --suppress=missingIncludeSystem --quiet \
             --template="{file}:{line}: {severity}: {message}" \
             "$chapter_name" 2> "$temp_file"
    
    # 結果をカウント
    errors=$(grep -c ": error:" "$temp_file" || echo "0")
    warnings=$(grep -c ": warning:" "$temp_file" || echo "0")
    style=$(grep -c ": style:" "$temp_file" || echo "0")
    performance=$(grep -c ": performance:" "$temp_file" || echo "0")
    portability=$(grep -c ": portability:" "$temp_file" || echo "0")
    information=$(grep -c ": information:" "$temp_file" || echo "0")
    
    # サマリーを出力
    echo "**検出された問題**:" >> "$REPORT_FILE"
    echo "- Errors: $errors" >> "$REPORT_FILE"
    echo "- Warnings: $warnings" >> "$REPORT_FILE"
    echo "- Style: $style" >> "$REPORT_FILE"
    echo "- Performance: $performance" >> "$REPORT_FILE"
    echo "- Portability: $portability" >> "$REPORT_FILE"
    echo "- Information: $information" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # 問題がある場合は詳細を出力
    if [ -s "$temp_file" ]; then
        echo "**詳細**:" >> "$REPORT_FILE"
        echo '```' >> "$REPORT_FILE"
        cat "$temp_file" >> "$REPORT_FILE"
        echo '```' >> "$REPORT_FILE"
    else
        echo "✅ **問題は検出されませんでした**" >> "$REPORT_FILE"
    fi
    
    # 一時ファイルを削除
    rm -f "$temp_file"
done

# 総合評価を追加
echo -e "\n---\n\n## 総合評価\n" >> "$REPORT_FILE"

# 全体の統計を計算
total_files=$(find . -name "*.c" | wc -l | tr -d ' ')
echo "**総検査ファイル数**: $total_files 個" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

# 全体でcppcheckを再実行して統計を取得
temp_all="/tmp/cppcheck_all.txt"
cppcheck --enable=all --suppress=missingIncludeSystem --quiet \
         --template="{file}:{line}: {severity}: {message}" \
         . 2> "$temp_all"

total_errors=$(grep -c ": error:" "$temp_all" || echo "0")
total_warnings=$(grep -c ": warning:" "$temp_all" || echo "0")
total_style=$(grep -c ": style:" "$temp_all" || echo "0")
total_performance=$(grep -c ": performance:" "$temp_all" || echo "0")
total_portability=$(grep -c ": portability:" "$temp_all" || echo "0")
total_information=$(grep -c ": information:" "$temp_all" || echo "0")

echo "**検出された問題の総数**:" >> "$REPORT_FILE"
echo "- Errors: $total_errors" >> "$REPORT_FILE"
echo "- Warnings: $total_warnings" >> "$REPORT_FILE"
echo "- Style: $total_style" >> "$REPORT_FILE"
echo "- Performance: $total_performance" >> "$REPORT_FILE"
echo "- Portability: $total_portability" >> "$REPORT_FILE"
echo "- Information: $total_information" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

# 評価結果のサマリー
echo "### 評価結果" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

if [ "$total_errors" -eq 0 ] && [ "$total_warnings" -eq 0 ]; then
    echo "🎉 **優秀**: エラーおよび警告は検出されませんでした。" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    echo "教材のサンプルコードは、静的解析の観点から高品質であることが確認されました。" >> "$REPORT_FILE"
else
    echo "⚠️ **要確認**: いくつかの問題が検出されました。" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    echo "検出された問題の多くは、教育目的のシンプルなコード例であることに起因する可能性があります。" >> "$REPORT_FILE"
fi

echo "" >> "$REPORT_FILE"
echo "### 備考" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"
echo "- 本教材は教育目的のため、エラーハンドリングを簡略化している箇所があります" >> "$REPORT_FILE"
echo "- C90準拠のコードも含まれるため、一部の最新のコーディング規約とは異なる場合があります" >> "$REPORT_FILE"
echo "- システムヘッダーに関する警告は除外しています（--suppress=missingIncludeSystem）" >> "$REPORT_FILE"

rm -f "$temp_all"

echo "評価完了: $REPORT_FILE"