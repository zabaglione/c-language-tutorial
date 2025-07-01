#!/usr/bin/env python3
"""
Extract code examples from README files and create organized source files
"""

import os
import re
import sys

def extract_code_blocks(content):
    """Extract all C code blocks from markdown content"""
    # Pattern to match ```c ... ``` blocks
    pattern = r'```c\n(.*?)\n```'
    matches = re.findall(pattern, content, re.DOTALL)
    return matches

def is_complete_program(code):
    """Check if code block is a complete, compilable program"""
    # Must have main function and includes
    has_main = 'int main(' in code or 'void main(' in code
    has_include = '#include' in code
    return has_main and has_include

def categorize_code(code, context=""):
    """Categorize code example based on content"""
    code_lower = code.lower()
    context_lower = context.lower()
    
    if 'hello' in code_lower or 'world' in code_lower:
        return 'hello_world'
    elif 'printf' in code_lower and 'formatted' in context_lower:
        return 'formatted_output'
    elif 'scanf' in code_lower:
        return 'input_demo'
    elif 'if' in code_lower and 'else' in code_lower:
        return 'conditional_demo'
    elif 'for' in code_lower or 'while' in code_lower:
        return 'loop_demo'
    elif 'array' in code_lower or 'arr[' in code_lower:
        return 'array_demo'
    elif 'struct' in code_lower:
        return 'struct_demo'
    elif 'function' in context_lower or '関数' in context_lower:
        return 'function_demo'
    elif 'pointer' in code_lower or '*' in code_lower:
        return 'pointer_demo'
    else:
        return 'basic_demo'

def clean_code_block(code):
    """Clean up code block for compilation"""
    # Remove extra comments at the end
    lines = code.split('\n')
    cleaned_lines = []
    in_main = False
    
    for line in lines:
        # Skip empty lines at the beginning
        if not cleaned_lines and not line.strip():
            continue
        
        # Track if we're in main function
        if 'int main(' in line:
            in_main = True
        
        cleaned_lines.append(line)
        
        # Stop after main function closes (if we find it)
        if in_main and line.strip() == '}':
            break
    
    return '\n'.join(cleaned_lines)

def analyze_chapter(chapter_path):
    """Analyze a chapter and extract code examples"""
    readme_path = os.path.join(chapter_path, 'README.md')
    if not os.path.exists(readme_path):
        return None
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    code_blocks = extract_code_blocks(content)
    examples = []
    
    for i, code in enumerate(code_blocks):
        if is_complete_program(code):
            # Get context around the code block
            code_start = content.find(f'```c\n{code}\n```')
            context_start = max(0, code_start - 500)
            context = content[context_start:code_start]
            
            category = categorize_code(code, context)
            clean_code = clean_code_block(code)
            
            examples.append({
                'code': clean_code,
                'category': category,
                'index': i,
                'context': context[-100:] if len(context) > 100 else context
            })
    
    return examples

def main():
    """Main function"""
    src_dir = '/Users/zabaglione/clinetest/c-language-tutorial/src'
    
    # Analyze first few chapters to establish pattern
    chapters_to_analyze = [
        'introduction',
        'basics-syntax', 
        'data-types',
        'operators',
        'control-if',
        'control-loop'
    ]
    
    report = {}
    
    for chapter in chapters_to_analyze:
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_path):
            examples = analyze_chapter(chapter_path)
            if examples:
                report[chapter] = examples
    
    # Print report
    print("# Code Examples Analysis Report\n")
    
    for chapter, examples in report.items():
        print(f"## Chapter: {chapter}")
        print(f"Found {len(examples)} complete programs:\n")
        
        for example in examples:
            print(f"- **{example['category']}_{example['index']}.c**")
            print(f"  - Category: {example['category']}")
            print(f"  - Lines of code: {len(example['code'].split())}")
            if example['context']:
                context_summary = example['context'].replace('\n', ' ')[:80] + "..."
                print(f"  - Context: {context_summary}")
            print()
        
        print("---\n")
    
    return report

if __name__ == "__main__":
    main()