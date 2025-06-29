# C言語学習教材 - 第13章: 高度なトピック
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
memory_optimization: $(EXAMPLES_DIR)/memory_optimization
preprocessor_advanced: $(EXAMPLES_DIR)/preprocessor_advanced

# 個別ターゲット（解答例）
macro_basics: $(SOLUTIONS_DIR)/macro_basics
safe_memory_macros: $(SOLUTIONS_DIR)/safe_memory_macros
simple_memory_pool: $(SOLUTIONS_DIR)/simple_memory_pool

# 実行ターゲット
run-examples: examples
	@echo "=== 高度なトピックの例題実行 ==="
	@echo "--- メモリ最適化 ---"
	@./$(EXAMPLES_DIR)/memory_optimization
	@echo ""
	@echo "--- 高度なプリプロセッサ ---"
	@./$(EXAMPLES_DIR)/preprocessor_advanced

run-solutions: solutions
	@echo "=== 解答例の実行 ==="
	@echo "--- マクロの基本 ---"
	@./$(SOLUTIONS_DIR)/macro_basics
	@echo ""
	@echo "--- 安全なメモリマクロ ---"
	@./$(SOLUTIONS_DIR)/safe_memory_macros
	@echo ""
	@echo "--- 簡単なメモリプール ---"
	@./$(SOLUTIONS_DIR)/simple_memory_pool

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

# デバッグビルド
debug:
	$(MAKE) CFLAGS="$(CFLAGS_BASE) -std=$(STANDARD) -g -DDEBUG -O0" all

# リリースビルド
release:
	$(MAKE) CFLAGS="$(CFLAGS_BASE) -std=$(STANDARD) -O2 -DNDEBUG" all

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
	@echo "  memory_optimization    - メモリ最適化の例題をコンパイル"
	@echo "  preprocessor_advanced  - 高度なプリプロセッサをコンパイル"
	@echo "  macro_basics           - マクロ基本をコンパイル"
	@echo "  safe_memory_macros     - 安全なメモリマクロをコンパイル"
	@echo "  simple_memory_pool     - メモリプールをコンパイル"
	@echo "  run-examples           - 例題を実行"
	@echo "  run-solutions          - 解答例を実行"
	@echo "  run-all                - 全てを実行"
	@echo "  c90/c99/c11            - 指定された規格でコンパイル"
	@echo "  test-standards         - 複数のC規格でコンパイルテスト"
	@echo "  debug                  - デバッグビルド"
	@echo "  release                - リリースビルド"
	@echo "  clean                  - 生成されたファイルを削除"
	@echo "  help                   - このヘルプを表示"
	@echo ""
	@echo "例: make STANDARD=c99 examples"