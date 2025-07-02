#!/usr/bin/env python3
"""
各章のREADME.mdの段落記号の前に適切な改行を追加するスクリプト
文脈を考慮して、自然な改行を挿入します。
"""

import os
import re
import sys

def add_linebreak_before_markers(content):
    """段落記号の前に適切な改行を追加"""
    lines = content.split('\n')
    result = []
    
    for i in range(len(lines)):
        line = lines[i].strip()
        prev_line = lines[i-1].strip() if i > 0 else ""
        
        # 現在の行が段落記号で始まる場合
        if line and (
            line.startswith('#') or  # 見出し
            line.startswith('- ') or  # 箇条書き
            line.startswith('* ') or  # 箇条書き（アスタリスク）
            re.match(r'^\d+\.\s', line) or  # 番号付きリスト
            line.startswith('```') or  # コードブロック
            line.startswith('|') or  # テーブル
            line.startswith('>') or  # 引用
            line.startswith('#### ') or  # 4レベル見出し
            line.startswith('### ') or  # 3レベル見出し
            line.startswith('## ')  # 2レベル見出し
        ):
            # 前の行との関係を確認
            if i > 0 and prev_line and not prev_line.startswith('```'):
                # 以下の場合は改行を追加しない
                skip_conditions = [
                    # すでに空行がある
                    prev_line == "",
                    # 連続した箇条書き
                    (line.startswith('- ') and prev_line.startswith('- ')),
                    (line.startswith('* ') and prev_line.startswith('* ')),
                    # 連続した番号付きリスト
                    (re.match(r'^\d+\.\s', line) and re.match(r'^\d+\.\s', prev_line)),
                    # テーブルの連続行
                    (line.startswith('|') and prev_line.startswith('|')),
                    # コードブロックの開始/終了
                    (line.startswith('```') and i > 1 and lines[i-2].strip().startswith('```')),
                ]
                
                if not any(skip_conditions):
                    # 文脈に応じた改行の追加
                    add_break = False
                    
                    # 見出しの前は常に改行
                    if line.startswith('#'):
                        add_break = True
                    
                    # 通常の文章から箇条書きへの移行
                    elif (line.startswith('- ') or line.startswith('* ')) and not (prev_line.startswith('- ') or prev_line.startswith('* ')):
                        add_break = True
                    
                    # 通常の文章から番号付きリストへの移行
                    elif re.match(r'^\d+\.\s', line) and not re.match(r'^\d+\.\s', prev_line):
                        add_break = True
                    
                    # コードブロックの前
                    elif line.startswith('```') and not prev_line.startswith('```'):
                        add_break = True
                    
                    # テーブルの前（ただし見出し行とセパレータ行の間は除く）
                    elif line.startswith('|') and not prev_line.startswith('|'):
                        add_break = True
                    
                    if add_break and result and result[-1].strip() != "":
                        result.append("")
        
        # オリジナルの行を追加（元のインデントを保持）
        if i < len(lines):
            result.append(lines[i].rstrip())
    
    return '\n'.join(result)

def process_readme(file_path):
    """README.mdファイルを処理"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 改行を修正
        fixed_content = add_linebreak_before_markers(content)
        
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