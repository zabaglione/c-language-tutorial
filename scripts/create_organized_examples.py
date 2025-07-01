#!/usr/bin/env python3
"""
Create well-organized code examples for each chapter
"""

import os
import re
import sys

# Define chapter-specific code examples to extract
CHAPTER_EXAMPLES = {
    'introduction': [
        {
            'name': 'hello_world',
            'description': 'Basic Hello World program',
            'code': '''/*
 * Hello World プログラム
 * C言語の最も基本的なプログラム
 */
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\\n");
    return 0;
}'''
        },
        {
            'name': 'compiler_test',
            'description': 'Test different C standards compilation',
            'code': '''/*
 * コンパイラテストプログラム
 * 異なるC規格での動作確認
 */
#include <stdio.h>

int main(void)
{
    printf("=== C言語環境テスト ===\\n");
    printf("コンパイラが正常に動作しています\\n");
    printf("環境構築が完了しました\\n");
    return 0;
}'''
        }
    ],
    
    'basics-syntax': [
        {
            'name': 'hello_world_basic',
            'description': 'Basic Hello World with explanation',
            'code': '''/*
 * Hello World プログラム（基本版）
 * プログラムの基本構造を学習
 */
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\\n");
    return 0;
}'''
        },
        {
            'name': 'formatted_output_demo',
            'description': 'Demonstration of printf formatting',
            'code': '''/*
 * フォーマット出力のデモ
 * printf関数の様々な使い方
 */
#include <stdio.h>

int main(void)
{
    printf("=== フォーマット出力デモ ===\\n");
    
    /* 基本的な文字列出力 */
    printf("こんにちは、世界！\\n");
    
    /* 整数の出力 */
    printf("整数: %d\\n", 42);
    
    /* 文字の出力 */
    printf("文字: %c\\n", 'A');
    
    /* 浮動小数点数の出力 */
    printf("小数: %.2f\\n", 3.14159);
    
    /* 文字列の出力 */
    printf("文字列: %s\\n", "プログラミング");
    
    return 0;
}'''
        },
        {
            'name': 'escape_sequences',
            'description': 'Demonstration of escape sequences',
            'code': '''/*
 * エスケープシーケンスのデモ
 * 特殊文字の使い方
 */
#include <stdio.h>

int main(void)
{
    printf("=== エスケープシーケンス ===\\n");
    
    /* 改行とタブ */
    printf("改行\\nとタブ\\tの例\\n");
    
    /* ダブルクォート */
    printf("ダブルクォート: \\"Hello\\"\\n");
    
    /* バックスラッシュ */
    printf("パス: C:\\\\Program Files\\\\\\n");
    
    /* 表形式の出力 */
    printf("\\n--- 表形式の例 ---\\n");
    printf("名前\\t年齢\\t職業\\n");
    printf("田中\\t25\\tエンジニア\\n");
    printf("佐藤\\t30\\tデザイナー\\n");
    
    return 0;
}'''
        }
    ],
    
    'data-types': [
        {
            'name': 'basic_types',
            'description': 'Basic data types demonstration',
            'code': '''/*
 * 基本データ型のデモ
 * 各データ型の宣言と使用方法
 */
#include <stdio.h>

int main(void)
{
    /* 整数型 */
    int age = 25;
    char letter = 'A';
    short small_num = 1000;
    long big_num = 1234567L;
    
    /* 浮動小数点型 */
    float pi_f = 3.14f;
    double pi_d = 3.141592653589793;
    
    /* 符号なし型 */
    unsigned int positive = 100U;
    
    printf("=== 基本データ型 ===\\n");
    printf("int: %d\\n", age);
    printf("char: %c (%d)\\n", letter, letter);
    printf("short: %d\\n", small_num);
    printf("long: %ld\\n", big_num);
    printf("float: %.2f\\n", pi_f);
    printf("double: %.10f\\n", pi_d);
    printf("unsigned int: %u\\n", positive);
    
    return 0;
}'''
        },
        {
            'name': 'sizeof_demo',
            'description': 'Demonstration of sizeof operator',
            'code': '''/*
 * sizeof演算子のデモ
 * データ型のサイズ確認
 */
#include <stdio.h>

int main(void)
{
    printf("=== データ型のサイズ ===\\n");
    printf("char: %lu バイト\\n", sizeof(char));
    printf("short: %lu バイト\\n", sizeof(short));
    printf("int: %lu バイト\\n", sizeof(int));
    printf("long: %lu バイト\\n", sizeof(long));
    printf("float: %lu バイト\\n", sizeof(float));
    printf("double: %lu バイト\\n", sizeof(double));
    
    /* 変数のサイズ */
    int number = 42;
    printf("\\n変数のサイズ:\\n");
    printf("int number: %lu バイト\\n", sizeof(number));
    
    return 0;
}'''
        },
        {
            'name': 'arithmetic_operations',
            'description': 'Basic arithmetic operations',
            'code': '''/*
 * 基本演算のデモ
 * 四則演算と型変換
 */
#include <stdio.h>

int main(void)
{
    int a = 10, b = 3;
    
    printf("=== 基本演算 ===\\n");
    printf("a = %d, b = %d\\n\\n", a, b);
    
    /* 整数演算 */
    printf("整数演算:\\n");
    printf("%d + %d = %d\\n", a, b, a + b);
    printf("%d - %d = %d\\n", a, b, a - b);
    printf("%d * %d = %d\\n", a, b, a * b);
    printf("%d / %d = %d (整数除算)\\n", a, b, a / b);
    printf("%d %% %d = %d (剰余)\\n", a, b, a % b);
    
    /* 実数演算 */
    printf("\\n実数演算:\\n");
    printf("%.1f / %.1f = %.2f\\n", (double)a, (double)b, (double)a / b);
    
    return 0;
}'''
        }
    ],
    
    'operators': [
        {
            'name': 'comparison_operators',
            'description': 'Comparison operators demonstration',
            'code': '''/*
 * 比較演算子のデモ
 * 各種比較演算子の使用方法
 */
#include <stdio.h>

int main(void)
{
    int a = 5, b = 3, c = 5;
    
    printf("=== 比較演算子 ===\\n");
    printf("a = %d, b = %d, c = %d\\n\\n", a, b, c);
    
    printf("a == b: %d (等しい)\\n", a == b);
    printf("a != b: %d (等しくない)\\n", a != b);
    printf("a > b:  %d (より大きい)\\n", a > b);
    printf("a < b:  %d (より小さい)\\n", a < b);
    printf("a >= c: %d (以上)\\n", a >= c);
    printf("a <= c: %d (以下)\\n", a <= c);
    
    return 0;
}'''
        },
        {
            'name': 'logical_operators',
            'description': 'Logical operators demonstration',
            'code': '''/*
 * 論理演算子のデモ
 * AND, OR, NOT演算子の使用方法
 */
#include <stdio.h>

int main(void)
{
    int age = 25;
    int income = 300000;
    int has_license = 1;
    
    printf("=== 論理演算子 ===\\n");
    printf("年齢: %d, 収入: %d, 免許: %d\\n\\n", age, income, has_license);
    
    /* AND演算子 */
    printf("AND演算子 (&&):\\n");
    printf("年齢20以上 AND 収入200000以上: %d\\n", 
           (age >= 20) && (income >= 200000));
    
    /* OR演算子 */
    printf("\\nOR演算子 (||):\\n");
    printf("年齢18未満 OR 年齢65以上: %d\\n", 
           (age < 18) || (age >= 65));
    
    /* NOT演算子 */
    printf("\\nNOT演算子 (!):\\n");
    printf("免許を持っていない: %d\\n", !has_license);
    
    return 0;
}'''
        }
    ],
    
    'control-if': [
        {
            'name': 'basic_if',
            'description': 'Basic if statement',
            'code': '''/*
 * 基本的なif文のデモ
 * 単純な条件分岐
 */
#include <stdio.h>

int main(void)
{
    int temperature = 28;
    int score = 85;
    
    printf("=== 基本的なif文 ===\\n");
    
    /* 単純なif文 */
    printf("気温: %d度\\n", temperature);
    if (temperature > 25) {
        printf("暑いのでエアコンをつけます\\n");
    }
    
    /* 条件が偽の場合 */
    printf("\\n点数: %d点\\n", score);
    if (score >= 90) {
        printf("優秀な成績です\\n");
    }
    
    return 0;
}'''
        },
        {
            'name': 'if_else',
            'description': 'If-else statement demonstration',
            'code': '''/*
 * if-else文のデモ
 * 二者択一の条件分岐
 */
#include <stdio.h>

int main(void)
{
    int age = 19;
    int password = 1234;
    int input = 1234;
    
    printf("=== if-else文 ===\\n");
    
    /* 成人判定 */
    printf("年齢: %d歳\\n", age);
    if (age >= 20) {
        printf("成人です\\n");
        printf("選挙権があります\\n");
    } else {
        printf("未成年です\\n");
        printf("あと%d年で成人です\\n", 20 - age);
    }
    
    /* パスワード認証 */
    printf("\\nパスワード認証:\\n");
    if (password == input) {
        printf("ログイン成功！\\n");
        printf("ようこそ！\\n");
    } else {
        printf("パスワードが違います\\n");
        printf("もう一度お試しください\\n");
    }
    
    return 0;
}'''
        },
        {
            'name': 'grade_system',
            'description': 'Grade evaluation system using if-else if',
            'code': '''/*
 * 成績判定システム
 * if-else if文を使った多段階判定
 */
#include <stdio.h>

int main(void)
{
    int score = 85;
    
    printf("=== 成績判定システム ===\\n");
    printf("点数: %d点\\n", score);
    
    if (score >= 90) {
        printf("成績: A（優秀）\\n");
        printf("素晴らしい成績です！\\n");
    } else if (score >= 80) {
        printf("成績: B（良好）\\n");
        printf("よく頑張りました！\\n");
    } else if (score >= 70) {
        printf("成績: C（普通）\\n");
        printf("合格です\\n");
    } else if (score >= 60) {
        printf("成績: D（可）\\n");
        printf("ギリギリ合格です\\n");
    } else {
        printf("成績: F（不可）\\n");
        printf("もう少し頑張りましょう\\n");
    }
    
    return 0;
}'''
        }
    ],
    
    'control-loop': [
        {
            'name': 'basic_for',
            'description': 'Basic for loop demonstration',
            'code': '''/*
 * 基本的なfor文のデモ
 * 基礎的な繰り返し処理
 */
#include <stdio.h>

int main(void)
{
    int i;
    
    printf("=== 基本的なfor文 ===\\n");
    
    /* 1から5まで出力 */
    printf("1から5まで: ");
    for (i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\\n");
    
    /* 逆順ループ */
    printf("5から1まで: ");
    for (i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\\n");
    
    /* 偶数のみ */
    printf("偶数のみ: ");
    for (i = 2; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\\n");
    
    return 0;
}'''
        },
        {
            'name': 'while_loop',
            'description': 'While loop demonstration',
            'code': '''/*
 * while文のデモ
 * 条件による繰り返し処理
 */
#include <stdio.h>

int main(void)
{
    int count = 1;
    int sum = 0;
    int i = 1;
    
    printf("=== while文 ===\\n");
    
    /* 基本的なwhile文 */
    printf("1から5まで: ");
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\\n");
    
    /* 累計計算 */
    printf("1から10までの合計: ");
    while (i <= 10) {
        sum += i;
        i++;
    }
    printf("%d\\n", sum);
    
    return 0;
}'''
        },
        {
            'name': 'nested_loops',
            'description': 'Nested loops demonstration',
            'code': '''/*
 * ネストしたループのデモ
 * 二重ループによるパターン出力
 */
#include <stdio.h>

int main(void)
{
    int i, j;
    
    printf("=== ネストしたループ ===\\n");
    
    /* 九九の表（3x3） */
    printf("3x3の九九:\\n");
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            printf("%2d ", i * j);
        }
        printf("\\n");
    }
    
    /* 三角形パターン */
    printf("\\n三角形パターン:\\n");
    for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\\n");
    }
    
    return 0;
}'''
        }
    ]
}

def create_examples_for_chapter(chapter_name, chapter_path):
    """Create example files for a specific chapter"""
    if chapter_name not in CHAPTER_EXAMPLES:
        print(f"No predefined examples for chapter: {chapter_name}")
        return False
    
    examples_dir = os.path.join(chapter_path, 'examples')
    os.makedirs(examples_dir, exist_ok=True)
    
    examples = CHAPTER_EXAMPLES[chapter_name]
    created_files = []
    
    for example in examples:
        # Create C90 version
        c90_filename = f"{example['name']}.c"
        c90_path = os.path.join(examples_dir, c90_filename)
        
        with open(c90_path, 'w', encoding='utf-8') as f:
            f.write(example['code'])
        
        created_files.append(c90_filename)
        
        # Create C99 version with appropriate modifications
        c99_code = example['code'].replace(
            '/*',
            '/*\n * C99バージョン - 必要に応じてC99機能を使用\n *'
        )
        
        c99_filename = f"{example['name']}_c99.c"
        c99_path = os.path.join(examples_dir, c99_filename)
        
        with open(c99_path, 'w', encoding='utf-8') as f:
            f.write(c99_code)
        
        created_files.append(c99_filename)
    
    print(f"Created {len(created_files)} example files for {chapter_name}:")
    for filename in created_files:
        print(f"  - {filename}")
    
    return True

def main():
    """Main function"""
    src_dir = '/Users/zabaglione/clinetest/c-language-tutorial/src'
    
    chapters_to_process = [
        'introduction',
        'basics-syntax',
        'data-types', 
        'operators',
        'control-if',
        'control-loop'
    ]
    
    print("Creating organized code examples...\n")
    
    for chapter in chapters_to_process:
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_path):
            print(f"Processing chapter: {chapter}")
            create_examples_for_chapter(chapter, chapter_path)
            print()
        else:
            print(f"Chapter directory not found: {chapter}")
    
    print("Code example creation completed!")

if __name__ == "__main__":
    main()