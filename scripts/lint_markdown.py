#!/usr/bin/env python3
"""
Markdownファイルのリンティングと修正を行うスクリプト
"""

import os
import re
import sys
from pathlib import Path

class MarkdownLinter:
    def __init__(self):
        self.errors = []
        self.fixed_count = 0
        
    def lint_file(self, filepath, fix=False):
        """単一のMarkdownファイルをリンティング"""
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            print(f"Error reading {filepath}: {e}")
            return
            
        original_content = content
        
        # 各種ルールを適用
        if fix:
            content = self.fix_list_spacing(content)
            content = self.fix_heading_spacing(content)
            content = self.fix_trailing_whitespace(content)
            content = self.fix_multiple_blank_lines(content)
            content = self.fix_code_block_spacing(content)
        else:
            self.check_list_spacing(content, filepath)
            self.check_heading_spacing(content, filepath)
            self.check_trailing_whitespace(content, filepath)
            self.check_multiple_blank_lines(content, filepath)
            self.check_code_block_spacing(content, filepath)
        
        # 修正モードで内容が変更された場合、ファイルを更新
        if fix and content != original_content:
            try:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                self.fixed_count += 1
                print(f"✅ 修正: {filepath}")
            except Exception as e:
                print(f"Error writing {filepath}: {e}")
                
    def check_list_spacing(self, content, filepath):
        """リストの前後の空行をチェック"""
        lines = content.split('\n')
        
        for i, line in enumerate(lines):
            # リストアイテムかどうか
            if re.match(r'^(\s*[-*+]|\s*\d+\.)\s', line):
                # 前の行をチェック（最初のリストアイテムの場合）
                if i > 0:
                    prev_line = lines[i-1]
                    # 前の行もリストアイテムでないかチェック
                    if not re.match(r'^(\s*[-*+]|\s*\d+\.)\s', prev_line) and prev_line.strip():
                        self.errors.append(f"{filepath}: Line {i+1}: MD032 - リストの前に空行が必要です")
                
                # 次の行をチェック（最後のリストアイテムの場合）
                if i < len(lines) - 1:
                    next_line = lines[i+1]
                    # 次の行がリストアイテムでも空行でもない場合
                    if not re.match(r'^(\s*[-*+]|\s*\d+\.)\s', next_line) and next_line.strip():
                        # さらに次の行も確認（リストが終わっているか）
                        is_last_item = True
                        for j in range(i+1, len(lines)):
                            if not lines[j].strip():
                                continue
                            if re.match(r'^(\s*[-*+]|\s*\d+\.)\s', lines[j]):
                                is_last_item = False
                            break
                        
                        if is_last_item:
                            self.errors.append(f"{filepath}: Line {i+2}: MD032 - リストの後に空行が必要です")
    
    def fix_list_spacing(self, content):
        """リストの前後に空行を追加"""
        lines = content.split('\n')
        result = []
        i = 0
        
        while i < len(lines):
            line = lines[i]
            
            # リストアイテムの場合
            if re.match(r'^(\s*[-*+]|\s*\d+\.)\s', line):
                # リストブロックの開始を検出
                if i == 0 or not re.match(r'^(\s*[-*+]|\s*\d+\.)\s', lines[i-1]):
                    # 前に空行を追加（必要な場合）
                    if result and result[-1].strip():
                        result.append('')
                
                # リストブロックを収集
                list_block = [line]
                j = i + 1
                while j < len(lines):
                    if re.match(r'^(\s*[-*+]|\s*\d+\.)\s', lines[j]):
                        list_block.append(lines[j])
                        j += 1
                    elif not lines[j].strip():
                        # 空行は保持
                        list_block.append(lines[j])
                        j += 1
                        # 次の行もチェック
                        if j < len(lines) and re.match(r'^(\s*[-*+]|\s*\d+\.)\s', lines[j]):
                            continue
                        else:
                            break
                    else:
                        break
                
                # リストブロックを追加
                result.extend(list_block)
                
                # リストの後に空行を追加（必要な場合）
                if j < len(lines) and lines[j].strip():
                    result.append('')
                
                i = j
            else:
                result.append(line)
                i += 1
        
        return '\n'.join(result)
    
    def check_heading_spacing(self, content, filepath):
        """見出しの前後の空行をチェック"""
        lines = content.split('\n')
        
        for i, line in enumerate(lines):
            if re.match(r'^#{1,6}\s', line):
                # 前の行をチェック（ファイルの先頭を除く）
                if i > 0 and lines[i-1].strip():
                    self.errors.append(f"{filepath}: Line {i+1}: 見出しの前に空行が必要です")
    
    def fix_heading_spacing(self, content):
        """見出しの前後に適切な空行を追加"""
        lines = content.split('\n')
        result = []
        
        for i, line in enumerate(lines):
            # 見出しの場合
            if re.match(r'^#{1,6}\s', line):
                # 前に空行を追加（必要な場合）
                if i > 0 and result and result[-1].strip():
                    result.append('')
            
            result.append(line)
        
        return '\n'.join(result)
    
    def check_trailing_whitespace(self, content, filepath):
        """行末の空白をチェック"""
        lines = content.split('\n')
        
        for i, line in enumerate(lines):
            if line.endswith(' ') or line.endswith('\t'):
                self.errors.append(f"{filepath}: Line {i+1}: MD009 - 行末に空白があります")
    
    def fix_trailing_whitespace(self, content):
        """行末の空白を削除"""
        lines = content.split('\n')
        return '\n'.join(line.rstrip() for line in lines)
    
    def check_multiple_blank_lines(self, content, filepath):
        """連続する空行をチェック"""
        lines = content.split('\n')
        blank_count = 0
        
        for i, line in enumerate(lines):
            if not line.strip():
                blank_count += 1
                if blank_count > 1:
                    self.errors.append(f"{filepath}: Line {i+1}: MD012 - 連続する空行があります")
            else:
                blank_count = 0
    
    def fix_multiple_blank_lines(self, content):
        """連続する空行を1つに減らす"""
        lines = content.split('\n')
        result = []
        blank_count = 0
        
        for line in lines:
            if not line.strip():
                blank_count += 1
                if blank_count <= 1:
                    result.append(line)
            else:
                blank_count = 0
                result.append(line)
        
        # 末尾の空行を1つだけにする
        while len(result) > 1 and not result[-1].strip() and not result[-2].strip():
            result.pop()
        
        return '\n'.join(result)
    
    def check_code_block_spacing(self, content, filepath):
        """コードブロックの前後の空行をチェック"""
        lines = content.split('\n')
        in_code_block = False
        
        for i, line in enumerate(lines):
            if line.strip().startswith('```'):
                if not in_code_block:
                    # コードブロックの開始
                    if i > 0 and lines[i-1].strip() and not lines[i-1].strip().startswith('```'):
                        self.errors.append(f"{filepath}: Line {i+1}: コードブロックの前に空行が必要です")
                    in_code_block = True
                else:
                    # コードブロックの終了
                    in_code_block = False
                    if i < len(lines) - 1 and lines[i+1].strip() and not lines[i+1].strip().startswith('```'):
                        self.errors.append(f"{filepath}: Line {i+2}: コードブロックの後に空行が必要です")
    
    def fix_code_block_spacing(self, content):
        """コードブロックの前後に空行を追加"""
        lines = content.split('\n')
        result = []
        in_code_block = False
        
        for i, line in enumerate(lines):
            if line.strip().startswith('```'):
                if not in_code_block:
                    # コードブロックの開始
                    if result and result[-1].strip() and not result[-1].strip().startswith('```'):
                        result.append('')
                    in_code_block = True
                else:
                    # コードブロックの終了
                    in_code_block = False
                    result.append(line)
                    if i < len(lines) - 1 and lines[i+1].strip() and not lines[i+1].strip().startswith('```'):
                        result.append('')
                    continue
            
            result.append(line)
        
        return '\n'.join(result)
    
    def lint_directory(self, directory, fix=False):
        """ディレクトリ内のすべてのMarkdownファイルをリンティング"""
        md_files = []
        
        # Markdownファイルを収集
        for root, dirs, files in os.walk(directory):
            # 除外するディレクトリ
            if 'node_modules' in root or 'output' in root or '.git' in root:
                continue
                
            for file in files:
                if file.endswith('.md'):
                    md_files.append(os.path.join(root, file))
        
        print(f"{'修正' if fix else 'チェック'}中: {len(md_files)} 個のMarkdownファイル")
        
        # 各ファイルをリンティング
        for filepath in sorted(md_files):
            self.lint_file(filepath, fix)
        
        # 結果を表示
        if fix:
            print(f"\n✅ {self.fixed_count} 個のファイルを修正しました")
        else:
            if self.errors:
                print(f"\n❌ {len(self.errors)} 個のエラーが見つかりました:")
                for error in self.errors[:20]:  # 最初の20個のエラーを表示
                    print(f"  {error}")
                if len(self.errors) > 20:
                    print(f"  ... 他 {len(self.errors) - 20} 個のエラー")
                print("\n修正するには --fix オプションを使用してください")
            else:
                print("\n✅ エラーは見つかりませんでした")

def main():
    linter = MarkdownLinter()
    fix_mode = '--fix' in sys.argv
    
    # プロジェクトルートを取得
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    
    print(f"Markdownリンター {'(修正モード)' if fix_mode else '(チェックモード)'}")
    print(f"プロジェクトルート: {project_root}")
    print("-" * 50)
    
    linter.lint_directory(project_root, fix=fix_mode)

if __name__ == "__main__":
    main()