# C言語学習教材 - 第4章: 制御構造（条件分岐）
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
.PHONY: all clean run run-all run-examples run-exercises run-solutions help

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
if_basic: $(EXAMPLES_DIR)/if_basic
switch_basic: $(EXAMPLES_DIR)/switch_basic
conditional_operator: $(EXAMPLES_DIR)/conditional_operator

# C99版のターゲット（例題）
if_basic_c99: $(EXAMPLES_DIR)/if_basic_c99
switch_basic_c99: $(EXAMPLES_DIR)/switch_basic_c99
conditional_operator_c99: $(EXAMPLES_DIR)/conditional_operator_c99

# 個別ターゲット（演習解答例）
ex4_1: $(SOLUTIONS_DIR)/ex4_1_ticket_pricing
ex4_2: $(SOLUTIONS_DIR)/ex4_2_calculator
ex4_3: $(SOLUTIONS_DIR)/ex4_3_bmi_judge
ex4_4: $(SOLUTIONS_DIR)/ex4_4_leap_year
ex4_5: $(SOLUTIONS_DIR)/ex4_5_grade_system
ex4_6: $(SOLUTIONS_DIR)/ex4_6_janken_game

# C99版のターゲット（演習解答例）
ex4_1_c99: $(SOLUTIONS_DIR)/ex4_1_ticket_pricing_c99
ex4_2_c99: $(SOLUTIONS_DIR)/ex4_2_calculator_c99
ex4_3_c99: $(SOLUTIONS_DIR)/ex4_3_bmi_judge_c99
ex4_4_c99: $(SOLUTIONS_DIR)/ex4_4_leap_year_c99
ex4_5_c99: $(SOLUTIONS_DIR)/ex4_5_grade_system_c99
ex4_6_c99: $(SOLUTIONS_DIR)/ex4_6_janken_game_c99

# 個別ターゲット（解答例）
grade_calculator: $(SOLUTIONS_DIR)/grade_calculator
grade_calculator_c99: $(SOLUTIONS_DIR)/grade_calculator_c99

# 実行ターゲット
run-examples: examples
	@echo "=== 制御構造の例題実行 ==="
	@echo "--- if文の基本 ---"
	@echo "85" | ./$(EXAMPLES_DIR)/if_basic
	@echo ""
	@echo "--- switch文の基本 ---"
	@echo "2" | ./$(EXAMPLES_DIR)/switch_basic
	@echo ""
	@echo "--- 条件演算子 ---"
	@echo "10 5" | ./$(EXAMPLES_DIR)/conditional_operator

run-exercises: ex4_1 ex4_2 ex4_3
	@echo "=== 演習解答例の実行 ==="
	@echo "--- 演習4-1: 料金計算 ---"
	@echo "25" | ./$(SOLUTIONS_DIR)/ex4_1_ticket_pricing
	@echo ""
	@echo "--- 演習4-2: 電卓 ---"
	@echo "10" | echo "+ 5" | ./$(SOLUTIONS_DIR)/ex4_2_calculator
	@echo ""
	@echo "--- 演習4-3: BMI判定 ---"
	@echo "170 65" | ./$(SOLUTIONS_DIR)/ex4_3_bmi_judge

run-solutions: solutions
	@echo "=== 解答例の実行 ==="
	@echo "--- 成績計算システム ---"
	@echo "85 95 90 80 1" | ./$(SOLUTIONS_DIR)/grade_calculator

run-all: run-examples run-exercises run-solutions

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
	$(MAKE) clean && $(MAKE) STANDARD=c90 all
	@echo ""
	@echo "=== C99規格でのコンパイルテスト ==="
	$(MAKE) clean && $(MAKE) STANDARD=c99 all
	@echo ""
	@echo "=== C11規格でのコンパイルテスト ==="
	$(MAKE) clean && $(MAKE) STANDARD=c11 all

# クリーンアップ
clean:
	rm -f $(EXAMPLES_BIN)
	rm -f $(SOLUTIONS_BIN)
	rm -f $(EXERCISES_DIR)/*.o $(EXERCISES_DIR)/a.out
	rm -f $(SOLUTIONS_DIR)/*.o $(SOLUTIONS_DIR)/a.out

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all                    - 全ての例題と解答例をコンパイル"
	@echo "  examples               - 例題プログラムをコンパイル"
	@echo "  solutions              - 解答例をコンパイル"
	@echo "  if_basic               - if文の基本をコンパイル"
	@echo "  switch_basic           - switch文の基本をコンパイル"
	@echo "  conditional_operator   - 条件演算子をコンパイル"
	@echo "  ex4_1, ex4_2, ...      - 個別の演習解答例をコンパイル"
	@echo "  *_c99                  - C99版をコンパイル"
	@echo "  run-examples           - 例題を実行"
	@echo "  run-exercises          - 演習解答例を実行"
	@echo "  run-solutions          - 解答例を実行"
	@echo "  run-all                - 全てを実行"
	@echo "  c90/c99/c11            - 指定された規格でコンパイル"
	@echo "  test-standards         - 複数のC規格でコンパイルテスト"
	@echo "  clean                  - 生成されたファイルを削除"
	@echo "  help                   - このヘルプを表示"
	@echo ""
	@echo "例: make STANDARD=c99 solutions"