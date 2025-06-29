# C言語学習教材 - 第5章: 制御構造（ループ）
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
.PHONY: all clean run examples solutions help

all: examples solutions

examples: $(EXAMPLES_BIN)

solutions: $(SOLUTIONS_BIN)

# 例題プログラムのコンパイル
$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 解答例プログラムのコンパイル（数学関数を使用する場合は-lmを追加）
$(SOLUTIONS_DIR)/ex5_3_prime_list: $(SOLUTIONS_DIR)/ex5_3_prime_list.c
	$(CC) $(CFLAGS) $< -o $@ -lm

$(SOLUTIONS_DIR)/ex5_3_prime_list_c99: $(SOLUTIONS_DIR)/ex5_3_prime_list_c99.c
	$(CC) $(CFLAGS) $< -o $@ -lm

$(SOLUTIONS_DIR)/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 個別ターゲット（例題）
for_loop_basics: $(EXAMPLES_DIR)/for_loop_basics
while_dowhile: $(EXAMPLES_DIR)/while_dowhile
break_continue: $(EXAMPLES_DIR)/break_continue

# C99版のターゲット（例題）
for_loop_basics_c99: $(EXAMPLES_DIR)/for_loop_basics_c99
while_dowhile_c99: $(EXAMPLES_DIR)/while_dowhile_c99
break_continue_c99: $(EXAMPLES_DIR)/break_continue_c99

# 個別ターゲット（演習解答例）
ex5_1: $(SOLUTIONS_DIR)/ex5_1_fibonacci
ex5_2: $(SOLUTIONS_DIR)/ex5_2_number_guess
ex5_3: $(SOLUTIONS_DIR)/ex5_3_prime_list
ex5_4: $(SOLUTIONS_DIR)/ex5_4_draw_shapes
ex5_5: $(SOLUTIONS_DIR)/ex5_5_multiplication_table
ex5_6: $(SOLUTIONS_DIR)/ex5_6_factorial

# C99版のターゲット（演習解答例）
ex5_1_c99: $(SOLUTIONS_DIR)/ex5_1_fibonacci_c99
ex5_2_c99: $(SOLUTIONS_DIR)/ex5_2_number_guess_c99
ex5_3_c99: $(SOLUTIONS_DIR)/ex5_3_prime_list_c99
ex5_4_c99: $(SOLUTIONS_DIR)/ex5_4_draw_shapes_c99
ex5_5_c99: $(SOLUTIONS_DIR)/ex5_5_multiplication_table_c99
ex5_6_c99: $(SOLUTIONS_DIR)/ex5_6_factorial_c99

# 実行ターゲット（例題）
run-examples: examples
	@echo "=== ループ構造の例題実行 ==="
	@echo "--- for文の基本 ---"
	@./$(EXAMPLES_DIR)/for_loop_basics
	@echo ""
	@echo "--- while文とdo-while文 ---"
	@./$(EXAMPLES_DIR)/while_dowhile
	@echo ""
	@echo "--- break文とcontinue文 ---"
	@./$(EXAMPLES_DIR)/break_continue

# 実行ターゲット（演習解答例 - 非対話的なもののみ）
run-solutions: ex5_5 ex5_4
	@echo "=== 解答例の実行（非対話的なもの） ==="
	@echo "--- 演習5-5: 掛け算表 ---"
	@echo "9" | ./$(SOLUTIONS_DIR)/ex5_5_multiplication_table
	@echo ""
	@echo "--- 演習5-4: 図形描画 ---"
	@echo "5" | ./$(SOLUTIONS_DIR)/ex5_4_draw_shapes

# 個別実行ターゲット
run-ex5_1: ex5_1
	@echo "10" | ./$(SOLUTIONS_DIR)/ex5_1_fibonacci

run-ex5_2: ex5_2
	./$(SOLUTIONS_DIR)/ex5_2_number_guess

run-ex5_3: ex5_3
	@echo "10 50" | ./$(SOLUTIONS_DIR)/ex5_3_prime_list

run-ex5_4: ex5_4
	@echo "5" | ./$(SOLUTIONS_DIR)/ex5_4_draw_shapes

run-ex5_5: ex5_5
	./$(SOLUTIONS_DIR)/ex5_5_multiplication_table

run-ex5_6: ex5_6
	@echo "5" | ./$(SOLUTIONS_DIR)/ex5_6_factorial

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
	@echo "  for_loop_basics        - for文の基本をコンパイル"
	@echo "  while_dowhile          - while文とdo-while文をコンパイル"
	@echo "  break_continue         - break文とcontinue文をコンパイル"
	@echo "  ex5_1, ex5_2, ...      - 個別の演習解答例をコンパイル"
	@echo "  *_c99                  - C99版をコンパイル"
	@echo "  run-examples           - 例題を実行"
	@echo "  run-solutions          - 非対話的な解答例を実行"
	@echo "  run-ex5_1, ...         - 個別の解答例を実行"
	@echo "  c90/c99/c11            - 指定された規格でコンパイル"
	@echo "  test-standards         - 複数のC規格でコンパイルテスト"
	@echo "  clean                  - 生成されたファイルを削除"
	@echo "  help                   - このヘルプを表示"
	@echo ""
	@echo "例: make STANDARD=c99 solutions"
	@echo ""
	@echo "注意: 素数判定プログラム(ex5_3)は数学ライブラリ(-lm)が必要です"