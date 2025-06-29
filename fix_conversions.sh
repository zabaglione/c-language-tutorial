#!/bin/bash

echo "誤変換された文字列を修正中..."

# すべてのmarkdownファイルを対象に修正（バックアップ除外）
find . -name "*.md" -not -path "./backup_before_emoji_removal/*" -exec sed -i '' \
    -e 's/C9\([^0-9]\)/C90\1/g' \
    -e 's/\([^0-9]\)C\([^0-9]\)/\1C11\2/g' \
    -e 's/\([^0-9]\)C\([^0-9]\)/\1C17\2/g' \
    -e 's/RADM\.md/README.md/g' \
    -e 's/fnctions/functions/g' \
    -e 's/fnction-pointers/function-pointers/g' \
    -e 's/strctres/structures/g' \
    -e 's/introdction/introduction/g' \
    -e 's/contine/continue/g' \
    {} \;

echo "修正完了！"

# 修正結果の確認
echo ""
echo "=== 修正結果の確認 ==="
echo "C90の出現回数: $(grep -r "C90" . --include="*.md" | grep -v "backup_before_emoji_removal" | wc -l)"
echo "C11の出現回数: $(grep -r "C11" . --include="*.md" | grep -v "backup_before_emoji_removal" | wc -l)"
echo "C17の出現回数: $(grep -r "C17" . --include="*.md" | grep -v "backup_before_emoji_removal" | wc -l)"
echo "README.mdの出現回数: $(grep -r "README.md" . --include="*.md" | grep -v "backup_before_emoji_removal" | wc -l)"
echo "functionsの出現回数: $(grep -r "functions" . --include="*.md" | grep -v "backup_before_emoji_removal" | wc -l)"