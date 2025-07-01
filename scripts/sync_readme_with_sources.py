#!/usr/bin/env python3
"""
各章のREADME.mdを実際のソースファイルと同期するスクリプト
- 完全なコードブロックを保持
- エスケープシーケンスを正しく処理
- 欠落した値を補完
"""

import os
import re
import sys

def read_source_file(file_path):
    """ソースファイルを読み込む"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            return f.read()
    except FileNotFoundError:
        return None

def extract_code_section(source_code, start_pattern=None, end_pattern=None):
    """ソースコードから特定のセクションを抽出"""
    if not start_pattern:
        # main関数全体を抽出
        main_match = re.search(r'(int main\([^)]*\)\s*\{.*?\n\})', source_code, re.DOTALL)
        if main_match:
            return main_match.group(1)
        
        # #includeから始まる完全なコード
        include_match = re.search(r'(#include.*?\n\})', source_code, re.DOTALL)
        if include_match:
            return include_match.group(1)
    
    return source_code

def find_and_replace_code_blocks(readme_content, examples_dir):
    """README内のコードブロックを実際のソースコードで置き換え"""
    # コードブロックを見つける
    code_blocks = re.finditer(r'```c\n(.*?)\n```', readme_content, re.DOTALL)
    
    for block in code_blocks:
        code = block.group(1)
        
        # 特徴的なキーワードでソースファイルを特定
        if 'for文のカウントアップ' in code:
            # 基本的な使用例
            source_file = os.path.join(examples_dir, 'loop_basic.c')
            if os.path.exists(source_file):
                source_content = read_source_file(source_file)
                if source_content:
                    # 適切なセクションを抽出
                    new_code = extract_code_section(source_content)
                    if new_code:
                        readme_content = readme_content.replace(block.group(0), f'```c\n{new_code}\n```')
    
    return readme_content

def fix_escape_sequences(content):
    """エスケープシーケンスを修正"""
    # 二重バックスラッシュを単一に
    content = content.replace('\\\\n', '\\n')
    
    # printf文の改行を修正
    content = re.sub(r'printf\("([^"]*?)\n"\);\n"', r'printf("\1\\n");', content)
    
    return content

def fix_missing_values(content):
    """欠落した値を補完"""
    replacements = [
        (r'for \(i = ; i <', 'for (i = 0; i <'),
        (r'for \(j = ; j <', 'for (j = 0; j <'),
        (r'while \(\)\s*\{', 'while (1) {'),
        (r'return ;', 'return 0;'),
        (r'case :', 'case 1:'),
        (r'if \(i == \)', 'if (i == 5)'),
        (r'if \(i % \s*== \)', 'if (i % 2 == 0)'),
        (r'scanf\("%d", &choice\) != \)', 'scanf("%d", &choice) != 1)'),
    ]
    
    for pattern, replacement in replacements:
        content = re.sub(pattern, replacement, content)
    
    return content

def sync_readme_with_sources(readme_path, examples_dir):
    """READMEをソースファイルと同期"""
    print(f"Syncing {readme_path}...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # ソースファイルと同期
    if os.path.exists(examples_dir):
        content = find_and_replace_code_blocks(content, examples_dir)
    
    # エスケープシーケンスを修正
    content = fix_escape_sequences(content)
    
    # 欠落した値を補完
    content = fix_missing_values(content)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print(f"  Synced {readme_path}")

def main():
    """メイン処理"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    src_dir = os.path.join(project_root, "src")
    
    # すべての章を処理
    for chapter in os.listdir(src_dir):
        chapter_dir = os.path.join(src_dir, chapter)
        if not os.path.isdir(chapter_dir):
            continue
        
        readme_path = os.path.join(chapter_dir, "README.md")
        examples_dir = os.path.join(chapter_dir, "examples")
        
        if os.path.exists(readme_path):
            sync_readme_with_sources(readme_path, examples_dir)
    
    print("\nCompleted syncing all README files with source code!")

if __name__ == "__main__":
    main()
