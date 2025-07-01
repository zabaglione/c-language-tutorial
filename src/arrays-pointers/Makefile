# Makefile for 配列とポインタ
# C90およびC99準拠のサンプルコードをビルド

# コンパイラとフラグの設定
CC = gcc
STANDARD ?= c90
CFLAGS = -std=$(STANDARD) -Wall -Wextra -pedantic
DEBUGFLAGS = -g -DDEBUG

# ディレクトリ
EXAMPLES_DIR = examples
SOLUTIONS_DIR = solutions

# ソースファイル
EXAMPLE_SRCS = $(wildcard $(EXAMPLES_DIR)/*.c)
SOLUTION_SRCS = $(wildcard $(SOLUTIONS_DIR)/*.c)

# 実行ファイル名（拡張子を除去）
EXAMPLE_EXECS = $(EXAMPLE_SRCS:.c=)
SOLUTION_EXECS = $(SOLUTION_SRCS:.c=)

# すべてのターゲット
ALL_EXECS = $(EXAMPLE_EXECS) $(SOLUTION_EXECS)

# デフォルトターゲット
.PHONY: all
all: examples solutions

# examplesのビルド
.PHONY: examples
examples: $(EXAMPLE_EXECS)

# solutionsのビルド
.PHONY: solutions
solutions: $(SOLUTION_EXECS)

# パターンルール
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# デバッグビルド
.PHONY: debug
debug: CFLAGS += $(DEBUGFLAGS)
debug: all

# 実行
.PHONY: run-examples
run-examples: examples
	@echo "=== サンプルプログラムの実行 ==="
	@for exec in $(EXAMPLE_EXECS); do \
		echo "\n--- $$exec の実行 ---"; \
		./$$exec; \
	done

.PHONY: run-solutions
run-solutions: solutions
	@echo "=== 演習解答の実行 ==="
	@for exec in $(SOLUTION_EXECS); do \
		echo "\n--- $$exec の実行 ---"; \
		./$$exec; \
	done

.PHONY: run-all
run-all: run-examples run-solutions

# クリーン
.PHONY: clean
clean:
	rm -f $(ALL_EXECS)
	rm -rf *.dSYM
	rm -rf $(EXAMPLES_DIR)/*.dSYM $(SOLUTIONS_DIR)/*.dSYM

# ヘルプ
.PHONY: help
help:
	@echo "使用方法:"
	@echo "  make                - すべてをビルド（C90）"
	@echo "  make STANDARD=c99   - C99モードでビルド"
	@echo "  make examples       - サンプルコードのみビルド"
	@echo "  make solutions      - 演習解答のみビルド"
	@echo "  make debug          - デバッグモードでビルド"
	@echo "  make run-examples   - サンプルを実行"
	@echo "  make run-solutions  - 解答を実行"
	@echo "  make run-all        - すべて実行"
	@echo "  make clean          - ビルドファイルを削除"
	@echo "  make help           - このヘルプを表示"