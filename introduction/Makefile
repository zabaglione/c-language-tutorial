# C言語学習教材 - 第1章: はじめに
# コンパイラとフラグの設定

CC = gcc
CFLAGS_BASE = -Wall -Wextra -pedantic
STANDARD ?= c90
CFLAGS = $(CFLAGS_BASE) -std=$(STANDARD)

# ディレクトリ設定
EXAMPLES_DIR = examples
EXERCISES_DIR = exercises
SOLUTIONS_DIR = solutions

# ソースファイル
EXAMPLES_SRC = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLES_BIN = $(EXAMPLES_SRC:.c=)

SOLUTIONS_SRC = $(wildcard $(SOLUTIONS_DIR)/*.c)
SOLUTIONS_BIN = $(SOLUTIONS_SRC:.c=)

# デフォルトターゲット
.PHONY: all clean run run-all run-examples run-solutions help

all: examples solutions

examples: $(EXAMPLES_BIN)

solutions: $(SOLUTIONS_BIN)

# 例題プログラムのコンパイル
$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 解答例プログラムのコンパイル
$(SOLUTIONS_DIR)/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 個別ターゲット（例題）
environment_check: $(EXAMPLES_DIR)/environment_check

# 個別ターゲット（解答例）
ex1_3_hello_name: $(SOLUTIONS_DIR)/ex1_3_hello_name
ex1_3_hello_name_c99: $(SOLUTIONS_DIR)/ex1_3_hello_name_c99
ex1_6_system_info: $(SOLUTIONS_DIR)/ex1_6_system_info
ex1_6_system_info_c99: $(SOLUTIONS_DIR)/ex1_6_system_info_c99

# 実行ターゲット
run-all: run-examples run-solutions

run-examples: examples
	@echo "=== 例題プログラムの実行 ==="
	@for prog in $(EXAMPLES_BIN); do \
		echo "\n--- $$prog の実行 ---"; \
		$$prog || true; \
	done

run-solutions: solutions
	@echo "=== 解答例プログラムの実行 ==="
	@for prog in $(SOLUTIONS_BIN); do \
		echo "\n--- $$prog の実行 ---"; \
		$$prog || true; \
	done

# 個別実行ターゲット（例題）
run-environment_check: environment_check
	@echo "=== environment_check の実行 ==="
	@$(EXAMPLES_DIR)/environment_check

# 個別実行ターゲット（解答例）
run-ex1_3_hello_name: ex1_3_hello_name
	@echo "=== ex1_3_hello_name の実行 ==="
	@$(SOLUTIONS_DIR)/ex1_3_hello_name

run-ex1_3_hello_name_c99: ex1_3_hello_name_c99
	@echo "=== ex1_3_hello_name_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex1_3_hello_name_c99

run-ex1_6_system_info: ex1_6_system_info
	@echo "=== ex1_6_system_info の実行 ==="
	@$(SOLUTIONS_DIR)/ex1_6_system_info

run-ex1_6_system_info_c99: ex1_6_system_info_c99
	@echo "=== ex1_6_system_info_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex1_6_system_info_c99

# 規格テスト用の特別ターゲット
test-standards: clean
	@echo "=== C規格別のコンパイルテスト ==="
	@echo "\n--- C90でコンパイル ---"
	$(MAKE) STANDARD=c90 environment_check
	@echo "\n--- C99でコンパイル ---"
	$(MAKE) STANDARD=c99 environment_check
	@echo "\n--- C11でコンパイル ---"
	$(MAKE) STANDARD=c11 environment_check
	@echo "\n--- C17でコンパイル ---"
	$(MAKE) STANDARD=c17 environment_check
	@echo "\n=== 各規格での実行結果 ==="
	@echo "\n--- C90 ---"
	@$(EXAMPLES_DIR)/environment_check
	@echo "\n--- C99 ---"
	@$(MAKE) clean > /dev/null 2>&1
	@$(MAKE) STANDARD=c99 environment_check > /dev/null 2>&1
	@$(EXAMPLES_DIR)/environment_check
	@echo "\n--- C11 ---"
	@$(MAKE) clean > /dev/null 2>&1
	@$(MAKE) STANDARD=c11 environment_check > /dev/null 2>&1
	@$(EXAMPLES_DIR)/environment_check
	@echo "\n--- C17 ---"
	@$(MAKE) clean > /dev/null 2>&1
	@$(MAKE) STANDARD=c17 environment_check > /dev/null 2>&1
	@$(EXAMPLES_DIR)/environment_check

# クリーンアップ
clean:
	rm -f $(EXAMPLES_BIN) $(SOLUTIONS_BIN)
	rm -f $(EXAMPLES_DIR)/*.dSYM
	rm -f $(SOLUTIONS_DIR)/*.dSYM
	rm -rf $(EXAMPLES_DIR)/*.dSYM/
	rm -rf $(SOLUTIONS_DIR)/*.dSYM/

# ヘルプ
help:
	@echo "使用可能なターゲット:"
	@echo "  all             - すべてのプログラムをコンパイル"
	@echo "  examples        - 例題プログラムをコンパイル"
	@echo "  solutions       - 解答例プログラムをコンパイル"
	@echo "  clean           - ビルド生成物を削除"
	@echo "  run-all         - すべてのプログラムを実行"
	@echo "  run-examples    - 例題プログラムを実行"
	@echo "  run-solutions   - 解答例プログラムを実行"
	@echo "  test-standards  - 全C規格でコンパイル・実行テスト"
	@echo ""
	@echo "個別実行（例）:"
	@echo "  make run-environment_check     - environment_checkを実行"
	@echo "  make run-ex1_3_hello_name      - ex1_3_hello_nameを実行"
	@echo "  make run-ex1_6_system_info     - ex1_6_system_infoを実行"
	@echo ""
	@echo "C標準の指定:"
	@echo "  make STANDARD=c90  - C90でコンパイル（デフォルト）"
	@echo "  make STANDARD=c99  - C99でコンパイル"
	@echo "  make STANDARD=c11  - C11でコンパイル"
	@echo "  make STANDARD=c17  - C17でコンパイル"