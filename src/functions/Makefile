# C言語学習教材 - 第9章: 関数
# コンパイラとフラグの設定

CC = gcc
CFLAGS_BASE = -Wall -Wextra -pedantic
STANDARD ?= c90
CFLAGS = $(CFLAGS_BASE) -std=$(STANDARD)
LDFLAGS = -lm  # 数学関数用のリンクフラグ

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
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# 解答例プログラムのコンパイル
$(SOLUTIONS_DIR)/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# 個別ターゲット（例題）
function_basics: $(EXAMPLES_DIR)/function_basics
advanced_functions: $(EXAMPLES_DIR)/advanced_functions

# C99版のターゲット（例題）
function_basics_c99: $(EXAMPLES_DIR)/function_basics_c99
advanced_functions_c99: $(EXAMPLES_DIR)/advanced_functions_c99

# 個別ターゲット（解答例）
ex9_1_prime_functions: $(SOLUTIONS_DIR)/ex9_1_prime_functions
ex9_1_prime_functions_c99: $(SOLUTIONS_DIR)/ex9_1_prime_functions_c99
ex9_2_array_operations: $(SOLUTIONS_DIR)/ex9_2_array_operations
ex9_2_array_operations_c99: $(SOLUTIONS_DIR)/ex9_2_array_operations_c99
ex9_3_string_processing: $(SOLUTIONS_DIR)/ex9_3_string_processing
ex9_3_string_processing_c99: $(SOLUTIONS_DIR)/ex9_3_string_processing_c99
ex9_4_multiple_returns: $(SOLUTIONS_DIR)/ex9_4_multiple_returns
ex9_4_multiple_returns_c99: $(SOLUTIONS_DIR)/ex9_4_multiple_returns_c99
ex9_5_error_handling: $(SOLUTIONS_DIR)/ex9_5_error_handling
ex9_5_error_handling_c99: $(SOLUTIONS_DIR)/ex9_5_error_handling_c99
ex9_6_struct_functions: $(SOLUTIONS_DIR)/ex9_6_struct_functions
ex9_6_struct_functions_c99: $(SOLUTIONS_DIR)/ex9_6_struct_functions_c99
ex9_7_recursive_functions: $(SOLUTIONS_DIR)/ex9_7_recursive_functions
ex9_7_recursive_functions_c99: $(SOLUTIONS_DIR)/ex9_7_recursive_functions_c99
ex9_8_advanced_strings: $(SOLUTIONS_DIR)/ex9_8_advanced_strings
ex9_8_advanced_strings_c99: $(SOLUTIONS_DIR)/ex9_8_advanced_strings_c99
ex9_9_sorting_algorithms: $(SOLUTIONS_DIR)/ex9_9_sorting_algorithms
ex9_9_sorting_algorithms_c99: $(SOLUTIONS_DIR)/ex9_9_sorting_algorithms_c99

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
run-function_basics: function_basics
	@echo "=== function_basics の実行 ==="
	@$(EXAMPLES_DIR)/function_basics

run-function_basics_c99: function_basics_c99
	@echo "=== function_basics_c99 の実行 ==="
	@$(EXAMPLES_DIR)/function_basics_c99

run-advanced_functions: advanced_functions
	@echo "=== advanced_functions の実行 ==="
	@$(EXAMPLES_DIR)/advanced_functions

run-advanced_functions_c99: advanced_functions_c99
	@echo "=== advanced_functions_c99 の実行 ==="
	@$(EXAMPLES_DIR)/advanced_functions_c99

# 個別実行ターゲット（解答例）
run-ex9_1: ex9_1_prime_functions
	@echo "=== ex9_1_prime_functions の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_1_prime_functions

run-ex9_1_c99: ex9_1_prime_functions_c99
	@echo "=== ex9_1_prime_functions_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_1_prime_functions_c99

run-ex9_2: ex9_2_array_operations
	@echo "=== ex9_2_array_operations の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_2_array_operations

run-ex9_2_c99: ex9_2_array_operations_c99
	@echo "=== ex9_2_array_operations_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_2_array_operations_c99

run-ex9_3: ex9_3_string_processing
	@echo "=== ex9_3_string_processing の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_3_string_processing

run-ex9_3_c99: ex9_3_string_processing_c99
	@echo "=== ex9_3_string_processing_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_3_string_processing_c99

run-ex9_4: ex9_4_multiple_returns
	@echo "=== ex9_4_multiple_returns の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_4_multiple_returns

run-ex9_4_c99: ex9_4_multiple_returns_c99
	@echo "=== ex9_4_multiple_returns_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_4_multiple_returns_c99

run-ex9_5: ex9_5_error_handling
	@echo "=== ex9_5_error_handling の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_5_error_handling

run-ex9_5_c99: ex9_5_error_handling_c99
	@echo "=== ex9_5_error_handling_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_5_error_handling_c99

run-ex9_6: ex9_6_struct_functions
	@echo "=== ex9_6_struct_functions の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_6_struct_functions

run-ex9_6_c99: ex9_6_struct_functions_c99
	@echo "=== ex9_6_struct_functions_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_6_struct_functions_c99

run-ex9_7: ex9_7_recursive_functions
	@echo "=== ex9_7_recursive_functions の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_7_recursive_functions

run-ex9_7_c99: ex9_7_recursive_functions_c99
	@echo "=== ex9_7_recursive_functions_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_7_recursive_functions_c99

run-ex9_8: ex9_8_advanced_strings
	@echo "=== ex9_8_advanced_strings の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_8_advanced_strings

run-ex9_8_c99: ex9_8_advanced_strings_c99
	@echo "=== ex9_8_advanced_strings_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_8_advanced_strings_c99

run-ex9_9: ex9_9_sorting_algorithms
	@echo "=== ex9_9_sorting_algorithms の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_9_sorting_algorithms

run-ex9_9_c99: ex9_9_sorting_algorithms_c99
	@echo "=== ex9_9_sorting_algorithms_c99 の実行 ==="
	@$(SOLUTIONS_DIR)/ex9_9_sorting_algorithms_c99

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
	@echo ""
	@echo "個別実行（例）:"
	@echo "  make run-function_basics      - function_basicsを実行"
	@echo "  make run-ex9_1               - 演習9-1を実行"
	@echo "  make run-ex9_1_c99           - 演習9-1のC99版を実行"
	@echo ""
	@echo "C標準の指定:"
	@echo "  make STANDARD=c90  - C90でコンパイル（デフォルト）"
	@echo "  make STANDARD=c99  - C99でコンパイル"
	@echo "  make STANDARD=c11  - C11でコンパイル"
	@echo "  make STANDARD=c17  - C17でコンパイル"
	@echo ""
	@echo "注意: 数学関数を使用するプログラムには-lmオプションが自動的に付加されます"