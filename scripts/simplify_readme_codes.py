#!/usr/bin/env python3
"""
各章のREADME.mdの解説用コードを目的に合わせて短く、実行可能な形に修正
"""

import os
import re

def process_introduction_readme(readme_path):
    """introduction章は変更不要（主に環境構築の説明）"""
    print("  introduction章: スキップ（環境構築の説明のため）")
    return False

def process_basics_syntax_readme(readme_path):
    """basics-syntax章のREADMEを修正"""
    print("  basics-syntax章を処理中...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. 最初のHello Worldは適切なのでそのまま
    
    # 2. main関数の2つの形式 - 基本形式の例を簡潔に
    basic_main_example = '''int main(void)
{
    printf("Hello from main!\\n");
    return 0;
}'''
    
    # 基本形式の長い例を短いものに置き換え
    content = re.sub(
        r'```c\nint main\(void\)\n\{[^}]+\n    return 0;\n\}\n```',
        f'```c\n{basic_main_example}\n```',
        content,
        count=2  # 最初の2つだけ置き換え
    )
    
    # 3. コマンドライン引数の例
    cmdline_example = '''int main(int argc, char *argv[])
{
    printf("プログラム名: %s\\n", argv[0]);
    if (argc > 1) {
        printf("引数1: %s\\n", argv[1]);
    }
    return 0;
}'''
    
    # コマンドライン引数の説明部分を探して置き換え
    content = re.sub(
        r'(\*\*2\. コマンドライン引数を受け取る形式:\*\*\s*\n```c\n)int main\(void\)\n\{[^}]+\n\}',
        f'\\1{cmdline_example}',
        content
    )
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return True

def process_data_types_readme(readme_path):
    """data-types章のREADMEを修正"""
    print("  data-types章を処理中...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. ファイルスコープの例
    file_scope_example = '''int global_var = 100;  /* ファイル全体で使える */

int main(void)
{
    printf("グローバル変数: %d\\n", global_var);
    return 0;
}'''
    
    # 2. 関数スコープの例
    function_scope_example = '''void function_a(void)
{
    int local_a = 10;  /* この関数内でのみ有効 */
    printf("local_a = %d\\n", local_a);
}

void function_b(void)
{
    /* local_a はここでは使えない */
    int local_b = 20;
    printf("local_b = %d\\n", local_b);
}'''
    
    # 3. ブロックスコープの例
    block_scope_example = '''int main(void)
{
    int x = 10;
    
    if (x > 5) {
        int y = 20;  /* ifブロック内でのみ有効 */
        printf("x = %d, y = %d\\n", x, y);
    }
    /* y はここでは使えない */
    
    return 0;
}'''
    
    # 4. スコープの隠蔽の例
    shadowing_example = '''int x = 100;  /* グローバル変数 */

int main(void)
{
    printf("グローバルx = %d\\n", x);
    
    int x = 200;  /* ローカル変数（グローバルを隠蔽） */
    printf("ローカルx = %d\\n", x);
    
    return 0;
}'''
    
    # 5. 自動変数の例
    auto_var_example = '''void count_calls(void)
{
    int count = 0;  /* 自動変数：毎回0に初期化 */
    count++;
    printf("呼び出し回数: %d\\n", count);
}'''
    
    # 6. 静的変数の例
    static_var_example = '''void count_calls_static(void)
{
    static int count = 0;  /* 静的変数：値を保持 */
    count++;
    printf("呼び出し回数: %d\\n", count);
}'''
    
    # 7. 静的グローバル変数の例
    static_global_example = '''static int file_private = 100;  /* このファイル内でのみ有効 */

int get_private_value(void)
{
    return file_private;
}'''
    
    # 8. レジスタ変数の例
    register_example = '''int main(void)
{
    register int i;  /* 高速アクセス用（推奨） */
    
    for (i = 0; i < 1000000; i++) {
        /* 繰り返し処理 */
    }
    
    return 0;
}'''
    
    # 9. 自動変数の初期化の例
    auto_init_example = '''int main(void)
{
    int a;        /* 初期化なし：不定値 */
    int b = 10;   /* 初期化あり：10 */
    
    printf("a = %d (不定値)\\n", a);
    printf("b = %d\\n", b);
    
    return 0;
}'''
    
    # 10. 静的変数の初期化の例
    static_init_example = '''static int global_static;      /* 0に自動初期化 */
static int global_init = 100;  /* 明示的に初期化 */

void show_values(void)
{
    static int local_static;   /* 0に自動初期化 */
    printf("静的変数: %d, %d, %d\\n", 
           global_static, global_init, local_static);
}'''
    
    # 11. カウンター関数の実装例
    counter_example = '''int get_next_id(void)
{
    static int id = 0;  /* 静的変数で状態を保持 */
    return ++id;
}

int main(void)
{
    printf("ID: %d\\n", get_next_id());  /* 1 */
    printf("ID: %d\\n", get_next_id());  /* 2 */
    printf("ID: %d\\n", get_next_id());  /* 3 */
    return 0;
}'''
    
    # 各セクションを探して置き換え
    replacements = [
        (r'(#### 1\. ファイルスコープ.*?\n```c\n)[^`]+', f'\\1{file_scope_example}'),
        (r'(#### 2\. 関数スコープ.*?\n```c\n)[^`]+', f'\\1{function_scope_example}'),
        (r'(#### 3\. ブロックスコープ.*?\n```c\n)[^`]+', f'\\1{block_scope_example}'),
        (r'(#### 4\. スコープの隠蔽.*?\n```c\n)[^`]+', f'\\1{shadowing_example}'),
        (r'(#### 1\. 自動変数.*?\n```c\n)[^`]+', f'\\1{auto_var_example}'),
        (r'(#### 2\. 静的変数.*?\n```c\n)[^`]+', f'\\1{static_var_example}'),
        (r'(#### 3\. 静的グローバル変数.*?\n```c\n)[^`]+', f'\\1{static_global_example}'),
        (r'(#### 4\. レジスタ変数.*?\n```c\n)[^`]+', f'\\1{register_example}'),
        (r'(#### 自動変数の初期化.*?\n```c\n)[^`]+', f'\\1{auto_init_example}'),
        (r'(#### 静的変数の初期化.*?\n```c\n)[^`]+', f'\\1{static_init_example}'),
        (r'(#### カウンター関数の実装.*?\n```c\n)[^`]+', f'\\1{counter_example}'),
    ]
    
    for pattern, replacement in replacements:
        content = re.sub(pattern, replacement, content, flags=re.DOTALL)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return True

def process_operators_readme(readme_path):
    """operators章のREADMEを修正（演算子の説明は短いコードが多いので変更少なめ）"""
    print("  operators章を処理中...")
    
    # この章は既に短いコード例が多いので、大きな変更は不要
    return False

def process_control_if_readme(readme_path):
    """control-if章のREADMEを修正"""
    print("  control-if章を処理中...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. 単純なif文の例
    simple_if_example = '''int age = 18;

if (age >= 18) {
    printf("成人です\\n");
}'''
    
    # 2. 実生活に例えた単純なif文
    real_life_if_example = '''int temperature = 28;

if (temperature > 25) {
    printf("暑いのでエアコンをつけます\\n");
}'''
    
    # 3. if-else文の例
    if_else_example = '''int score = 75;

if (score >= 60) {
    printf("合格\\n");
} else {
    printf("不合格\\n");
}'''
    
    # 4. if-else if-else文の例
    if_elseif_example = '''int score = 85;

if (score >= 90) {
    printf("秀\\n");
} else if (score >= 80) {
    printf("優\\n");
} else if (score >= 70) {
    printf("良\\n");
} else if (score >= 60) {
    printf("可\\n");
} else {
    printf("不可\\n");
}'''
    
    # 5. ネストしたif文の例
    nested_if_example = '''int age = 20;
int has_license = 1;

if (age >= 18) {
    if (has_license) {
        printf("車を運転できます\\n");
    } else {
        printf("免許を取得してください\\n");
    }
} else {
    printf("18歳未満は運転できません\\n");
}'''
    
    # 6. switch文の基本
    switch_basic_example = '''int day = 3;

switch (day) {
    case 1:
        printf("月曜日\\n");
        break;
    case 2:
        printf("火曜日\\n");
        break;
    case 3:
        printf("水曜日\\n");
        break;
    default:
        printf("その他の曜日\\n");
}'''
    
    # 7. 条件演算子の例
    ternary_example = '''int a = 10, b = 20;
int max = (a > b) ? a : b;
printf("最大値: %d\\n", max);'''
    
    # 置き換え処理
    # 実生活に例えた単純なif文のセクションを探して置き換え
    content = re.sub(
        r'(#### 実生活に例えた単純なif文\s*\n```c\n).*?(\n```)',
        f'\\1{real_life_if_example}\\2',
        content,
        flags=re.DOTALL
    )
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return True

def process_control_loop_readme(readme_path):
    """control-loop章のREADMEを修正"""
    print("  control-loop章を処理中...")
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. 基本的なfor文の使用例
    basic_for_example = '''#include <stdio.h>

int main(void)
{
    int i;
    
    /* 基本的なfor文 */
    printf("1から5まで: ");
    for (i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\\n");
    
    return 0;
}'''
    
    # 2. while文の使用例
    while_example = '''#include <stdio.h>

int main(void)
{
    int count = 1;
    
    printf("while文の例: ");
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\\n");
    
    return 0;
}'''
    
    # 3. do-while文の使用例
    do_while_example = '''#include <stdio.h>

int main(void)
{
    int num;
    
    do {
        printf("正の数を入力（0で終了）: ");
        scanf("%d", &num);
        if (num > 0) {
            printf("入力値: %d\\n", num);
        }
    } while (num != 0);
    
    printf("終了します\\n");
    return 0;
}'''
    
    # 4. break文の例
    break_example = '''#include <stdio.h>

int main(void)
{
    int i;
    
    for (i = 1; i <= 10; i++) {
        if (i == 5) {
            printf("\\n5で終了\\n");
            break;
        }
        printf("%d ", i);
    }
    
    return 0;
}'''
    
    # 5. continue文の例
    continue_example = '''#include <stdio.h>

int main(void)
{
    int i;
    
    printf("奇数のみ: ");
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  /* 偶数をスキップ */
        }
        printf("%d ", i);
    }
    printf("\\n");
    
    return 0;
}'''
    
    # 6. 九九の表（ネストしたループ）
    nested_loop_example = '''#include <stdio.h>

int main(void)
{
    int i, j;
    
    /* 九九の表（3x3のみ） */
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            printf("%2d ", i * j);
        }
        printf("\\n");
    }
    
    return 0;
}'''
    
    # 7. 三角形パターンの出力
    triangle_pattern_example = '''#include <stdio.h>

int main(void)
{
    int i, j;
    int n = 5;
    
    /* 上向き三角形 */
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\\n");
    }
    
    return 0;
}'''
    
    # 8. 無限ループの実用例
    infinite_loop_example = '''#include <stdio.h>

int main(void)
{
    int choice;
    
    while (1) {
        printf("\\n1. 続行\\n");
        printf("0. 終了\\n");
        printf("選択: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        }
        
        printf("処理を続行します\\n");
    }
    
    printf("終了しました\\n");
    return 0;
}'''
    
    # 9. ループ変数の適切な使用
    loop_var_example = '''#include <stdio.h>

int main(void)
{
    int i;  /* C90では先頭で宣言 */
    
    for (i = 0; i < 5; i++) {
        printf("i = %d\\n", i);
    }
    
    /* ループ後もiは有効 */
    printf("最終的なi = %d\\n", i);
    
    return 0;
}'''
    
    # 各セクションを置き換え
    replacements = [
        (r'(#### 基本的な使用例\s*\n```c\n).*?(\n```)', f'\\1{basic_for_example}\\2', 1),
        (r'(#### while文の使用例\s*\n```c\n).*?(\n```)', f'\\1{while_example}\\2', 1),
        (r'(#### do-while文の使用例\s*\n```c\n).*?(\n```)', f'\\1{do_while_example}\\2', 1),
        (r'(#### break文\s*\n.*?\n```c\n).*?(\n```)', f'\\1{break_example}\\2', 1),
        (r'(#### continue文\s*\n.*?\n```c\n).*?(\n```)', f'\\1{continue_example}\\2', 1),
        (r'(#### 二重ループの例\s*\n```c\n).*?(\n```)', f'\\1{nested_loop_example}\\2', 1),
        (r'(#### 三角形パターンの出力\s*\n\s*\n```c\n).*?(\n```)', f'\\1{triangle_pattern_example}\\2', 1),
        (r'(#### 無限ループの実用例\s*\n```c\n).*?(\n```)', f'\\1{infinite_loop_example}\\2', 1),
        (r'(#### ループ変数の適切な使用\s*\n```c\n).*?(\n```)', f'\\1{loop_var_example}\\2', 1),
    ]
    
    for pattern, replacement, count in replacements:
        content = re.sub(pattern, replacement, content, count=count, flags=re.DOTALL)
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return True

def main():
    """メイン処理"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    src_dir = os.path.join(project_root, "src")
    
    chapters = [
        ('introduction', process_introduction_readme),
        ('basics-syntax', process_basics_syntax_readme),
        ('data-types', process_data_types_readme),
        ('operators', process_operators_readme),
        ('control-if', process_control_if_readme),
        ('control-loop', process_control_loop_readme),
    ]
    
    print("解説用コードを簡潔に修正します...")
    print("=" * 60)
    
    for chapter_name, process_func in chapters:
        chapter_path = os.path.join(src_dir, chapter_name)
        readme_path = os.path.join(chapter_path, "README.md")
        
        if os.path.exists(readme_path):
            print(f"\n{chapter_name}章:")
            if process_func(readme_path):
                print(f"  ✅ 修正完了")
        else:
            print(f"\n{chapter_name}章: README.mdが見つかりません")
    
    print("\n" + "=" * 60)
    print("✅ 1-6章の処理が完了しました")

if __name__ == "__main__":
    main()