#!/usr/bin/env python3
"""
Fix split newline characters in README files
"""

import os
import re
import sys

def fix_split_newlines(content):
    """Fix split newline characters in content"""
    # Pattern to match split newlines like:
    # printf("text\n
    # ", var);
    # Should become: printf("text\n", var);
    
    # First, find all printf/scanf statements that might have split newlines
    lines = content.split('\n')
    fixed_lines = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # Check if this line ends with \n or similar pattern inside a string
        # and the next line starts with a quote
        if i + 1 < len(lines):
            # Pattern for lines ending with \n" or \n') etc
            if re.search(r'\\n\s*$', line) and i + 1 < len(lines):
                next_line = lines[i + 1]
                # Check if next line starts with a quote (possibly with leading spaces)
                if re.match(r'^\s*"', next_line):
                    # Merge the lines
                    # Remove trailing \n and spaces from current line
                    current = re.sub(r'\\n\s*$', '', line)
                    # Extract the content after the opening quote in next line
                    next_content = re.sub(r'^\s*"', '', next_line)
                    # Combine them with \n"
                    fixed_lines.append(current + '\\n"' + next_content)
                    i += 2  # Skip the next line as we've merged it
                    continue
        
        fixed_lines.append(line)
        i += 1
    
    return '\n'.join(fixed_lines)

def process_readme(filepath):
    """Process a single README file"""
    print(f"Processing: {filepath}")
    
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Apply fixes
    fixed_content = fix_split_newlines(content)
    
    # Additional pattern to fix: sometimes newlines are truly split
    # e.g., "text\n\n" on two lines
    fixed_content = re.sub(r'\\n\n\s*"', '\\n"', fixed_content)
    
    # Fix patterns where \n is at the end of a line followed by more content
    lines = fixed_content.split('\n')
    for i in range(len(lines) - 1):
        # Look for patterns like: printf("xxx: %d\n
        if '\\n' in lines[i] and lines[i].rstrip().endswith('\\n'):
            if i + 1 < len(lines) and lines[i + 1].lstrip().startswith('"'):
                # Merge these lines
                lines[i] = lines[i].rstrip() + lines[i + 1].lstrip()
                lines[i + 1] = ''  # Mark for removal
    
    # Remove empty lines that were marked
    fixed_content = '\n'.join(line for line in lines if line != '')
    
    # Count changes
    if content != fixed_content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(fixed_content)
        
        # Count the number of fixes
        original_count = content.count('\\n\n')
        fixed_count = fixed_content.count('\\n\n') 
        split_pattern_count = len(re.findall(r'\\n\s*\n\s*"', content))
        
        print(f"  - Fixed {split_pattern_count} split newline patterns")
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