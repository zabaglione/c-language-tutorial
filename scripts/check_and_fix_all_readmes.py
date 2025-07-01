#!/usr/bin/env python3
"""
全章のREADME.mdで欠落した括弧やその他の構文エラーをチェックして修正
"""

import os
import re

def check_function_syntax(content):
    """関数定義の構文エラーをチェック"""
    issues = []
    
    # 関数定義で開き括弧が欠落しているパターン
    pattern1 = re.findall(r'(\w+\s+\w+\s*\([^)]*\)\s*\n)\s*\n(\s*(?:printf|return|if|for|while|switch))', content)
    for match in pattern1:
        if '{' not in match[0]:
            issues.append(f"Missing opening brace after: {match[0].strip()}")
    
    # 関数本体で閉じ括弧が欠落しているパターン
    in_code_block = False
    lines = content.split('\n')
    brace_count = 0
    func_start = None
    
    for i, line in enumerate(lines):
        if '```c' in line:
            in_code_block = True
            brace_count = 0
            continue
        if '```' in line and in_code_block:
            in_code_block = False
            if brace_count > 0:
                issues.append(f"Unmatched braces in code block ending at line {i+1}")
            continue
        
        if in_code_block:
            # 関数定義を検出
            if re.match(r'^\s*\w+\s+\w+\s*\([^)]*\)\s*$', line) or \
               re.match(r'^\s*\w+\s+\(\*\w+\([^)]*\)\)\([^)]*\)\s*$', line):
                func_start = i
            
            brace_count += line.count('{') - line.count('}')
    
    return issues

def fix_common_issues(content):
    """一般的な問題を修正"""
    # エスケープシーケンスの修正
    content = re.sub(r'printf\("([^"]*?)n"\)', r'printf("\1\\n")', content)
    content = re.sub(r'printf\("([^"]*?)nn"\)', r'printf("\1\\n\\n")', content)
    
    # 二重バックスラッシュを単一に
    content = content.replace('\\\\n', '\\n')
    
    # 欠落した値の修正
    replacements = [
        (r'for \(i = ; i <', 'for (i = 0; i <'),
        (r'for \(j = ; j <', 'for (j = 0; j <'),
        (r'int i = ;', 'int i = 0;'),
        (r'int j = ;', 'int j = 0;'),
        (r'return ;', 'return 0;'),
        (r'if \(b != \.\)', 'if (b != 0)'),
        (r'return \.;', 'return 0.0;'),
    ]
    
    for pattern, replacement in replacements:
        content = re.sub(pattern, replacement, content)
    
    return content

def ensure_complete_code_blocks(content):
    """コードブロックが完全であることを確認"""
    code_blocks = list(re.finditer(r'```c\n(.*?)\n```', content, re.DOTALL))
    
    for block in code_blocks:
        code = block.group(1)
        lines = code.split('\n')
        
        # main関数が完全でない場合
        if 'int main' in code and not code.strip().endswith('}'):
            # 最後に } を追加
            new_code = code.rstrip() + '\n}'
            content = content.replace(block.group(0), f'```c\n{new_code}\n```')
    
    return content

def process_readme(readme_path):
    """READMEファイルを処理"""
    print(f"\nProcessing {readme_path}...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 構文エラーをチェック
    issues = check_function_syntax(content)
    if issues:
        print(f"  Found {len(issues)} issues:")
        for issue in issues[:5]:  # 最初の5つだけ表示
            print(f"    - {issue}")
        if len(issues) > 5:
            print(f"    ... and {len(issues) - 5} more")
    
    # 共通の問題を修正
    original_content = content
    content = fix_common_issues(content)
    content = ensure_complete_code_blocks(content)
    
    if content != original_content:
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"  Fixed issues in {readme_path}")
    else:
        print(f"  No issues found in {readme_path}")

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
    
    print("Checking and fixing all README files...")
    
    for chapter in chapters:
        chapter_dir = os.path.join(src_dir, chapter)
        readme_path = os.path.join(chapter_dir, "README.md")
        
        if os.path.exists(readme_path):
            process_readme(readme_path)
        else:
            print(f"\nSkipping {chapter} - README.md not found")
    
    print("\n✅ Completed checking all README files!")

if __name__ == "__main__":
    main()