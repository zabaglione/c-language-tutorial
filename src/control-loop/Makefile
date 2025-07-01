# Makefile for control-loop chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = basic_for.c while_loop.c nested_loops.c for_loop_basics.c break_continue.c while_dowhile.c
TARGETS = basic_for while_loop nested_loops for_loop_basics break_continue while_dowhile
C99_TARGETS = basic_for_c99 while_loop_c99 nested_loops_c99 for_loop_basics_c99 break_continue_c99 while_dowhile_c99

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
basic_for: $(SRCDIR)/basic_for.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

basic_for_c99: $(SRCDIR)/basic_for_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

while_loop: $(SRCDIR)/while_loop.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

while_loop_c99: $(SRCDIR)/while_loop_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

nested_loops: $(SRCDIR)/nested_loops.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

nested_loops_c99: $(SRCDIR)/nested_loops_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

for_loop_basics: $(SRCDIR)/for_loop_basics.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

for_loop_basics_c99: $(SRCDIR)/for_loop_basics_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

break_continue: $(SRCDIR)/break_continue.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

break_continue_c99: $(SRCDIR)/break_continue_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

while_dowhile: $(SRCDIR)/while_dowhile.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

while_dowhile_c99: $(SRCDIR)/while_dowhile_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

# Run targets
run-all: all
	@echo "Running all programs:"
	@echo "--- basic_for ---"
	@$(BUILDDIR)/basic_for || true
	@echo
	@echo "--- while_loop ---"
	@$(BUILDDIR)/while_loop || true
	@echo
	@echo "--- nested_loops ---"
	@$(BUILDDIR)/nested_loops || true
	@echo
	@echo "--- for_loop_basics ---"
	@$(BUILDDIR)/for_loop_basics || true
	@echo
	@echo "--- break_continue ---"
	@$(BUILDDIR)/break_continue || true
	@echo
	@echo "--- while_dowhile ---"
	@$(BUILDDIR)/while_dowhile || true
	@echo

# Individual run targets
run-basic_for: basic_for
	@echo "Running basic_for:"
	@$(BUILDDIR)/basic_for

run-basic_for-c99: basic_for_c99
	@echo "Running basic_for (C99):"
	@$(BUILDDIR)/basic_for_c99

run-while_loop: while_loop
	@echo "Running while_loop:"
	@$(BUILDDIR)/while_loop

run-while_loop-c99: while_loop_c99
	@echo "Running while_loop (C99):"
	@$(BUILDDIR)/while_loop_c99

run-nested_loops: nested_loops
	@echo "Running nested_loops:"
	@$(BUILDDIR)/nested_loops

run-nested_loops-c99: nested_loops_c99
	@echo "Running nested_loops (C99):"
	@$(BUILDDIR)/nested_loops_c99

run-for_loop_basics: for_loop_basics
	@echo "Running for_loop_basics:"
	@$(BUILDDIR)/for_loop_basics

run-for_loop_basics-c99: for_loop_basics_c99
	@echo "Running for_loop_basics (C99):"
	@$(BUILDDIR)/for_loop_basics_c99

run-break_continue: break_continue
	@echo "Running break_continue:"
	@$(BUILDDIR)/break_continue

run-break_continue-c99: break_continue_c99
	@echo "Running break_continue (C99):"
	@$(BUILDDIR)/break_continue_c99

run-while_dowhile: while_dowhile
	@echo "Running while_dowhile:"
	@$(BUILDDIR)/while_dowhile

run-while_dowhile-c99: while_dowhile_c99
	@echo "Running while_dowhile (C99):"
	@$(BUILDDIR)/while_dowhile_c99

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
	@echo "  basic_for            - Build basic_for.c"
	@echo "  run-basic_for       - Build and run basic_for"
	@echo "  while_loop           - Build while_loop.c"
	@echo "  run-while_loop      - Build and run while_loop"
	@echo "  nested_loops         - Build nested_loops.c"
	@echo "  run-nested_loops    - Build and run nested_loops"
	@echo "  for_loop_basics      - Build for_loop_basics.c"
	@echo "  run-for_loop_basics - Build and run for_loop_basics"
	@echo "  break_continue       - Build break_continue.c"
	@echo "  run-break_continue  - Build and run break_continue"
	@echo "  while_dowhile        - Build while_dowhile.c"
	@echo "  run-while_dowhile   - Build and run while_dowhile"

.PHONY: all c99 test test-c90 test-c99 run-all clean help
