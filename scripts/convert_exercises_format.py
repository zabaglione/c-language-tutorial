#!/usr/bin/env python3
"""
すべての演習問題を「基礎問題」「応用問題」「チャレンジ問題」形式に変換するスクリプト
"""

import os
import re

def convert_exercises_format(file_path, chapter_num, chapter_name):
    """演習問題を統一形式に変換"""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 元の内容を保存（デバッグ用）
    original_content = content
    
    # タイトルを統一
    content = re.sub(
        r'^#\s*.*演習.*$',
        f'# 第{chapter_num}章 演習問題: {chapter_name}',
        content,
        count=1,
        flags=re.MULTILINE
    )
    
    # 既に正しい形式の場合はスキップ
    if all(x in content for x in ['## 基礎問題', '## 応用問題', '## チャレンジ問題']):
        return False
    
    # 演習番号形式を検出して分類
    exercises = []
    current_exercise = None
    
    lines = content.split('\n')
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # 演習番号の検出（### 演習X-Y: または ## 演習 X-Y: 形式）
        match = re.match(r'^#{2,3}\s*演習\s*(\d+)[-−](\d+)[:\s：](.*)$', line)
        if match:
            if current_exercise:
                exercises.append(current_exercise)
            
            chapter = int(match.group(1))
            num = int(match.group(2))
            title = match.group(3).strip()
            
            current_exercise = {
                'chapter': chapter,
                'num': num,
                'title': title,
                'content': [],
                'difficulty': 1
            }
            i += 1
            continue
        
        # 難易度の検出
        if line.strip().startswith('**難易度:**') and current_exercise:
            stars = line.count('★')
            if stars > 0:
                current_exercise['difficulty'] = stars
        
        # 内容の収集
        if current_exercise:
            current_exercise['content'].append(line)
        
        i += 1
    
    # 最後の演習を追加
    if current_exercise:
        exercises.append(current_exercise)
    
    # 演習を難易度で分類
    basic_exercises = []
    applied_exercises = []
    challenge_exercises = []
    
    for ex in exercises:
        if ex['num'] <= 2 or ex['difficulty'] == 1:
            basic_exercises.append(ex)
        elif ex['num'] <= 4 or ex['difficulty'] == 2:
            applied_exercises.append(ex)
        else:
            challenge_exercises.append(ex)
    
    # 新しい形式で再構築
    new_content = []
    
    # ヘッダー部分を保持
    header_end = content.find('## 演習')
    if header_end == -1:
        header_end = content.find('### 演習')
    if header_end == -1:
        header_end = content.find('## 基礎')
    
    if header_end > 0:
        new_content.append(content[:header_end].strip())
    else:
        new_content.append(f"# 第{chapter_num}章 演習問題: {chapter_name}")
    
    # 基礎問題
    if basic_exercises:
        new_content.append("\n## 基礎問題")
        new_content.append("")
        for i, ex in enumerate(basic_exercises, 1):
            new_content.append(f"### 問題{chapter_num}-{i}: {ex['title']}")
            new_content.extend(ex['content'])
            new_content.append("")
    
    # 応用問題
    if applied_exercises:
        new_content.append("## 応用問題")
        new_content.append("")
        for i, ex in enumerate(applied_exercises, len(basic_exercises) + 1):
            new_content.append(f"### 問題{chapter_num}-{i}: {ex['title']}")
            new_content.extend(ex['content'])
            new_content.append("")
    
    # チャレンジ問題
    if challenge_exercises:
        new_content.append("## チャレンジ問題")
        new_content.append("")
        for i, ex in enumerate(challenge_exercises, len(basic_exercises) + len(applied_exercises) + 1):
            new_content.append(f"### 問題{chapter_num}-{i}: {ex['title']}")
            new_content.extend(ex['content'])
            new_content.append("")
    
    # 提出方法などのフッター部分を追加
    if '## 提出方法' in content:
        footer_start = content.find('## 提出方法')
        new_content.append(content[footer_start:])
    else:
        new_content.append("## 提出方法")
        new_content.append("")
        new_content.append("1. 各問題に対して個別のCファイルを作成")
        new_content.append(f"2. ファイル名は `ex{chapter_num}_1.c`, `ex{chapter_num}_2.c` のような形式で")
        new_content.append("3. コメントで問題番号と簡単な説明を記載")
        new_content.append("4. コンパイル・実行確認を必ず行う")
    
    # ファイルに書き込み
    final_content = '\n'.join(new_content)
    
    if final_content != original_content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(final_content)
        return True
    
    return False

def get_chapter_info():
    """章情報を取得"""
    return {
        'introduction': (1, '導入・環境構築'),
        'basics-syntax': (2, '基本文法・Hello World'),
        'data-types': (3, 'データ型と変数'),
        'operators': (4, '演算子'),
        'control-if': (5, '制御構造（条件分岐）'),
        'control-loop': (6, '制御構造（ループ）'),
        'arrays-basics': (7, '配列（基本編）'),
        'pointers': (8, 'ポインタ基礎'),
        'arrays-pointers': (9, '配列とポインタ'),
        'strings': (10, '文字列処理'),
        'functions': (11, '関数'),
        'bit-operations': (12, 'ビット操作とビットフィールド'),
        'structures': (13, '構造体とポインタ'),
        'function-pointers': (14, '関数ポインタ'),
        'advanced': (15, '複数ファイル・発展技術'),
        'c23-features': (16, 'C23の新機能')
    }

def main():
    """メイン処理"""
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    src_dir = os.path.join(project_root, 'src')
    
    chapter_info = get_chapter_info()
    updated_count = 0
    
    for chapter_dir, (chapter_num, chapter_name) in chapter_info.items():
        chapter_path = os.path.join(src_dir, chapter_dir)
        if not os.path.exists(chapter_path):
            continue
        
        exercises_readme = os.path.join(chapter_path, 'exercises', 'README.md')
        if os.path.exists(exercises_readme):
            print(f"処理中: 第{chapter_num}章 {chapter_name}")
            if convert_exercises_format(exercises_readme, chapter_num, chapter_name):
                print(f"  ✅ 更新完了")
                updated_count += 1
            else:
                print(f"  - スキップ（既に正しい形式）")
    
    print(f"\n完了: {updated_count}個のファイルを更新しました")

if __name__ == "__main__":
    main()