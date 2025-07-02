#!/usr/bin/env python3
"""
すべての演習問題を「基礎問題」「応用問題」「チャレンジ問題」に統一するスクリプト
"""

import os
import re

def check_exercise_format(file_path):
    """演習問題の形式をチェック"""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    has_basic = '基礎問題' in content or '## 基礎問題' in content
    has_applied = '応用問題' in content or '## 応用問題' in content or '応用課題' in content
    has_challenge = 'チャレンジ問題' in content or '## チャレンジ問題' in content or '挑戦課題' in content
    
    # その他の形式をチェック
    has_exercise_num = bool(re.search(r'## 演習\s*\d+', content))
    has_difficulty = '★' in content
    
    return {
        'has_basic': has_basic,
        'has_applied': has_applied,
        'has_challenge': has_challenge,
        'has_exercise_num': has_exercise_num,
        'has_difficulty': has_difficulty,
        'needs_update': not (has_basic and has_applied and has_challenge)
    }

def get_chapter_info(chapter_name):
    """章番号と章名を取得"""
    chapter_mapping = {
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
    return chapter_mapping.get(chapter_name, (0, ''))

def main():
    """メイン処理"""
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    src_dir = os.path.join(project_root, 'src')
    
    results = {}
    
    # 各章の演習問題をチェック
    for chapter in os.listdir(src_dir):
        chapter_path = os.path.join(src_dir, chapter)
        if not os.path.isdir(chapter_path):
            continue
        
        exercises_readme = os.path.join(chapter_path, 'exercises', 'README.md')
        if os.path.exists(exercises_readme):
            chapter_num, chapter_title = get_chapter_info(chapter)
            format_info = check_exercise_format(exercises_readme)
            results[chapter] = {
                'num': chapter_num,
                'title': chapter_title,
                'format': format_info
            }
    
    # 結果を表示
    print("演習問題の形式チェック結果:\n")
    print("章 | 基礎 | 応用 | チャレンジ | 更新必要 | 備考")
    print("-" * 60)
    
    for chapter in sorted(results.keys(), key=lambda x: results[x]['num']):
        info = results[chapter]
        fmt = info['format']
        
        basic = "○" if fmt['has_basic'] else "×"
        applied = "○" if fmt['has_applied'] else "×"
        challenge = "○" if fmt['has_challenge'] else "×"
        needs_update = "要" if fmt['needs_update'] else "-"
        
        notes = []
        if fmt['has_exercise_num']:
            notes.append("演習番号形式")
        if fmt['has_difficulty']:
            notes.append("難易度★")
            
        print(f"{info['num']:2d} | {basic:^4} | {applied:^4} | {challenge:^6} | {needs_update:^8} | {', '.join(notes)}")
    
    # 更新が必要な章をリスト
    print("\n更新が必要な章:")
    for chapter in sorted(results.keys(), key=lambda x: results[x]['num']):
        if results[chapter]['format']['needs_update']:
            print(f"- 第{results[chapter]['num']}章: {results[chapter]['title']} ({chapter})")

if __name__ == "__main__":
    main()