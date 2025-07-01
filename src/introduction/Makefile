# Makefile for introduction chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = hello_world.c compiler_test.c environment_check.c
TARGETS = hello_world compiler_test environment_check
C99_TARGETS = hello_world_c99 compiler_test_c99 environment_check_c99

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
hello_world: $(SRCDIR)/hello_world.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

hello_world_c99: $(SRCDIR)/hello_world_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

compiler_test: $(SRCDIR)/compiler_test.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

compiler_test_c99: $(SRCDIR)/compiler_test_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

environment_check: $(SRCDIR)/environment_check.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

environment_check_c99: $(SRCDIR)/environment_check_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

# Run targets
run-all: all
	@echo "Running all programs:"
	@echo "--- hello_world ---"
	@$(BUILDDIR)/hello_world || true
	@echo
	@echo "--- compiler_test ---"
	@$(BUILDDIR)/compiler_test || true
	@echo
	@echo "--- environment_check ---"
	@$(BUILDDIR)/environment_check || true
	@echo

# Individual run targets
run-hello_world: hello_world
	@echo "Running hello_world:"
	@$(BUILDDIR)/hello_world

run-hello_world-c99: hello_world_c99
	@echo "Running hello_world (C99):"
	@$(BUILDDIR)/hello_world_c99

run-compiler_test: compiler_test
	@echo "Running compiler_test:"
	@$(BUILDDIR)/compiler_test

run-compiler_test-c99: compiler_test_c99
	@echo "Running compiler_test (C99):"
	@$(BUILDDIR)/compiler_test_c99

run-environment_check: environment_check
	@echo "Running environment_check:"
	@$(BUILDDIR)/environment_check

run-environment_check-c99: environment_check_c99
	@echo "Running environment_check (C99):"
	@$(BUILDDIR)/environment_check_c99

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
	@echo "  hello_world          - Build hello_world.c"
	@echo "  run-hello_world     - Build and run hello_world"
	@echo "  compiler_test        - Build compiler_test.c"
	@echo "  run-compiler_test   - Build and run compiler_test"
	@echo "  environment_check    - Build environment_check.c"
	@echo "  run-environment_check - Build and run environment_check"

.PHONY: all c99 test test-c90 test-c99 run-all clean help
