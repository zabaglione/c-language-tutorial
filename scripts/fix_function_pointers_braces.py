#!/usr/bin/env python3
"""
function-pointers/README.mdの欠落した括弧を修正
"""

import os
import re

def fix_function_braces(content):
    """関数定義の欠落した括弧を修正"""
    
    # 1. 関数定義で開き括弧が欠落しているパターンを修正
    patterns = [
        # void greet(void) の後に { が欠落
        (r'(void greet\(void\)\s*\n)\s*\n(\s*printf)', r'\1{\n\2'),
        
        # int multiply の後に { が欠落
        (r'(int multiply\(int x, int y\)\s*\n)\s*\n(\s*return)', r'\1{\n\2'),
        
        # 関数の終わりで } が欠落
        (r'(printf\("こんにちは！n"\);)\s*\n\n(int multiply)', r'\1\n}\n\n\2'),
        (r'(return x \* y;)\s*\n\n(double divide)', r'\1\n}\n\n\2'),
        
        # double divide の後に { が欠落
        (r'(double divide\(double a, double b\))\s*\n(\s*if)', r'\1\n{\n\2'),
        
        # divide関数の終わりで } が欠落
        (r'(return \.;)\s*\n\n(int main)', r'\1\n}\n\n\2'),
        
        # main関数の終わりで } が欠落
        (r'(return 0;)\s*\n\n(```)', r'\1\n}\n\2'),
        
        # 演算関数群の修正
        (r'double add_op\(double a, double b\)\s*return', r'double add_op(double a, double b) { return'),
        (r'double sb_op\(double a, double b\)\s*return', r'double sub_op(double a, double b) { return'),
        (r'double ml_op\(double a, double b\)\s*return', r'double mul_op(double a, double b) { return'),
        (r'return a \+ b;\s*\n(double sub_op)', r'return a + b; }\n\1'),
        (r'return a - b;\s*\n(double mul_op)', r'return a - b; }\n\1'),
        (r'return a \* b;\s*\n(double div_op)', r'return a * b; }\n\1'),
        
        # div_op関数の { が欠落
        (r'(double div_op\(double a, double b\))\s*\n\n(\s*if)', r'\1\n{\n\2'),
        
        # calculate関数の { が欠落
        (r'(double calculate\(.*?\))\s*\n\n(\s*return operation)', r'\1\n{\n\2'),
        (r'(return operation\(a, b\);)\s*\n\n(\s*/\* 演算子)', r'\1\n}\n\n\2'),
        
        # get_operation関数の { が欠落
        (r'(double \(\*get_operation\(char op\)\)\(double, double\))\s*\n\n(\s*switch)', r'\1\n{\n\2'),
        
        # main関数の { が欠落（計算機システム）
        (r'(int main\(void\))\s*\n\{\s*\n\n(\s*double num1)', r'\1\n{\n\2'),
        
        # メニューシステムの関数修正
        (r'(void show_profile\(void\))\s*\n\{\s*\n\n(\s*printf)', r'\1\n{\n\2'),
        (r'(void show_settings\(void\))\s*\n\{\s*\n\n(\s*printf)', r'\1\n{\n\2'),
        (r'(void show_help\(void\))\s*\n\{\s*\n\n(\s*printf)', r'\1\n{\n\2'),
        (r'(void exit_app\(void\))\s*\n\{\s*\n\n(\s*printf)', r'\1\n{\n\2'),
        
        # printf文の後の } 追加
        (r'(printf\("職業: エンジニアnn"\);)\s*\n\n(void show_settings)', r'\1\n}\n\n\2'),
        (r'(printf\("通知: ONnn"\);)\s*\n\n(void show_help)', r'\1\n}\n\n\2'),
        (r'(printf\("\. 処理が実行されますnn"\);)\s*\n\n(void exit_app)', r'\1\n}\n\n\2'),
        (r'(printf\("アプリケーションを終了します。n"\);)\s*\n\n(/\* メニュー項目)', r'\1\n}\n\n\2'),
        
        # struct MenuItem の修正
        (r'strct MenuItem\s*\n', r'struct MenuItem {\n'),
        (r'(void \(\*handler\)\(void\);.*?)\n;', r'\1\n};'),
        
        # menu配列の修正
        (r'strct MenuItem men\[\]', r'struct MenuItem menu[]'),
        (r'(struct MenuItem menu\[\] =)\s*\n', r'\1 {\n'),
        (r'("終了", exit_app)\s*\n(\s*;)', r'\1\n    \2'),
        
        # main関数の最後の } 修正
        (r'(return 0;)\s*\n\n(```)', r'\1\n}\n\2'),
    ]
    
    for pattern, replacement in patterns:
        content = re.sub(pattern, replacement, content)
    
    return content

def fix_missing_values(content):
    """欠落した値を修正"""
    replacements = [
        # printf内の改行を修正
        (r'printf\("([^"]*?)n"\)', r'printf("\1\\n")'),
        (r'printf\("([^"]*?)nn"\)', r'printf("\1\\n\\n")'),
        
        # 数値の欠落を修正
        (r'printf\("年齢: 歳', r'printf("年齢: 30歳'),
        (r'printf\("%d\. %s\\n", i \+ , men', r'printf("%d. %s\\n", i + 1, menu'),
        (r'if \(scanf\("%d", &choice\) == ', r'if (scanf("%d", &choice) == 1'),
        (r'&& choice >= ', r'&& choice >= 1'),
        (r'menu\[choice - \]\.handler', r'menu[choice - 1].handler'),
        (r'printf\("乗算: %d\\n", math_func\(5\.0, 3\.0\)\)', r'printf("乗算: %d\\n", math_func(5, 3))'),
        (r'printf\("除算: %\.fn", calc_fnc\(\., \.\)\)', r'printf("除算: %.2f\\n", calc_func(10.0, 3.0))'),
        (r'multiply\(, \)', r'multiply(5, 3)'),
        (r'divide\(\., \.\)', r'divide(10.0, 3.0)'),
        (r'printf\("直接呼び出し: %d\\n", \(\*math_func\)\(, \)\)', r'printf("直接呼び出し: %d\\n", (*math_func)(4, 6))'),
        (r'printf\("間接呼び出し: %d\\n", math_func\(5\.0, 3\.0\)\)', r'printf("間接呼び出し: %d\\n", math_func(7, 2))'),
        (r'if \(b != \.\)', r'if (b != 0.0)'),
        (r'return \.;', r'return 0.0;'),
        (r'printf\("\. メニューから項目を選択n"\)', r'printf("1. メニューから項目を選択\\n")'),
        (r'printf\("\. 処理が実行されますnn"\)', r'printf("2. 処理が実行されます\\n\\n")'),
        
        # 関数名の修正
        (r'greeting_fnc', r'greeting_func'),
        (r'calc_fnc', r'calc_func'),
        (r'sb_op', r'sub_op'),
        (r'ml_op', r'mul_op'),
        
        # 配列名の修正
        (r'men\[', r'menu['),
        (r'sizeof\(men\)', r'sizeof(menu)'),
        
        # char name[]の修正
        (r'char name\[\];', r'char name[50];'),
    ]
    
    for pattern, replacement in replacements:
        content = re.sub(pattern, replacement, content)
    
    return content

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    readme_path = os.path.join(project_root, "src", "function-pointers", "README.md")
    
    print("Fixing function-pointers/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 括弧を修正
    content = fix_function_braces(content)
    
    # 欠落した値を修正
    content = fix_missing_values(content)
    
    # 特定のコードブロックを完全に置き換える
    # 関数ポインタの基本文法の例
    basic_syntax = '''```c
#include <stdio.h>

/* さまざまな関数 */
void greet(void)
{
    printf("こんにちは！\\n");
}

int multiply(int x, int y)
{
    return x * y;
}

double divide(double a, double b)
{
    if (b != 0.0) {
        return a / b;
    }
    return 0.0;
}

int main(void)
{
    /* さまざまな関数ポインタの宣言 */
    void (*greeting_func)(void);           /* 引数なし、戻り値なし */
    int (*math_func)(int, int);            /* int引数2つ、int戻り値 */
    double (*calc_func)(double, double);   /* double引数2つ、double戻り値 */
    
    /* 関数ポインタの初期化 */
    greeting_func = greet;
    math_func = multiply;
    calc_func = divide;
    
    /* 関数ポインタを使った呼び出し */
    greeting_func();                             /* greet()を呼び出し */
    printf("乗算: %d\\n", math_func(5, 3));      /* multiply(5, 3)を呼び出し */
    printf("除算: %.2f\\n", calc_func(10.0, 3.0)); /* divide(10.0, 3.0)を呼び出し */
    
    /* 2つの異なる呼び出し方法 */
    printf("直接呼び出し: %d\\n", (*math_func)(4, 6));  /* (*ptr)(args) */
    printf("間接呼び出し: %d\\n", math_func(7, 2));     /* ptr(args) */
    
    return 0;
}
```'''
    
    # 基本文法セクションを探して置き換え
    pattern = r'(#### 関数ポインタの基本文法\s*\n\s*)(```c.*?```)'
    match = re.search(pattern, content, re.DOTALL)
    if match:
        content = content[:match.start(2)] + basic_syntax + content[match.end(2):]
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed function-pointers/README.md successfully!")

if __name__ == "__main__":
    main()