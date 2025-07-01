#!/usr/bin/env python3
"""
README.mdの最終的な修正を行うスクリプト
"""

import os
import re

def fix_control_if_readme(project_root):
    """control-if/README.mdを修正"""
    readme_path = os.path.join(project_root, "src", "control-if", "README.md")
    
    print("Final fixing control-if/README.md...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 実生活の例を修正（正しいインデント構造）
    content = re.sub(
        r'(int rain_probability = 70;.*?\n\s*\n)(if \(rain_probability >= 50\).*?\n)(int temperature = 35;.*?\n)(if \(temperature >= 30\).*?\n)\s*}(\s*\n\s*return 0;)',
        r'''\1    if (rain_probability >= 50) {
        printf("傘を持っていきましょう\\n");
    }
    
    int temperature = 35;  /* 気温35度 */
    
    if (temperature >= 30) {
        printf("熱中症に注意！水分補給を忘れずに\\n");
    }\5''',
        content,
        flags=re.DOTALL
    )
    
    # printfのパターンを修正 - 改行が途中で切れている箇所
    content = re.sub(r'printf\("([^"]+)\\n"\);\n"', r'printf("\1\\n");', content)
    
    # printf行で不正な改行を修正
    content = re.sub(
        r'(printf\("[^"]*?)\\n";\s*\n(printf\("[^"]*?\\n"\);)',
        r'\1\\n");\n    \2',
        content
    )
    
    # 比較演算子セクションの修正
    content = re.sub(
        r'(if \(a == b\)\s+printf\("[^"]+)\\n"\);\s*\\n"',
        r'\1\\n");',
        content
    )
    content = re.sub(
        r'(if \(a != b\)\s+printf\("[^"]+)\\n"\);\s*\\n"',
        r'\1\\n");',
        content
    )
    content = re.sub(
        r'(if \(a < b\)\s+printf\("[^"]+)\\n"\);\s*\\n"',
        r'\1\\n");',
        content
    )
    content = re.sub(
        r'(if \(a <= b\)\s+printf\("[^"]+)\\n"\);\s*\\n"',
        r'\1\\n");',
        content
    )
    content = re.sub(
        r'(if \(a > b\)\s+printf\("[^"]+)\\n"\);\s*\\n"',
        r'\1\\n");',
        content
    )
    content = re.sub(
        r'(if \(a >= b\)\s+printf\("[^"]+)\\n"\);\s*\\n"',
        r'\1\\n");',
        content
    )
    
    # 成績判定の閉じ括弧の修正
    content = re.sub(
        r'(printf\("もう少し頑張りましょう\\\\n"\);)\s*\n}\s*\n}',
        r'\1\n}',
        content
    )
    
    # case文の値の修正
    content = re.sub(r'printf\("(\d+)です\\\\n"\)', r'printf("\1です\\n")', content)
    
    # caseのラベル部分も修正
    content = re.sub(
        r'case 1:\s*\n\s*printf\("です\\\\n"\);\s*\n\s*/\* break;.*?\*/\s*\n\s*case 1:',
        r'''case 1:
        printf("1です\\n");
        /* break; を忘れると次のcaseも実行される */
    case 2:''',
        content
    )
    
    # さらにOK版も修正
    content = re.sub(
        r'case 1:\s*\n\s*printf\("です\\\\n"\);\s*\n\s*break;\s*\n\s*case 1:',
        r'''case 1:
        printf("1です\\n");
        break;
    case 2:''',
        content
    )
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("Fixed control-if/README.md")

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    fix_control_if_readme(project_root)
    
    # 他の章も確認
    chapters = ['control-loop', 'arrays', 'strings', 'functions', 'pointers', 
                'structures', 'function-pointers', 'advanced', 'data-types', 
                'operators', 'basics-syntax']
    
    for chapter in chapters:
        readme_path = os.path.join(project_root, "src", chapter, "README.md")
        if os.path.exists(readme_path):
            print(f"\nChecking {chapter}/README.md...")
            
            with open(readme_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            original_content = content
            
            # エスケープシーケンスを修正
            content = content.replace('\\\\n', '\\n')
            
            # printfの不正な改行を修正
            content = re.sub(r'printf\("([^"]+)\\n"\);\n"', r'printf("\1\\n");', content)
            
            # 欠落した値の修正
            content = re.sub(r'for \(i = ; i <', 'for (i = 0; i <', content)
            content = re.sub(r'int a = , b = ;', 'int a = 5, b = 3;', content)
            
            if content != original_content:
                with open(readme_path, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"  Fixed {chapter}/README.md")

if __name__ == "__main__":
    main()