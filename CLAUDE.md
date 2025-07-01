# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a comprehensive C programming tutorial written in Japanese (C言語学習教材). The project teaches C programming from basics to advanced topics through 14 structured chapters, supporting multiple C standards (C90, C99, C11, C17, C23).

**Primary Purpose**: Educational material for learning C programming, designed for Japanese learners from beginner to advanced levels.

## Directory Structure

```
c-language-tutorial/
├── src/                 # Tutorial chapters (14 chapters)
│   ├── introduction/    # 第1章: 導入・環境構築
│   ├── basics-syntax/   # 第2章: 基本文法・Hello World
│   └── ...             # Chapters 3-14
├── scripts/            # Document generation scripts
├── output/             # Generated documents
│   ├── word/          # Word documents (.docx)
│   ├── pdf/           # PDF documents
│   └── html/          # HTML documents
├── docs/              # Project documentation (Markdown)
└── reports/           # Work reports and evaluations
```

## Common Development Commands

### Building and Running Code

```bash
# Navigate to a chapter
cd src/[chapter-name]

# Build all examples in a chapter
make all

# Build with specific C standard
make clean && make STANDARD=c90    # C90 standard (default)
make clean && make STANDARD=c99    # C99 standard  
make clean && make STANDARD=c11    # C11 standard
make clean && make STANDARD=c17    # C17 standard
make clean && make STANDARD=c23    # C23 standard (compiler support required)

# Run all examples
make run-all

# Run specific example
make run-<example-name>  # e.g., make run-ex1_hello

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

### Direct Compilation (without Make)

```bash
# Basic compilation
gcc -Wall -Wextra -pedantic -std=c99 source.c -o output

# Debug build
gcc -Wall -Wextra -pedantic -g -DDEBUG -O0 source.c -o output

# Release build
gcc -Wall -Wextra -pedantic -O2 -DNDEBUG source.c -o output
```

### Document Generation

```bash
# Generate Word documents
cd scripts
./create_main_textbook.sh      # Main textbook
./create_exercises.sh           # Exercise workbook

# Generate PDF documents
./create_pdf.sh                 # Requires Chrome/Chromium

# Combine all chapters
./combine_chapters.sh
```

## High-Level Architecture

### Chapter Organization

Each chapter follows this consistent structure:
```
chapter-name/
├── Makefile          # Build configuration with multi-standard support
├── README.md         # Theory and explanations in Japanese
├── examples/         # Demonstration code
│   ├── *.c          # C90 standard (base version)
│   └── *_c99.c      # C99 standard version
├── exercises/        # Practice problems
│   └── README.md    # Exercise descriptions
└── solutions/        # Complete solutions
    ├── README.md    # Solution explanations
    ├── *.c          # C90 versions
    └── *_c99.c      # C99 versions
```

### Build System Architecture

1. **Makefile Pattern**: Each chapter has a standardized Makefile that:
   - Auto-discovers source files using `$(wildcard *.c)`
   - Supports multiple C standards via `STANDARD` variable
   - Provides consistent targets across all chapters
   - Handles both C90 base files and C99 variants (`*_c99.c`)

2. **Special Cases**:
   - `function-pointers` chapter uses a `bin/` directory for outputs
   - `introduction` chapter includes `test-standards` target
   - `c23-features` chapter requires C23 compiler support

### Learning Path Structure

| Level | Chapters | Topics | Key Files |
|-------|----------|---------|-----------|
| 🟢 Beginner | 1-6 | Introduction through loops | Basic syntax, data types, operators |
| 🟡 Intermediate | 7-10 | Arrays through pointers | Memory concepts, string handling |
| 🔴 Advanced | 11-13 | Structures through multi-file | Complex data structures, modular programming |
| 🟣 Optional | 14 | C23 features | Modern C language features |

## Code Architecture and Conventions

### Coding Standards

1. **Language Convention**:
   - Documentation/comments: Japanese (日本語)
   - Code identifiers: English
   - Error messages: Japanese

2. **File Naming**:
   - Base files: C90 standard (e.g., `hello.c`)
   - C99 versions: `_c99` suffix (e.g., `hello_c99.c`)
   - Exercise solutions: `ex[chapter]_[number]_[description].c`

3. **Code Style Requirements**:
   ```c
   // ALWAYS use braces, even for single statements
   if (condition) {
       statement;
   }
   
   // Correct escape sequences
   printf("Hello\n");  // NOT printf("Hello\\n");
   
   // ASCII only in code (no Unicode)
   // Use 'x' not '×'
   
   // Always include return in main
   int main(void) {
       // code
       return 0;  // Required
   }
   ```

4. **Compiler Flags**:
   - Always use: `-Wall -Wextra -pedantic`
   - Educational focus: prioritize warnings/errors for learning

### Error Fixing Priority

When fixing code issues, address in this order:
1. Include errors (e.g., `#include <studio.h>` → `#include <stdio.h>`)
2. Escape sequence errors (`\\n` → `\n`)
3. Typos (e.g., `retrn` → `return`, `doble` → `double`)
4. Missing or corrupted values

## Working with This Codebase

### When Adding New Content

1. **Maintain Structure**: Follow the established chapter directory pattern
2. **Dual Versions**: Create both C90 and C99 versions when appropriate
3. **Japanese Comments**: Include detailed explanations in Japanese
4. **Educational Focus**: Prioritize clarity over optimization

### Before Committing

1. **Build Test**: Run `make clean && make all` in the chapter directory
2. **Standard Test**: Verify compilation with target C standards
3. **Documentation**: Update README.md files to reflect changes
4. **Exercise Solutions**: Ensure all exercises have working solutions

### Common Pitfalls to Avoid

1. **Don't mix C standards** in base files (use separate `_c99.c` files)
2. **Don't use Unicode characters** in source code
3. **Don't forget braces** for single-line if/while/for statements
4. **Don't omit return 0** in main functions
5. **Don't use `\\n`** instead of `\n` in strings

## Key Technical Details

### Makefile Variables and Targets

- `STANDARD`: Controls C standard (c90, c99, c11, c17, c23)
- `CFLAGS`: Compiler flags, always includes `-Wall -Wextra -pedantic`
- Pattern rules: `%.o: %.c` for automatic compilation
- Phony targets: `.PHONY` prevents conflicts with file names

### Platform Considerations

- Primary development on Unix-like systems (Linux, macOS)
- Windows users should use WSL or MinGW
- Line endings: LF (not CRLF)
- Character encoding: UTF-8

### Special Chapter Notes

- **introduction**: Contains environment setup and standard testing utilities
- **function-pointers**: Uses separate `bin/` directory for build outputs
- **advanced**: Demonstrates C11/C17 features like `_Generic` and `_Static_assert`
- **c23-features**: Optional chapter requiring modern compiler (gcc 13+ with -std=c23)

## Generated Documentation

The project maintains multiple documentation formats:

**Source Documents** (in `docs/`):
- `main_textbook.md` - Complete tutorial content (can be generated from chapter READMEs)
- `exercises_workbook.md` - All exercises compiled
- `complete_tutorial.md` - Everything combined

**Generated Outputs** (in `output/`):
- Word: `C言語プログラミング教材_メインテキスト.docx` (main textbook)
- Word: `C言語プログラミング教材_演習問題集.docx` (exercise workbook)
- PDF: Various PDF versions for different use cases
- HTML: Web-viewable versions

### Documentation Management Scripts

The `scripts/` directory contains tools for managing documentation:

**Synchronization Scripts:**
- `update_chapter_readmes.py` - Splits main_textbook.md content into individual chapter README.md files
- `generate_main_textbook.py` - Combines chapter README.md files into main_textbook.md

**Generation Scripts:**
- `create_main_textbook.sh` - Creates Word version of main textbook
- `create_exercises.sh` - Creates Word version of exercise workbook
- `create_pdf.sh` - Generates PDF documentation (requires Chrome/Chromium)

**Documentation Workflow:**
```bash
# After editing main_textbook.md, update chapters:
python3 scripts/update_chapter_readmes.py

# After editing chapter README.md files, regenerate main textbook:
python3 scripts/generate_main_textbook.py
# Then review and rename if satisfactory:
mv docs/main_textbook_generated.md docs/main_textbook.md
```

## Quick Reference

### Run a Single Test
```bash
cd src/introduction
make test
```

### Build Only Examples (not Solutions)
```bash
make examples
```

### Build and Run Everything in a Chapter
```bash
make all && make run-all
```

### Check Which Programs Will Be Built
```bash
make help
```

### Test Multiple C Standards
```bash
# In chapters that support it
make test-standards
```

### Generate All Documentation
```bash
cd scripts
./create_main_textbook.sh && ./create_exercises.sh && ./create_pdf.sh
```