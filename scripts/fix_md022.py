#!/usr/bin/env python3
"""
MD022エラー（見出しの前後に空行が必要）を修正するスクリプト
"""

import os
import re
import sys
from pathlib import Path

def fix_heading_spacing(filepath):
    """単一のMarkdownファイルの見出しの前後に空行を追加"""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        return False
    
    lines = content.split('\n')
    result = []
    i = 0
    fixed = False
    
    while i < len(lines):
        line = lines[i]
        
        # 見出しかどうかチェック
        if re.match(r'^#{1,6}\s', line):
            # 前の行を確認（ファイルの先頭でない場合）
            if i > 0 and result and result[-1].strip() != '':
                # 前の行が空行でない場合、空行を追加
                result.append('')
                fixed = True
            
            # 見出しを追加
            result.append(line)
            
            # 次の行を確認（ファイルの最後でない場合）
            if i < len(lines) - 1:
                next_line = lines[i + 1]
                # 次の行が空行でない場合
                if next_line.strip() != '':
                    # 次の行も見出しでない場合のみ空行を追加
                    if not re.match(r'^#{1,6}\s', next_line):
                        result.append('')
                        fixed = True
        else:
            result.append(line)
        
        i += 1
    
    if fixed:
        try:
            # 末尾の空行を調整（1つだけにする）
            while len(result) > 1 and result[-1] == '' and result[-2] == '':
                result.pop()
            
            # ファイルに書き込み
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write('\n'.join(result))
            print(f"✅ Fixed: {filepath}")
            return True
        except Exception as e:
            print(f"Error writing {filepath}: {e}")
            return False
    
    return False

def fix_all_md_files(directory):
    """ディレクトリ内のすべてのMarkdownファイルを修正"""
    md_files = []
    fixed_count = 0
    
    # Markdownファイルを収集
    for root, dirs, files in os.walk(directory):
        # 除外するディレクトリ
        if 'node_modules' in root or 'output' in root or '.git' in root:
            continue
        
        for file in files:
            if file.endswith('.md'):
                md_files.append(os.path.join(root, file))
    
    print(f"Processing {len(md_files)} Markdown files for MD022 fixes...")
    
    # 各ファイルを修正
    for filepath in sorted(md_files):
        if fix_heading_spacing(filepath):
            fixed_count += 1
    
    print(f"\n✅ Fixed {fixed_count} files")

def main():
    # プロジェクトルートを取得
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    
    print("MD022 Fixer - Adding blank lines around headings")
    print(f"Project root: {project_root}")
    print("-" * 50)
    
    fix_all_md_files(project_root)

if __name__ == "__main__":
    main()