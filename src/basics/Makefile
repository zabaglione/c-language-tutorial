# C言語学習教材 - 第1章: C言語の基本
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
.PHONY: all clean run run-solutions help

all: examples solutions

examples: $(EXAMPLES_BIN)

solutions: $(SOLUTIONS_BIN)

# 例題プログラムのコンパイル
$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 解答例プログラムのコンパイル
$(SOLUTIONS_DIR)/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ -lm

# 個別ターゲット（解答例）
ex1_1: $(SOLUTIONS_DIR)/ex1_1_self_introduction
ex1_2: $(SOLUTIONS_DIR)/ex1_2_message_box
ex1_3: $(SOLUTIONS_DIR)/ex1_3_weekday_display
ex2_1: $(SOLUTIONS_DIR)/ex2_1_personal_info
ex2_2: $(SOLUTIONS_DIR)/ex2_2_data_type_sizes
ex2_3: $(SOLUTIONS_DIR)/ex2_3_type_conversion
ex3_1: $(SOLUTIONS_DIR)/ex3_1_calculator
ex3_2: $(SOLUTIONS_DIR)/ex3_2_temperature_converter
ex3_3: $(SOLUTIONS_DIR)/ex3_3_geometry_calculator
ex4_1: $(SOLUTIONS_DIR)/ex4_1_compound_assignment
ex4_2: $(SOLUTIONS_DIR)/ex4_2_increment_decrement
ex4_3: $(SOLUTIONS_DIR)/ex4_3_ternary_operator
ex5_1: $(SOLUTIONS_DIR)/ex5_1_household_budget
ex5_2: $(SOLUTIONS_DIR)/ex5_2_loan_calculator

# C99版のターゲット
ex1_1_c99: $(SOLUTIONS_DIR)/ex1_1_self_introduction_c99
ex1_2_c99: $(SOLUTIONS_DIR)/ex1_2_message_box_c99
ex1_3_c99: $(SOLUTIONS_DIR)/ex1_3_weekday_display_c99
ex2_1_c99: $(SOLUTIONS_DIR)/ex2_1_personal_info_c99
ex2_2_c99: $(SOLUTIONS_DIR)/ex2_2_data_type_sizes_c99
ex2_3_c99: $(SOLUTIONS_DIR)/ex2_3_type_conversion_c99
ex3_1_c99: $(SOLUTIONS_DIR)/ex3_1_calculator_c99
ex3_2_c99: $(SOLUTIONS_DIR)/ex3_2_temperature_converter_c99
ex3_3_c99: $(SOLUTIONS_DIR)/ex3_3_geometry_calculator_c99
ex4_1_c99: $(SOLUTIONS_DIR)/ex4_1_compound_assignment_c99
ex4_2_c99: $(SOLUTIONS_DIR)/ex4_2_increment_decrement_c99
ex4_3_c99: $(SOLUTIONS_DIR)/ex4_3_ternary_operator_c99
ex5_1_c99: $(SOLUTIONS_DIR)/ex5_1_household_budget_c99
ex5_2_c99: $(SOLUTIONS_DIR)/ex5_2_loan_calculator_c99

# 実行ターゲット
run-solutions: solutions
	@echo "=== 解答例の実行 ==="
	@echo "--- 演習1-1: 自己紹介 ---"
	@./$(SOLUTIONS_DIR)/ex1_1_self_introduction
	@echo ""
	@echo "--- 演習2-1: 個人情報 ---"
	@./$(SOLUTIONS_DIR)/ex2_1_personal_info
	@echo ""
	@echo "--- 演習3-1: 電卓 ---"
	@echo "5 3" | ./$(SOLUTIONS_DIR)/ex3_1_calculator
	@echo ""
	@echo "--- 演習3-2: 温度変換 ---"
	@echo "25" | ./$(SOLUTIONS_DIR)/ex3_2_temperature_converter

# 規格別コンパイル
c90:
	$(MAKE) STANDARD=c90 all

c99:
	$(MAKE) STANDARD=c99 all

c11:
	$(MAKE) STANDARD=c11 all

# 規格別テスト
test-standards:
	@echo "=== C90規格でのコンパイルテスト ==="
	$(MAKE) clean && $(MAKE) STANDARD=c90 solutions
	@echo ""
	@echo "=== C99規格でのコンパイルテスト ==="
	$(MAKE) clean && $(MAKE) STANDARD=c99 solutions
	@echo ""
	@echo "=== C11規格でのコンパイルテスト ==="
	$(MAKE) clean && $(MAKE) STANDARD=c11 solutions

# クリーンアップ
clean:
	rm -f $(EXAMPLES_BIN)
	rm -f $(SOLUTIONS_BIN)
	rm -f $(EXERCISES_DIR)/*.o $(EXERCISES_DIR)/a.out
	rm -f $(SOLUTIONS_DIR)/*.o $(SOLUTIONS_DIR)/a.out

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all                 - 全ての例題と解答例をコンパイル"
	@echo "  examples            - 例題プログラムをコンパイル"
	@echo "  solutions           - 解答例をコンパイル"
	@echo "  ex1_1, ex2_1, ...   - 個別の解答例をコンパイル"
	@echo "  ex1_1_c99, ...      - 個別の解答例をコンパイル (C99版)"
	@echo "  run-solutions       - 解答例を実行"
	@echo "  c90/c99/c11         - 指定された規格でコンパイル"
	@echo "  test-standards      - 複数のC規格でコンパイルテスト"
	@echo "  clean               - 生成されたファイルを削除"
	@echo "  help                - このヘルプを表示"
	@echo ""
	@echo "例: make STANDARD=c99 solutions"