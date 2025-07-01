#!/usr/bin/env python3
"""
README.md内のprintf文の改行を修正するスクリプト
"""

import os
import re

def fix_printf_newlines(content):
    """printf文内の改行を\nに修正"""
    
    # パターン1: printf("文字列の改行
    # ");  のパターンを修正
    content = re.sub(
        r'(printf\("[^"]*?)\n("\);)',
        r'\1\\n\2',
        content,
        flags=re.MULTILINE
    )
    
    # パターン2: printf("文字列
    # ", 引数); のパターンを修正
    content = re.sub(
        r'(printf\("[^"]*?)\n(",[^)]+\);)',
        r'\1\\n\2',
        content,
        flags=re.MULTILINE
    )
    
    # パターン3: 1ですのようなケース値の欠落を修正
    content = re.sub(
        r'printf\("(\d+)です\\\\n"\)',
        r'printf("\1です\\n")',
        content
    )
    
    # 改行が変換されていない箇所を修正
    lines = content.split('\n')
    in_code_block = False
    fixed_lines = []
    
    for i, line in enumerate(lines):
        if line.strip() == '```c':
            in_code_block = True
        elif line.strip() == '```':
            in_code_block = False
        
        # コードブロック内でprintf文の改行を修正
        if in_code_block and 'printf(' in line and i + 1 < len(lines):
            next_line = lines[i + 1]
            if '");' in next_line and not line.rstrip().endswith('\\n"):'):
                # 次の行が ");  で終わり、現在の行が \n"); で終わっていない場合
                line = line.rstrip() + '\\n"'
                lines[i + 1] = next_line.lstrip()
        
        fixed_lines.append(line)
    
    return '\n'.join(fixed_lines)

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    # control-if/README.mdを修正
    readme_path = os.path.join(project_root, "src", "control-if", "README.md")
    
    print(f"Fixing newlines in {readme_path}...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 修正を適用
    fixed_content = fix_printf_newlines(content)
    
    # ブレースの位置も修正（main関数のみ）
    fixed_content = re.sub(
        r'(printf\("熱中症に注意！水分補給を忘れずに\\\\n"\);\s*\n)\s*}(\s*\n\s*return 0;)',
        r'\1\n    return 0;',
        fixed_content
    )
    
    # 書き込み
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(fixed_content)
    
    print("Fixed newlines in control-if/README.md")
    
    # その他の章もチェック
    chapters = ['control-loop', 'arrays', 'strings', 'functions', 'pointers', 
                'structures', 'function-pointers', 'advanced']
    
    for chapter in chapters:
        readme_path = os.path.join(project_root, "src", chapter, "README.md")
        if os.path.exists(readme_path):
            print(f"\nProcessing {chapter}/README.md...")
            
            with open(readme_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            fixed_content = fix_printf_newlines(content)
            
            if content != fixed_content:
                with open(readme_path, 'w', encoding='utf-8') as f:
                    f.write(fixed_content)
                print(f"  Fixed newlines in {chapter}/README.md")
            else:
                print(f"  No changes needed for {chapter}/README.md")

if __name__ == "__main__":
    main()