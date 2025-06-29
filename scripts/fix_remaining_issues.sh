#!/bin/bash

# 残りの修正スクリプト - 文字列置換エラーを修正

echo "=== C言語学習教材 - 残りの修正スクリプト ==="
echo "処理開始..."

# すべてのREADME.mdファイルを検索
find . -name "README.md" -type f | while read -r file; do
    echo "処理中: $file"
    
    # 残りの修正を適用
    sed -i '' '
        # C規格の番号修正
        s/C900/C90/g
        s/C909/C99/g
        
        # 関数名の修正（functionが誤ってfuunctionになっている）
        s/fuunction/function/g
        s/fuunctional/functional/g
        
        # extern の修正
        s/exterun/extern/g
        
        # return の修正
        s/returun/return/g
        
        # その他の修正
        s/strunct/struct/g
        s/eEvent/event/g
        s/nsignued/unsigned/g
        s/struncpy/strncpy/g
        s/cont_words/count_words/g
        s/cont/count/g
        
        # その他の変数名修正
        s/seruname/username/g
        s/otpt/output/g
        s/sorce/source/g
        s/bild/build/g
        s/sdo/sudo/g
        s/tre/true/g
        s/patterun/pattern/g
        s/waruning/warning/g
        s/ato/auto/g
        s/docmentation/documentation/g
        s/fnc/func/g
        s/nms/nums/g
        s/flsh/flush/g
        s/plgin/plugin/g
        s/sm/sum/g
        s/nm/num/g
        s/volme/volume/g
        s/fll/full/g
        s/sqared/squared/g
        s/cbed/cubed/g
        s/dobled/doubled/g
        
        # ファイル名・ディレクトリ名の修正
        s/IL_/FILE_/g
        s/IL/FILE/g
        s/ILNAM/FILENAME/g
        s/ATUR/FEATURE/g
        s/C11ONIG/CONFIG/g
        s/C11HC11K/CHECK/g
        s/MALLOC11_C11HC11K/MALLOC_CHECK/g
        s/C11RITIC11AL/CRITICAL/g
        s/C11onfig/Config/g
        s/MMORY/MEMORY/g
        s/ALLOC11ATION/ALLOCATION/g
        s/PRMISSION/PERMISSION/g
        s/DNID/DENIED/g
        s/ARGUMNT/ARGUMENT/g
        s/OUND/FOUND/g
        s/SUC11CSS/SUCCESS/g
        s/AILUR/FAILURE/g
        s/XIT/EXIT/g
        s/RROR/ERROR/g
        s/rrorC11ode/ErrorCode/g
        s/ileInfo/FileInfo/g
        s/UNC11/FUNC/g
        s/DPS/DEPS/g
        s/OJC11TS/OBJECTS/g
        s/SOURC11/SOURCE/g
        s/C11C/CC/g
        s/C11LAGS/CFLAGS/g
        s/INC11/INC/g
        s/PROJC11T/PROJECT/g
        s/TARGT/TARGET/g
        s/SPARATOR/SEPARATOR/g
        s/VRSION/VERSION/g
        s/LOGGR/LOGGER/g
        s/DUG/DEBUG/g
        s/INO/INFO/g
        s/NDING/ENDING/g
        s/PATC11H/PATCH/g
        s/NC11RYPTION/ENCRYPTION/g
        s/C11OMPRSSION/COMPRESSION/g
        s/PLATORM/PLATFORM/g
        s/linx/linux/g
        s/APPL/APPLE/g
        s/MAC11OS/MACOS/g
        s/nistd/unistd/g
        s/GNUC11/GNUC/g
        s/C11OMPILR/COMPILER/g
        s/GC11C/GCC/g
        s/ORC11/FORCE/g
        s/INLIN/INLINE/g
        s/MSC11_VR/MSC_VER/g
        s/USRNAM/USERNAME/g
        s/USR/USER/g
        s/AS/ABS/g
        s/SQUAR/SQUARE/g
        s/ARRAY_SIZ/ARRAY_SIZE/g
        s/SA_R/SAFE_FREE/g
        s/MAC11ROS/MACROS/g
        s/TYP/TYPE/g
        s/MAK/MAKE/g
        s/TRAC/TRACE/g
        s/HADR/HEADER/g
        s/MNU/MENU/g
        s/LIS/LIBS/g
        s/IN/BIN/g
        s/PROIL/PROFILE/g
        s/LI_/LIB_/g
        s/NAM/NAME/g
        s/ARLAGS/ARFLAGS/g
        s/KY/KEY/g
        s/LNGTH/LENGTH/g
        s/VALU/VALUE/g
        s/GLOALS/GLOBALS/g
        s/modle/module/g
        s/STOPPDF/STOPPED/g
        s/beatifl/beautiful/g
        
        # 複合修正
        s/STAT_IDL/STATE_IDLE/g
        s/STAT_RUNNING/STATE_RUNNING/g
        s/STAT_PAUSD/STATE_PAUSED/g
        s/STAT_C11OUNT/STATE_COUNT/g
        s/VNT_C11LIC11K/EVENT_CLICK/g
        s/VNT_KYPRSS/EVENT_KEYPRESS/g
        s/VNT_MOUS_MOV/EVENT_MOUSE_MOVE/g
        s/VNT_WINDOW_C11LOS/EVENT_WINDOW_CLOSE/g
        s/VNT_TYP_C11OUNT/EVENT_TYPE_COUNT/g
        s/ventType/EventType/g
        s/ventHandler/EventHandler/g
        s/ventC11allback/EventCallback/g
        s/BinaryOperation/BinaryOperation/g
        s/Mathunction/MathFunction/g
        s/topper/toupper/g
        s/LIND/LINE/g
        s/IL__/FILE__/g
        s/__LIN__/__LINE__/g
        s/UNC11TION/FUNCTION/g
        s/ttorial/tutorial/g
        s/C11ompiler/Compiler/g
        s/C11allback/Callback/g
        s/learun/learn/g
    ' "$file"
done

# メインREADME.mdの特別な修正
if [ -f "README.md" ]; then
    echo "メインREADME.mdの最終修正..."
    sed -i '' '
        # C言語規格の正しい表記
        /対応C11規格/s/C11/C/
        /^本教材は以下のC言語規格/s/C言語/C言語/
        /^- \*\*C11\*\*: C11/s/: C11/: C11/
    ' "README.md"
fi

echo ""
echo "=== 修正完了 ==="
echo "残りの文字列置換エラーを修正しました。"