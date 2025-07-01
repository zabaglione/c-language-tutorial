# Makefile for basics-syntax chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = hello_world_basic.c formatted_output_demo.c hello_world.c formatted_output.c escape_sequences.c
TARGETS = hello_world_basic formatted_output_demo hello_world formatted_output escape_sequences
C99_TARGETS = hello_world_basic_c99 formatted_output_demo_c99 hello_world_c99 formatted_output_c99 escape_sequences_c99

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
hello_world_basic: $(SRCDIR)/hello_world_basic.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

hello_world_basic_c99: $(SRCDIR)/hello_world_basic_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

formatted_output_demo: $(SRCDIR)/formatted_output_demo.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

formatted_output_demo_c99: $(SRCDIR)/formatted_output_demo_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

hello_world: $(SRCDIR)/hello_world.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

hello_world_c99: $(SRCDIR)/hello_world_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

formatted_output: $(SRCDIR)/formatted_output.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

formatted_output_c99: $(SRCDIR)/formatted_output_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

escape_sequences: $(SRCDIR)/escape_sequences.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

escape_sequences_c99: $(SRCDIR)/escape_sequences_c99.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

# Run targets
run-all: all
	@echo "Running all programs:"
	@echo "--- hello_world_basic ---"
	@$(BUILDDIR)/hello_world_basic || true
	@echo
	@echo "--- formatted_output_demo ---"
	@$(BUILDDIR)/formatted_output_demo || true
	@echo
	@echo "--- hello_world ---"
	@$(BUILDDIR)/hello_world || true
	@echo
	@echo "--- formatted_output ---"
	@$(BUILDDIR)/formatted_output || true
	@echo
	@echo "--- escape_sequences ---"
	@$(BUILDDIR)/escape_sequences || true
	@echo

# Individual run targets
run-hello_world_basic: hello_world_basic
	@echo "Running hello_world_basic:"
	@$(BUILDDIR)/hello_world_basic

run-hello_world_basic-c99: hello_world_basic_c99
	@echo "Running hello_world_basic (C99):"
	@$(BUILDDIR)/hello_world_basic_c99

run-formatted_output_demo: formatted_output_demo
	@echo "Running formatted_output_demo:"
	@$(BUILDDIR)/formatted_output_demo

run-formatted_output_demo-c99: formatted_output_demo_c99
	@echo "Running formatted_output_demo (C99):"
	@$(BUILDDIR)/formatted_output_demo_c99

run-hello_world: hello_world
	@echo "Running hello_world:"
	@$(BUILDDIR)/hello_world

run-hello_world-c99: hello_world_c99
	@echo "Running hello_world (C99):"
	@$(BUILDDIR)/hello_world_c99

run-formatted_output: formatted_output
	@echo "Running formatted_output:"
	@$(BUILDDIR)/formatted_output

run-formatted_output-c99: formatted_output_c99
	@echo "Running formatted_output (C99):"
	@$(BUILDDIR)/formatted_output_c99

run-escape_sequences: escape_sequences
	@echo "Running escape_sequences:"
	@$(BUILDDIR)/escape_sequences

run-escape_sequences-c99: escape_sequences_c99
	@echo "Running escape_sequences (C99):"
	@$(BUILDDIR)/escape_sequences_c99

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
	@echo "  hello_world_basic    - Build hello_world_basic.c"
	@echo "  run-hello_world_basic - Build and run hello_world_basic"
	@echo "  formatted_output_demo - Build formatted_output_demo.c"
	@echo "  run-formatted_output_demo - Build and run formatted_output_demo"
	@echo "  hello_world          - Build hello_world.c"
	@echo "  run-hello_world     - Build and run hello_world"
	@echo "  formatted_output     - Build formatted_output.c"
	@echo "  run-formatted_output - Build and run formatted_output"
	@echo "  escape_sequences     - Build escape_sequences.c"
	@echo "  run-escape_sequences - Build and run escape_sequences"

.PHONY: all c99 test test-c90 test-c99 run-all clean help
