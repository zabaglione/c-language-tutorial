# Makefile for strings chapter
# Supports multiple C standards: C90, C99, C11, C17

# Compiler and flags
CC = gcc
STANDARD ?= c99
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
DEBUG_FLAGS = -g -DDEBUG -O0
RELEASE_FLAGS = -O2 -DNDEBUG

# Directories
EXAMPLES_DIR = examples
SOLUTIONS_DIR = solutions
BUILD_DIR = build

# Source files
EXAMPLE_SOURCES = $(wildcard $(EXAMPLES_DIR)/*.c)
SOLUTION_SOURCES = $(wildcard $(SOLUTIONS_DIR)/*.c)
ALL_SOURCES = $(EXAMPLE_SOURCES) $(SOLUTION_SOURCES)

# Object files
EXAMPLE_OBJECTS = $(EXAMPLE_SOURCES:$(EXAMPLES_DIR)/%.c=$(BUILD_DIR)/examples/%.o)
SOLUTION_OBJECTS = $(SOLUTION_SOURCES:$(SOLUTIONS_DIR)/%.c=$(BUILD_DIR)/solutions/%.o)

# Executable files
EXAMPLE_EXECUTABLES = $(EXAMPLE_SOURCES:$(EXAMPLES_DIR)/%.c=$(BUILD_DIR)/examples/%)
SOLUTION_EXECUTABLES = $(SOLUTION_SOURCES:$(SOLUTIONS_DIR)/%.c=$(BUILD_DIR)/solutions/%)

# Default target
all: directories examples solutions

# Create build directories
directories:
	@mkdir -p $(BUILD_DIR)/examples $(BUILD_DIR)/solutions

# Build all examples
examples: $(EXAMPLE_EXECUTABLES)

# Build all solutions
solutions: $(SOLUTION_EXECUTABLES)

# Pattern rule for example executables
$(BUILD_DIR)/examples/%: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Pattern rule for solution executables
$(BUILD_DIR)/solutions/%: $(SOLUTIONS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: all

# Run all examples
run-examples: examples
	@echo "=== Running Examples ==="
	@for exe in $(EXAMPLE_EXECUTABLES); do \
		if [ -f $$exe ]; then \
			echo "Running $$exe:"; \
			$$exe; \
			echo ""; \
		fi; \
	done

# Run all solutions
run-solutions: solutions
	@echo "=== Running Solutions ==="
	@for exe in $(SOLUTION_EXECUTABLES); do \
		if [ -f $$exe ]; then \
			echo "Running $$exe:"; \
			$$exe; \
			echo ""; \
		fi; \
	done

# Run all programs
run-all: run-examples run-solutions

# Individual example targets
run-string-basic: $(BUILD_DIR)/examples/string_basic
	@echo "=== String Basic (C90) ==="
	@$(BUILD_DIR)/examples/string_basic

run-string-basic-c99: $(BUILD_DIR)/examples/string_basic_c99
	@echo "=== String Basic (C99) ==="
	@$(BUILD_DIR)/examples/string_basic_c99

run-string-array-operations: $(BUILD_DIR)/examples/string_array_operations
	@echo "=== String Array Operations (C90) ==="
	@$(BUILD_DIR)/examples/string_array_operations

run-string-array-operations-c99: $(BUILD_DIR)/examples/string_array_operations_c99
	@echo "=== String Array Operations (C99) ==="
	@$(BUILD_DIR)/examples/string_array_operations_c99

run-advanced-string-processing: $(BUILD_DIR)/examples/advanced_string_processing
	@echo "=== Advanced String Processing (C90) ==="
	@$(BUILD_DIR)/examples/advanced_string_processing

run-advanced-string-processing-c99: $(BUILD_DIR)/examples/advanced_string_processing_c99
	@echo "=== Advanced String Processing (C99) ==="
	@$(BUILD_DIR)/examples/advanced_string_processing_c99

# Individual solution targets
run-ex8-1: $(BUILD_DIR)/solutions/ex8_1_string_operations
	@echo "=== 演習8-1: 基本的な文字列操作 ==="
	@$(BUILD_DIR)/solutions/ex8_1_string_operations

run-ex8-1-c99: $(BUILD_DIR)/solutions/ex8_1_string_operations_c99
	@echo "=== 演習8-1: 基本的な文字列操作 (C99) ==="
	@$(BUILD_DIR)/solutions/ex8_1_string_operations_c99

run-ex8-2: $(BUILD_DIR)/solutions/ex8_2_string_arrays
	@echo "=== 演習8-2: 文字列配列の操作 ==="
	@$(BUILD_DIR)/solutions/ex8_2_string_arrays

run-ex8-2-c99: $(BUILD_DIR)/solutions/ex8_2_string_arrays_c99
	@echo "=== 演習8-2: 文字列配列の操作 (C99) ==="
	@$(BUILD_DIR)/solutions/ex8_2_string_arrays_c99

run-ex8-3: $(BUILD_DIR)/solutions/ex8_3_string_search
	@echo "=== 演習8-3: 文字列検索と置換 ==="
	@$(BUILD_DIR)/solutions/ex8_3_string_search

run-ex8-3-c99: $(BUILD_DIR)/solutions/ex8_3_string_search_c99
	@echo "=== 演習8-3: 文字列検索と置換 (C99) ==="
	@$(BUILD_DIR)/solutions/ex8_3_string_search_c99

# Test different C standards
test-standards:
	@echo "=== Testing C90 Standard ==="
	@$(MAKE) clean
	@$(MAKE) STANDARD=c90 all
	@echo ""
	@echo "=== Testing C99 Standard ==="
	@$(MAKE) clean
	@$(MAKE) STANDARD=c99 all
	@echo ""
	@echo "=== Testing C11 Standard ==="
	@$(MAKE) clean
	@$(MAKE) STANDARD=c11 all
	@echo ""
	@echo "=== Testing C17 Standard ==="
	@$(MAKE) clean
	@$(MAKE) STANDARD=c17 all

# Check code style and potential issues
check:
	@echo "=== Code Style Check ==="
	@for src in $(ALL_SOURCES); do \
		echo "Checking $$src..."; \
		$(CC) $(CFLAGS) -fsyntax-only $$src; \
	done

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)

# Force rebuild
rebuild: clean all

# Install (copy to system directory - optional)
install: release
	@echo "Install target not implemented (educational project)"

# Uninstall
uninstall:
	@echo "Uninstall target not implemented (educational project)"

# Show help
help:
	@echo "Available targets:"
	@echo "  all              - Build all examples and solutions"
	@echo "  examples         - Build all examples"
	@echo "  solutions        - Build all solutions"
	@echo "  debug            - Build with debug flags"
	@echo "  release          - Build with release flags"
	@echo "  run-all          - Run all examples and solutions"
	@echo "  run-examples     - Run all examples"
	@echo "  run-solutions    - Run all solutions"
	@echo ""
	@echo "Individual run targets:"
	@echo "  run-string-basic          - Run string_basic.c"
	@echo "  run-string-basic-c99      - Run string_basic_c99.c"
	@echo "  run-string-array-operations - Run string_array_operations.c"
	@echo "  run-string-array-operations-c99 - Run string_array_operations_c99.c"
	@echo "  run-advanced-string-processing - Run advanced_string_processing.c"
	@echo "  run-advanced-string-processing-c99 - Run advanced_string_processing_c99.c"
	@echo "  run-ex8-1                 - Run exercise 8-1 solution (基本的な文字列操作)"
	@echo "  run-ex8-1-c99             - Run exercise 8-1 solution (C99)"
	@echo "  run-ex8-2                 - Run exercise 8-2 solution (文字列配列の操作)"
	@echo "  run-ex8-2-c99             - Run exercise 8-2 solution (C99)"
	@echo "  run-ex8-3                 - Run exercise 8-3 solution (文字列検索と置換)"
	@echo "  run-ex8-3-c99             - Run exercise 8-3 solution (C99)"
	@echo ""
	@echo "Utility targets:"
	@echo "  test-standards   - Test compilation with C90/C99/C11/C17"
	@echo "  check            - Check code syntax"
	@echo "  clean            - Remove build files"
	@echo "  rebuild          - Clean and build"
	@echo "  help             - Show this help"
	@echo ""
	@echo "Variables:"
	@echo "  STANDARD={c90|c99|c11|c17} - Set C standard (default: c99)"
	@echo "  CC=compiler                - Set compiler (default: gcc)"
	@echo ""
	@echo "Examples:"
	@echo "  make STANDARD=c90          - Build with C90 standard"
	@echo "  make debug run-ex8-1       - Debug build and run exercise 8-1"
	@echo "  make clean all run-all     - Clean, build, and run everything"

# Declare phony targets
.PHONY: all directories examples solutions debug release run-examples run-solutions run-all \
        run-string-basic run-string-basic-c99 run-string-array-operations run-string-array-operations-c99 \
        run-advanced-string-processing run-advanced-string-processing-c99 \
        run-ex8-1 run-ex8-1-c99 run-ex8-2 run-ex8-2-c99 run-ex8-3 run-ex8-3-c99 \
        test-standards check clean rebuild install uninstall help