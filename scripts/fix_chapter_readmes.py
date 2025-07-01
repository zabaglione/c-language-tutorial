#!/usr/bin/env python3
"""
各章のREADME.mdファイルの欠落した値やエラーを修正するスクリプト
"""

import os
import re
import sys

def fix_control_if_readme(readme_path):
    """control-if章のREADME.mdを修正"""
    print("Fixing control-if/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 比較演算子セクションの修正
    content = re.sub(r'int a = , b = ;', 'int a = 5, b = 3;', content)
    content = re.sub(r'printf\("等しい\\n"\);', 'printf("等しい\\n");', content)
    content = re.sub(r'printf\("等しくない\\n"\);', 'printf("等しくない\\n");', content)
    content = re.sub(r'printf\("a は b より小さい\\n"\);', 'printf("a は b より小さい\\n");', content)
    content = re.sub(r'printf\("a は b 以下\\n"\);', 'printf("a は b 以下\\n");', content)
    content = re.sub(r'printf\("a は b より大きい\\n"\);', 'printf("a は b より大きい\\n");', content)
    content = re.sub(r'printf\("a は b 以上\\n"\);', 'printf("a は b 以上\\n");', content)
    
    # 論理演算子セクションの修正
    content = re.sub(r'int age = ;', 'int age = 25;', content)
    content = re.sub(r'int income = ;', 'int income = 300000;', content)
    content = re.sub(r'if \(age >= && income >= \)', 'if (age >= 20 && income >= 200000)', content)
    content = re.sub(r'printf\("ローン審査に通りました\\n"\);', 'printf("ローン審査に通りました\\n");', content)
    content = re.sub(r'if \(age < \|\| age > \)', 'if (age < 6 || age > 65)', content)
    content = re.sub(r'printf\("特別料金が適用されます\\n"\);', 'printf("特別料金が適用されます\\n");', content)
    content = re.sub(r'if \(!\(age >= \)\)', 'if (!(age >= 18))', content)
    content = re.sub(r'printf\("歳未満です\\n"\);', 'printf("18歳未満です\\n");', content)
    
    # switch文の基本構文の修正
    content = re.sub(r'switch \(変数または式\)\s*\n', 'switch (変数または式) {\n', content)
    content = re.sub(r'case 値:', 'case 値1:', content, count=1)
    content = re.sub(r'/\* 値の場合の処理 \*/', '/* 値1の場合の処理 */', content, count=1)
    content = re.sub(r'case 値:', 'case 値2:', content, count=1)
    content = re.sub(r'/\* 値の場合の処理 \*/', '/* 値2の場合の処理 */', content, count=1)
    content = re.sub(r'case 値:', 'case 値3:', content, count=1)
    content = re.sub(r'/\* 値の場合の処理 \*/', '/* 値3の場合の処理 */', content, count=1)
    content = re.sub(r'break;\n\n```', 'break;\n}\n```', content, count=1)
    
    # 曜日判定の例の修正
    content = re.sub(r'int day = ;', 'int day = 3;', content)
    content = re.sub(r'switch \(day\)\s*\n', 'switch (day) {\n', content)
    content = re.sub(r'case :\n\s*printf\("月曜日\\n"\);', 'case 1:\n        printf("月曜日\\n");', content)
    content = re.sub(r'case :\n\s*printf\("火曜日\\n"\);', 'case 2:\n        printf("火曜日\\n");', content)
    content = re.sub(r'case :\n\s*printf\("水曜日\\n"\);', 'case 3:\n        printf("水曜日\\n");', content)
    content = re.sub(r'case :\n\s*printf\("木曜日\\n"\);', 'case 4:\n        printf("木曜日\\n");', content)
    content = re.sub(r'case :\n\s*printf\("金曜日\\n"\);', 'case 5:\n        printf("金曜日\\n");', content)
    content = re.sub(r'case :\n\s*printf\("土曜日\\n"\);', 'case 6:\n        printf("土曜日\\n");', content)
    content = re.sub(r'case :\n\s*printf\("日曜日\\n"\);', 'case 7:\n        printf("日曜日\\n");', content)
    content = re.sub(r'printf\("無効な曜日です\\n"\);', 'printf("無効な曜日です\\n");', content)
    content = re.sub(r'break;\n\n```', 'break;\n}\n```', content, count=1)
    
    # break文の重要性セクションの修正
    content = re.sub(r"int grade = '';", "int grade = 'B';", content)
    content = re.sub(r'switch \(grade\)\s*\n', 'switch (grade) {\n', content)
    content = re.sub(r'printf\("優秀\\n"\);', 'printf("優秀\\n");', content)
    content = re.sub(r"case '':", "case 'B':", content)
    content = re.sub(r'printf\("良好\\n"\);', 'printf("良好\\n");', content)
    content = re.sub(r'printf\("普通\\n"\);', 'printf("普通\\n");', content)
    content = re.sub(r'printf\("要努力\\n"\);', 'printf("要努力\\n");', content)
    content = re.sub(r'break;\n\n/\* grade が', 'break;\n}\n/* grade が', content)
    
    # フォールスルーセクションの修正
    content = re.sub(r'switch \(ch\)\s*\n', 'switch (ch) {\n', content)
    content = re.sub(r"case '':", "case 'u':", content)
    content = re.sub(r'printf\("母音です\\n"\);', 'printf("母音です\\n");', content)
    content = re.sub(r'printf\("子音です\\n"\);', 'printf("子音です\\n");', content)
    content = re.sub(r'break;\n\n```', 'break;\n}\n```', content)
    
    # 条件演算子セクションの修正
    content = re.sub(r'int a = , b = ;', 'int a = 10, b = 5;', content)
    content = re.sub(r'if \(a > b\)\s*\n', 'if (a > b) {\n', content)
    content = re.sub(r'else\s*\n', '} else {\n', content)
    content = re.sub(r'max = b;\n\n', 'max = b;\n}\n', content)
    
    # 代入と比較の混同セクションの修正
    content = re.sub(r'int x = ;', 'int x = 5;', content)
    
    # switch文のbreak忘れセクションの修正
    content = re.sub(r'switch \(vale\)\s*\n', 'switch (value) {\n', content)
    content = re.sub(r'case :\n\s*printf\("です\\n"\);', 'case 1:\n        printf("1です\\n");', content)
    content = re.sub(r'case :\n\s*printf\("です\\n"\);', 'case 2:\n        printf("2です\\n");', content)
    content = re.sub(r'switch \(vale\)\s*\n', 'switch (value) {\n', content)
    content = re.sub(r'case :\n\s*printf\("です\\n"\);', 'case 1:\n        printf("1です\\n");', content)
    content = re.sub(r'case :\n\s*printf\("です\\n"\);', 'case 2:\n        printf("2です\\n");', content)
    content = re.sub(r'break;\n\n```', 'break;\n}\n```', content)
    
    # 複雑な条件式での括弧不足セクションの修正
    content = re.sub(r'if \(a == \|\| b == && c == \)', 'if (a == 1 || b == 2 && c == 3)', content)
    content = re.sub(r'if \(\(a == \) \|\| \(b == && c == \)\)', 'if ((a == 1) || (b == 2 && c == 3))', content)
    
    # 演習課題セクションの修正
    content = re.sub(r'(\d)\. \*\*', r'\1. **', content)
    content = re.sub(r'点数を入力してA〜の成績', '点数を入力してA〜Fの成績', content)
    content = re.sub(r'条件: で割り切れる、ただしで割り切れる年は平年、で割り切れる年はうるう年', 
                    '条件: 4で割り切れる、ただし100で割り切れる年は平年、400で割り切れる年はうるう年', content)
    content = re.sub(r'MI計算', 'BMI計算', content)
    content = re.sub(r'2つの辺の長さ', '3つの辺の長さ', content)
    
    # よくある間違いセクションの修正
    content = re.sub(r'### \. ', '### 1. ', content)
    content = re.sub(r'if \(condition\);\n\n', 'if (condition);\n{\n', content)
    content = re.sub(r'printf\("常に実行される\\n"\);', 'printf("常に実行される\\n");', content)
    content = re.sub(r'if \(condition\)\s*\n', 'if (condition) {\n', content)
    content = re.sub(r'printf\("条件が真の場合のみ実行\\n"\);', 'printf("条件が真の場合のみ実行\\n");', content)
    content = re.sub(r'/\* 条件に関係なく実行 \*/\n\n', '/* 条件に関係なく実行 */\n}\n', content)
    content = re.sub(r'printf\("条件が真の場合のみ実行\\n"\);\n\n```', 'printf("条件が真の場合のみ実行\\n");\n}\n```', content)
    
    # switch文セクションの最終修正
    content = re.sub(r'### \. switch文でのbreak忘れ', '### 2. switch文でのbreak忘れ', content)
    
    # 複雑な条件式セクションの修正
    content = re.sub(r'### \. 複雑な条件式での括弧不足', '### 3. 複雑な条件式での括弧不足', content)
    
    # nをすべて\nに置換（printf文内）
    content = re.sub(r'printf\("([^"]*?)n"\)', lambda m: 'printf("' + m.group(1) + '\\n")', content)
    
    # operautor_other -> operator_other
    content = re.sub(r'operautor_other', 'operator_other', content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed control-if/README.md")

def fix_advanced_readme(readme_path):
    """advanced章のREADME.mdを修正"""
    print("Fixing advanced/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # math_tils -> math_utils, string_tils -> string_utils
    content = re.sub(r'math_tils', 'math_utils', content)
    content = re.sub(r'string_tils', 'string_utils', content)
    
    # 関数名の修正
    content = re.sub(r'to_uuppercase', 'to_uppercase', content)
    content = re.sub(r'topper', 'toupper', content)
    
    # main.cの数値修正
    content = re.sub(r'printf\("=== 数学関数テスト ===n"\);', 'printf("=== 数学関数テスト ===\\n");', content)
    content = re.sub(r'printf\("add\(, \) = %d\\n", add\(, \)\);', 'printf("add(5, 3) = %d\\n", add(5, 3));', content)
    content = re.sub(r'printf\("multiply\(, \) = %d\\n", multiply\(, \)\);', 'printf("multiply(4, 7) = %d\\n", multiply(4, 7));', content)
    content = re.sub(r'printf\("power\(, \) = %ldn", power\(, \)\);', 'printf("power(2, 10) = %ld\\n", power(2, 10));', content)
    content = re.sub(r'printf\("n=== 文字列関数テスト ===n"\);', 'printf("\\n=== 文字列関数テスト ===\\n");', content)
    content = re.sub(r'return ;', 'return 0;', content)
    
    # math_utils.hの定数修正
    content = re.sub(r'#define PI \.99', '#define PI 3.14159', content)
    content = re.sub(r'#define   \.', '#define E 2.71828', content)
    
    # 関数の波括弧と数値の修正
    content = re.sub(r'int add\(int a, int b\)\n\{\n\n    return a \+ b;\n\n', 'int add(int a, int b)\n{\n    return a + b;\n}\n', content)
    content = re.sub(r'int multiply\(int a, int b\)\n\{\n\n    return a \* b;\n\n', 'int multiply(int a, int b)\n{\n    return a * b;\n}\n', content)
    
    # power関数の修正
    content = re.sub(r'long power\(int base, int exponent\)\n\n    long result = ;', 'long power(int base, int exponent)\n{\n    long result = 1;', content)
    content = re.sub(r'if \(exponent < \) return ;', 'if (exponent < 0) return 0;', content)
    content = re.sub(r'for \(i = ; i < exponent; i\+\+\)\s*\n        result \*= base;', 'for (i = 0; i < exponent; i++) {\n        result *= base;\n    }', content)
    content = re.sub(r'return result;\n\n', 'return result;\n}\n', content)
    
    # average関数の修正
    content = re.sub(r'double average\(int arr\[\], int size\)\n\n    int sum = ;', 'double average(int arr[], int size)\n{\n    int sum = 0;', content)
    content = re.sub(r'if \(size <= \) return \.;', 'if (size <= 0) return 0.0;', content)
    content = re.sub(r'for \(i = ; i < size; i\+\+\)\s*\n        sum \+= arr\[i\];', 'for (i = 0; i < size; i++) {\n        sum += arr[i];\n    }', content)
    content = re.sub(r'return \(double\)sum / size;\n\n```', 'return (double)sum / size;\n}\n```', content)
    
    # to_uppercase関数の修正
    content = re.sub(r'void to_uppercase\(char \*str\)\n\{\n\n    if', 'void to_uppercase(char *str)\n{\n    if', content)
    content = re.sub(r'while \(\*str\)\s*\n        \*str = toupper', 'while (*str) {\n        *str = toupper', content)
    content = re.sub(r'str\+\+;\n    \n\n', 'str++;\n    }\n}\n', content)
    
    # to_lowercase関数の修正
    content = re.sub(r'void to_lowercase\(char \*str\)\n\{\n\n    if', 'void to_lowercase(char *str)\n{\n    if', content)
    content = re.sub(r'while \(\*str\)\s*\n        \*str = tolower', 'while (*str) {\n        *str = tolower', content)
    content = re.sub(r'str\+\+;\n    \n\n', 'str++;\n    }\n}\n', content)
    
    # reverse_string関数の修正
    content = re.sub(r'void reverse_string\(char \*str\)\n\{\n\n    int len', 'void reverse_string(char *str)\n{\n    int len', content)
    content = re.sub(r'for \(i = ; i < len / ; i\+\+\)\s*\n        temp', 'for (i = 0; i < len / 2; i++) {\n        temp', content)
    content = re.sub(r'str\[len -  - i\]', 'str[len - 1 - i]', content)
    content = re.sub(r'= temp;\n    \n\n', '= temp;\n    }\n}\n', content)
    
    # count_words関数の修正
    content = re.sub(r'int count_words\(const char \*str\)\n\{\n\n    int count = ;', 'int count_words(const char *str)\n{\n    int count = 0;', content)
    content = re.sub(r'int in_word = ;', 'int in_word = 0;', content)
    content = re.sub(r'if \(str == NULL\) return ;', 'if (str == NULL) return 0;', content)
    content = re.sub(r'while \(\*str\)\s*\n        if \(isspace', 'while (*str) {\n        if (isspace', content)
    content = re.sub(r'in_word = ;\n         else if', 'in_word = 0;\n        } else if', content)
    content = re.sub(r'in_word = ;\n            count\+\+;', 'in_word = 1;\n            count++;', content)
    content = re.sub(r'str\+\+;\n    \n    \n    return count;\n\n', 'str++;\n    }\n    \n    return count;\n}\n', content)
    
    # trim_whitespace関数の修正
    content = re.sub(r'char\* trim_whitespace\(char \*str\)\n\n    char \*end;', 'char* trim_whitespace(char *str)\n{\n    char *end;', content)
    content = re.sub(r"if \(\*str == ''\) return str;", "if (*str == '\\0') return str;", content)
    
    # GLOBALS_Hのタイプミス修正
    content = re.sub(r'GLOALS_H', 'GLOBALS_H', content)
    
    # プリプロセッサマクロの修正
    content = re.sub(r'SA_R', 'SAFE_FREE', content)
    content = re.sub(r'MALLOC_CHCK', 'MALLOC_CHECK', content)
    content = re.sub(r'DUG', 'DEBUG', content)
    content = re.sub(r'RROR_XIT', 'ERROR_EXIT', content)
    
    # test_program.cの数値修正
    content = re.sub(r'printf\("add\(, \) = %d\\n", add\(, \)\);', 'printf("add(5, 3) = %d\\n", add(5, 3));', content)
    content = re.sub(r'printf\("power\(, \) = %ldn", power\(, \)\);', 'printf("power(2, 3) = %ld\\n", power(2, 3));', content)
    content = re.sub(r'int numbers\[\] = , , , , ;', 'int numbers[] = {10, 20, 30, 40, 50};', content)
    
    # nをすべて\nに置換（printf文内）
    content = re.sub(r'printf\("([^"]*?)n"\)', lambda m: 'printf("' + m.group(1) + '\\n")', content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed advanced/README.md")

def fix_function_pointers_readme(readme_path):
    """function-pointers章のREADME.mdを修正"""
    print("Fixing function-pointers/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # forループの初期値修正
    content = re.sub(r'for \(i = ; i < men_size; i\+\+\)', 'for (i = 0; i < menu_size; i++)', content)
    content = re.sub(r'for \(i = ; i < size; i\+\+\)', 'for (i = 0; i < size; i++)', content)
    
    # 関数呼び出しの引数修正
    content = re.sub(r'operation\(, \)', 'operation(10, 5)', content)
    content = re.sub(r'math_fnc\(, \)', 'math_func(5.0, 3.0)', content)
    
    # 数値の欠落修正
    content = re.sub(r'num - ;', 'num - 1;', content)
    content = re.sub(r'= ;', '= 0;', content)
    
    # その他の修正
    content = re.sub(r'men_size', 'menu_size', content)
    content = re.sub(r'math_fnc', 'math_func', content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed function-pointers/README.md")

def fix_strings_readme(readme_path):
    """strings章のREADME.mdを修正"""
    print("Fixing strings/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 初期値の修正
    content = re.sub(r'int count = ;', 'int count = 0;', content)
    content = re.sub(r'int item_count = ;', 'int item_count = 0;', content)
    content = re.sub(r'int stdent_count = ;', 'int student_count = 0;', content)
    
    # forループの初期値修正
    content = re.sub(r'for \(i = ; i < count; i\+\+\)', 'for (i = 0; i < count; i++)', content)
    content = re.sub(r'for \(i = ; i < [^;]+; i\+\+\)', 'for (i = 0; i < count; i++)', content)
    
    # タイポの修正
    content = re.sub(r'stdent', 'student', content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed strings/README.md")

def fix_control_loop_readme(readme_path):
    """control-loop章のREADME.mdを修正"""
    print("Fixing control-loop/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 初期値の修正
    content = re.sub(r'int count = ;', 'int count = 0;', content)
    
    # forループの修正
    content = re.sub(r'for \(i = ; i <= ; i\+\+\)', 'for (i = 1; i <= 10; i++)', content)
    content = re.sub(r'for \(i = ; i < [^;]*; i\+\+\)', 'for (i = 0; i < count; i++)', content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed control-loop/README.md")

def fix_pointers_readme(readme_path):
    """pointers章のREADME.mdを修正"""
    print("Fixing pointers/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # forループの初期値修正
    content = re.sub(r'for \(i = ; i < size; i\+\+\)', 'for (i = 0; i < size; i++)', content)
    
    # 変数の初期値修正
    content = re.sub(r'int search_target = ;', 'int search_target = 30;', content)
    content = re.sub(r'int a = , b = , c = , d = ;', 'int a = 10, b = 20, c = 30, d = 40;', content)
    
    # ポインタ配列の修正
    content = re.sub(r'\*ptr_array\[\] = ;', '*ptr_array[4] = {&a, &b, &c, &d};', content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed pointers/README.md")

def main():
    """メイン処理"""
    # プロジェクトのルートディレクトリを取得
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    # control-if/README.mdを修正
    control_if_readme = os.path.join(project_root, "src", "control-if", "README.md")
    if os.path.exists(control_if_readme):
        fix_control_if_readme(control_if_readme)
    else:
        print(f"Warning: {control_if_readme} not found")
    
    # advanced/README.mdを修正
    advanced_readme = os.path.join(project_root, "src", "advanced", "README.md")
    if os.path.exists(advanced_readme):
        fix_advanced_readme(advanced_readme)
    else:
        print(f"Warning: {advanced_readme} not found")
    
    # function-pointers/README.mdを修正
    function_pointers_readme = os.path.join(project_root, "src", "function-pointers", "README.md")
    if os.path.exists(function_pointers_readme):
        fix_function_pointers_readme(function_pointers_readme)
    else:
        print(f"Warning: {function_pointers_readme} not found")
    
    # strings/README.mdを修正
    strings_readme = os.path.join(project_root, "src", "strings", "README.md")
    if os.path.exists(strings_readme):
        fix_strings_readme(strings_readme)
    else:
        print(f"Warning: {strings_readme} not found")
    
    # control-loop/README.mdを修正
    control_loop_readme = os.path.join(project_root, "src", "control-loop", "README.md")
    if os.path.exists(control_loop_readme):
        fix_control_loop_readme(control_loop_readme)
    else:
        print(f"Warning: {control_loop_readme} not found")
    
    # pointers/README.mdを修正
    pointers_readme = os.path.join(project_root, "src", "pointers", "README.md")
    if os.path.exists(pointers_readme):
        fix_pointers_readme(pointers_readme)
    else:
        print(f"Warning: {pointers_readme} not found")
    
    print("\nFixed all README.md files with missing values and typos!")

if __name__ == "__main__":
    main()