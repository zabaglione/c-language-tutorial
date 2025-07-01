#!/usr/bin/env python3
"""
Test build and execution of all chapter examples
"""

import os
import subprocess
import sys

def run_command(cmd, cwd):
    """Run a command and return success status"""
    try:
        result = subprocess.run(
            cmd, 
            cwd=cwd, 
            shell=True, 
            capture_output=True, 
            text=True,
            timeout=30
        )
        return result.returncode == 0, result.stdout, result.stderr
    except subprocess.TimeoutExpired:
        return False, "", "Command timed out"
    except Exception as e:
        return False, "", str(e)

def test_chapter_build(chapter_path, chapter_name):
    """Test building examples in a chapter"""
    makefile_path = os.path.join(chapter_path, 'Makefile')
    
    if not os.path.exists(makefile_path):
        return False, f"No Makefile found in {chapter_name}"
    
    print(f"\n{'='*50}")
    print(f"Testing chapter: {chapter_name}")
    print(f"{'='*50}")
    
    # Test C90 build
    print("Testing C90 compilation...")
    success, stdout, stderr = run_command("make clean && make test-c90", chapter_path)
    
    if success:
        print("✓ C90 compilation: SUCCESS")
    else:
        print("✗ C90 compilation: FAILED")
        if stderr:
            print("Errors:", stderr)
        return False, f"C90 compilation failed for {chapter_name}"
    
    # Test C99 build
    print("Testing C99 compilation...")
    success, stdout, stderr = run_command("make clean && make test-c99", chapter_path)
    
    if success:
        print("✓ C99 compilation: SUCCESS")
    else:
        print("✗ C99 compilation: FAILED")
        if stderr:
            print("Errors:", stderr)
        return False, f"C99 compilation failed for {chapter_name}"
    
    return True, f"All tests passed for {chapter_name}"

def test_chapter_execution(chapter_path, chapter_name):
    """Test execution of examples in a chapter"""
    print(f"\nTesting execution for {chapter_name}...")
    
    # Build all programs first
    success, stdout, stderr = run_command("make clean && make all", chapter_path)
    if not success:
        return False, f"Failed to build programs for execution test in {chapter_name}"
    
    # Run all programs
    success, stdout, stderr = run_command("make run-all", chapter_path)
    if success:
        print("✓ Execution test: SUCCESS")
        if stdout:
            print("Sample output:")
            print(stdout[:500] + "..." if len(stdout) > 500 else stdout)
    else:
        print("✗ Execution test: FAILED")
        if stderr:
            print("Errors:", stderr)
        return False, f"Execution test failed for {chapter_name}"
    
    return True, f"Execution test passed for {chapter_name}"

def main():
    """Main function"""
    src_dir = '/Users/zabaglione/clinetest/c-language-tutorial/src'
    
    chapters_to_test = [
        'introduction',
        'basics-syntax',
        'data-types',
        'operators',
        'control-if', 
        'control-loop'
    ]
    
    print("Starting comprehensive build and execution tests...")
    print(f"Testing {len(chapters_to_test)} chapters")
    
    build_results = []
    execution_results = []
    
    # Build tests
    for chapter in chapters_to_test:
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_path):
            success, message = test_chapter_build(chapter_path, chapter)
            build_results.append((chapter, success, message))
        else:
            build_results.append((chapter, False, f"Chapter directory not found: {chapter}"))
    
    # Execution tests
    for chapter in chapters_to_test:
        chapter_path = os.path.join(src_dir, chapter)
        if os.path.exists(chapter_path):
            success, message = test_chapter_execution(chapter_path, chapter)
            execution_results.append((chapter, success, message))
        else:
            execution_results.append((chapter, False, f"Chapter directory not found: {chapter}"))
    
    # Summary report
    print(f"\n{'='*60}")
    print("FINAL TEST RESULTS")
    print(f"{'='*60}")
    
    print("\nBuild Test Results:")
    build_passed = 0
    for chapter, success, message in build_results:
        status = "✓ PASS" if success else "✗ FAIL"
        print(f"  {chapter:<20} {status}")
        if success:
            build_passed += 1
    
    print("\nExecution Test Results:")
    execution_passed = 0
    for chapter, success, message in execution_results:
        status = "✓ PASS" if success else "✗ FAIL"
        print(f"  {chapter:<20} {status}")
        if success:
            execution_passed += 1
    
    print(f"\nSummary:")
    print(f"  Build tests:     {build_passed}/{len(build_results)} passed")
    print(f"  Execution tests: {execution_passed}/{len(execution_results)} passed")
    
    if build_passed == len(build_results) and execution_passed == len(execution_results):
        print("\n🎉 ALL TESTS PASSED! 🎉")
        return True
    else:
        print("\n❌ Some tests failed. Check the output above for details.")
        return False

if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)