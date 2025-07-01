#!/usr/bin/env python3
"""
main_textbook.mdファイルの欠落した値やエラーを修正するスクリプト
"""

import os
import re
import sys

def fix_main_textbook(file_path):
    """main_textbook.mdファイルを修正"""
    print("Fixing main_textbook.md...")
    
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 共通の修正
    # エスケープシーケンスの修正（printf文内のnを\nに）
    content = re.sub(r'printf\("([^"]*?)n"\)', lambda m: 'printf("' + m.group(1) + '\\n")', content)
    
    # control-if章の修正
    content = re.sub(r'int a = , b = ;', 'int a = 5, b = 3;', content)
    content = re.sub(r'int age = ;', 'int age = 25;', content)
    content = re.sub(r'int income = ;', 'int income = 300000;', content)
    content = re.sub(r'if \(age >= && income >= \)', 'if (age >= 20 && income >= 200000)', content)
    content = re.sub(r'if \(age < \|\| age > \)', 'if (age < 6 || age > 65)', content)
    content = re.sub(r'if \(!\(age >= \)\)', 'if (!(age >= 18))', content)
    content = re.sub(r'printf\("歳未満です', 'printf("18歳未満です', content)
    content = re.sub(r'int day = ;', 'int day = 3;', content)
    content = re.sub(r'int x = ;', 'int x = 5;', content)
    content = re.sub(r'operautor_other', 'operator_other', content)
    
    # switch文の修正
    content = re.sub(r'switch \(変数または式\)\s*\n', 'switch (変数または式) {\n', content)
    content = re.sub(r'case 値:', 'case 値1:', content, count=1)
    content = re.sub(r'switch \(day\)\s*\n', 'switch (day) {\n', content)
    content = re.sub(r'case :\n\s*printf\("月曜日', 'case 1:\n        printf("月曜日', content)
    content = re.sub(r'case :\n\s*printf\("火曜日', 'case 2:\n        printf("火曜日', content)
    content = re.sub(r'case :\n\s*printf\("水曜日', 'case 3:\n        printf("水曜日', content)
    content = re.sub(r'case :\n\s*printf\("木曜日', 'case 4:\n        printf("木曜日', content)
    content = re.sub(r'case :\n\s*printf\("金曜日', 'case 5:\n        printf("金曜日', content)
    content = re.sub(r'case :\n\s*printf\("土曜日', 'case 6:\n        printf("土曜日', content)
    content = re.sub(r'case :\n\s*printf\("日曜日', 'case 7:\n        printf("日曜日', content)
    content = re.sub(r"int grade = '';", "int grade = 'B';", content)
    content = re.sub(r"case '':", "case 'B':", content)
    content = re.sub(r"case '':", "case 'u':", content)
    content = re.sub(r'switch \(ch\)\s*\n', 'switch (ch) {\n', content)
    content = re.sub(r'switch \(grade\)\s*\n', 'switch (grade) {\n', content)
    content = re.sub(r'switch \(vale\)\s*\n', 'switch (value) {\n', content)
    content = re.sub(r'if \(a > b\)\s*\n', 'if (a > b) {\n', content)
    content = re.sub(r'else\s*\n\s*max = b;', '} else {\n    max = b;\n}', content)
    content = re.sub(r'if \(a == \|\| b == && c == \)', 'if (a == 1 || b == 2 && c == 3)', content)
    content = re.sub(r'if \(\(a == \) \|\| \(b == && c == \)\)', 'if ((a == 1) || (b == 2 && c == 3))', content)
    
    # advanced章の修正
    content = re.sub(r'math_tils', 'math_utils', content)
    content = re.sub(r'string_tils', 'string_utils', content)
    content = re.sub(r'to_uuppercase', 'to_uppercase', content)
    content = re.sub(r'topper', 'toupper', content)
    content = re.sub(r'printf\("add\(, \) = %d\\n", add\(, \)\);', 'printf("add(5, 3) = %d\\n", add(5, 3));', content)
    content = re.sub(r'printf\("multiply\(, \) = %d\\n", multiply\(, \)\);', 'printf("multiply(4, 7) = %d\\n", multiply(4, 7));', content)
    content = re.sub(r'printf\("power\(, \) = %ldn", power\(, \)\);', 'printf("power(2, 10) = %ld\\n", power(2, 10));', content)
    content = re.sub(r'return ;', 'return 0;', content)
    content = re.sub(r'#define PI \.99', '#define PI 3.14159', content)
    content = re.sub(r'#define   \.', '#define E 2.71828', content)
    content = re.sub(r'long result = ;', 'long result = 1;', content)
    content = re.sub(r'if \(exponent < \) return ;', 'if (exponent < 0) return 0;', content)
    content = re.sub(r'for \(i = ; i < exponent; i\+\+\)', 'for (i = 0; i < exponent; i++)', content)
    content = re.sub(r'int sum = ;', 'int sum = 0;', content)
    content = re.sub(r'if \(size <= \) return \.;', 'if (size <= 0) return 0.0;', content)
    content = re.sub(r'for \(i = ; i < size; i\+\+\)', 'for (i = 0; i < size; i++)', content)
    content = re.sub(r'for \(i = ; i < len / ; i\+\+\)', 'for (i = 0; i < len / 2; i++)', content)
    content = re.sub(r'str\[len -  - i\]', 'str[len - 1 - i]', content)
    content = re.sub(r'int count = ;', 'int count = 0;', content)
    content = re.sub(r'int in_word = ;', 'int in_word = 0;', content)
    content = re.sub(r'if \(str == NULL\) return ;', 'if (str == NULL) return 0;', content)
    content = re.sub(r'in_word = ;', 'in_word = 0;', content)
    content = re.sub(r'in_word = ;\n\s*count\+\+;', 'in_word = 1;\n            count++;', content)
    content = re.sub(r"if \(\*str == ''\) return str;", "if (*str == '\\0') return str;", content)
    content = re.sub(r'GLOALS_H', 'GLOBALS_H', content)
    
    # プリプロセッサマクロの修正
    content = re.sub(r'SA_R', 'SAFE_FREE', content)
    content = re.sub(r'MALLOC_CHCK', 'MALLOC_CHECK', content)
    content = re.sub(r'DUG', 'DEBUG', content)
    content = re.sub(r'RROR_XIT', 'ERROR_EXIT', content)
    
    # その他の章の修正
    # forループの初期値修正
    content = re.sub(r'for \(i = ; i < ', 'for (i = 0; i < ', content)
    content = re.sub(r'for \(j = ; j < ', 'for (j = 0; j < ', content)
    content = re.sub(r'for \(i = ; i <= ; i\+\+\)', 'for (i = 1; i <= 10; i++)', content)
    
    # 関数呼び出しの引数修正
    content = re.sub(r'operation\(, \)', 'operation(10, 5)', content)
    content = re.sub(r'math_fnc\(, \)', 'math_func(5.0, 3.0)', content)
    
    # タイポの修正
    content = re.sub(r'stdent', 'student', content)
    content = re.sub(r'math_fnc', 'math_func', content)
    content = re.sub(r'men_size', 'menu_size', content)
    
    # 配列の修正
    content = re.sub(r'int numbers\[\] = , , , , ;', 'int numbers[] = {10, 20, 30, 40, 50};', content)
    content = re.sub(r'\*ptr_array\[\] = ;', '*ptr_array[4] = {&a, &b, &c, &d};', content)
    
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed main_textbook.md")

def main():
    """メイン処理"""
    # プロジェクトのルートディレクトリを取得
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    # main_textbook.mdのパス
    main_textbook_path = os.path.join(project_root, "docs", "main_textbook.md")
    
    if os.path.exists(main_textbook_path):
        fix_main_textbook(main_textbook_path)
    else:
        print(f"Error: {main_textbook_path} not found")
        sys.exit(1)
    
    print("\nFixed main_textbook.md with missing values and typos!")

if __name__ == "__main__":
    main()