#!/usr/bin/env python3
"""
Create standardized Makefiles for each chapter
"""

import os
import glob

def create_makefile_for_chapter(chapter_path, chapter_name):
    """Create a standardized Makefile for a chapter"""
    examples_dir = os.path.join(chapter_path, 'examples')
    
    if not os.path.exists(examples_dir):
        print(f"No examples directory found for {chapter_name}")
        return False
    
    # Find all .c files in examples directory
    c_files = glob.glob(os.path.join(examples_dir, '*.c'))
    c_files = [os.path.basename(f) for f in c_files if not f.endswith('_c99.c')]
    
    if not c_files:
        print(f"No C files found in {chapter_name}/examples")
        return False
    
    # Generate base names (without .c extension)
    base_names = [f[:-2] for f in c_files]  # Remove .c extension
    
    makefile_content = f'''# Makefile for {chapter_name} chapter
# Supports both C90 and C99 standards

# Compiler settings
CC = gcc
STANDARD ?= c90
CFLAGS = -Wall -Wextra -pedantic -std=$(STANDARD)
SRCDIR = examples
BUILDDIR = build

# Source files
SOURCES = {' '.join(c_files)}
TARGETS = {' '.join(base_names)}
C99_TARGETS = {' '.join([f"{name}_c99" for name in base_names])}

# Default target
all: $(TARGETS)

# C99 versions
c99: STANDARD=c99
c99: $(C99_TARGETS)

# Build directory
$(BUILDDIR):
\t@mkdir -p $(BUILDDIR)

# Generic rule for C90 programs
%: $(SRCDIR)/%.c | $(BUILDDIR)
\t$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@
\t@echo "Built $@ (C90)"

# Generic rule for C99 programs
%_c99: $(SRCDIR)/%_c99.c | $(BUILDDIR)
\t$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@
\t@echo "Built $@ (C99)"

# Individual targets
'''

    # Add individual targets
    for base_name in base_names:
        makefile_content += f'''{base_name}: $(SRCDIR)/{base_name}.c | $(BUILDDIR)
\t$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

{base_name}_c99: $(SRCDIR)/{base_name}_c99.c | $(BUILDDIR)
\t$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

'''

    makefile_content += f'''# Run targets
run-all: all
\t@echo "Running all programs:"
'''
    
    for base_name in base_names:
        makefile_content += f'''\t@echo "--- {base_name} ---"
\t@$(BUILDDIR)/{base_name} || true
\t@echo
'''

    makefile_content += f'''
# Individual run targets
'''
    
    for base_name in base_names:
        makefile_content += f'''run-{base_name}: {base_name}
\t@echo "Running {base_name}:"
\t@$(BUILDDIR)/{base_name}

run-{base_name}-c99: {base_name}_c99
\t@echo "Running {base_name} (C99):"
\t@$(BUILDDIR)/{base_name}_c99

'''

    makefile_content += '''# Test targets
test: test-c90 test-c99

test-c90:
\t@echo "Testing C90 compilation..."
\t@$(MAKE) clean
\t@$(MAKE) STANDARD=c90 all
\t@echo "C90 compilation: SUCCESS"

test-c99:
\t@echo "Testing C99 compilation..."
\t@$(MAKE) clean  
\t@$(MAKE) STANDARD=c99 c99
\t@echo "C99 compilation: SUCCESS"

# Clean target
clean:
\t@echo "Cleaning build directory..."
\t@rm -rf $(BUILDDIR)
\t@echo "Clean completed"

# Help target
help:
\t@echo "Available targets:"
\t@echo "  all       - Build all C90 programs"
\t@echo "  c99       - Build all C99 programs"
\t@echo "  test      - Test both C90 and C99 compilation"
\t@echo "  run-all   - Build and run all programs"
\t@echo "  clean     - Clean build directory"
\t@echo ""
\t@echo "Individual programs:"
'''

    for base_name in base_names:
        makefile_content += f'\t@echo "  {base_name:<20} - Build {base_name}.c"\n'
        makefile_content += f'\t@echo "  run-{base_name:<15} - Build and run {base_name}"\n'

    makefile_content += '''
.PHONY: all c99 test test-c90 test-c99 run-all clean help
'''
    
    # Write Makefile
    makefile_path = os.path.join(chapter_path, 'Makefile')
    with open(makefile_path, 'w', encoding='utf-8') as f:
        f.write(makefile_content)
    
    print(f"Created Makefile for {chapter_name} with {len(base_names)} targets")
    return True

def main():
    """Main function"""
    src_dir = '/Users/zabaglione/clinetest/c-language-tutorial/src'
    
    chapters_to_process = [
        'introduction',
        'basics-syntax',
        'data-types',
        'operators', 
        'control-if',
        'control-loop'
    ]
    
    print("Creating Makefiles for chapters...\n")
    
    for chapter in chapters_to_process:
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_path):
            create_makefile_for_chapter(chapter_path, chapter)
        else:
            print(f"Chapter directory not found: {chapter}")
    
    print("\nMakefile creation completed!")

if __name__ == "__main__":
    main()