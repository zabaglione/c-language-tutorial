# C言語学習教材 - 第6章: 配列
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
array_basics: $(EXAMPLES_DIR)/array_basics
multidimensional_arrays: $(EXAMPLES_DIR)/multidimensional_arrays
string_arrays: $(EXAMPLES_DIR)/string_arrays

# C99版のターゲット（例題）
array_basics_c99: $(EXAMPLES_DIR)/array_basics_c99
multidimensional_arrays_c99: $(EXAMPLES_DIR)/multidimensional_arrays_c99
string_arrays_c99: $(EXAMPLES_DIR)/string_arrays_c99

# 個別ターゲット（解答例）
ex6_1: $(SOLUTIONS_DIR)/ex6_1
ex6_2: $(SOLUTIONS_DIR)/ex6_2
ex6_3: $(SOLUTIONS_DIR)/ex6_3
ex6_4: $(SOLUTIONS_DIR)/ex6_4
ex6_5: $(SOLUTIONS_DIR)/ex6_5
challenge1: $(SOLUTIONS_DIR)/challenge1
challenge2: $(SOLUTIONS_DIR)/challenge2

# C99版のターゲット（解答例）
ex6_1_c99: $(SOLUTIONS_DIR)/ex6_1_c99
ex6_2_c99: $(SOLUTIONS_DIR)/ex6_2_c99
ex6_3_c99: $(SOLUTIONS_DIR)/ex6_3_c99
ex6_4_c99: $(SOLUTIONS_DIR)/ex6_4_c99
ex6_5_c99: $(SOLUTIONS_DIR)/ex6_5_c99
challenge1_c99: $(SOLUTIONS_DIR)/challenge1_c99
challenge2_c99: $(SOLUTIONS_DIR)/challenge2_c99

# 実行ターゲット
run-examples: examples
	@echo "=== 配列の例題実行 ==="
	@echo "--- 1次元配列の基本 ---"
	@./$(EXAMPLES_DIR)/array_basics
	@echo ""
	@echo "--- 多次元配列 ---"
	@./$(EXAMPLES_DIR)/multidimensional_arrays
	@echo ""
	@echo "--- 文字列配列 ---"
	@./$(EXAMPLES_DIR)/string_arrays

run-solutions: solutions
	@echo "=== 解答例の実行 ==="
	@echo "--- 演習6-1: 数値の統計 ---"
	@echo "1 2 3 4 5" | ./$(SOLUTIONS_DIR)/ex6_1
	@echo ""
	@echo "--- 演習6-2: 配列の検索 ---"
	@echo "10 1 2 3 4 5 6 7 8 9 10 3" | ./$(SOLUTIONS_DIR)/ex6_2

run-all: run-examples run-solutions

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
	@echo "  all                      - 全ての例題と解答例をコンパイル"
	@echo "  examples                 - 例題プログラムをコンパイル"
	@echo "  solutions                - 解答例をコンパイル"
	@echo "  array_basics             - 配列基本プログラムをコンパイル"
	@echo "  multidimensional_arrays  - 多次元配列プログラムをコンパイル"
	@echo "  string_arrays            - 文字列配列プログラムをコンパイル"
	@echo "  ex6_1, ex6_2, ...        - 個別の解答例をコンパイル"
	@echo "  challenge1, challenge2   - チャレンジ問題をコンパイル"
	@echo "  *_c99                    - C99版をコンパイル"
	@echo "  run-examples             - 例題を実行"
	@echo "  run-solutions            - 解答例を実行"
	@echo "  run-all                  - 全てを実行"
	@echo "  c90/c99/c11              - 指定された規格でコンパイル"
	@echo "  test-standards           - 複数のC規格でコンパイルテスト"
	@echo "  clean                    - 生成されたファイルを削除"
	@echo "  help                     - このヘルプを表示"
	@echo ""
	@echo "例: make STANDARD=c99 examples"