# Makefile for operators chapter
# 演算子と式の章

# コンパイラとフラグの設定
CC = gcc
STANDARD ?= c90
CFLAGS_BASE = -Wall -Wextra -pedantic
CFLAGS_DEBUG = $(CFLAGS_BASE) -g -DDEBUG -O0
CFLAGS_RELEASE = $(CFLAGS_BASE) -O2 -DNDEBUG

# 標準規格に応じたフラグ設定
ifeq ($(STANDARD),c90)
    CFLAGS = $(CFLAGS_BASE) -std=c90
    CFLAGS_DEBUG := $(CFLAGS_DEBUG) -std=c90
    CFLAGS_RELEASE := $(CFLAGS_RELEASE) -std=c90
else ifeq ($(STANDARD),c99)
    CFLAGS = $(CFLAGS_BASE) -std=c99
    CFLAGS_DEBUG := $(CFLAGS_DEBUG) -std=c99
    CFLAGS_RELEASE := $(CFLAGS_RELEASE) -std=c99
else ifeq ($(STANDARD),c11)
    CFLAGS = $(CFLAGS_BASE) -std=c11
    CFLAGS_DEBUG := $(CFLAGS_DEBUG) -std=c11
    CFLAGS_RELEASE := $(CFLAGS_RELEASE) -std=c11
else ifeq ($(STANDARD),c17)
    CFLAGS = $(CFLAGS_BASE) -std=c17
    CFLAGS_DEBUG := $(CFLAGS_DEBUG) -std=c17
    CFLAGS_RELEASE := $(CFLAGS_RELEASE) -std=c17
endif

# ソースファイルの検出
EXAMPLE_SOURCES = $(wildcard examples/*.c)
SOLUTION_SOURCES = $(wildcard solutions/*.c)

# バイナリファイル名の生成
EXAMPLE_TARGETS = $(EXAMPLE_SOURCES:.c=)
SOLUTION_TARGETS = $(SOLUTION_SOURCES:.c=)

# 全ターゲット
ALL_TARGETS = $(EXAMPLE_TARGETS) $(SOLUTION_TARGETS)

# デフォルトターゲット
all: $(ALL_TARGETS)

# 例題のビルド
examples: $(EXAMPLE_TARGETS)

# 解答例のビルド
solutions: $(SOLUTION_TARGETS)

# 汎用ビルドルール
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# C99ファイル用の特別なビルドルール
%_c99: %_c99.c
	$(CC) $(CFLAGS_BASE) -std=c99 $< -o $@

# デバッグビルド
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: $(ALL_TARGETS)

# リリースビルド
release: CFLAGS = $(CFLAGS_RELEASE)
release: $(ALL_TARGETS)

# 全例題の実行
run-all: examples
	@echo "===== 演算子の基本デモ (C$(STANDARD)) ====="
	@if [ -f examples/operators_demo ]; then ./examples/operators_demo; fi
	@if [ -f examples/operators_demo_c99 ]; then echo ""; echo "===== 演算子の基本デモ (C99版) ====="; ./examples/operators_demo_c99; fi
	@echo ""
	@echo "===== ビット演算デモ (C$(STANDARD)) ====="
	@if [ -f examples/bitwise_demo ]; then ./examples/bitwise_demo; fi
	@if [ -f examples/bitwise_demo_c99 ]; then echo ""; echo "===== ビット演算デモ (C99版) ====="; ./examples/bitwise_demo_c99; fi
	@echo ""
	@echo "===== 演算子優先順位デモ (C$(STANDARD)) ====="
	@if [ -f examples/precedence_demo ]; then ./examples/precedence_demo; fi
	@if [ -f examples/precedence_demo_c99 ]; then echo ""; echo "===== 演算子優先順位デモ (C99版) ====="; ./examples/precedence_demo_c99; fi

# 個別実行ターゲット
run-operators_demo: examples/operators_demo
	./examples/operators_demo

run-operators_demo_c99: examples/operators_demo_c99
	./examples/operators_demo_c99

run-bitwise_demo: examples/bitwise_demo
	./examples/bitwise_demo

run-bitwise_demo_c99: examples/bitwise_demo_c99
	./examples/bitwise_demo_c99

run-precedence_demo: examples/precedence_demo
	./examples/precedence_demo

run-precedence_demo_c99: examples/precedence_demo_c99
	./examples/precedence_demo_c99

# 解答例の実行ターゲット
run-ex4_1_calculator: solutions/ex4_1_calculator
	./solutions/ex4_1_calculator

run-ex4_1_calculator_c99: solutions/ex4_1_calculator_c99
	./solutions/ex4_1_calculator_c99

run-ex4_2_comparison: solutions/ex4_2_comparison
	./solutions/ex4_2_comparison

run-ex4_2_comparison_c99: solutions/ex4_2_comparison_c99
	./solutions/ex4_2_comparison_c99

run-ex4_3_increment: solutions/ex4_3_increment
	./solutions/ex4_3_increment

run-ex4_3_increment_c99: solutions/ex4_3_increment_c99
	./solutions/ex4_3_increment_c99

run-ex4_4_bitwise: solutions/ex4_4_bitwise
	./solutions/ex4_4_bitwise

run-ex4_4_bitwise_c99: solutions/ex4_4_bitwise_c99
	./solutions/ex4_4_bitwise_c99

run-ex4_5_conditional: solutions/ex4_5_conditional
	./solutions/ex4_5_conditional

run-ex4_5_conditional_c99: solutions/ex4_5_conditional_c99
	./solutions/ex4_5_conditional_c99

run-ex4_6_precedence: solutions/ex4_6_precedence
	./solutions/ex4_6_precedence

run-ex4_6_precedence_c99: solutions/ex4_6_precedence_c99
	./solutions/ex4_6_precedence_c99

# クリーンアップ
clean:
	rm -f $(ALL_TARGETS)

# ヘルプの表示
help:
	@echo "利用可能なターゲット:"
	@echo "  all              - 全てのプログラムをビルド"
	@echo "  examples         - 例題のみビルド"
	@echo "  solutions        - 解答例のみビルド"
	@echo "  run-all          - 全例題を実行"
	@echo "  clean            - 生成されたファイルを削除"
	@echo "  help             - このヘルプを表示"
	@echo ""
	@echo "個別実行:"
	@echo "  run-operators_demo      - 演算子デモを実行"
	@echo "  run-operators_demo_c99  - 演算子デモ(C99)を実行"
	@echo "  run-bitwise_demo        - ビット演算デモを実行"
	@echo "  run-bitwise_demo_c99    - ビット演算デモ(C99)を実行"
	@echo "  run-precedence_demo     - 優先順位デモを実行"
	@echo "  run-precedence_demo_c99 - 優先順位デモ(C99)を実行"
	@echo ""
	@echo "解答例実行:"
	@echo "  run-ex4_1_calculator    - 四則演算電卓演習解答"
	@echo "  run-ex4_2_comparison    - 比較演算子演習解答"
	@echo "  run-ex4_3_increment     - インクリメント/デクリメント演習解答"
	@echo "  run-ex4_4_bitwise       - ビット演算演習解答"
	@echo "  run-ex4_5_conditional   - 条件演算子演習解答"
	@echo "  run-ex4_6_precedence    - 演算子優先順位演習解答"
	@echo "  (各解答例のC99版は末尾に_c99を付加)"
	@echo ""
	@echo "ビルド設定:"
	@echo "  STANDARD=c90|c99|c11|c17 - C標準規格を指定 (デフォルト: c90)"
	@echo "  debug                    - デバッグ版をビルド"
	@echo "  release                  - リリース版をビルド"
	@echo ""
	@echo "使用例:"
	@echo "  make STANDARD=c99        - C99でビルド"
	@echo "  make clean && make debug - デバッグ版をビルド"

# 依存関係の定義
.PHONY: all examples solutions run-all debug release clean help \
        run-operators_demo run-operators_demo_c99 \
        run-bitwise_demo run-bitwise_demo_c99 \
        run-precedence_demo run-precedence_demo_c99 \
        run-ex4_1_calculator run-ex4_1_calculator_c99 \
        run-ex4_2_comparison run-ex4_2_comparison_c99 \
        run-ex4_3_increment run-ex4_3_increment_c99 \
        run-ex4_4_bitwise run-ex4_4_bitwise_c99 \
        run-ex4_5_conditional run-ex4_5_conditional_c99 \
        run-ex4_6_precedence run-ex4_6_precedence_c99