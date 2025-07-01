# Makefile for data-types chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = basic_types.c arithmetic_operations.c sizeof_demo.c data_types_demo.c
TARGETS = basic_types arithmetic_operations sizeof_demo data_types_demo
C99_TARGETS = basic_types_c99 arithmetic_operations_c99 sizeof_demo_c99 data_types_demo_c99

# Default target
all: $(TARGETS)

# C99 versions
c99: STANDARD=c99
c99: $(C99_TARGETS)

# Build directory
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Generic rule for C90 programs
%: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@
	@echo "Built $@ (C90)"

# Generic rule for C99 programs
%_c99: $(SRCDIR)/%_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@
	@echo "Built $@ (C99)"

# Individual targets
basic_types: $(SRCDIR)/basic_types.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

basic_types_c99: $(SRCDIR)/basic_types_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

arithmetic_operations: $(SRCDIR)/arithmetic_operations.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

arithmetic_operations_c99: $(SRCDIR)/arithmetic_operations_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

sizeof_demo: $(SRCDIR)/sizeof_demo.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

sizeof_demo_c99: $(SRCDIR)/sizeof_demo_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

data_types_demo: $(SRCDIR)/data_types_demo.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

data_types_demo_c99: $(SRCDIR)/data_types_demo_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

# Run targets
run-all: all
	@echo "Running all programs:"
	@echo "--- basic_types ---"
	@$(BUILDDIR)/basic_types || true
	@echo
	@echo "--- arithmetic_operations ---"
	@$(BUILDDIR)/arithmetic_operations || true
	@echo
	@echo "--- sizeof_demo ---"
	@$(BUILDDIR)/sizeof_demo || true
	@echo
	@echo "--- data_types_demo ---"
	@$(BUILDDIR)/data_types_demo || true
	@echo

# Individual run targets
run-basic_types: basic_types
	@echo "Running basic_types:"
	@$(BUILDDIR)/basic_types

run-basic_types-c99: basic_types_c99
	@echo "Running basic_types (C99):"
	@$(BUILDDIR)/basic_types_c99

run-arithmetic_operations: arithmetic_operations
	@echo "Running arithmetic_operations:"
	@$(BUILDDIR)/arithmetic_operations

run-arithmetic_operations-c99: arithmetic_operations_c99
	@echo "Running arithmetic_operations (C99):"
	@$(BUILDDIR)/arithmetic_operations_c99

run-sizeof_demo: sizeof_demo
	@echo "Running sizeof_demo:"
	@$(BUILDDIR)/sizeof_demo

run-sizeof_demo-c99: sizeof_demo_c99
	@echo "Running sizeof_demo (C99):"
	@$(BUILDDIR)/sizeof_demo_c99

run-data_types_demo: data_types_demo
	@echo "Running data_types_demo:"
	@$(BUILDDIR)/data_types_demo

run-data_types_demo-c99: data_types_demo_c99
	@echo "Running data_types_demo (C99):"
	@$(BUILDDIR)/data_types_demo_c99

# Test targets
test: test-c90 test-c99

test-c90:
	@echo "Testing C90 compilation..."
	@$(MAKE) clean
	@$(MAKE) STANDARD=c90 all
	@echo "C90 compilation: SUCCESS"

test-c99:
	@echo "Testing C99 compilation..."
	@$(MAKE) clean  
	@$(MAKE) STANDARD=c99 c99
	@echo "C99 compilation: SUCCESS"

# Clean target
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILDDIR)
	@echo "Clean completed"

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build all C90 programs"
	@echo "  c99       - Build all C99 programs"
	@echo "  test      - Test both C90 and C99 compilation"
	@echo "  run-all   - Build and run all programs"
	@echo "  clean     - Clean build directory"
	@echo ""
	@echo "Individual programs:"
	@echo "  basic_types          - Build basic_types.c"
	@echo "  run-basic_types     - Build and run basic_types"
	@echo "  arithmetic_operations - Build arithmetic_operations.c"
	@echo "  run-arithmetic_operations - Build and run arithmetic_operations"
	@echo "  sizeof_demo          - Build sizeof_demo.c"
	@echo "  run-sizeof_demo     - Build and run sizeof_demo"
	@echo "  data_types_demo      - Build data_types_demo.c"
	@echo "  run-data_types_demo - Build and run data_types_demo"

.PHONY: all c99 test test-c90 test-c99 run-all clean help
