#!/usr/bin/env python3
"""
README.mdファイルに適切な改行を追加するスクリプト
- コードブロックの前に改行を追加（コードブロック内は変更しない）
- 段落の前に改行を追加
"""

import os
import re

def add_proper_linebreaks(content):
    """適切な位置に改行を追加"""
    lines = content.split('\n')
    result = []
    in_code_block = False
    i = 0
    
    while i < len(lines):
        line = lines[i]
        prev_line = lines[i-1].strip() if i > 0 else ""
        
        # コードブロックの開始/終了を追跡
        if line.strip().startswith('```'):
            if not in_code_block:
                # コードブロック開始前に改行を追加
                if i > 0 and prev_line != "" and not prev_line.startswith('```'):
                    result.append("")
                in_code_block = True
            else:
                # コードブロック終了
                in_code_block = False
        
        # コードブロック内では何も変更しない
        if in_code_block:
            result.append(line)
            i += 1
            continue
        
        # コードブロック外での処理
        if not in_code_block and line.strip() != "":
            # 見出しの前に改行
            if line.strip().startswith('#') and i > 0 and prev_line != "":
                result.append("")
            
            # 箇条書きの開始前に改行（連続する箇条書きは除く）
            elif (line.strip().startswith('- ') or line.strip().startswith('* ')) and \
                 i > 0 and prev_line != "" and \
                 not prev_line.startswith('- ') and not prev_line.startswith('* ') and \
                 not prev_line.startswith('  '):  # インデントされた箇条書きも考慮
                result.append("")
            
            # 番号付きリストの開始前に改行（連続する番号付きリストは除く）
            elif re.match(r'^\d+\.\s', line.strip()) and \
                 i > 0 and prev_line != "" and \
                 not re.match(r'^\d+\.\s', prev_line):
                result.append("")
            
            # テーブルの前に改行（ヘッダー行の前のみ）
            elif line.strip().startswith('|') and \
                 i > 0 and prev_line != "" and \
                 not prev_line.startswith('|'):
                result.append("")
            
            # 段落の検出（通常のテキストで、特殊な記号で始まらない）
            elif not any(line.strip().startswith(prefix) for prefix in 
                        ['#', '-', '*', '|', '>', '```', '  ', '\t']) and \
                 not re.match(r'^\d+\.\s', line.strip()) and \
                 i > 0 and prev_line != "" and len(line.strip()) > 20:
                # 前の行が段落の終わりと思われる場合
                if not prev_line.endswith(':') and not prev_line.endswith('：') and \
                   not prev_line.endswith(',') and not prev_line.endswith('、'):
                    # 次の条件のいずれかを満たす場合、新しい段落として扱う
                    conditions = [
                        # 前の行が句点で終わる
                        prev_line.endswith('。'),
                        prev_line.endswith('.') and not re.search(r'\d\.$', prev_line),
                        # 前の行が感嘆符や疑問符で終わる
                        prev_line.endswith('!') or prev_line.endswith('?'),
                        prev_line.endswith('！') or prev_line.endswith('？'),
                        # 話題が変わりそうな接続詞で始まる
                        line.strip().startswith(('また、', 'さらに、', 'ただし、', 
                                               'なお、', 'ところで、', 'しかし、',
                                               'そして、', 'それでは、', 'では、',
                                               'ここで、', 'つまり、', '例えば、')),
                    ]
                    
                    if any(conditions):
                        result.append("")
        
        result.append(line)
        i += 1
    
    return '\n'.join(result)

def process_readme(file_path):
    """README.mdファイルを処理"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 改行を追加
        fixed_content = add_proper_linebreaks(content)
        
        # ファイルが変更された場合のみ書き込み
        if content != fixed_content:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(fixed_content)
            return True
        return False
    except Exception as e:
        print(f"エラー: {file_path} - {e}")
        return False

def main():
    """メイン処理"""
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    src_dir = os.path.join(project_root, 'src')
    
    # 処理する章のリスト
    chapters = [
        'introduction', 'basics-syntax', 'data-types', 'operators',
        'control-if', 'control-loop', 'arrays-basics', 'pointers',
        'arrays-pointers', 'strings', 'functions', 'bit-operations',
        'structures', 'function-pointers', 'advanced', 'c23-features'
    ]
    
    modified_count = 0
    
    for chapter in chapters:
        readme_path = os.path.join(src_dir, chapter, 'README.md')
        if os.path.exists(readme_path):
            print(f"処理中: {chapter}/README.md", end='... ')
            if process_readme(readme_path):
                print("✅ 修正")
                modified_count += 1
            else:
                print("変更なし")
        else:
            print(f"⚠️  スキップ: {chapter}/README.md (ファイルが存在しません)")
    
    print(f"\n完了: {modified_count}個のファイルを修正しました")

if __name__ == "__main__":
    main()