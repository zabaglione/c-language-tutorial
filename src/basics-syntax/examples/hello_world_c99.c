/*
 * ファイル名: hello_world_c99.c
 * 説明: C言語の最も基本的なプログラム（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}

/*
C99での変更点:
- この基本的なプログラムでは、C90版と同一内容
- より複雑なプログラムでは以下のC99機能を活用可能:
  - forループ内での変数宣言
  - 必要な時点での変数宣言
  - C99特有のデータ型（long long, _Bool等）
  - 配列の可変長宣言など
*/