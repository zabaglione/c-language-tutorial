# 開発環境の詳細設定 - Makefile

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

# 環境チェック
.PHONY: check-env
check-env: examples/environment_check
	@echo "$(YELLOW)=== 開発環境チェック ===$(NC)"
	@./examples/environment_check

# 実行ヘルパー
.PHONY: run-%
run-%: %
	@echo "$(YELLOW)実行中: $<$(NC)"
	@./$<

# コンパイル過程の確認
.PHONY: show-compile-stages
show-compile-stages:
	@echo "$(YELLOW)=== コンパイル過程の確認 ===$(NC)"
	@echo "1. プリプロセッサ処理"
	@$(CC) -E examples/compiler_test.c > compiler_test.i
	@echo "   → compiler_test.i が生成されました"
	@echo "2. コンパイル（アセンブリコード生成）"
	@$(CC) -S compiler_test.i -o compiler_test.s
	@echo "   → compiler_test.s が生成されました"
	@echo "3. アセンブル（オブジェクトファイル生成）"
	@$(CC) -c compiler_test.s -o compiler_test.o
	@echo "   → compiler_test.o が生成されました"
	@echo "4. リンク（実行ファイル生成）"
	@$(CC) compiler_test.o -o compiler_test
	@echo "   → compiler_test が生成されました"
	@echo "$(GREEN)✓ すべての段階が完了しました$(NC)"

# クリーンアップ
.PHONY: clean
clean:
	@echo "$(YELLOW)クリーンアップ中...$(NC)"
	@rm -f $(ALL_BINS)
	@rm -f examples/*.o solutions/*.o
	@rm -f compiler_test.i compiler_test.s compiler_test.o
	@echo "$(GREEN)✓ クリーンアップ完了$(NC)"

# ヘルプ
.PHONY: help
help:
	@echo "使用可能なターゲット:"
	@echo "  make all          - すべてのプログラムをビルド"
	@echo "  make examples     - サンプルプログラムのみビルド"
	@echo "  make solutions    - 解答プログラムのみビルド"
	@echo "  make check-env    - 開発環境をチェック"
	@echo "  make show-compile-stages - コンパイル過程を表示"
	@echo "  make c90/c99/c11/c17 - 特定の規格でビルド"
	@echo "  make run-<program> - 特定のプログラムを実行"
	@echo "  make clean        - ビルド生成物を削除"
	@echo ""
	@echo "C規格の指定:"
	@echo "  make STANDARD=c90  - C90準拠でビルド"
	@echo "  make STANDARD=c99  - C99準拠でビルド（デフォルト）"
	@echo "  make STANDARD=c11  - C11準拠でビルド"
	@echo "  make STANDARD=c17  - C17準拠でビルド"