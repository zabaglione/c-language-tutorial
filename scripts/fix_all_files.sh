#!/bin/bash

# C言語学習教材 - 全ファイル文字列置換エラー修正スクリプト

echo "=== C言語学習教材 - 全ファイル修正スクリプト ==="
echo "処理開始..."

# すべてのREADME.mdファイルを処理
find . -name "README.md" -type f | while read -r file; do
    echo "処理中: $file"
    
    # バックアップ作成
    if [ ! -f "${file}.backup_original" ]; then
        cp "$file" "${file}.backup_original"
    fi
    
    # 文字列置換エラーの修正
    sed -i '' '
        # C規格関連
        s/C900/C90/g
        s/C909/C99/g
        s/C11omplex/Complex/g
        
        # 一般的な単語
        s/nsignued/unsigned/g
        s/inclde/include/g
        s/retrn/return/g
        s/returun/return/g
        s/sbtract/subtract/g
        s/mltiply/multiply/g
        s/doble/double/g
        s/fnction/function/g
        s/fuunction/function/g
        s/contine/continue/g
        s/soltions/solutions/g
        s/strctres/structures/g
        s/introdction/introduction/g
        s/ppercase/uppercase/g
        s/calclate/calculate/g
        s/execte/execute/g
        s/cleanp/cleanup/g
        s/nload/unload/g
        s/crrent/current/g
        s/pased/paused/g
        s/resme/resume/g
        s/qit/quit/g
        s/mose/mouse/g
        s/nknown/unknown/g
        s/langage/language/g
        s/compter/computer/g
        s/torial/tutorial/g
        s/ttorial/tutorial/g
        s/manal/manual/g
        s/visalstdio/visualstudio/g
        s/visal/visual/g
        s/stdio/studio/g
        s/xplorer/Explorer/g
        s/docmentation/documentation/g
        s/exterun/extern/g
        s/ato/auto/g
        s/Atomatic/Automatic/g
        s/Dration/Duration/g
        s/pblic/public/g
        s/ninitialized/uninitialized/g
        s/conter/counter/g
        s/cont/count/g
        s/debg/debug/g
        s/bild/build/g
        s/pdate/update/g
        s/sdo/sudo/g
        s/nms/nums/g
        s/cbe/cube/g
        s/sqare/square/g
        s/reslt/result/g
        s/defalt/default/g
        s/absolte/absolute/g
        s/ronded/rounded/g
        s/prodct/product/g
        s/qotient/quotient/g
        s/nm/num/g
        s/nmber/number/g
        s/sm/sum/g
        s/otpt/output/g
        s/conter/counter/g
        s/STUDNTS/STUDENTS/g
        s/TITL/TITLE/g
        s/SIZ/SIZE/g
        s/tre/true/g
        s/ool/_Bool/g
        s/Linx/Linux/g
        s/Ubnt/Ubuntu/g
        s/C11ommand/Command/g
        s/C11ommnity/Community/g
        s/C11ode/Code/g
        s/C11hrome/Chrome/g
        s/C11/C/g
        s/GC11C/GCC/g
        s/IC11/IEC/g
        s/RADM/README/g
        s/VNT/EVENT/g
        s/C11LIC11K/CLICK/g
        s/C11OUNT/COUNT/g
        s/C11SS/CSS/g
        s/C11ompiler/Compiler/g
        s/C11allback/Callback/g
        s/STAT_/STATE_/g
        s/inaryOperation/BinaryOperation/g
        s/Mathnction/MathFunction/g
        s/PD/PDF/g
        s/gn/gnu/g
        
        # printf フォーマット修正
        s/%dn/%d\\n/g
        s/%sn/%s\\n/g
        s/%fn/%f\\n/g
        s/%cn/%c\\n/g
        s/%xn/%x\\n/g
        s/%ln/%lu\\n/g
        s/%l /%lu /g
        
        # エスケープシーケンス修正（注意深く処理）
        /printf/s/\\\\n/\\n/g
        /printf/s/\\\\t/\\t/g
        
        # { } ブロック修正
        s/`` と ``/`{` と `}`/g
        s/`{``/`{`/g
        s/`}``/`}`/g
        
        # 番号付きリスト修正
        s/^\. \([A-Za-z]\)/1. \1/
        s/^\\. \([A-Za-z]\)/2. \1/
        s/^\\. \([A-Za-z]\)/3. \1/
        s/^\\. \([A-Za-z]\)/4. \1/
        s/^\\. \([A-Za-z]\)/5. \1/
        s/^\\. \([A-Za-z]\)/6. \1/
        
        # 日本語の数字修正
        s/回/1回/g
        s/つ/2つ/g
        s/つ/3つ/g
        s/桁/7桁/g
        s/桁/15桁/g
        s/バイト/1バイト/g
        s/バイト/2バイト/g
        s/バイト/4バイト/g
        s/バイト/8バイト/g
        s/バイト/12バイト/g
        s/バイト/16バイト/g
        s/ビット/64ビット/g
        s/行/1行/g
        s/行/3行/g
        
        # 数値の修正（慎重に）
        /char.*範囲/s/ \~/-128 ~/
        /char.*範囲/s/\~ /~ 127/
        /unsigned char.*範囲/s/ \~/0 ~/
        /unsigned char.*範囲/s/\~ /~ 255/
        /short.*範囲/s/-, \~/-32,768 ~/
        /short.*範囲/s/\~ , /~ 32,767/
        /unsigned short.*範囲/s/ \~/0 ~/
        /unsigned short.*範囲/s/\~ , /~ 65,535/
        /int.*範囲/s/-,,, \~/-2,147,483,648 ~/
        /int.*範囲/s/\~ ,,,/~ 2,147,483,647/
        /unsigned int.*範囲/s/ \~/0 ~/
        /unsigned int.*範囲/s/\~ ,9,9,9/~ 4,294,967,295/
    ' "$file"
    
    # C言語のコード内の修正（別パス）
    sed -i '' '
        # main関数のブロック修正
        /^int main(void)$/,/^}$/ {
            /^int main(void)$/ {
                n
                s/^$/{\n/
            }
        }
        
        # その他の関数のブロック修正
        /^void.*([^)]*)$/,/^}$/ {
            /^void.*([^)]*)$/ {
                n
                s/^$/{\n/
            }
        }
        
        /^int.*([^)]*)$/,/^}$/ {
            /^int.*([^)]*)$/ {
                n
                s/^$/{\n/
            }
        }
    ' "$file"
done

# C言語のサンプルファイルも修正
find . -name "*.c" -type f | while read -r file; do
    echo "処理中: $file"
    
    if [ ! -f "${file}.backup_original" ]; then
        cp "$file" "${file}.backup_original"
    fi
    
    sed -i '' '
        s/returun/return/g
        s/retrn/return/g
        s/inclde/include/g
        s/fnction/function/g
        s/fuunction/function/g
        s/nmber/number/g
        s/sm/sum/g
        s/cont/count/g
        s/reslt/result/g
        s/otpt/output/g
        s/ato/auto/g
        s/exterun/extern/g
        s/nsignued/unsigned/g
        s/doble/double/g
        s/tre/true/g
        s/stdio/studio/g
        s/C11/C/g
        
        # printf修正
        s/printf("\(.*\)n"/printf("\1\\n"/g
        s/printf(\(.*\)n"/printf(\1\\n"/g
    ' "$file"
done

echo ""
echo "=== 修正完了 ==="
echo "すべてのファイルの文字列置換エラーを修正しました。"
echo "バックアップは .backup_original 拡張子で保存されています。"