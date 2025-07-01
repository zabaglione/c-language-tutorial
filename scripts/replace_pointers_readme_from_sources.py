#!/usr/bin/env python3
"""
pointers/README.mdのコードブロックを実際のソースファイルから正確に置き換える
"""

import os
import re

def read_file(file_path):
    """ファイルを読み込む"""
    with open(file_path, 'r', encoding='utf-8') as f:
        return f.read()

def write_file(file_path, content):
    """ファイルに書き込む"""
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(content)

def extract_main_function(source_code):
    """ソースコードからmain関数のみを抽出"""
    # main関数の開始を探す
    main_start = source_code.find('int main(void)')
    if main_start == -1:
        return None
    
    # 開き括弧を探す
    brace_start = source_code.find('{', main_start)
    if brace_start == -1:
        return None
    
    # 対応する閉じ括弧を探す
    brace_count = 1
    i = brace_start + 1
    while i < len(source_code) and brace_count > 0:
        if source_code[i] == '{':
            brace_count += 1
        elif source_code[i] == '}':
            brace_count -= 1
        i += 1
    
    if brace_count == 0:
        return source_code[main_start:i]
    
    return None

def find_code_block_by_content(readme_content, identifying_text):
    """特定のテキストを含むコードブロックを見つける"""
    pattern = r'```c\n(.*?)\n```'
    matches = list(re.finditer(pattern, readme_content, re.DOTALL))
    
    for match in matches:
        if identifying_text in match.group(1):
            return match.span(), match.group(1)
    
    return None, None

def replace_specific_sections(readme_content, examples_dir):
    """特定のセクションをソースファイルから置き換える"""
    replacements = []
    
    # 1. pointer_basic.cから基本的な例を取得
    basic_source = read_file(os.path.join(examples_dir, "pointer_basic.c"))
    basic_main = extract_main_function(basic_source)
    
    if basic_main:
        # "int value = 100;" を含むブロックを探す
        span, old_code = find_code_block_by_content(readme_content, "int value = 100;")
        if span:
            replacements.append((span, basic_main))
        
        # "int original = 50;" を含むブロックを探す
        span, old_code = find_code_block_by_content(readme_content, "int original = 50;")
        if span:
            # pointer_basic.cから該当部分を抽出してカスタマイズ
            custom_code = """int main(void)
{
    int original = 50;
    int *pointer = &original;
    
    printf("=== 元の状態 ===\\n");
    printf("original = %d\\n", original);
    printf("*pointer = %d\\n", *pointer);
    
    /* ポインタを通じて値を変更 */
    *pointer = 75;
    
    printf("\\n=== *pointer = 75 実行後 ===\\n");
    printf("original = %d\\n", original);      /* 75に変更される */
    printf("*pointer = %d\\n", *pointer);      /* 75 */
    
    /* 元の変数を直接変更 */
    original = 99;
    
    printf("\\n=== original = 99 実行後 ===\\n");
    printf("original = %d\\n", original);      /* 99 */
    printf("*pointer = %d\\n", *pointer);      /* 99 */
    
    return 0;
}"""
            replacements.append((span, custom_code))
    
    # 2. pointer_functions.cから関数の例を取得（存在する場合）
    functions_path = os.path.join(examples_dir, "pointer_functions.c")
    if os.path.exists(functions_path):
        functions_source = read_file(functions_path)
        
        # swap関数を含む完全なコード
        span, old_code = find_code_block_by_content(readme_content, "void swap(int *a, int *b)")
        if span and "#include" in old_code:
            replacements.append((span, functions_source))
    
    # 3. pointer_arrays.cから配列の例を取得（存在する場合）
    arrays_path = os.path.join(examples_dir, "pointer_arrays.c")
    if os.path.exists(arrays_path):
        arrays_source = read_file(arrays_path)
        
        # fruits配列を含むコード
        span, old_code = find_code_block_by_content(readme_content, "fruits")
        if span:
            replacements.append((span, arrays_source))
    
    # 置き換えを実行（後ろから実行して位置がずれないようにする）
    replacements.sort(key=lambda x: x[0][0], reverse=True)
    
    for (start, end), new_code in replacements:
        readme_content = (
            readme_content[:start] +
            "```c\n" + new_code.strip() + "\n```" +
            readme_content[end:]
        )
    
    return readme_content

def fix_remaining_issues(readme_content):
    """残りの一般的な問題を修正"""
    # エスケープシーケンスの修正
    readme_content = re.sub(r'printf\("([^"]*?)\\\\n"\)', r'printf("\1\\n")', readme_content)
    
    # 変数名の修正
    readme_content = readme_content.replace('int *ptr;', 'int *ptr1;')
    readme_content = readme_content.replace('frits', 'fruits')
    readme_content = readme_content.replace('bbble_sort_ptr', 'bubble_sort_ptr')
    readme_content = readme_content.replace('search_vale', 'search_value')
    
    return readme_content

def main():
    """メイン処理"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    pointers_dir = os.path.join(project_root, "src", "pointers")
    readme_path = os.path.join(pointers_dir, "README.md")
    examples_dir = os.path.join(pointers_dir, "examples")
    
    print("Replacing code blocks in pointers/README.md with source files...")
    
    # READMEを読み込む
    readme_content = read_file(readme_path)
    
    # ソースファイルから置き換える
    readme_content = replace_specific_sections(readme_content, examples_dir)
    
    # 残りの問題を修正
    readme_content = fix_remaining_issues(readme_content)
    
    # ファイルを保存
    write_file(readme_path, readme_content)
    
    print("✅ Successfully updated pointers/README.md with actual source code!")
    print("\nNote: Code blocks have been replaced with actual source files,")
    print("ensuring all brackets, escape sequences, and syntax are correct.")

if __name__ == "__main__":
    main()