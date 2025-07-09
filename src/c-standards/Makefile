# C言語の規格と歴史 - Makefile

# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = 

# C言語規格の設定（デフォルトはC99）
STANDARD ?= c99
CFLAGS += -std=$(STANDARD)

# ソースファイルと実行ファイル
EXAMPLE_SRCS = $(wildcard examples/*.c)
SOLUTION_SRCS = $(wildcard solutions/*.c)
ALL_SRCS = $(EXAMPLE_SRCS) $(SOLUTION_SRCS)

# ソースファイルから実行ファイル名を生成
EXAMPLE_BINS = $(EXAMPLE_SRCS:.c=)
SOLUTION_BINS = $(SOLUTION_SRCS:.c=)
ALL_BINS = $(EXAMPLE_BINS) $(SOLUTION_BINS)

# 色付き出力
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m

# デフォルトターゲット
.PHONY: all
all: examples solutions
	@echo "$(GREEN)✓ すべてのプログラムのビルドが完了しました$(NC)"

# examplesのビルド
.PHONY: examples
examples: $(EXAMPLE_BINS)
	@echo "$(GREEN)✓ サンプルプログラムのビルドが完了しました$(NC)"

# solutionsのビルド
.PHONY: solutions
solutions: $(SOLUTION_BINS)
	@echo "$(GREEN)✓ 解答プログラムのビルドが完了しました$(NC)"

# 汎用的なビルドルール
%: %.c
	@echo "$(YELLOW)コンパイル中: $< → $@$(NC)"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# 各規格でのビルドターゲット
.PHONY: c90 c99 c11 c17
c90:
	@$(MAKE) clean
	@$(MAKE) all STANDARD=c90

c99:
	@$(MAKE) clean
	@$(MAKE) all STANDARD=c99

c11:
	@$(MAKE) clean
	@$(MAKE) all STANDARD=c11

c17:
	@$(MAKE) clean
	@$(MAKE) all STANDARD=c17

# 規格テスト（異なる規格での動作確認）
.PHONY: test-standards
test-standards:
	@echo "$(YELLOW)=== C90でのテスト ===$(NC)"
	@$(MAKE) c90
	@if [ -f examples/standard_test ]; then ./examples/standard_test; fi
	@echo "\n$(YELLOW)=== C99でのテスト ===$(NC)"
	@$(MAKE) c99
	@if [ -f examples/standard_test ]; then ./examples/standard_test; fi
	@echo "\n$(YELLOW)=== C11でのテスト ===$(NC)"
	@$(MAKE) c11
	@if [ -f examples/standard_test ]; then ./examples/standard_test; fi

# 実行ヘルパー
.PHONY: run-%
run-%: %
	@echo "$(YELLOW)実行中: $<$(NC)"
	@./$<

# クリーンアップ
.PHONY: clean
clean:
	@echo "$(YELLOW)クリーンアップ中...$(NC)"
	@rm -f $(ALL_BINS)
	@rm -f examples/*.o solutions/*.o
	@echo "$(GREEN)✓ クリーンアップ完了$(NC)"

# ヘルプ
.PHONY: help
help:
	@echo "使用可能なターゲット:"
	@echo "  make all          - すべてのプログラムをビルド"
	@echo "  make examples     - サンプルプログラムのみビルド"
	@echo "  make solutions    - 解答プログラムのみビルド"
	@echo "  make c90/c99/c11/c17 - 特定の規格でビルド"
	@echo "  make test-standards - 各規格での動作テスト"
	@echo "  make run-<program> - 特定のプログラムを実行"
	@echo "  make clean        - ビルド生成物を削除"
	@echo ""
	@echo "C規格の指定:"
	@echo "  make STANDARD=c90  - C90準拠でビルド"
	@echo "  make STANDARD=c99  - C99準拠でビルド（デフォルト）"
	@echo "  make STANDARD=c11  - C11準拠でビルド"
	@echo "  make STANDARD=c17  - C17準拠でビルド"