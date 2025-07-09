#!/usr/bin/env python3
"""
カタカナ表記の長音チェックと修正を行うスクリプト
"""

import os
import re
import sys
from pathlib import Path

class KatakanaChecker:
    def __init__(self):
        self.replacements = {
            # -er ending
            'コンピュータ': 'コンピューター',
            'ユーザ': 'ユーザー',
            'サーバ': 'サーバー',
            'プログラマ': 'プログラマー',
            'デバッガ': 'デバッガー',
            'コンパイラ': 'コンパイラー',
            'ポインタ': 'ポインター',
            'バッファ': 'バッファー',
            'レジスタ': 'レジスター',
            'パラメータ': 'パラメーター',
            'パラメタ': 'パラメーター',
            'マスタ': 'マスター',
            'エンタ': 'エンター',
            'センタ': 'センター',
            'フィルタ': 'フィルター',
            'ヘッダ': 'ヘッダー',
            'フッタ': 'フッター',
            'カウンタ': 'カウンター',
            'タイマ': 'タイマー',
            'ハンドラ': 'ハンドラー',
            'マネージャ': 'マネージャー',
            'コントローラ': 'コントローラー',
            'デコーダ': 'デコーダー',
            'エンコーダ': 'エンコーダー',
            'アダプタ': 'アダプター',
            'ドライバ': 'ドライバー',
            'レイヤ': 'レイヤー',
            'プレイヤ': 'プレイヤー',
            'ビューア': 'ビューアー',
            'エディタ': 'エディター',
            'リーダ': 'リーダー',
            'ライタ': 'ライター',
            'スキャナ': 'スキャナー',
            'プリンタ': 'プリンター',
            'ルータ': 'ルーター',
            'リスナ': 'リスナー',
            'レンダラ': 'レンダラー',
            'ブラウザ': 'ブラウザー',
            'インタープリタ': 'インタープリター',
            'インタプリタ': 'インタープリター',
            'イテレータ': 'イテレーター',
            
            # -or ending
            'エラ': 'エラー',
            'ベクタ': 'ベクター',
            'セクタ': 'セクター',
            'ファクタ': 'ファクター',
            'アクタ': 'アクター',
            'モニタ': 'モニター',
            'ジェネレータ': 'ジェネレーター',
            'イニシエータ': 'イニシエーター',
            'オペレータ': 'オペレーター',
            'モデレータ': 'モデレーター',
            'ナビゲータ': 'ナビゲーター',
            'セレクタ': 'セレクター',
            'インジケータ': 'インジケーター',
            'アロケータ': 'アロケーター',
            'イニシャライザ': 'イニシャライザー',
            'ターミネータ': 'ターミネーター',
            'シミュレータ': 'シミュレーター',
            'エミュレータ': 'エミュレーター',
            'コンストラクタ': 'コンストラクター',
            'デストラクタ': 'デストラクター',
            'プロセッサ': 'プロセッサー',
            'アクセサ': 'アクセサー',
            'デコレータ': 'デコレーター',
            'ディレクタ': 'ディレクター',
            'コレクタ': 'コレクター',
            'インスペクタ': 'インスペクター',
            'プロテクタ': 'プロテクター',
            'リフレクタ': 'リフレクター',
            'コネクタ': 'コネクター',
            'ビジタ': 'ビジター',
            'アンカ': 'アンカー',
            'トランジスタ': 'トランジスター',
            'キャパシタ': 'キャパシター',
            'センサ': 'センサー',
            
            # -ar ending
            'カレンダ': 'カレンダー',
            'スカラ': 'スカラー',
            'レギュラ': 'レギュラー',
            'ポピュラ': 'ポピュラー',
            'シミラ': 'シミラー',
            'パーティキュラ': 'パーティキュラー',
        }
        
        self.found_issues = []
        self.fixed_count = 0
    
    def check_file(self, filepath, fix=False):
        """ファイルをチェックして、必要に応じて修正"""
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                original_content = content
        except Exception as e:
            print(f"Error reading {filepath}: {e}")
            return
        
        # 各置換パターンをチェック
        for incorrect, correct in self.replacements.items():
            # 単語境界を考慮した正規表現パターン
            # カタカナの後に長音記号が続かない場合のみマッチ
            pattern = r'\b' + re.escape(incorrect) + r'(?!ー)'
            
            matches = re.finditer(pattern, content)
            for match in matches:
                line_num = content[:match.start()].count('\n') + 1
                self.found_issues.append({
                    'file': filepath,
                    'line': line_num,
                    'incorrect': incorrect,
                    'correct': correct
                })
            
            if fix:
                content = re.sub(pattern, correct, content)
        
        # 修正モードで変更があった場合、ファイルを更新
        if fix and content != original_content:
            try:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                self.fixed_count += 1
                print(f"✅ Fixed: {filepath}")
            except Exception as e:
                print(f"Error writing {filepath}: {e}")
    
    def check_directory(self, directory, fix=False):
        """ディレクトリ内のすべてのファイルをチェック"""
        files_to_check = []
        
        # チェック対象のファイルを収集
        for root, dirs, files in os.walk(directory):
            # 除外するディレクトリ
            if 'node_modules' in root or 'output' in root or '.git' in root:
                continue
            
            for file in files:
                # Markdown、C言語ソース、ヘッダーファイルをチェック
                if file.endswith(('.md', '.c', '.h')):
                    files_to_check.append(os.path.join(root, file))
        
        print(f"{'修正' if fix else 'チェック'}中: {len(files_to_check)} 個のファイル")
        
        # 各ファイルをチェック
        for filepath in sorted(files_to_check):
            self.check_file(filepath, fix)
        
        # 結果を表示
        if fix:
            print(f"\n✅ {self.fixed_count} 個のファイルを修正しました")
        else:
            if self.found_issues:
                print(f"\n❌ {len(self.found_issues)} 個の問題が見つかりました:")
                
                # ファイルごとにグループ化
                issues_by_file = {}
                for issue in self.found_issues:
                    if issue['file'] not in issues_by_file:
                        issues_by_file[issue['file']] = []
                    issues_by_file[issue['file']].append(issue)
                
                # 最初の5ファイルの問題を表示
                for i, (filepath, issues) in enumerate(issues_by_file.items()):
                    if i >= 5:
                        remaining = len(issues_by_file) - 5
                        print(f"\n  ... 他 {remaining} 個のファイルに問題があります")
                        break
                    
                    print(f"\n  {filepath}:")
                    for issue in issues[:3]:  # 各ファイルの最初の3つの問題を表示
                        print(f"    Line {issue['line']}: '{issue['incorrect']}' → '{issue['correct']}'")
                    if len(issues) > 3:
                        print(f"    ... 他 {len(issues) - 3} 個の問題")
                
                print("\n修正するには --fix オプションを使用してください")
            else:
                print("\n✅ 問題は見つかりませんでした")

def main():
    checker = KatakanaChecker()
    fix_mode = '--fix' in sys.argv
    
    # プロジェクトルートを取得
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    
    print("カタカナ長音チェッカー")
    print("語尾が -er, -or, -ar で終わる外来語の長音をチェックします")
    print(f"モード: {'修正' if fix_mode else 'チェック'}")
    print(f"プロジェクトルート: {project_root}")
    print("-" * 50)
    
    checker.check_directory(project_root, fix=fix_mode)

if __name__ == "__main__":
    main()