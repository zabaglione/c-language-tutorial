# C言語学習教材 - 第2章: 基本文法・Hello World
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

# 解答例プログラムのコンパイル
$(SOLUTIONS_DIR)/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 個別ターゲット（例題）
hello_world: $(EXAMPLES_DIR)/hello_world
formatted_output: $(EXAMPLES_DIR)/formatted_output
hello_world_c99: $(EXAMPLES_DIR)/hello_world_c99
formatted_output_c99: $(EXAMPLES_DIR)/formatted_output_c99

# 個別ターゲット（解答例）
ex2_1: $(SOLUTIONS_DIR)/ex2_1_hello_intro
ex2_2: $(SOLUTIONS_DIR)/ex2_2_personal_data
ex2_3: $(SOLUTIONS_DIR)/ex2_3_age_calculator
ex2_4: $(SOLUTIONS_DIR)/ex2_4_format_demo
ex2_5: $(SOLUTIONS_DIR)/ex2_5_simple_calculator
ex2_6: $(SOLUTIONS_DIR)/ex2_6_ascii_explorer

# C99版の個別ターゲット
ex2_1_c99: $(SOLUTIONS_DIR)/ex2_1_hello_intro_c99
ex2_2_c99: $(SOLUTIONS_DIR)/ex2_2_personal_data_c99
ex2_3_c99: $(SOLUTIONS_DIR)/ex2_3_age_calculator_c99
ex2_4_c99: $(SOLUTIONS_DIR)/ex2_4_format_demo_c99
ex2_5_c99: $(SOLUTIONS_DIR)/ex2_5_simple_calculator_c99
ex2_6_c99: $(SOLUTIONS_DIR)/ex2_6_ascii_explorer_c99

# 実行ターゲット
run: hello_world
	@echo "=== Hello World プログラムの実行 ==="
	@./$(EXAMPLES_DIR)/hello_world
	@echo ""
	@echo "=== フォーマット出力プログラムの実行 ==="
	@./$(EXAMPLES_DIR)/formatted_output

run-c99: hello_world_c99 formatted_output_c99
	@echo "=== Hello World プログラムの実行 (C99版) ==="
	@./$(EXAMPLES_DIR)/hello_world_c99
	@echo ""
	@echo "=== フォーマット出力プログラムの実行 (C99版) ==="
	@./$(EXAMPLES_DIR)/formatted_output_c99

# 解答例実行（非対話的なもののみ）
run-solutions: ex2_1 ex2_2
	@echo "=== 解答例の実行 ==="
	@echo "--- 課題2-1: 基本的な出力 ---"
	@./$(SOLUTIONS_DIR)/ex2_1_hello_intro
	@echo ""
	@echo "--- 課題2-2: 個人データ表示 ---"
	@./$(SOLUTIONS_DIR)/ex2_2_personal_data

# 個別実行ターゲット
run-ex2_1: ex2_1
	./$(SOLUTIONS_DIR)/ex2_1_hello_intro

run-ex2_2: ex2_2
	./$(SOLUTIONS_DIR)/ex2_2_personal_data

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

# クリーンアップ
clean:
	rm -f $(EXAMPLES_BIN) $(SOLUTIONS_BIN)
	find . -name "*.o" -delete
	find . -name "a.out" -delete

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all                 - 全ての例題と解答例をコンパイル"
	@echo "  examples            - 例題プログラムをコンパイル"
	@echo "  solutions           - 解答例をコンパイル"
	@echo "  hello_world         - Hello Worldプログラムをコンパイル"
	@echo "  formatted_output    - フォーマット出力プログラムをコンパイル"
	@echo "  ex2_1, ex2_2, ...   - 個別の解答例をコンパイル"
	@echo "  ex2_1_c99, ...      - 個別の解答例をコンパイル (C99版)"
	@echo "  run                 - 例題プログラムを実行 (C90版)"
	@echo "  run-c99             - 例題プログラムを実行 (C99版)"
	@echo "  run-solutions       - 非対話的な解答例を実行"
	@echo "  run-ex2_1, ...      - 個別の解答例を実行"
	@echo "  c90/c99/c11         - 指定された規格でコンパイル"
	@echo "  test-standards      - 複数のC規格でコンパイルテスト"
	@echo "  clean               - 生成されたファイルを削除"
	@echo "  help                - このヘルプを表示"
	@echo ""
	@echo "例: make STANDARD=c99 solutions"
