# Makefile for operators chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = operators_demo.c bitwise_demo.c precedence_demo.c logical_operators.c comparison_operators.c
TARGETS = operators_demo bitwise_demo precedence_demo logical_operators comparison_operators
C99_TARGETS = operators_demo_c99 bitwise_demo_c99 precedence_demo_c99 logical_operators_c99 comparison_operators_c99

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
operators_demo: $(SRCDIR)/operators_demo.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

operators_demo_c99: $(SRCDIR)/operators_demo_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

bitwise_demo: $(SRCDIR)/bitwise_demo.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

bitwise_demo_c99: $(SRCDIR)/bitwise_demo_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

precedence_demo: $(SRCDIR)/precedence_demo.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

precedence_demo_c99: $(SRCDIR)/precedence_demo_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

logical_operators: $(SRCDIR)/logical_operators.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

logical_operators_c99: $(SRCDIR)/logical_operators_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

comparison_operators: $(SRCDIR)/comparison_operators.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

comparison_operators_c99: $(SRCDIR)/comparison_operators_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

# Run targets
run-all: all
	@echo "Running all programs:"
	@echo "--- operators_demo ---"
	@$(BUILDDIR)/operators_demo || true
	@echo
	@echo "--- bitwise_demo ---"
	@$(BUILDDIR)/bitwise_demo || true
	@echo
	@echo "--- precedence_demo ---"
	@$(BUILDDIR)/precedence_demo || true
	@echo
	@echo "--- logical_operators ---"
	@$(BUILDDIR)/logical_operators || true
	@echo
	@echo "--- comparison_operators ---"
	@$(BUILDDIR)/comparison_operators || true
	@echo

# Individual run targets
run-operators_demo: operators_demo
	@echo "Running operators_demo:"
	@$(BUILDDIR)/operators_demo

run-operators_demo-c99: operators_demo_c99
	@echo "Running operators_demo (C99):"
	@$(BUILDDIR)/operators_demo_c99

run-bitwise_demo: bitwise_demo
	@echo "Running bitwise_demo:"
	@$(BUILDDIR)/bitwise_demo

run-bitwise_demo-c99: bitwise_demo_c99
	@echo "Running bitwise_demo (C99):"
	@$(BUILDDIR)/bitwise_demo_c99

run-precedence_demo: precedence_demo
	@echo "Running precedence_demo:"
	@$(BUILDDIR)/precedence_demo

run-precedence_demo-c99: precedence_demo_c99
	@echo "Running precedence_demo (C99):"
	@$(BUILDDIR)/precedence_demo_c99

run-logical_operators: logical_operators
	@echo "Running logical_operators:"
	@$(BUILDDIR)/logical_operators

run-logical_operators-c99: logical_operators_c99
	@echo "Running logical_operators (C99):"
	@$(BUILDDIR)/logical_operators_c99

run-comparison_operators: comparison_operators
	@echo "Running comparison_operators:"
	@$(BUILDDIR)/comparison_operators

run-comparison_operators-c99: comparison_operators_c99
	@echo "Running comparison_operators (C99):"
	@$(BUILDDIR)/comparison_operators_c99

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
	@echo "  operators_demo       - Build operators_demo.c"
	@echo "  run-operators_demo  - Build and run operators_demo"
	@echo "  bitwise_demo         - Build bitwise_demo.c"
	@echo "  run-bitwise_demo    - Build and run bitwise_demo"
	@echo "  precedence_demo      - Build precedence_demo.c"
	@echo "  run-precedence_demo - Build and run precedence_demo"
	@echo "  logical_operators    - Build logical_operators.c"
	@echo "  run-logical_operators - Build and run logical_operators"
	@echo "  comparison_operators - Build comparison_operators.c"
	@echo "  run-comparison_operators - Build and run comparison_operators"

.PHONY: all c99 test test-c90 test-c99 run-all clean help
