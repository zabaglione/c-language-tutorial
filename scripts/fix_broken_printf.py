#!/usr/bin/env python3
"""
Fix broken printf statements where ;\n" appears at line end
"""

import os
import re
import sys

def fix_broken_printf_pattern(content):
    """Fix patterns where ;\n" appears at the end of a line"""
    lines = content.split('\n')
    fixed_lines = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # Check if line ends with ;\n"
        if line.rstrip().endswith(';\\n"'):
            # This is likely a broken printf statement
            # Fix by moving the \n" to inside the quotes
            fixed_line = re.sub(r';\\n"$', '\\n");', line.rstrip())
            fixed_lines.append(fixed_line)
        else:
            fixed_lines.append(line)
        
        i += 1
    
    return '\n'.join(fixed_lines)

def fix_multiline_printf_issues(content):
    """Fix various multiline printf formatting issues"""
    
    # Pattern 1: Fix ;\n" at end of line
    content = re.sub(
        r';\\n"\s*$',
        '\\n");',
        content,
        flags=re.MULTILINE
    )
    
    # Pattern 2: Fix printf statements that have been incorrectly split
    # e.g., printf("text\n");\n"
    content = re.sub(
        r'(printf\([^)]*\\n"\));\\n"',
        r'\1',
        content,
        flags=re.MULTILINE
    )
    
    # Pattern 3: Fix cases where we have printf("text\n"); followed by orphaned "
    # Remove lines that are just a quote
    lines = content.split('\n')
    fixed_lines = []
    skip_next = False
    
    for i, line in enumerate(lines):
        if skip_next:
            skip_next = False
            continue
            
        # Check if this line is printf with \n"); and next line is just a quote
        if 'printf(' in line and line.rstrip().endswith('\\n");'):
            if i + 1 < len(lines) and lines[i + 1].strip() == '"':
                # Skip the next line (just a quote)
                skip_next = True
            fixed_lines.append(line)
        else:
            fixed_lines.append(line)
    
    return '\n'.join(fixed_lines)

def process_readme(filepath):
    """Process a single README file"""
    print(f"Processing: {filepath}")
    
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    
    # Apply fixes
    content = fix_broken_printf_pattern(content)
    content = fix_multiline_printf_issues(content)
    
    # Additional cleanup - remove orphaned quotes on their own lines
    content = re.sub(r'^\s*"\s*$\n', '', content, flags=re.MULTILINE)
    
    # Count changes
    if content != original_content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        
        print(f"  - Fixed printf formatting issues")
        return True
    
    return False

def main():
    """Main function"""
    # Get all chapter directories
    src_dir = '/Users/zabaglione/clinetest/c-language-tutorial/src'
    
    if not os.path.exists(src_dir):
        print(f"Error: {src_dir} not found")
        sys.exit(1)
    
    total_fixed = 0
    
    # Process each chapter
    for chapter in sorted(os.listdir(src_dir)):
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.isdir(chapter_path):
            readme_path = os.path.join(chapter_path, 'README.md')
            if os.path.exists(readme_path):
                if process_readme(readme_path):
                    total_fixed += 1
    
    print(f"\nTotal files fixed: {total_fixed}")
    
    # Now run the other script to fix remaining newline issues
    print("\nRunning comprehensive newline fix...")
    os.system("python3 /Users/zabaglione/clinetest/c-language-tutorial/scripts/fix_split_newlines_final.py")

if __name__ == "__main__":
    main()