#!/usr/bin/env python3
"""
main_textbook.mdの内容を各章のREADME.mdファイルに反映させるスクリプト
"""

import os
import re
import sys

# 章の開始行と対応するディレクトリのマッピング
CHAPTER_MAPPING = {
    1: {"start": 29, "end": 571, "dir": "introduction", "title": "C言語入門"},
    2: {"start": 572, "end": 1061, "dir": "basics-syntax", "title": "基本構文"},
    3: {"start": 1062, "end": 1891, "dir": "data-types", "title": "データ型と変数"},
    4: {"start": 1892, "end": 2931, "dir": "operators", "title": "演算子"},
    5: {"start": 2932, "end": 3900, "dir": "control-if", "title": "条件分岐"},
    6: {"start": 3901, "end": 5054, "dir": "control-loop", "title": "繰り返し処理"},
    7: {"start": 5055, "end": 6743, "dir": "arrays", "title": "配列"},
    8: {"start": 6744, "end": 8174, "dir": "strings", "title": "文字列処理"},
    9: {"start": 8175, "end": 8974, "dir": "functions", "title": "関数"},
    10: {"start": 8975, "end": 10702, "dir": "pointers", "title": "ポインタ"},
    11: {"start": 10703, "end": 13037, "dir": "structures", "title": "構造体"},
    12: {"start": 13038, "end": 15061, "dir": "function-pointers", "title": "関数ポインタ"},
    13: {"start": 15062, "end": 17984, "dir": "advanced", "title": "高度なトピック"},
    14: {"start": 17985, "end": -1, "dir": "c23-features", "title": "C23の新機能"}
}

def read_main_textbook(file_path):
    """main_textbook.mdファイルを読み込む"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        return lines
    except FileNotFoundError:
        print(f"エラー: {file_path} が見つかりません")
        sys.exit(1)

def extract_chapter_content(lines, chapter_num):
    """指定された章の内容を抽出する"""
    chapter_info = CHAPTER_MAPPING[chapter_num]
    start_line = chapter_info["start"] - 1  # 0-indexed
    end_line = chapter_info["end"] - 1 if chapter_info["end"] != -1 else len(lines)
    
    # 章のタイトル行をスキップ（# 第N章: タイトル）
    content_lines = lines[start_line + 1:end_line]
    
    # 先頭の空行を削除
    while content_lines and content_lines[0].strip() == "":
        content_lines.pop(0)
    
    return content_lines

def clean_chapter_content(content_lines):
    """章の内容をクリーンアップする"""
    cleaned_lines = []
    
    # サンプルコードのセクションを処理
    in_sample_code_section = False
    skip_until_next_section = False
    
    for line in content_lines:
        # サンプルコードセクションの開始を検出
        if line.strip() == "## サンプルコード":
            in_sample_code_section = True
            cleaned_lines.append(line)
            continue
        
        # 次のセクションを検出
        if line.startswith("## ") and in_sample_code_section:
            in_sample_code_section = False
            skip_until_next_section = False
        
        # サンプルコード内の実際のコードブロックをスキップ
        if in_sample_code_section and line.strip().startswith("```"):
            skip_until_next_section = True
            continue
        
        # スキップ中は何も追加しない
        if skip_until_next_section:
            if line.strip().startswith("```"):
                skip_until_next_section = False
            continue
        
        # 区切り線（---）を削除
        if line.strip() == "---":
            continue
        
        cleaned_lines.append(line)
    
    return cleaned_lines

def write_chapter_readme(chapter_num, content_lines, base_dir):
    """章のREADME.mdファイルを書き込む"""
    chapter_info = CHAPTER_MAPPING[chapter_num]
    chapter_dir = os.path.join(base_dir, "src", chapter_info["dir"])
    readme_path = os.path.join(chapter_dir, "README.md")
    
    # タイトルを追加
    title = f"# {chapter_info['title']}\n"
    
    # 内容をクリーンアップ
    cleaned_content = clean_chapter_content(content_lines)
    
    # ファイルに書き込む
    try:
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.write(title)
            f.writelines(cleaned_content)
        print(f"更新完了: {readme_path}")
    except Exception as e:
        print(f"エラー: {readme_path} の書き込みに失敗しました - {e}")

def main():
    # プロジェクトのルートディレクトリを取得
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    # main_textbook.mdのパス
    main_textbook_path = os.path.join(project_root, "docs", "main_textbook.md")
    
    # ファイルを読み込む
    lines = read_main_textbook(main_textbook_path)
    
    # 各章を処理
    for chapter_num in range(1, 15):
        print(f"\n第{chapter_num}章を処理中...")
        content = extract_chapter_content(lines, chapter_num)
        write_chapter_readme(chapter_num, content, project_root)
    
    print("\n全ての章の更新が完了しました！")

if __name__ == "__main__":
    main()