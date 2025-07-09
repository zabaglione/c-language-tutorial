#!/usr/bin/env python3
"""
MD007エラー（リストのインデント幅）を修正するスクリプト
markdownlintの設定に従い、ネストしたリストは4スペースでインデントする
"""

import os
import re
import sys
from typing import List, Tuple

def fix_list_indentation(content: str) -> Tuple[str, int]:
    """リストのインデントを修正"""
    lines = content.split('\n')
    result = []
    fixed_count = 0
    in_code_block = False
    
    for i, line in enumerate(lines):
        # コードブロックの開始/終了を検出
        if line.strip().startswith('```'):
            in_code_block = not in_code_block
            result.append(line)
            continue
        
        # コードブロック内はスキップ
        if in_code_block:
            result.append(line)
            continue
        
        # リスト項目を検出（-, *, +）
        match = re.match(r'^(\s*)([-*+])\s+(.*)$', line)
        if match:
            indent = match.group(1)
            marker = match.group(2)
            content_part = match.group(3)
            
            # インデントレベルを計算（4スペース単位）
            current_indent_len = len(indent)
            
            # 2スペースインデントを4スペースに修正
            if current_indent_len > 0 and current_indent_len % 4 != 0:
                # 最も近い4の倍数に調整
                new_indent_len = (current_indent_len // 2) * 4
                new_indent = ' ' * new_indent_len
                new_line = f"{new_indent}{marker} {content_part}"
                
                if new_line != line:
                    fixed_count += 1
                    result.append(new_line)
                else:
                    result.append(line)
            else:
                result.append(line)
        else:
            result.append(line)
    
    return '\n'.join(result), fixed_count

def process_file(filepath: str) -> bool:
    """単一のMarkdownファイルを処理"""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
        
        fixed_content, count = fix_list_indentation(content)
        
        if count > 0:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(fixed_content)
            print(f"✅ {filepath} - {count} 箇所修正")
            return True
        
        return False
        
    except Exception as e:
        print(f"❌ {filepath} - エラー: {e}")
        return False

def find_markdown_files(root_dir: str) -> List[str]:
    """Markdownファイルを再帰的に検索"""
    markdown_files = []
    
    exclude_dirs = {'.git', 'node_modules', '.venv', '__pycache__'}
    
    for dirpath, dirnames, filenames in os.walk(root_dir):
        dirnames[:] = [d for d in dirnames if d not in exclude_dirs]
        
        for filename in filenames:
            if filename.endswith('.md'):
                filepath = os.path.join(dirpath, filename)
                markdown_files.append(filepath)
    
    return sorted(markdown_files)

def main():
    """メイン処理"""
    if len(sys.argv) > 1:
        # 特定のファイルを処理
        filepath = sys.argv[1]
        if os.path.exists(filepath):
            process_file(filepath)
        else:
            print(f"ファイルが見つかりません: {filepath}")
    else:
        # プロジェクト全体を処理
        print("MD007エラー（リストインデント）修正スクリプト")
        print("=" * 50)
        
        root_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        markdown_files = find_markdown_files(root_dir)
        
        print(f"対象ファイル数: {len(markdown_files)}")
        print()
        
        fixed_files = 0
        for filepath in markdown_files:
            if process_file(filepath):
                fixed_files += 1
        
        print()
        print(f"修正完了: {fixed_files} ファイル")

if __name__ == "__main__":
    main()