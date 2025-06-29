# Makefile for structures chapter
# 構造体の章のビルド設定

# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
DEBUGFLAGS = -g -O0 -DDEBUG
RELEASEFLAGS = -O2 -DNDEBUG

# C標準の選択（デフォルトはC90）
STANDARD ?= c90
CFLAGS += -std=$(STANDARD)

# 数学ライブラリのリンク（座標計算で必要）
LDFLAGS = -lm

# ディレクトリ
EXAMPLES_DIR = examples
SOLUTIONS_DIR = solutions

# ソースファイルの自動検出
EXAMPLE_SOURCES = $(wildcard $(EXAMPLES_DIR)/*.c)
SOLUTION_SOURCES = $(wildcard $(SOLUTIONS_DIR)/*.c)

# 実行ファイル名の生成（.c を除去）
EXAMPLE_TARGETS = $(EXAMPLE_SOURCES:.c=)
SOLUTION_TARGETS = $(SOLUTION_SOURCES:.c=)

# すべてのターゲット
ALL_TARGETS = $(EXAMPLE_TARGETS) $(SOLUTION_TARGETS)

# デフォルトターゲット
.PHONY: all
all: examples solutions

# 例題のビルド
.PHONY: examples
examples: $(EXAMPLE_TARGETS)
	@echo "===== 例題のビルド完了 ($(STANDARD)) ====="

# 解答例のビルド
.PHONY: solutions
solutions: $(SOLUTION_TARGETS)
	@echo "===== 解答例のビルド完了 ($(STANDARD)) ====="

# パターンルール（.cから実行ファイルを生成）
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# C99ファイル用の特別ルール
%_c99: %_c99.c
	$(CC) -std=c99 -Wall -Wextra -pedantic $< -o $@ $(LDFLAGS)

# デバッグビルド
.PHONY: debug
debug: CFLAGS += $(DEBUGFLAGS)
debug: all

# 個別ターゲット（使いやすいエイリアス）
.PHONY: struct_basics
struct_basics: $(EXAMPLES_DIR)/struct_basics

.PHONY: struct_pointers
struct_pointers: $(EXAMPLES_DIR)/struct_pointers

.PHONY: struct_arrays
struct_arrays: $(EXAMPLES_DIR)/struct_arrays

# 実行ターゲット
.PHONY: run-struct_basics
run-struct_basics: $(EXAMPLES_DIR)/struct_basics
	@echo "===== struct_basics を実行 ====="
	@./$(EXAMPLES_DIR)/struct_basics

.PHONY: run-struct_pointers
run-struct_pointers: $(EXAMPLES_DIR)/struct_pointers
	@echo "===== struct_pointers を実行 ====="
	@./$(EXAMPLES_DIR)/struct_pointers

.PHONY: run-struct_arrays
run-struct_arrays: $(EXAMPLES_DIR)/struct_arrays
	@echo "===== struct_arrays を実行 ====="
	@./$(EXAMPLES_DIR)/struct_arrays

# C99版の実行
.PHONY: run-struct_basics_c99
run-struct_basics_c99: $(EXAMPLES_DIR)/struct_basics_c99
	@echo "===== struct_basics_c99 を実行 ====="
	@./$(EXAMPLES_DIR)/struct_basics_c99

.PHONY: run-struct_pointers_c99
run-struct_pointers_c99: $(EXAMPLES_DIR)/struct_pointers_c99
	@echo "===== struct_pointers_c99 を実行 ====="
	@./$(EXAMPLES_DIR)/struct_pointers_c99

.PHONY: run-struct_arrays_c99
run-struct_arrays_c99: $(EXAMPLES_DIR)/struct_arrays_c99
	@echo "===== struct_arrays_c99 を実行 ====="
	@./$(EXAMPLES_DIR)/struct_arrays_c99

# すべての例題を実行
.PHONY: run-examples
run-examples: examples
	@echo "===== すべての例題を実行 ====="
	@for prog in $(EXAMPLE_TARGETS); do \
		echo "\n--- $$prog を実行 ---"; \
		./$$prog || true; \
		echo ""; \
	done

# すべての解答例を実行
.PHONY: run-solutions
run-solutions: solutions
	@echo "===== すべての解答例を実行 ====="
	@for prog in $(SOLUTION_TARGETS); do \
		echo "\n--- $$prog を実行 ---"; \
		./$$prog || true; \
		echo ""; \
	done

# すべてを実行
.PHONY: run-all
run-all: run-examples run-solutions

# 演習問題の個別実行
.PHONY: run-ex11_1
run-ex11_1: $(SOLUTIONS_DIR)/ex11_1_student
	@echo "===== 演習11-1: 学生情報管理 ====="
	@./$(SOLUTIONS_DIR)/ex11_1_student

.PHONY: run-ex11_2
run-ex11_2: $(SOLUTIONS_DIR)/ex11_2_coordinate
	@echo "===== 演習11-2: 座標計算 ====="
	@./$(SOLUTIONS_DIR)/ex11_2_coordinate

.PHONY: run-ex11_3
run-ex11_3: $(SOLUTIONS_DIR)/ex11_3_product
	@echo "===== 演習11-3: 商品管理 ====="
	@./$(SOLUTIONS_DIR)/ex11_3_product

# C標準別のビルドテスト
.PHONY: test-standards
test-standards:
	@echo "===== 異なるC標準でビルドテスト ====="
	@for std in c90 c99 c11 c17; do \
		echo "\n--- $$std でビルド ---"; \
		$(MAKE) clean > /dev/null 2>&1; \
		$(MAKE) STANDARD=$$std all > /dev/null 2>&1 && echo "$$std: 成功" || echo "$$std: 失敗"; \
	done
	@$(MAKE) clean > /dev/null 2>&1

# クリーンアップ
.PHONY: clean
clean:
	rm -f $(ALL_TARGETS)
	rm -f $(EXAMPLES_DIR)/*.o $(SOLUTIONS_DIR)/*.o
	rm -f core *.core
	@echo "クリーンアップ完了"

# ヘルプ
.PHONY: help
help:
	@echo "構造体の章 - Makefile ヘルプ"
	@echo "=============================="
	@echo ""
	@echo "使用可能なターゲット:"
	@echo "  make all              - すべてをビルド（デフォルト）"
	@echo "  make examples         - 例題のみビルド"
	@echo "  make solutions        - 解答例のみビルド"
	@echo "  make debug            - デバッグ情報付きでビルド"
	@echo "  make clean            - ビルド成果物を削除"
	@echo "  make run-all          - すべてのプログラムを実行"
	@echo ""
	@echo "個別ビルド:"
	@echo "  make struct_basics    - 構造体の基本操作をビルド"
	@echo "  make struct_pointers  - 構造体ポインタをビルド"
	@echo "  make struct_arrays    - 構造体配列をビルド"
	@echo ""
	@echo "実行:"
	@echo "  make run-struct_basics    - struct_basics を実行"
	@echo "  make run-struct_pointers  - struct_pointers を実行"
	@echo "  make run-struct_arrays    - struct_arrays を実行"
	@echo "  make run-examples         - すべての例題を実行"
	@echo "  make run-solutions        - すべての解答例を実行"
	@echo "  make run-ex11_1           - 演習11-1 学生情報管理を実行"
	@echo "  make run-ex11_2           - 演習11-2 座標計算を実行"
	@echo "  make run-ex11_3           - 演習11-3 商品管理を実行"
	@echo ""
	@echo "C99版の実行:"
	@echo "  make run-struct_basics_c99    - C99版を実行"
	@echo "  make run-struct_pointers_c99  - C99版を実行"
	@echo "  make run-struct_arrays_c99    - C99版を実行"
	@echo ""
	@echo "C標準の切り替え:"
	@echo "  make STANDARD=c99 all     - C99でビルド"
	@echo "  make STANDARD=c11 all     - C11でビルド"
	@echo "  make STANDARD=c17 all     - C17でビルド"
	@echo ""
	@echo "テスト:"
	@echo "  make test-standards   - 各C標準でビルドテスト"

# ファイル変更監視ターゲット（開発用）
.PHONY: watch
watch:
	@echo "ファイル変更を監視中... (Ctrl+C で終了)"
	@while true; do \
		$(MAKE) all; \
		inotifywait -qre modify $(EXAMPLES_DIR) $(SOLUTIONS_DIR) 2>/dev/null || \
		fswatch -1 $(EXAMPLES_DIR) $(SOLUTIONS_DIR) 2>/dev/null || \
		sleep 5; \
	done