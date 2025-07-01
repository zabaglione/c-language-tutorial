# Makefile for control-if chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = switch_basic.c basic_if.c grade_system.c if_basic.c conditional_operator.c if_else.c
TARGETS = switch_basic basic_if grade_system if_basic conditional_operator if_else
C99_TARGETS = switch_basic_c99 basic_if_c99 grade_system_c99 if_basic_c99 conditional_operator_c99 if_else_c99

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
switch_basic: $(SRCDIR)/switch_basic.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

switch_basic_c99: $(SRCDIR)/switch_basic_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

basic_if: $(SRCDIR)/basic_if.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

basic_if_c99: $(SRCDIR)/basic_if_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

grade_system: $(SRCDIR)/grade_system.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

grade_system_c99: $(SRCDIR)/grade_system_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

if_basic: $(SRCDIR)/if_basic.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

if_basic_c99: $(SRCDIR)/if_basic_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

conditional_operator: $(SRCDIR)/conditional_operator.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

conditional_operator_c99: $(SRCDIR)/conditional_operator_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

if_else: $(SRCDIR)/if_else.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

if_else_c99: $(SRCDIR)/if_else_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

# Run targets
run-all: all
	@echo "Running all programs:"
	@echo "--- switch_basic ---"
	@$(BUILDDIR)/switch_basic || true
	@echo
	@echo "--- basic_if ---"
	@$(BUILDDIR)/basic_if || true
	@echo
	@echo "--- grade_system ---"
	@$(BUILDDIR)/grade_system || true
	@echo
	@echo "--- if_basic ---"
	@$(BUILDDIR)/if_basic || true
	@echo
	@echo "--- conditional_operator ---"
	@$(BUILDDIR)/conditional_operator || true
	@echo
	@echo "--- if_else ---"
	@$(BUILDDIR)/if_else || true
	@echo

# Individual run targets
run-switch_basic: switch_basic
	@echo "Running switch_basic:"
	@$(BUILDDIR)/switch_basic

run-switch_basic-c99: switch_basic_c99
	@echo "Running switch_basic (C99):"
	@$(BUILDDIR)/switch_basic_c99

run-basic_if: basic_if
	@echo "Running basic_if:"
	@$(BUILDDIR)/basic_if

run-basic_if-c99: basic_if_c99
	@echo "Running basic_if (C99):"
	@$(BUILDDIR)/basic_if_c99

run-grade_system: grade_system
	@echo "Running grade_system:"
	@$(BUILDDIR)/grade_system

run-grade_system-c99: grade_system_c99
	@echo "Running grade_system (C99):"
	@$(BUILDDIR)/grade_system_c99

run-if_basic: if_basic
	@echo "Running if_basic:"
	@$(BUILDDIR)/if_basic

run-if_basic-c99: if_basic_c99
	@echo "Running if_basic (C99):"
	@$(BUILDDIR)/if_basic_c99

run-conditional_operator: conditional_operator
	@echo "Running conditional_operator:"
	@$(BUILDDIR)/conditional_operator

run-conditional_operator-c99: conditional_operator_c99
	@echo "Running conditional_operator (C99):"
	@$(BUILDDIR)/conditional_operator_c99

run-if_else: if_else
	@echo "Running if_else:"
	@$(BUILDDIR)/if_else

run-if_else-c99: if_else_c99
	@echo "Running if_else (C99):"
	@$(BUILDDIR)/if_else_c99

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
	@echo "  switch_basic         - Build switch_basic.c"
	@echo "  run-switch_basic    - Build and run switch_basic"
	@echo "  basic_if             - Build basic_if.c"
	@echo "  run-basic_if        - Build and run basic_if"
	@echo "  grade_system         - Build grade_system.c"
	@echo "  run-grade_system    - Build and run grade_system"
	@echo "  if_basic             - Build if_basic.c"
	@echo "  run-if_basic        - Build and run if_basic"
	@echo "  conditional_operator - Build conditional_operator.c"
	@echo "  run-conditional_operator - Build and run conditional_operator"
	@echo "  if_else              - Build if_else.c"
	@echo "  run-if_else         - Build and run if_else"

.PHONY: all c99 test test-c90 test-c99 run-all clean help
