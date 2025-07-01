#!/usr/bin/env python3
"""
pointers/README.mdの欠落した括弧を修正
"""

import os
import re

def fix_function_braces(content):
    """関数定義の欠落した括弧を修正"""
    
    # 1. main関数の開き括弧を修正
    content = re.sub(r'(int main\(void\)\s*\n)\s*\n(\s*int)', r'\1{\n\2', content)
    content = re.sub(r'(int main\(void\)\s*\n)\s*\n(\s*char)', r'\1{\n\2', content)
    content = re.sub(r'(int main\(void\)\s*\n)\s*\n(\s*/\*)', r'\1{\n\2', content)
    
    # 2. 他の関数定義の開き括弧を修正
    patterns = [
        # find_max_ptr関数
        (r'(int\* find_max_ptr\(int arr\[\], int size\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
        
        # search_value関数（タイポも修正）
        (r'int\* search_vale\(int arr\[\], int size, int target\)', 
         r'int* search_value(int arr[], int size, int target)'),
        (r'(int\* search_value\(int arr\[\], int size, int target\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
        
        # string_length関数
        (r'(int string_length\(char \*str\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
        
        # string_copy関数
        (r'(void string_copy\(char \*dest, char \*src\)\s*\n)\s*\n(\s*while)', r'\1{\n\2'),
        
        # string_concat関数
        (r'(void string_concat\(char \*dest, char \*src\)\s*\n)\s*\n(\s*/\*)', r'\1{\n\2'),
        
        # reverse_array関数
        (r'(void reverse_array\(int \*arr, int size\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
        
        # rotate_right関数
        (r'(void rotate_right\(int \*arr, int size\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
        
        # bubble_sort_ptr関数（タイポも修正）
        (r'void bbble_sort_ptr\(', r'void bubble_sort_ptr('),
        (r'(void bubble_sort_ptr\(int \*arr, int size\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
        
        # compare_arrays関数（パラメータ名も修正）
        (r'int compare_arrays\(int \*arr, int \*arr, int size\)', 
         r'int compare_arrays(int *arr1, int *arr2, int size)'),
        (r'(int compare_arrays\(int \*arr1, int \*arr2, int size\)\s*\n)\s*\n(\s*int)', r'\1{\n\2'),
    ]
    
    for pattern, replacement in patterns:
        content = re.sub(pattern, replacement, content)
    
    # 3. 複数行のループ・条件文に括弧を追加
    # for文
    content = re.sub(
        r'(for \([^)]+\)\s*\n)(\s*)(if|printf|[^{].*?)(\n)(\s*)(.*?)(\n)',
        r'\1\2{\n\2    \3\4\2    \6\n\2}\7',
        content
    )
    
    # while文
    content = re.sub(
        r'(while \([^)]+\)\s*\n)(\s*)(\*dest = \*src;)\n(\s*)(dest\+\+;)\n(\s*)(src\+\+;)',
        r'\1\2{\n\2    \3\n\2    \5\n\2    \7\n\2}',
        content
    )
    
    # if文
    content = re.sub(
        r'(if \([^)]+\)\s*\n)(\s*)(printf.*?)\n(\s*)(.*?;)\n(\s*)(else)',
        r'\1\2{\n\2    \3\n\2    \5\n\2}\n\6\7',
        content
    )
    
    return content

def fix_missing_values(content):
    """欠落した値を修正"""
    replacements = [
        # 配列の初期化
        (r'char \*frits\[\] =\s*\n\s*"Apple",', r'char *fruits[] = {\n        "Apple",'),
        (r'"anana",', r'"Banana",'),
        (r'"lderberry"\s*\n\s*;', r'"Elderberry"\n    };'),
        
        # printf内の改行
        (r'printf\("([^"]*?)n"\)', r'printf("\1\\n")'),
        (r'printf\("([^"]*?)nn"\)', r'printf("\1\\n\\n")'),
        
        # 数値の欠落
        (r'for \(i = 0; i < ; i\+\+\)', r'for (i = 0; i < 5; i++)'),
        (r'for \(i = 0; i < 10; i\+\+\)', r'for (i = 0; i < 5; i++)'),  # fruits配列のサイズ
        (r'i \+ ,', r'i + 1,'),
        (r'size - ;', r'size - 1;'),
        (r'i > ;', r'i > 0;'),
        (r'見2つかりました', r'見つかりました'),
        (r'見2つかりませんでした', r'見つかりませんでした'),
        
        # 文字列リテラル
        (r"''", r"'\\0'"),
        
        # ポインタ変数名
        (r'int \*ptr;', r'int *ptr1;'),
        (r'int \*ptr;', r'int *ptr2;'),
        (r'\*ptr > \*ptr\)', r'*ptr1 > *ptr2)'),
        (r'temp = \*ptr;', r'temp = *ptr1;'),
        (r'\*ptr = \*ptr;', r'*ptr1 = *ptr2;'),
        (r'\*ptr = temp;', r'*ptr2 = temp;'),
        
        # compare_arrays内の変数名
        (r'\*\(arr \+ i\) != \*\(arr \+ i\)', r'*(arr1 + i) != *(arr2 + i)'),
    ]
    
    for pattern, replacement in replacements:
        content = re.sub(pattern, replacement, content)
    
    return content

def ensure_closing_braces(content):
    """関数の閉じ括弧を確保"""
    # コードブロック内でブレースカウントを確認
    lines = content.split('\n')
    fixed_lines = []
    in_code_block = False
    brace_count = 0
    
    for i, line in enumerate(lines):
        if '```c' in line:
            in_code_block = True
            brace_count = 0
        elif '```' in line and in_code_block:
            if brace_count > 0:
                # 閉じ括弧が不足している場合は追加
                fixed_lines.append('}' * brace_count)
            in_code_block = False
            brace_count = 0
        elif in_code_block:
            brace_count += line.count('{') - line.count('}')
        
        fixed_lines.append(line)
    
    return '\n'.join(fixed_lines)

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    readme_path = os.path.join(project_root, "src", "pointers", "README.md")
    
    print("Fixing pointers/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 括弧を修正
    content = fix_function_braces(content)
    
    # 欠落した値を修正
    content = fix_missing_values(content)
    
    # 閉じ括弧を確保
    content = ensure_closing_braces(content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed pointers/README.md successfully!")

if __name__ == "__main__":
    main()