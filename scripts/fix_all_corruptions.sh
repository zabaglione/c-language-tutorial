#!/bin/bash

# 修正スクリプト - 文字列置換エラーを修正

echo "=== C言語学習教材 - 文字列置換エラー修正スクリプト ==="
echo "処理開始..."

# すべてのREADME.mdファイルを検索
find . -name "README.md" -type f | while read -r file; do
    echo "処理中: $file"
    
    # バックアップ作成
    cp "$file" "${file}.backup_fix"
    
    # 修正を適用
    sed -i '' '
        # C言語関連の修正（順序が重要）
        s/C17言語/C言語/g
        s/C17/C11/g
        s/C9/C90/g
        
        # プログラミング用語の修正
        s/inclde/include/g
        s/retrn/return/g
        s/sbtract/subtract/g
        s/mltiply/multiply/g
        s/doble/double/g
        s/fnction/function/g
        s/nction/unction/g
        s/contine/continue/g
        s/soltions/solutions/g
        s/rn-all/run-all/g
        s/rn/run/g
        
        # 大文字の修正
        s/RADM/README/g
        s/VNT/EVENT/g
        s/C17LIC17K/CLICK/g
        s/C17OUNT/COUNT/g
        s/C17SS/CSS/g
        s/C17hrome/Chrome/g
        s/C17ode/Code/g
        s/C17allback/Callback/g
        s/C17ompiler/Compiler/g
        
        # その他の修正
        s/strctres/structures/g
        s/introdction/introduction/g
        s/ppercase/uppercase/g
        s/mlti/multi/g
        s/nms/nums/g
        s/cbe/cube/g
        s/sqare/square/g
        s/reslt/result/g
        s/defalt/default/g
        s/absolte/absolute/g
        s/calclate/calculate/g
        s/execte/execute/g
        s/cleanp/cleanup/g
        s/nload/unload/g
        s/vent/Event/g
        s/Plgin/Plugin/g
        s/MenItem/MenuItem/g
        s/crrent/current/g
        s/pased/paused/g
        s/STAT_/STATE_/g
        s/resme/resume/g
        s/qit/quit/g
        s/mose/mouse/g
        s/nknown/unknown/g
        s/inaryOperation/BinaryOperation/g
        s/Mathnction/MathFunction/g
        s/ttorial/tutorial/g
        s/PD/PDF/g
        s/gn/gnu/g
        s/manal/manual/g
        s/visalstdio/visualstudio/g
        s/xplorer/Explorer/g
        s/langage/language/g
        s/compter/computer/g
    ' "$file"
    
    # C11/C17の正しい使い分けを修正
    sed -i '' '
        # C11が正しい箇所を修正
        /匿名構造体、_Generic選択、_Static_assert/s/C11/C11/g
        /C11:/s/C11:/C11:/g
        
        # C17が正しい箇所を修正  
        /C17:/s/C11:/C17:/g
        /standard=c17/s/C11/C17/g
        /std=c17/s/C11/C17/g
    ' "$file"
done

# 特定のファイルに対する追加修正
if [ -f "README.md" ]; then
    echo "メインREADME.mdの追加修正..."
    sed -i '' '
        # C規格の正しい表記を修復
        /^- \*\*C90\*\*/s/C11/C90/
        /^- \*\*C99\*\*/s/C11/C99/
        /ISO\/IC11/s/IC11/IEC/
        /99:/s/99:/9899:/
        
        # gcc, emacs等の修正
        /GC11C/s/GC11C/GCC/g
        s/macs/Emacs/g
        
        # Visual Studio Code
        s/Visal Stdio C11ode/Visual Studio Code/g
        
        # その他の固有名詞
        s/Online GD/Online GDB/g
    ' "README.md"
fi

# C90とmakeコマンドの特別な修正
find . -name "README.md" -type f -exec sed -i '' '
    # make clean && make STANDARD=c90 の修正
    /make clean && make STANDARD=/s/c9$/c90/g
    
    # gcc -std=c90 の修正
    /-std=c9 /s/-std=c9 /-std=c90 /g
    /-std=c9$/s/-std=c9$/-std=c90/g
' {} \;

echo ""
echo "=== 修正完了 ==="
echo "すべてのREADME.mdファイルの文字列置換エラーを修正しました。"
echo "バックアップは .backup_fix 拡張子で保存されています。"