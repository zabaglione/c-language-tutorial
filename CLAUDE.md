# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a comprehensive C programming tutorial written in Japanese (C言語学習教材). The project teaches C programming from basics to advanced topics through 13 structured chapters, supporting multiple C standards (C90, C99, C11, C17).

The project is organized into:
- `src/` - Source code (tutorial chapters, including C23 optional chapter)
- `scripts/` - Support scripts for document generation
- `output/` - Generated documents
  - `word/` - Word documents (.docx)
  - `pdf/` - PDF documents
  - `html/` - HTML documents
- `docs/` - Project documentation (Markdown)
- `reports/` - Work reports and evaluations

## Common Development Commands

### Building and Running Code

```bash
# Navigate to a chapter
cd src/[chapter-name]

# Build all examples in a chapter
make all

# Build with specific C standard
make clean && make STANDARD=c90    # C90 standard
make clean && make STANDARD=c99    # C99 standard  
make clean && make STANDARD=c11    # C11 standard
make clean && make STANDARD=c17    # C17 standard
make clean && make STANDARD=c23    # C23 standard (compiler support required)

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

Each chapter in `src/` contains:
- `README.md` - Theory and explanations in Japanese
- `examples/` - Demonstration code with detailed comments
- `exercises/` - Practice problems for learners
- `solutions/` - Complete solutions to exercises
- `Makefile` - Build configuration supporting multiple C standards

### Chapter Structure

| Chapter | Directory | Topic | Target Standards |
|---------|-----------|-------|-----------------|
| 1 | introduction | 導入・環境構築 | All standards |
| 2 | basics-syntax | 基本文法・Hello World | C90 |
| 3 | data-types | データ型と変数 | C90/C99 |
| 4 | operators | 演算子 | C90 |
| 5 | control-if | 制御構造（条件分岐） | C90 |
| 6 | control-loop | 制御構造（ループ） | C90/C99 |
| 7 | arrays | 配列 | C90/C99 |
| 8 | strings | 文字列処理 | C90 |
| 9 | functions | 関数 | C90/C99 |
| 10 | pointers | ポインタ基礎 | C90 |
| 11 | structures | 構造体とポインタ | C90/C11 |
| 12 | function-pointers | 関数ポインタ | C90 |
| 13 | advanced | 複数ファイル・発展技術 | C90/C99/C11/C17 |
| 14 | c23-features | C23の新機能（オプション） | C23 |

### Build System Features

1. **Automatic Source Discovery**: Makefiles use wildcard patterns to find all `.c` files
2. **Standard Switching**: `make STANDARD=c99` to compile with different C standards
3. **Dual Version Support**: Most chapters include both C90 and C99 versions (`*_c99.c` files)
4. **Consistent Targets**:
   - `make all` - Build all programs
   - `make examples` - Build example programs
   - `make solutions` - Build exercise solutions
   - `make run-all` - Run all programs
   - `make run-<program>` - Run specific program
   - `make test-standards` - Test with multiple C standards

### Important Conventions

1. **Language**: All documentation and comments are in Japanese. Variable names and function names are typically in English.

2. **Compiler Flags**: Always use `-Wall -Wextra -pedantic` for educational builds to catch potential issues.

3. **C Standard Versions**:
   - Base files follow C90 standard
   - C99 versions have `_c99` suffix
   - Some chapters (function-pointers) organize binaries in a `bin/` directory

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

## Additional Resources

### Generated Documentation

The repository includes several types of generated documentation:

**Word Documents** (`output/word/`):
- `C言語プログラミング教材_メインテキスト.docx` - Main textbook
- `C言語プログラミング教材_演習問題集.docx` - Exercise workbook
- Individual chapter files (e.g., `chapter_01_textbook.docx`)

**PDF Documents** (`output/pdf/`):
- `C言語学習教材.pdf` - Complete tutorial
- `C言語プログラミング教材_メインテキスト.pdf` - Main textbook
- `C言語プログラミング教材_演習課題集.pdf` - Exercise workbook

**HTML Documents** (`output/html/`):
- Various HTML versions for web viewing

### Shell Scripts

Several utility scripts exist in the `scripts/` directory for documentation generation:
- `create_merged_docs_no_samples.sh` - Creates Word documents without sample code/exercises
- `create_pdf.sh` - Generates PDF documentation
- `create_main_textbook.sh` - Creates the main textbook
- `create_exercises.sh` - Creates the exercise workbook

These scripts are used for maintaining the documentation but are not part of the regular development workflow.

## Learning Path Recommendations

For learners using this tutorial:

1. **Standard Path**: introduction → basics-syntax → data-types → operators → control-if → control-loop → arrays → strings → functions → pointers → structures → function-pointers → advanced

2. **Focus on Fundamentals**: Spend extra time on pointers (chapter 10) and structures (chapter 11) as these are critical concepts

3. **Practice with Different Standards**: Try compiling examples with different C standards to understand language evolution

## Notes on Special Chapters

- **introduction**: Contains `test-standards` target for testing compiler compatibility
- **function-pointers**: Uses a `bin/` directory for build outputs instead of in-place compilation
- **advanced**: Covers advanced topics including C11/C17 features like `_Generic` and `_Static_assert`
- **c23-features**: Optional chapter requiring C23 compiler support (gcc -std=c23)

これらのガイドラインに従うことで、学習者にとって一貫性のある、理解しやすい教材を提供できます。