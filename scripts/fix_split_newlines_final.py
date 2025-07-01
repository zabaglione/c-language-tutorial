#!/usr/bin/env python3
"""
Fix split newline characters in README files - Final version
This specifically handles cases where \n is at the end of one line
and the next line continues the string.
"""

import os
import re
import sys

def fix_split_newlines_comprehensive(content):
    """Fix all types of split newlines in content"""
    lines = content.split('\n')
    fixed_lines = []
    i = 0
    
    while i < len(lines):
        if i + 1 < len(lines):
            current_line = lines[i]
            next_line = lines[i + 1]
            
            # Pattern 1: Line ends with backslash n literally, next line has closing quote
            # e.g., printf("text\n
            #       ");
            if current_line.rstrip().endswith('\\n') and re.match(r'^\s*"\s*\);', next_line):
                # Merge the lines
                merged = current_line.rstrip() + '");'
                fixed_lines.append(merged)
                i += 2
                continue
            
            # Pattern 2: printf/scanf line that ends without closing quote
            # and next line starts with quote
            if ('printf(' in current_line or 'scanf(' in current_line) and \
               not current_line.rstrip().endswith(';') and \
               not current_line.rstrip().endswith(')'):
                # Check if next line might be continuation
                if next_line.lstrip().startswith('"'):
                    # This could be a split - check more carefully
                    # Look for patterns like: printf("text: %d\n
                    # ", var);
                    if re.search(r'\\n\s*$', current_line):
                        # Remove trailing \n and spaces, add the rest from next line
                        base = re.sub(r'\\n\s*$', '\\n', current_line)
                        continuation = next_line.lstrip()
                        merged = base + continuation
                        fixed_lines.append(merged)
                        i += 2
                        continue
        
        fixed_lines.append(lines[i])
        i += 1
    
    return '\n'.join(fixed_lines)

def process_readme(filepath):
    """Process a single README file"""
    print(f"Processing: {filepath}")
    
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    
    # Apply comprehensive fixes
    content = fix_split_newlines_comprehensive(content)
    
    # Additional specific fixes
    # Fix patterns where printf has split newlines
    content = re.sub(
        r'(printf\([^)]*?)\\n\s*\n\s*"([^"]*"\s*[,)])',
        r'\1\\n"\2',
        content,
        flags=re.MULTILINE
    )
    
    # Fix patterns like: printf("text\n
    # ", variable);
    content = re.sub(
        r'(printf\([^;]*?)\\n\s*\n\s*"(\s*,)',
        r'\1\\n"',
        content,
        flags=re.MULTILINE
    )
    
    # Count changes
    if content != original_content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        
        # Count specific fixes
        split_count = original_content.count('\\n\n"') - content.count('\\n\n"')
        
        print(f"  - Fixed split newline issues")
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

if __name__ == "__main__":
    main()