#!/usr/bin/env python3
"""
各章のREADME.mdファイルからmain_textbook.mdを生成するスクリプト
"""

import os
import sys
from datetime import datetime

# 章の情報とディレクトリのマッピング
CHAPTERS = [
    {"num": 1, "dir": "introduction", "title": "C言語入門"},
    {"num": 2, "dir": "basics-syntax", "title": "基本構文"},
    {"num": 3, "dir": "data-types", "title": "データ型と変数"},
    {"num": 4, "dir": "operators", "title": "演算子"},
    {"num": 5, "dir": "control-if", "title": "条件分岐"},
    {"num": 6, "dir": "control-loop", "title": "繰り返し処理"},
    {"num": 7, "dir": "arrays", "title": "配列"},
    {"num": 8, "dir": "strings", "title": "文字列処理"},
    {"num": 9, "dir": "functions", "title": "関数"},
    {"num": 10, "dir": "pointers", "title": "ポインタ"},
    {"num": 11, "dir": "structures", "title": "構造体"},
    {"num": 12, "dir": "function-pointers", "title": "関数ポインタ"},
    {"num": 13, "dir": "advanced", "title": "高度なトピック"},
    {"num": 14, "dir": "c23-features", "title": "C23の新機能"}
]

def read_chapter_readme(base_dir, chapter_dir):
    """章のREADME.mdファイルを読み込む"""
    readme_path = os.path.join(base_dir, "src", chapter_dir, "README.md")
    try:
        with open(readme_path, 'r', encoding='utf-8') as f:
            content = f.read()
        return content
    except FileNotFoundError:
        print(f"警告: {readme_path} が見つかりません")
        return None

def read_example_files(base_dir, chapter_dir):
    """章のexamplesディレクトリからサンプルコードを読み込む"""
    examples_dir = os.path.join(base_dir, "src", chapter_dir, "examples")
    example_files = {}
    
    if not os.path.exists(examples_dir):
        return example_files
    
    # .cファイルを探す（C99版は除外）
    for filename in sorted(os.listdir(examples_dir)):
        if filename.endswith('.c') and not filename.endswith('_c99.c'):
            file_path = os.path.join(examples_dir, filename)
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    example_files[filename] = f.read()
            except Exception as e:
                print(f"警告: {file_path} の読み込みに失敗しました - {e}")
    
    return example_files

def format_example_code(filename, content):
    """サンプルコードをフォーマットする"""
    # ファイル名から拡張子を除去してタイトルを作成
    title = filename.replace('.c', '')
    
    formatted = f"\n### {title}.c\n\n```c\n{content}```\n"
    
    # C99版が存在する場合のリンクを追加
    formatted += f"\n> C99版は[こちら]({title}_c99.c)を参照してください。\n"
    
    return formatted

def generate_main_textbook(base_dir):
    """main_textbook.mdを生成する"""
    # ヘッダー部分
    header = f"""---
title: "C言語プログラミング教材"
author: "プログラミング学習教材"
date: "{datetime.now().year}年"
---

# C言語プログラミング教材

## 目次

"""
    
    # 目次を生成
    toc = ""
    for chapter in CHAPTERS:
        anchor = f"第{chapter['num']}章-{chapter['title'].lower().replace(' ', '-')}"
        toc += f"{chapter['num']}. [第{chapter['num']}章: {chapter['title']}](#{anchor})\n"
    
    # 本文を生成
    body = "\n---\n\n"
    
    for chapter in CHAPTERS:
        print(f"第{chapter['num']}章を処理中...")
        
        # 章のタイトル
        body += f"\n# 第{chapter['num']}章: {chapter['title']}\n\n"
        
        # README.mdの内容を読み込む
        readme_content = read_chapter_readme(base_dir, chapter['dir'])
        if readme_content:
            # タイトル行を削除（最初の#で始まる行）
            lines = readme_content.split('\n')
            if lines and lines[0].startswith('# '):
                lines = lines[1:]
            
            # 先頭の空行を削除
            while lines and lines[0].strip() == '':
                lines.pop(0)
            
            body += '\n'.join(lines)
            
            # サンプルコードセクションを追加
            example_files = read_example_files(base_dir, chapter['dir'])
            if example_files:
                # サンプルコードセクションの開始を見つける
                if "## サンプルコード" in body:
                    # 既存のサンプルコードセクションの後に追加
                    for filename, content in example_files.items():
                        body += format_example_code(filename, content)
        
        body += "\n---\n"
    
    return header + toc + body

def main():
    # プロジェクトのルートディレクトリを取得
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    # main_textbook.mdのパス
    output_path = os.path.join(project_root, "docs", "main_textbook_generated.md")
    
    print("main_textbook.mdを生成中...")
    
    # ファイルを生成
    content = generate_main_textbook(project_root)
    
    # ファイルに書き込む
    try:
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"\n生成完了: {output_path}")
        print("\n注意: 生成されたファイルは main_textbook_generated.md として保存されました。")
        print("内容を確認後、必要に応じて main_textbook.md にリネームしてください。")
    except Exception as e:
        print(f"エラー: ファイルの書き込みに失敗しました - {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()