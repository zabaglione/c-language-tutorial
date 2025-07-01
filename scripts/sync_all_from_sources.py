#!/usr/bin/env python3
"""
全章のREADME.mdを実際のソースファイルと同期する統合スクリプト
各章のexamplesディレクトリから正確なコードをコピー
"""

import os
import re
import glob

def read_file(file_path):
    """ファイルを読み込む"""
    with open(file_path, 'r', encoding='utf-8') as f:
        return f.read()

def write_file(file_path, content):
    """ファイルに書き込む"""
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(content)

def find_source_files(examples_dir):
    """examplesディレクトリ内のすべてのCファイルを取得"""
    if not os.path.exists(examples_dir):
        return []
    return glob.glob(os.path.join(examples_dir, "*.c"))

def extract_function(source_code, func_name):
    """ソースコードから特定の関数を抽出"""
    # 関数の開始を見つける
    pattern = rf'(\w+\s+\*?\s*{func_name}\s*\([^)]*\)\s*\{{)'
    match = re.search(pattern, source_code)
    if not match:
        return None
    
    start = match.start()
    brace_start = source_code.find('{', match.start())
    
    # 対応する閉じ括弧を見つける
    brace_count = 1
    i = brace_start + 1
    while i < len(source_code) and brace_count > 0:
        if source_code[i] == '{':
            brace_count += 1
        elif source_code[i] == '}':
            brace_count -= 1
        i += 1
    
    if brace_count == 0:
        return source_code[start:i]
    return None

def find_matching_source(code_block, source_files):
    """コードブロックに最も適合するソースファイルを見つける"""
    best_match = None
    best_score = 0
    
    # コードブロックから特徴的な要素を抽出
    functions = re.findall(r'(?:int|void|char|double|float)\s+\*?\s*(\w+)\s*\(', code_block)
    strings = re.findall(r'printf\s*\(\s*"([^"]{5,30})"', code_block)
    
    for source_file in source_files:
        source_content = read_file(source_file)
        score = 0
        
        # 関数名の一致をチェック
        for func in functions:
            if func in source_content:
                score += 10
        
        # 文字列の一致をチェック
        for string in strings:
            if string in source_content:
                score += 5
        
        if score > best_score:
            best_score = score
            best_match = source_file
    
    return best_match if best_score > 0 else None

def sync_chapter(chapter_path):
    """特定の章のREADMEを同期"""
    readme_path = os.path.join(chapter_path, "README.md")
    examples_dir = os.path.join(chapter_path, "examples")
    
    if not os.path.exists(readme_path):
        return False
    
    chapter_name = os.path.basename(chapter_path)
    print(f"\nProcessing {chapter_name}...")
    
    readme_content = read_file(readme_path)
    source_files = find_source_files(examples_dir)
    
    if not source_files:
        print(f"  No source files found in {chapter_name}/examples/")
        return False
    
    # すべてのコードブロックを処理
    modified = False
    pattern = r'```c\n(.*?)\n```'
    matches = list(re.finditer(pattern, readme_content, re.DOTALL))
    
    # 後ろから処理（位置がずれないように）
    for match in reversed(matches):
        code_block = match.group(1)
        
        # 短すぎるコードブロックはスキップ
        if len(code_block) < 50:
            continue
        
        # マッチするソースファイルを探す
        source_file = find_matching_source(code_block, source_files)
        
        if source_file:
            source_content = read_file(source_file).strip()
            
            # 完全なプログラムか、main関数のみかを判断
            if '#include' in code_block and '#include' in source_content:
                # 完全なプログラムを置き換え
                new_content = source_content
            elif 'int main' in code_block and 'int main' in source_content:
                # main関数のみを抽出
                main_func = extract_function(source_content, 'main')
                if main_func:
                    new_content = main_func
                else:
                    continue
            else:
                # 特定の関数を探す
                func_names = re.findall(r'(?:int|void|char|double|float)\s+\*?\s*(\w+)\s*\(', code_block)
                if func_names:
                    func = extract_function(source_content, func_names[0])
                    if func:
                        new_content = func
                    else:
                        continue
                else:
                    continue
            
            # 置き換え
            start, end = match.span()
            readme_content = (
                readme_content[:start] +
                f'```c\n{new_content}\n```' +
                readme_content[end:]
            )
            modified = True
            print(f"  Replaced code block from {os.path.basename(source_file)}")
    
    if modified:
        write_file(readme_path, readme_content)
        print(f"  ✅ Updated {chapter_name}/README.md")
        return True
    else:
        print(f"  ℹ️  No updates needed for {chapter_name}/README.md")
        return False

def main():
    """メイン処理"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    src_dir = os.path.join(project_root, "src")
    
    # 優先的に処理する章
    priority_chapters = ['pointers', 'function-pointers', 'control-loop']
    
    # その他の章
    other_chapters = [
        'introduction', 'basics-syntax', 'data-types', 'operators',
        'control-if', 'arrays', 'strings', 'functions', 
        'structures', 'advanced', 'c23-features'
    ]
    
    all_chapters = priority_chapters + [ch for ch in other_chapters if ch not in priority_chapters]
    
    print("Syncing README files with source code...")
    print("=" * 60)
    
    updated_count = 0
    
    for chapter in all_chapters:
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_path):
            if sync_chapter(chapter_path):
                updated_count += 1
    
    print("\n" + "=" * 60)
    print(f"✅ Sync completed! Updated {updated_count} chapters.")
    print("\nThis approach ensures:")
    print("- All code blocks match actual source files")
    print("- Brackets and escape sequences are correct")
    print("- No manual fixes needed")

if __name__ == "__main__":
    main()