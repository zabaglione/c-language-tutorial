# C言語学習教材 - 第14章: C23の新機能
# コンパイラとフラグの設定

CC = gcc
CFLAGS_BASE = -Wall -Wextra -pedantic
STANDARD = c23  # C23固定
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
.PHONY: all clean run run-all run-examples run-solutions help test

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
bool_basics: $(EXAMPLES_DIR)/bool_basics
numeric_literals: $(EXAMPLES_DIR)/numeric_literals
typeof_demo: $(EXAMPLES_DIR)/typeof_demo
nullptr_demo: $(EXAMPLES_DIR)/nullptr_demo

# 実行ターゲット
run-all: run-examples run-solutions

run-examples: examples
	@echo "=== C23機能の例題実行 ==="
	@for prog in $(EXAMPLES_BIN); do \
		if [ -f $$prog ]; then \
			echo "\n--- $$prog の実行 ---"; \
			$$prog || true; \
		fi \
	done

run-solutions: solutions
	@echo "=== C23機能の解答例実行 ==="
	@for prog in $(SOLUTIONS_BIN); do \
		if [ -f $$prog ]; then \
			echo "\n--- $$prog の実行 ---"; \
			$$prog || true; \
		fi \
	done

# 個別実行ターゲット
run-bool_basics: bool_basics
	@echo "=== bool型の基本 ==="
	@$(EXAMPLES_DIR)/bool_basics

run-numeric_literals: numeric_literals
	@echo "=== 数値リテラル ==="
	@$(EXAMPLES_DIR)/numeric_literals

run-typeof_demo: typeof_demo
	@echo "=== typeof演算子 ==="
	@$(EXAMPLES_DIR)/typeof_demo

run-nullptr_demo: nullptr_demo
	@echo "=== nullptr定数 ==="
	@$(EXAMPLES_DIR)/nullptr_demo

# テスト（C23サポートの確認）
test: 
	@echo "=== C23サポートテスト ==="
	@echo "コンパイラ: $(CC)"
	@$(CC) --version | head -n 1
	@echo ""
	@echo "C23規格バージョン:"
	@echo '__STDC_VERSION__' | $(CC) -std=c23 -E -x c - | tail -n 1
	@echo ""
	@echo "C23機能のコンパイルテスト:"
	@echo 'int main(){bool b=true;return 0;}' | $(CC) -std=c23 -x c - 2>&1 && echo "✓ bool型: サポート" || echo "✗ bool型: 未サポート"
	@echo 'int main(){int x=0b1010;return 0;}' | $(CC) -std=c23 -x c - 2>&1 && echo "✓ 2進数リテラル: サポート" || echo "✗ 2進数リテラル: 未サポート"
	@echo 'int main(){typeof(int) x;return 0;}' | $(CC) -std=c23 -x c - 2>&1 && echo "✓ typeof: サポート" || echo "✗ typeof: 未サポート"
	@echo 'int main(){void*p=nullptr;return 0;}' | $(CC) -std=c23 -x c - 2>&1 && echo "✓ nullptr: サポート" || echo "✗ nullptr: 未サポート"

# クリーンアップ
clean:
	rm -f $(EXAMPLES_BIN)
	rm -f $(SOLUTIONS_BIN)
	rm -f $(EXAMPLES_DIR)/*.dSYM
	rm -f $(SOLUTIONS_DIR)/*.dSYM
	rm -rf $(EXAMPLES_DIR)/*.dSYM/
	rm -rf $(SOLUTIONS_DIR)/*.dSYM/

# ヘルプ
help:
	@echo "使用可能なターゲット:"
	@echo "  all               - すべてのプログラムをコンパイル"
	@echo "  examples          - 例題プログラムをコンパイル"
	@echo "  solutions         - 解答例プログラムをコンパイル"
	@echo "  clean             - ビルド生成物を削除"
	@echo "  test              - C23サポートをテスト"
	@echo "  run-all           - すべてのプログラムを実行"
	@echo "  run-examples      - 例題プログラムを実行"
	@echo "  run-solutions     - 解答例プログラムを実行"
	@echo ""
	@echo "個別実行（例）:"
	@echo "  make run-bool_basics      - bool型の基本を実行"
	@echo "  make run-numeric_literals - 数値リテラルを実行"
	@echo "  make run-typeof_demo      - typeof演算子を実行"
	@echo "  make run-nullptr_demo     - nullptr定数を実行"
	@echo ""
	@echo "注意: このMakefileはC23専用です（gcc -std=c23）"