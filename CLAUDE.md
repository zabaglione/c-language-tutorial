# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a comprehensive C programming tutorial written in Japanese (C言語学習教材). The project teaches C programming from basics to advanced topics through 13 structured chapters, supporting multiple C standards (C90, C99, C11, C17).

## Common Development Commands

### Building and Running Code

```bash
# Build all examples in a chapter
make all

# Build with specific C standard
make clean && make STANDARD=c90    # C90 standard
make clean && make STANDARD=c99    # C99 standard  
make clean && make STANDARD=c11    # C11 standard
make clean && make STANDARD=c17    # C17 standard

# Run all examples
make run-all

# Run specific example
make run-<example-name>

# Clean build artifacts
make clean

# Debug build (where available)
make debug

# Check available targets
make help
```

### Testing

```bash
# Run tests (available in introduction and function-pointers chapters)
make test

# Test with different C standards (introduction chapter)
make test-standards
```

### Compilation Without Make

```bash
# Basic compilation
gcc -Wall -Wextra -pedantic -std=c99 source.c -o output

# Debug build
gcc -Wall -Wextra -pedantic -g -DDEBUG -O0 source.c -o output

# Release build
gcc -Wall -Wextra -pedantic -O2 -DNDEBUG source.c -o output
```

## Code Architecture and Structure

### Directory Organization

The project follows a chapter-based structure where each chapter contains:
- `README.md` - Theory and explanations in Japanese
- `examples/` - Demonstration code with detailed comments
- `exercises/` - Practice problems for learners
- `solutions/` - Complete solutions to exercises
- `Makefile` - Build configuration supporting multiple C standards

### Key Architectural Patterns

1. **Educational Code Style**
   - All code includes Japanese comments explaining concepts
   - Examples progress from simple to complex within each chapter
   - Each example is self-contained and compilable independently

2. **Build System Design**
   - Makefiles use pattern rules for automatic source discovery
   - Support for multiple C standards to demonstrate language evolution
   - Consistent targets across all chapters (all, clean, run, help)

3. **Content Progression**
   - Foundation: introduction, basics-syntax, data-types, operators, control-if, control-loop
   - Intermediate: arrays, strings, functions, pointers
   - Advanced: structures, function-pointers, advanced

### Important Conventions

1. **Language**: All documentation and comments are in Japanese. Variable names and function names are typically in English.

2. **Compiler Flags**: Always use `-Wall -Wextra -pedantic` for educational builds to catch potential issues.

3. **C Standard Flexibility**: Examples may use different C standard features. Check the Makefile for the default standard used in each chapter.

4. **No External Dependencies**: This is a pure C tutorial with no external libraries beyond the standard library.

## Working with This Codebase

When modifying or adding to this tutorial:

1. **Maintain Language Consistency**: Keep all documentation and comments in Japanese to match the existing content.

2. **Follow Chapter Structure**: New content should follow the established pattern of examples/, exercises/, and solutions/ directories.

3. **Preserve Educational Value**: Code should prioritize clarity and learning over optimization. Include detailed comments explaining concepts.

4. **Test Multiple Standards**: When adding examples, ensure they compile with the C standards specified in the chapter's Makefile.

5. **Build Before Committing**: Always run `make clean && make all` to ensure all examples compile without warnings.

## Chapter Standardization Guidelines (章の統一ガイドライン)

各章の構造とコードの統一を行う際は、以下のガイドラインに従ってください：

### 1. フォルダー構造の統一

各章は以下の構造を持つ必要があります：

```
chapter-name/
├── Makefile
├── README.md
├── examples/
│   └── *.c files
├── exercises/
│   └── README.md
└── solutions/
    ├── README.md
    └── *.c files
```

### 2. C90とC99バージョンの作成

- **基本方針**: C90を基準とし、C99準拠のコードは `*_c99.c` として別ファイルに作成
- **examples/**: 既存のC90コードに対してC99版を作成
- **solutions/**: 各演習解答にC90版とC99版の両方を作成

### 3. README.mdの更新

- **章のREADME.md**: 
  - ソースコードはC90版をインラインで記載
  - C99版はリンクとして参照
  - 実際のソースファイルの内容を正確に反映

- **exercises/README.md**:
  - 演習番号を明確に記載（例: 演習3-1, 演習3-2...）
  - 絵文字は削除
  - 欠落している数値や値を修正

- **solutions/README.md**:
  - 各演習解答の説明
  - C90版とC99版の両方へのリンク
  - 学習ポイントの記載

### 4. Makefileの作成・更新

標準的なMakefileテンプレート:
- C90/C99/C11/C17の切り替えサポート
- examples/とsolutions/の自動検出
- run-allターゲットの実装
- 個別実行ターゲット（run-ex3_1など）
- helpターゲットの実装

### 5. コーディングスタイル

- **ブレース使用**: if/while/forで実行文が1行でも必ず `{}` を使用
- **改行文字**: `\\n` ではなく `\n` を使用
- **文字エンコーディング**: Unicode文字（×）ではなくASCII文字（x）を使用
- **return文**: `int main(void)` では必ず `return 0;` を記載
- **ファイル末尾**: 必ず改行で終わる

### 6. エラー修正の優先順位

1. includeエラー（`#include <studio.h>` → `#include <stdio.h>`）
2. エスケープシーケンスエラー（`\\n` → `\n`）
3. タイプミス（retrn → return, doble → double）
4. 文字化けや欠落した値の修正

### 7. 演習解答の作成基準

- 各演習に対してC90版とC99版を作成
- ファイル名規則: `ex[章番号]_[演習番号]_[説明].c`
- C99版は `_c99.c` サフィックスを付与
- 詳細なコメントと学習ポイントを含める

### 8. テスト手順

1. 各ファイルをC90でコンパイルしてエラーがないことを確認
2. C99版も同様にテスト
3. 実行して期待される出力が得られることを確認
4. Makefileのすべてのターゲットが動作することを確認

これらのガイドラインに従うことで、学習者にとって一貫性のある、理解しやすい教材を提供できます。