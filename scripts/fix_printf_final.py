#!/usr/bin/env python3
"""
Final comprehensive fix for all printf formatting issues
"""

import os
import re
import sys

def fix_printf_issues(content):
    """Fix all printf formatting issues comprehensively"""
    lines = content.split('\n')
    fixed_lines = []
    i = 0
    
    while i < len(lines):
        current_line = lines[i]
        
        # Check if current line has printf ending with just )
        # and next line is ");
        if i + 1 < len(lines):
            next_line = lines[i + 1]
            
            # Pattern: printf("text\n")
            #          ");
            if ('printf(' in current_line and 
                current_line.rstrip().endswith('")') and
                next_line.strip() == '");'):
                # Fix by adding ; to current line and skip next line
                fixed_lines.append(current_line.rstrip() + ';')
                i += 2
                continue
            
            # Pattern: printf("text\n")\n");
            # This is another variant where the closing is split
            if ('printf(' in current_line and 
                current_line.rstrip().endswith('\\n")') and
                next_line.strip() == '");'):
                # Fix by adding ; to current line and skip next line
                fixed_lines.append(current_line.rstrip() + ';')
                i += 2
                continue
                
            # Pattern: printf("text\n"
            #          ");
            if ('printf(' in current_line and 
                not current_line.rstrip().endswith(';') and
                '\\n"' in current_line and
                next_line.strip() == '");'):
                # Fix by merging the lines
                fixed_lines.append(current_line.rstrip() + ');')
                i += 2
                continue
        
        fixed_lines.append(current_line)
        i += 1
    
    return '\n'.join(fixed_lines)

def fix_orphaned_printf_parts(content):
    """Remove orphaned "); lines and fix related issues"""
    # Pattern to remove standalone "); lines that shouldn't be there
    lines = content.split('\n')
    fixed_lines = []
    
    for i, line in enumerate(lines):
        # Skip lines that are just ");
        if line.strip() == '");' and i > 0:
            # Check if previous line already has a complete printf
            prev_line = lines[i-1] if i > 0 else ""
            if prev_line.rstrip().endswith(';'):
                # Previous line is complete, skip this orphaned ");
                continue
        
        fixed_lines.append(line)
    
    return '\n'.join(fixed_lines)

def fix_all_printf_patterns(content):
    """Apply all printf fixes"""
    # Fix split printf statements
    content = fix_printf_issues(content)
    
    # Remove orphaned parts
    content = fix_orphaned_printf_parts(content)
    
    # Additional regex fixes for specific patterns
    # Fix: printf("text\n")\n");  ->  printf("text\n");
    content = re.sub(
        r'(printf\([^;]+\\n"\))\s*\n\s*"\);',
        r'\1;',
        content,
        flags=re.MULTILINE
    )
    
    # Fix lines ending with \n")
    # followed by a line with just ");
    content = re.sub(
        r'(printf\([^;]+\\n"\))\s*\n\s*"\);',
        r'\1;',
        content,
        flags=re.MULTILINE
    )
    
    return content

def process_readme(filepath):
    """Process a single README file"""
    print(f"Processing: {filepath}")
    
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    
    # Apply all fixes
    content = fix_all_printf_patterns(content)
    
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

if __name__ == "__main__":
    main()