#!/bin/bash

# C言語学習教材 - 最終修正スクリプト

echo "=== C言語学習教材 - 最終修正スクリプト ==="
echo "処理開始..."

# すべてのREADME.mdファイルを処理
find . -name "README.md" -type f | while read -r file; do
    echo "処理中: $file"
    
    # 残りの修正を適用
    sed -i '' '
        # C11の誤った変換を修正
        s/C11の不具合修正版/C17の不具合修正版/g
        
        # 数字の誤変換を修正
        s/23つ/2つ/g
        s/13行/実行/g
        s/に23つ/につ/g
        
        # 重複した数字を修正
        s/112481216バイト/1バイト/g
        s/212481216バイト/2バイト/g
        s/412481216バイト/4バイト/g
        s/812481216バイト/8バイト/g
        s/1612481216バイト/16バイト/g
        s/12\/1612481216バイト/12\/16バイト/g
        s/4\/812481216バイト/4\/8バイト/g
        
        # 7715桁を修正
        s/7715桁/7桁/g
        s/15715桁/15桁/g
        
        # 毎1回を修正
        s/毎1回/毎回/g
        s/函数呼出1回数/関数呼出回数/g
        
        # unsigned の修正
        s/unsignued/unsigned/g
        
        # uuninitialized の修正
        s/uuninitialized/uninitialized/g
        
        # studio.h を stdio.h に修正
        s/studio\.h/stdio.h/g
        
        # その他の誤変換
        s/MAX_SIZEE/MAX_SIZE/g
        s/TITLEE/TITLE/g
        s/Tututorial/Tutorial/g
        
        # ディレクトリ名の修正
        s/operautors/operators/g
        s/countrol-if/control-if/g
        s/countrol-loop/control-loop/g
        s/countinue/continue/g
        
        # bool型の修正
        s/b_Bool/_Bool/g
        s/_B_Bool/_Bool/g
        
        # ビット演算の修正
        s/64ビット演算子/ビット演算子/g
        s/64ビット操作/ビット操作/g
        s/6464ビット/64ビット/g
        
        # GNU の修正
        s/gnuu\.org/gnu.org/g
        
        # Explorer の修正
        s/EExplorer/Explorer/g
        
        # 番号付きリストの修正（ピリオドが消えている）
        s/^\([0-9]\)\. /\1. /g
        
        # C11が単独のCになっている箇所を修正（文脈を考慮）
        /匿名構造体、_Generic選択、_Static_assert/s/C/C11/g
        /C17の不具合修正版/s/C/C17/g
        /構造体とポインタ.*C90\/C/s/C90\/C/C90\/C11/g
        /発展技術.*C90\/C99\/C\/C17/s/C90\/C99\/C\/C17/C90\/C99\/C11\/C17/g
    ' "$file"
done

# メインのREADME.mdの特別な修正
if [ -f "./README.md" ]; then
    echo "メインREADME.mdの特別な修正..."
    sed -i '' '
        # C11の箇所を正しく修正
        /- \*\*C\*\*: 匿名構造体/s/\*\*C\*\*/\*\*C11\*\*/
        /C17\*\*: Cの不具合修正版/s/Cの/C11の/
        
        # 表の修正
        /構造体とポインタ.*C90\/C /s/C90\/C /C90\/C11 /
        /複数ファイル.*C90\/C99\/C\/C17/s/C90\/C99\/C\/C17/C90\/C99\/C11\/C17/
    ' "./README.md"
fi

echo ""
echo "=== 修正完了 ==="
echo "最終的な文字列置換エラーを修正しました。"