#!/usr/bin/env python3
"""
全章のREADME.mdを実際のソースファイルと完全に同期するスクリプト
ソースファイルから直接コードをコピーすることで、括弧やエスケープシーケンスの問題を回避
"""

import os
import re
import glob

def find_source_file(examples_dir, keywords):
    """キーワードに基づいてソースファイルを見つける"""
    if not os.path.exists(examples_dir):
        return None
    
    c_files = glob.glob(os.path.join(examples_dir, "*.c"))
    
    for c_file in c_files:
        with open(c_file, 'r', encoding='utf-8') as f:
            content = f.read()
            # キーワードがすべて含まれているかチェック
            if all(keyword in content for keyword in keywords):
                return c_file
    
    return None

def extract_complete_code(source_file):
    """ソースファイルから完全なコードを抽出"""
    with open(source_file, 'r', encoding='utf-8') as f:
        return f.read().strip()

def find_main_function(source_code):
    """ソースコードからmain関数を抽出"""
    # main関数全体を抽出（複数行マッチング）
    main_match = re.search(
        r'(int\s+main\s*\([^)]*\)\s*\{[^{}]*(?:\{[^{}]*\}[^{}]*)*\})',
        source_code,
        re.DOTALL
    )
    if main_match:
        return main_match.group(1)
    return None

def find_specific_function(source_code, func_name):
    """特定の関数を抽出"""
    # 関数全体を抽出
    pattern = rf'(\w+\s+\*?\s*{func_name}\s*\([^)]*\)\s*\{{[^{{}}]*(?:\{{[^{{}}]*\}}[^{{}}]*)*\}})'
    func_match = re.search(pattern, source_code, re.DOTALL)
    if func_match:
        return func_match.group(1)
    return None

def replace_code_block(readme_content, old_code_block, new_code):
    """READMEのコードブロックを新しいコードで置き換え"""
    # コードブロック全体を置き換え
    pattern = re.escape("```c\n" + old_code_block + "\n```")
    replacement = "```c\n" + new_code + "\n```"
    return readme_content.replace("```c\n" + old_code_block + "\n```", replacement)

def sync_chapter_readme(chapter_dir, chapter_name):
    """特定の章のREADMEを同期"""
    readme_path = os.path.join(chapter_dir, "README.md")
    examples_dir = os.path.join(chapter_dir, "examples")
    
    if not os.path.exists(readme_path):
        return False
    
    print(f"\nProcessing {chapter_name}...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        readme_content = f.read()
    
    modified = False
    
    # コードブロックを見つける
    code_blocks = list(re.finditer(r'```c\n(.*?)\n```', readme_content, re.DOTALL))
    
    for block in code_blocks:
        code = block.group(1)
        
        # コードブロックの特徴的なキーワードを抽出
        keywords = []
        
        # 関数名を探す
        func_names = re.findall(r'(?:int|void|char|double|float)\s+\*?\s*(\w+)\s*\(', code)
        keywords.extend(func_names)
        
        # 特徴的な文字列を探す
        if 'swap' in code:
            keywords.append('swap')
        if 'ポインタ' in code or 'pointer' in code:
            keywords.append('ptr')
        if 'array' in code or '配列' in code:
            keywords.append('array')
        if 'string' in code or '文字列' in code:
            keywords.append('string')
        
        # printf内の特徴的な文字列
        printf_strings = re.findall(r'printf\("([^"]+)"', code)
        if printf_strings:
            # 最も特徴的な文字列を選ぶ
            for s in printf_strings[:3]:  # 最初の3つまで
                if len(s) > 5 and not s.startswith('%'):
                    keywords.append(s[:20])  # 最初の20文字まで
        
        # ソースファイルを探す
        if keywords:
            source_file = find_source_file(examples_dir, keywords[:2])  # 最初の2つのキーワードで検索
            
            if source_file:
                print(f"  Found source file: {os.path.basename(source_file)}")
                source_code = extract_complete_code(source_file)
                
                # main関数だけの場合
                if 'int main' in code and not code.strip().startswith('#include'):
                    main_func = find_main_function(source_code)
                    if main_func:
                        readme_content = replace_code_block(readme_content, code, main_func)
                        modified = True
                        print(f"    Replaced main function")
                # 完全なプログラムの場合
                elif '#include' in code:
                    readme_content = replace_code_block(readme_content, code, source_code)
                    modified = True
                    print(f"    Replaced complete program")
                # 特定の関数の場合
                else:
                    for func_name in func_names:
                        func_code = find_specific_function(source_code, func_name)
                        if func_code:
                            readme_content = replace_code_block(readme_content, code, func_code)
                            modified = True
                            print(f"    Replaced function: {func_name}")
                            break
    
    if modified:
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.write(readme_content)
        print(f"  ✅ Updated {chapter_name}/README.md")
    else:
        print(f"  ℹ️  No changes needed for {chapter_name}/README.md")
    
    return modified

def main():
    """メイン処理"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    src_dir = os.path.join(project_root, "src")
    
    chapters = [
        'introduction', 'basics-syntax', 'data-types', 'operators',
        'control-if', 'control-loop', 'arrays', 'strings',
        'functions', 'pointers', 'structures', 'function-pointers',
        'advanced', 'c23-features'
    ]
    
    print("Syncing all README files with actual source code...")
    print("=" * 60)
    
    updated_count = 0
    
    for chapter in chapters:
        chapter_dir = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_dir):
            if sync_chapter_readme(chapter_dir, chapter):
                updated_count += 1
    
    print("\n" + "=" * 60)
    print(f"✅ Sync completed! Updated {updated_count} chapters.")
    print("\nNote: This approach copies code directly from source files,")
    print("ensuring all brackets, escape sequences, and values are correct.")

if __name__ == "__main__":
    main()