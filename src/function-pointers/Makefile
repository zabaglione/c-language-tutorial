# C言語学習教材 - 第12章: 関数ポインタ
# Makefile for function pointer examples and solutions

# コンパイラ設定
CC = gcc
STANDARD ?= c90
CFLAGS = -std=$(STANDARD) -Wall -Wextra -pedantic -g
EXAMPLESDIR = examples
SOLUTIONSDIR = solutions
BINDIR = bin

# C90版 solutions
SOLUTION_TARGETS_C90 = ex12_1_basic_function_pointer \
                       ex12_2_function_selector \
                       ex12_3_array_callback \
                       ex12_4_calculator_function_array

# C99版 solutions  
SOLUTION_TARGETS_C99 = ex12_1_basic_function_pointer_c99 \
                       ex12_2_function_selector_c99 \
                       ex12_3_array_callback_c99 \
                       ex12_4_calculator_function_array_c99

# Examples (if they exist)
EXAMPLE_SOURCES = $(wildcard $(EXAMPLESDIR)/*.c)
EXAMPLE_TARGETS = $(basename $(notdir $(EXAMPLE_SOURCES)))

# デフォルトターゲット: C90版をビルド
all: $(BINDIR) solutions-c90

# C90版のみ
solutions-c90: $(BINDIR) $(SOLUTION_TARGETS_C90)

# C99版のみ  
solutions-c99: STANDARD=c99
solutions-c99: $(BINDIR) $(SOLUTION_TARGETS_C99)

# 両方のバージョン
all-versions: solutions-c90 solutions-c99

# ディレクトリ作成
$(BINDIR):
	mkdir -p $(BINDIR)

# C90版 solution rules
ex12_1_basic_function_pointer: $(SOLUTIONSDIR)/ex12_1_basic_function_pointer.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

ex12_2_function_selector: $(SOLUTIONSDIR)/ex12_2_function_selector.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

ex12_3_array_callback: $(SOLUTIONSDIR)/ex12_3_array_callback.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

ex12_4_calculator_function_array: $(SOLUTIONSDIR)/ex12_4_calculator_function_array.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

# C99版 solution rules
ex12_1_basic_function_pointer_c99: $(SOLUTIONSDIR)/ex12_1_basic_function_pointer_c99.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

ex12_2_function_selector_c99: $(SOLUTIONSDIR)/ex12_2_function_selector_c99.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

ex12_3_array_callback_c99: $(SOLUTIONSDIR)/ex12_3_array_callback_c99.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

ex12_4_calculator_function_array_c99: $(SOLUTIONSDIR)/ex12_4_calculator_function_array_c99.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

# Example rules (動的に生成)
$(EXAMPLE_TARGETS): %: $(EXAMPLESDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

# 個別実行 - C90版
run-ex12_1: ex12_1_basic_function_pointer
	@echo "=== 演習12-1: 関数ポインタの基本操作 (C90版) ==="
	./$(BINDIR)/ex12_1_basic_function_pointer

run-ex12_2: ex12_2_function_selector
	@echo "=== 演習12-2: 関数選択システム (C90版) ==="
	./$(BINDIR)/ex12_2_function_selector

run-ex12_3: ex12_3_array_callback
	@echo "=== 演習12-3: 配列処理のコールバック (C90版) ==="
	./$(BINDIR)/ex12_3_array_callback

run-ex12_4: ex12_4_calculator_function_array
	@echo "=== 演習12-4: 関数ポインタ配列を使った計算機 (C90版) ==="
	./$(BINDIR)/ex12_4_calculator_function_array

# 個別実行 - C99版
run-ex12_1_c99: ex12_1_basic_function_pointer_c99
	@echo "=== 演習12-1: 関数ポインタの基本操作 (C99版) ==="
	./$(BINDIR)/ex12_1_basic_function_pointer_c99

run-ex12_2_c99: ex12_2_function_selector_c99
	@echo "=== 演習12-2: 関数選択システム (C99版) ==="
	./$(BINDIR)/ex12_2_function_selector_c99

run-ex12_3_c99: ex12_3_array_callback_c99
	@echo "=== 演習12-3: 配列処理のコールバック (C99版) ==="
	./$(BINDIR)/ex12_3_array_callback_c99

run-ex12_4_c99: ex12_4_calculator_function_array_c99
	@echo "=== 演習12-4: 関数ポインタ配列を使った計算機 (C99版) ==="
	./$(BINDIR)/ex12_4_calculator_function_array_c99

# 全実行 - C90版
run-all: solutions-c90
	@echo "=== 第12章 全演習解答実行 (C90版) ==="
	@echo
	$(MAKE) run-ex12_1
	@echo
	$(MAKE) run-ex12_2
	@echo
	$(MAKE) run-ex12_3
	@echo
	$(MAKE) run-ex12_4

# 全実行 - C99版
run-all-c99: solutions-c99
	@echo "=== 第12章 全演習解答実行 (C99版) ==="
	@echo
	$(MAKE) run-ex12_1_c99
	@echo
	$(MAKE) run-ex12_2_c99
	@echo
	$(MAKE) run-ex12_3_c99
	@echo
	$(MAKE) run-ex12_4_c99

# 両バージョンで実行
run-all-versions: run-all run-all-c99

# Examples実行 (存在する場合)
run-examples: $(EXAMPLE_TARGETS)
	@if [ -n "$(EXAMPLE_TARGETS)" ]; then \
		echo "=== Examples実行 ==="; \
		for target in $(EXAMPLE_TARGETS); do \
			echo "実行: $$target"; \
			./$(BINDIR)/$$target; \
			echo; \
		done; \
	else \
		echo "Examplesフォルダにファイルがありません"; \
	fi

# デバッグビルド
debug: CFLAGS += -DDEBUG -O0
debug: all

# リリースビルド
release: CFLAGS += -O2 -DNDEBUG
release: all

# テスト実行（非対話型）
test: solutions-c90
	@echo "=== テスト実行 (全演習解答) ==="
	@echo "1. 演習12-1 テスト"
	./$(BINDIR)/ex12_1_basic_function_pointer
	@echo
	@echo "2. 演習12-2 テスト"
	./$(BINDIR)/ex12_2_function_selector  
	@echo
	@echo "3. 演習12-3 テスト"
	./$(BINDIR)/ex12_3_array_callback
	@echo
	@echo "4. 演習12-4 テスト"
	./$(BINDIR)/ex12_4_calculator_function_array
	@echo "=== テスト完了 ==="

# 標準別テスト
test-standards:
	@echo "=== 複数標準でのテスト ==="
	$(MAKE) clean
	$(MAKE) STANDARD=c90 test
	$(MAKE) clean
	$(MAKE) STANDARD=c99 solutions-c99
	$(MAKE) run-all-c99
	@echo "=== 標準別テスト完了 ==="

# クリーンアップ
clean:
	rm -rf $(BINDIR)
	@echo "クリーンアップ完了"

# ソースコード確認
check-syntax:
	@echo "=== 構文チェック ==="
	@for file in $(SOLUTIONSDIR)/*.c; do \
		echo "チェック: $$file"; \
		$(CC) $(CFLAGS) -fsyntax-only $$file; \
	done
	@if [ -n "$(EXAMPLE_SOURCES)" ]; then \
		for file in $(EXAMPLE_SOURCES); do \
			echo "チェック: $$file"; \
			$(CC) $(CFLAGS) -fsyntax-only $$file; \
		done; \
	fi
	@echo "構文チェック完了"

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all              - C90版解答例をビルド"
	@echo "  solutions-c90    - C90版解答例をビルド"
	@echo "  solutions-c99    - C99版解答例をビルド"
	@echo "  all-versions     - 両バージョンをビルド"
	@echo ""
	@echo "個別実行 (C90版):"
	@echo "  run-ex12_1       - 演習12-1を実行"
	@echo "  run-ex12_2       - 演習12-2を実行"
	@echo "  run-ex12_3       - 演習12-3を実行"
	@echo "  run-ex12_4       - 演習12-4を実行"
	@echo ""
	@echo "個別実行 (C99版):"
	@echo "  run-ex12_1_c99   - 演習12-1を実行"
	@echo "  run-ex12_2_c99   - 演習12-2を実行"
	@echo "  run-ex12_3_c99   - 演習12-3を実行"
	@echo "  run-ex12_4_c99   - 演習12-4を実行"
	@echo ""
	@echo "全実行:"
	@echo "  run-all          - 全解答例を実行 (C90版)"
	@echo "  run-all-c99      - 全解答例を実行 (C99版)"
	@echo "  run-all-versions - 両バージョンで実行"
	@echo "  run-examples     - Examples実行"
	@echo ""
	@echo "その他:"
	@echo "  debug            - デバッグビルド"
	@echo "  release          - リリースビルド"
	@echo "  test             - テスト実行"
	@echo "  test-standards   - 複数標準でテスト"
	@echo "  clean            - ビルドファイル削除"
	@echo "  check-syntax     - 構文チェック"
	@echo "  help             - このヘルプを表示"
	@echo ""
	@echo "標準指定: make STANDARD=c99 all"

# .PHONYターゲット
.PHONY: all solutions-c90 solutions-c99 all-versions run-ex12_1 run-ex12_2 run-ex12_3 run-ex12_4 \
        run-ex12_1_c99 run-ex12_2_c99 run-ex12_3_c99 run-ex12_4_c99 \
        run-all run-all-c99 run-all-versions run-examples \
        debug release test test-standards clean check-syntax help
