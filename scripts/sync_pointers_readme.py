#!/usr/bin/env python3
"""
pointers/README.mdを実際のソースファイルと同期する専用スクリプト
"""

import os
import re

def read_source_file(file_path):
    """ソースファイルを読み込む"""
    if os.path.exists(file_path):
        with open(file_path, 'r', encoding='utf-8') as f:
            return f.read()
    return None

def get_source_mapping():
    """READMEのセクションとソースファイルのマッピング"""
    return {
        # セクション名: (ソースファイル名, 抽出タイプ)
        "ポインタの基本概念": ("pointer_basic.c", "complete"),
        "アドレス演算子": ("pointer_basic.c", "complete"),
        "間接参照演算子": ("pointer_operations.c", "complete"),
        "ポインタのデータ型": ("pointer_types.c", "complete"),
        "配列とポインタの関係": ("array_pointer.c", "complete"),
        "ポインタ演算": ("pointer_arithmetic.c", "complete"),
        "関数とポインタ": ("pointer_functions.c", "complete"),
        "文字列とポインタ": ("string_pointer.c", "complete"),
        "ポインタの配列": ("pointer_array.c", "complete"),
        "実践的なポインタ活用例": ("advanced_pointer.c", "complete"),
    }

def extract_code_sections_from_readme(readme_content):
    """READMEからコードセクションを抽出"""
    sections = []
    
    # 各セクションを探す
    current_section = None
    lines = readme_content.split('\n')
    
    for i, line in enumerate(lines):
        # セクションヘッダーを検出
        if line.startswith('###') or line.startswith('####'):
            current_section = line.strip('#').strip()
        
        # コードブロックを検出
        if line.strip() == '```c' and current_section:
            # コードブロックの終わりを探す
            j = i + 1
            code_lines = []
            while j < len(lines) and lines[j].strip() != '```':
                code_lines.append(lines[j])
                j += 1
            
            if code_lines:
                sections.append({
                    'section': current_section,
                    'start': i,
                    'end': j,
                    'code': '\n'.join(code_lines)
                })
    
    return sections

def update_readme_with_sources(readme_path, examples_dir):
    """READMEをソースファイルで更新"""
    print(f"Updating {readme_path}...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        readme_content = f.read()
    
    # マッピング情報を取得
    mapping = get_source_mapping()
    
    # READMEからコードセクションを抽出
    sections = extract_code_sections_from_readme(readme_content)
    
    # 各セクションを処理
    updated = False
    for section_info in sections:
        section_name = section_info['section']
        
        # 対応するソースファイルを探す
        source_file = None
        
        # 直接マッピングがある場合
        for key, (filename, extract_type) in mapping.items():
            if key in section_name:
                source_file = os.path.join(examples_dir, filename)
                break
        
        # コード内容から推測
        if not source_file:
            code = section_info['code']
            if 'swap' in code and 'double_value' in code:
                source_file = os.path.join(examples_dir, "pointer_functions.c")
            elif 'find_max_ptr' in code or 'search_value' in code:
                source_file = os.path.join(examples_dir, "pointer_functions.c")
            elif 'string_length' in code or 'string_copy' in code:
                source_file = os.path.join(examples_dir, "string_pointer.c")
            elif 'reverse_array' in code or 'rotate_right' in code:
                source_file = os.path.join(examples_dir, "advanced_pointer.c")
            elif 'bubble_sort' in code or 'compare_arrays' in code:
                source_file = os.path.join(examples_dir, "advanced_pointer.c")
            elif 'fruits' in code:
                source_file = os.path.join(examples_dir, "pointer_array.c")
        
        # ソースファイルが見つかった場合
        if source_file and os.path.exists(source_file):
            source_content = read_source_file(source_file)
            if source_content:
                # コードブロックを置き換え
                old_block = f"```c\n{section_info['code']}\n```"
                new_block = f"```c\n{source_content.strip()}\n```"
                
                readme_content = readme_content.replace(old_block, new_block)
                updated = True
                print(f"  Updated section: {section_name} from {os.path.basename(source_file)}")
    
    if updated:
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.write(readme_content)
        print("✅ Successfully updated pointers/README.md")
    else:
        print("ℹ️  No updates needed")

def main():
    """メイン処理"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    pointers_dir = os.path.join(project_root, "src", "pointers")
    readme_path = os.path.join(pointers_dir, "README.md")
    examples_dir = os.path.join(pointers_dir, "examples")
    
    if not os.path.exists(examples_dir):
        print(f"Examples directory not found: {examples_dir}")
        return
    
    # 利用可能なソースファイルを表示
    print("Available source files:")
    for file in sorted(os.listdir(examples_dir)):
        if file.endswith('.c'):
            print(f"  - {file}")
    print()
    
    update_readme_with_sources(readme_path, examples_dir)

if __name__ == "__main__":
    main()