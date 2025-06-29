# Makefile for data-types chapter
# C言語学習教材 - データ型・変数・スコープ章

# コンパイラとフラグの設定
CC = gcc
STANDARD ?= c90
CFLAGS = -std=$(STANDARD) -Wall -Wextra -pedantic
MATHFLAGS = -lm

# ディレクトリ設定
EXAMPLES_DIR = examples
SOLUTIONS_DIR = solutions

# ソースファイルとターゲットファイルの自動検出
EXAMPLE_SOURCES = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_TARGETS = $(EXAMPLE_SOURCES:.c=)

SOLUTION_SOURCES = $(wildcard $(SOLUTIONS_DIR)/*.c)
SOLUTION_TARGETS = $(SOLUTION_SOURCES:.c=)

# すべてのターゲット
ALL_TARGETS = $(EXAMPLE_TARGETS) $(SOLUTION_TARGETS)

# デフォルトターゲット
.PHONY: all clean run run-examples run-solutions help test

all: $(ALL_TARGETS)

# 個別のコンパイルルール
$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(MATHFLAGS)

$(SOLUTIONS_DIR)/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(MATHFLAGS)

# 特定のプログラムのコンパイル
data_types_demo: $(EXAMPLES_DIR)/data_types_demo
data_types_demo_c99: $(EXAMPLES_DIR)/data_types_demo_c99

# 演習問題のコンパイル
ex3_1: $(SOLUTIONS_DIR)/ex3_1_variable_declaration
ex3_1_c99: $(SOLUTIONS_DIR)/ex3_1_variable_declaration_c99
ex3_2: $(SOLUTIONS_DIR)/ex3_2_calculator
ex3_2_c99: $(SOLUTIONS_DIR)/ex3_2_calculator_c99
ex3_3: $(SOLUTIONS_DIR)/ex3_3_sizeof_demo
ex3_3_c99: $(SOLUTIONS_DIR)/ex3_3_sizeof_demo_c99
ex3_4: $(SOLUTIONS_DIR)/ex3_4_type_conversion
ex3_4_c99: $(SOLUTIONS_DIR)/ex3_4_type_conversion_c99
ex3_5: $(SOLUTIONS_DIR)/ex3_5_scope_experiment
ex3_5_c99: $(SOLUTIONS_DIR)/ex3_5_scope_experiment_c99
ex3_6: $(SOLUTIONS_DIR)/ex3_6_constants_demo
ex3_6_c99: $(SOLUTIONS_DIR)/ex3_6_constants_demo_c99
ex3_7: $(SOLUTIONS_DIR)/ex3_7_temperature_converter
ex3_7_c99: $(SOLUTIONS_DIR)/ex3_7_temperature_converter_c99

# 実行ターゲット
run: run-examples

run-examples: $(EXAMPLE_TARGETS)
	@echo "=== データ型デモプログラムの実行 ==="
	@for target in $(EXAMPLE_TARGETS); do \
		if [ -f $$target ]; then \
			echo "--- $$target の実行 ---"; \
			./$$target; \
			echo; \
		fi \
	done

run-solutions: $(SOLUTION_TARGETS)
	@echo "=== 演習解答プログラムの実行 ==="
	@for target in $(SOLUTION_TARGETS); do \
		if [ -f $$target ]; then \
			echo "--- $$target の実行 ---"; \
			./$$target; \
			echo; \
		fi \
	done

# 特定のプログラムの実行
run-data_types_demo: $(EXAMPLES_DIR)/data_types_demo
	./$(EXAMPLES_DIR)/data_types_demo

run-data_types_demo_c99: $(EXAMPLES_DIR)/data_types_demo_c99
	./$(EXAMPLES_DIR)/data_types_demo_c99


# 演習問題の実行
run-ex3_1: $(SOLUTIONS_DIR)/ex3_1_variable_declaration
	./$(SOLUTIONS_DIR)/ex3_1_variable_declaration

run-ex3_1_c99: $(SOLUTIONS_DIR)/ex3_1_variable_declaration_c99
	./$(SOLUTIONS_DIR)/ex3_1_variable_declaration_c99

run-ex3_2: $(SOLUTIONS_DIR)/ex3_2_calculator
	./$(SOLUTIONS_DIR)/ex3_2_calculator

run-ex3_2_c99: $(SOLUTIONS_DIR)/ex3_2_calculator_c99
	./$(SOLUTIONS_DIR)/ex3_2_calculator_c99

run-ex3_3: $(SOLUTIONS_DIR)/ex3_3_sizeof_demo
	./$(SOLUTIONS_DIR)/ex3_3_sizeof_demo

run-ex3_3_c99: $(SOLUTIONS_DIR)/ex3_3_sizeof_demo_c99
	./$(SOLUTIONS_DIR)/ex3_3_sizeof_demo_c99

run-ex3_4: $(SOLUTIONS_DIR)/ex3_4_type_conversion
	./$(SOLUTIONS_DIR)/ex3_4_type_conversion

run-ex3_4_c99: $(SOLUTIONS_DIR)/ex3_4_type_conversion_c99
	./$(SOLUTIONS_DIR)/ex3_4_type_conversion_c99

run-ex3_5: $(SOLUTIONS_DIR)/ex3_5_scope_experiment
	./$(SOLUTIONS_DIR)/ex3_5_scope_experiment

run-ex3_5_c99: $(SOLUTIONS_DIR)/ex3_5_scope_experiment_c99
	./$(SOLUTIONS_DIR)/ex3_5_scope_experiment_c99

run-ex3_6: $(SOLUTIONS_DIR)/ex3_6_constants_demo
	./$(SOLUTIONS_DIR)/ex3_6_constants_demo

run-ex3_6_c99: $(SOLUTIONS_DIR)/ex3_6_constants_demo_c99
	./$(SOLUTIONS_DIR)/ex3_6_constants_demo_c99

run-ex3_7: $(SOLUTIONS_DIR)/ex3_7_temperature_converter
	./$(SOLUTIONS_DIR)/ex3_7_temperature_converter

run-ex3_7_c99: $(SOLUTIONS_DIR)/ex3_7_temperature_converter_c99
	./$(SOLUTIONS_DIR)/ex3_7_temperature_converter_c99

# 異なるC標準でのテスト
test: test-c90 test-c99

test-c90:
	@echo "=== C90標準でのコンパイルテスト ==="
	$(MAKE) clean
	$(MAKE) STANDARD=c90 all
	@echo "C90コンパイル成功"

test-c99:
	@echo "=== C99標準でのコンパイルテスト ==="
	$(MAKE) clean
	$(MAKE) STANDARD=c99 all
	@echo "C99コンパイル成功"

# クリーンアップ
clean:
	rm -f $(ALL_TARGETS)
	@echo "クリーンアップ完了"

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all              - すべてのプログラムをコンパイル"
	@echo "  clean            - 生成されたファイルを削除"
	@echo "  run              - サンプルプログラムを実行"
	@echo "  run-examples     - サンプルプログラムを実行"
	@echo "  run-solutions    - 演習解答プログラムを実行"
	@echo "  test             - C90とC99でコンパイルテスト"
	@echo ""
	@echo "個別プログラム:"
	@echo "  data_types_demo  - データ型デモプログラム（C90）"
	@echo "  data_types_demo_c99 - データ型デモプログラム（C99）"
	@echo ""
	@echo "演習問題:"
	@echo "  ex3_1, ex3_1_c99 - 変数宣言と初期化"
	@echo "  ex3_2, ex3_2_c99 - 四則演算計算機"
	@echo "  ex3_3, ex3_3_c99 - データ型サイズの確認"
	@echo "  ex3_4, ex3_4_c99 - 型変換の理解"
	@echo "  ex3_5, ex3_5_c99 - スコープの実験"
	@echo "  ex3_6, ex3_6_c99 - 定数の活用"
	@echo "  ex3_7, ex3_7_c99 - 温度変換プログラム"
	@echo ""
	@echo "実行例:"
	@echo "  make run-ex3_1   - 演習3-1を実行"
	@echo "  make STANDARD=c99 all - C99でコンパイル"