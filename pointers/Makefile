# Makefile for pointers chapter
# Supports multiple C standards (C90, C99, C11, C17)

CC = gcc
STANDARD ?= c90
CFLAGS = -std=$(STANDARD) -Wall -Wextra -pedantic

EXAMPLE_DIR = examples
SOLUTION_DIR = solutions

# C90 source files
EXAMPLE_SOURCES_C90 = $(wildcard $(EXAMPLE_DIR)/*.c)
SOLUTION_SOURCES_C90 = $(filter-out %_c99.c, $(wildcard $(SOLUTION_DIR)/ex*.c))

# C99 source files
EXAMPLE_SOURCES_C99 = $(wildcard $(EXAMPLE_DIR)/*_c99.c)
SOLUTION_SOURCES_C99 = $(wildcard $(SOLUTION_DIR)/*_c99.c)

# All source files
EXAMPLE_SOURCES = $(EXAMPLE_SOURCES_C90) $(EXAMPLE_SOURCES_C99)
SOLUTION_SOURCES = $(SOLUTION_SOURCES_C90) $(SOLUTION_SOURCES_C99)
ALL_SOURCES = $(EXAMPLE_SOURCES) $(SOLUTION_SOURCES)

# Target executables
EXAMPLE_TARGETS = $(EXAMPLE_SOURCES:.c=)
SOLUTION_TARGETS = $(SOLUTION_SOURCES:.c=)
ALL_TARGETS = $(EXAMPLE_TARGETS) $(SOLUTION_TARGETS)

# デフォルトターゲット
all: $(ALL_TARGETS)

# C99ファイル用の特別なルール（より具体的なため先に配置）
$(EXAMPLE_DIR)/%_c99: $(EXAMPLE_DIR)/%_c99.c
	$(CC) -std=c99 -Wall -Wextra -pedantic $< -o $@

$(SOLUTION_DIR)/%_c99: $(SOLUTION_DIR)/%_c99.c
	$(CC) -std=c99 -Wall -Wextra -pedantic $< -o $@

# C90ファイル用のデフォルトルール
$(EXAMPLE_DIR)/%: $(EXAMPLE_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(SOLUTION_DIR)/%: $(SOLUTION_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# 実行用ターゲット
run-all: run-examples run-solutions

run-examples: $(EXAMPLE_TARGETS)
	@echo "===== ポインタの基本操作デモ ($(STANDARD)) ====="
	@if [ -f $(EXAMPLE_DIR)/pointer_basic ]; then ./$(EXAMPLE_DIR)/pointer_basic; fi
	@echo ""
	@echo "===== ポインタと配列デモ ($(STANDARD)) ====="
	@if [ -f $(EXAMPLE_DIR)/pointer_arrays ]; then ./$(EXAMPLE_DIR)/pointer_arrays; fi
	@echo ""
	@echo "===== ポインタと関数デモ ($(STANDARD)) ====="
	@if [ -f $(EXAMPLE_DIR)/pointer_functions ]; then ./$(EXAMPLE_DIR)/pointer_functions; fi

run-solutions: $(SOLUTION_TARGETS)
	@echo "===== 演習10-1解答: ポインタの基本操作 ($(STANDARD)) ====="
	@if [ -f $(SOLUTION_DIR)/ex10_1_pointer_swap ]; then ./$(SOLUTION_DIR)/ex10_1_pointer_swap; fi
	@echo ""
	@echo "===== 演習10-2解答: 配列の逆順 ($(STANDARD)) ====="
	@if [ -f $(SOLUTION_DIR)/ex10_2_array_reverse ]; then ./$(SOLUTION_DIR)/ex10_2_array_reverse; fi
	@echo ""
	@echo "===== 演習10-3解答: 文字列操作 ($(STANDARD)) ====="
	@if [ -f $(SOLUTION_DIR)/ex10_3_string_manipulation ]; then ./$(SOLUTION_DIR)/ex10_3_string_manipulation; fi
	@echo ""
	@echo "===== 演習10-4解答: 配列関数 ($(STANDARD)) ====="
	@if [ -f $(SOLUTION_DIR)/ex10_4_array_functions ]; then ./$(SOLUTION_DIR)/ex10_4_array_functions; fi

# 個別実行ターゲット
run-pointer_basic: $(EXAMPLE_DIR)/pointer_basic
	./$(EXAMPLE_DIR)/pointer_basic

run-pointer_arrays: $(EXAMPLE_DIR)/pointer_arrays
	./$(EXAMPLE_DIR)/pointer_arrays

run-pointer_functions: $(EXAMPLE_DIR)/pointer_functions
	./$(EXAMPLE_DIR)/pointer_functions

run-ex10_1_pointer_swap: $(SOLUTION_DIR)/ex10_1_pointer_swap
	./$(SOLUTION_DIR)/ex10_1_pointer_swap

run-ex10_2_array_reverse: $(SOLUTION_DIR)/ex10_2_array_reverse
	./$(SOLUTION_DIR)/ex10_2_array_reverse

run-ex10_3_string_manipulation: $(SOLUTION_DIR)/ex10_3_string_manipulation
	./$(SOLUTION_DIR)/ex10_3_string_manipulation

run-ex10_4_array_functions: $(SOLUTION_DIR)/ex10_4_array_functions
	./$(SOLUTION_DIR)/ex10_4_array_functions

# C99版の個別実行ターゲット
run-pointer_basic_c99: $(EXAMPLE_DIR)/pointer_basic_c99
	./$(EXAMPLE_DIR)/pointer_basic_c99

run-pointer_arrays_c99: $(EXAMPLE_DIR)/pointer_arrays_c99
	./$(EXAMPLE_DIR)/pointer_arrays_c99

run-pointer_functions_c99: $(EXAMPLE_DIR)/pointer_functions_c99
	./$(EXAMPLE_DIR)/pointer_functions_c99

run-ex10_1_pointer_swap_c99: $(SOLUTION_DIR)/ex10_1_pointer_swap_c99
	./$(SOLUTION_DIR)/ex10_1_pointer_swap_c99

run-ex10_2_array_reverse_c99: $(SOLUTION_DIR)/ex10_2_array_reverse_c99
	./$(SOLUTION_DIR)/ex10_2_array_reverse_c99

run-ex10_3_string_manipulation_c99: $(SOLUTION_DIR)/ex10_3_string_manipulation_c99
	./$(SOLUTION_DIR)/ex10_3_string_manipulation_c99

run-ex10_4_array_functions_c99: $(SOLUTION_DIR)/ex10_4_array_functions_c99
	./$(SOLUTION_DIR)/ex10_4_array_functions_c99

# デバッグビルド
debug: CFLAGS += -g -DDEBUG -O0
debug: clean all

# 最適化ビルド
release: CFLAGS += -O2 -DNDEBUG
release: clean all

# クリーンアップ
clean:
	rm -f $(ALL_TARGETS)

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all             - 全ての例題と解答をビルド"
	@echo "  run-all         - 全ての例題と解答を実行"
	@echo "  run-examples    - 例題を実行"
	@echo "  run-solutions   - 解答を実行"
	@echo "  clean           - ビルド成果物を削除"
	@echo "  debug           - デバッグビルド"
	@echo "  release         - リリースビルド"
	@echo "  help            - このヘルプを表示"
	@echo ""
	@echo "個別実行:"
	@echo "  run-pointer_basic        - ポインタの基本操作 (C90)"
	@echo "  run-pointer_arrays       - ポインタと配列 (C90)"
	@echo "  run-pointer_functions    - ポインタと関数 (C90)"
	@echo "  run-ex10_1_pointer_swap       - 演習10-1解答 (C90)"
	@echo "  run-ex10_2_array_reverse      - 演習10-2解答 (C90)"
	@echo "  run-ex10_3_string_manipulation - 演習10-3解答 (C90)"
	@echo "  run-ex10_4_array_functions    - 演習10-4解答 (C90)"
	@echo ""
	@echo "C99版:"
	@echo "  run-pointer_basic_c99    - ポインタの基本操作 (C99)"
	@echo "  run-pointer_arrays_c99   - ポインタと配列 (C99)"
	@echo "  run-pointer_functions_c99 - ポインタと関数 (C99)"
	@echo "  run-ex10_1_pointer_swap_c99       - 演習10-1解答 (C99)"
	@echo "  run-ex10_2_array_reverse_c99      - 演習10-2解答 (C99)"
	@echo "  run-ex10_3_string_manipulation_c99 - 演習10-3解答 (C99)"
	@echo "  run-ex10_4_array_functions_c99    - 演習10-4解答 (C99)"
	@echo ""
	@echo "Cスタンダード指定:"
	@echo "  make STANDARD=c90 all   - C90でビルド (デフォルト)"
	@echo "  make STANDARD=c99 all   - C99でビルド"
	@echo "  make STANDARD=c11 all   - C11でビルド"
	@echo "  make STANDARD=c17 all   - C17でビルド"

# 依存関係
.PHONY: all run-all run-examples run-solutions clean debug release help
.PHONY: run-pointer_basic run-pointer_arrays run-pointer_functions
.PHONY: run-ex10_1_pointer_swap run-ex10_2_array_reverse run-ex10_3_string_manipulation run-ex10_4_array_functions
.PHONY: run-pointer_basic_c99 run-pointer_arrays_c99 run-pointer_functions_c99
.PHONY: run-ex10_1_pointer_swap_c99 run-ex10_2_array_reverse_c99 run-ex10_3_string_manipulation_c99 run-ex10_4_array_functions_c99