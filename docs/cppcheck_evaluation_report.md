# C言語学習教材 コード品質評価レポート

**評価ツール**: cppcheck Cppcheck 2.17.1  
**評価日時**: 2025-06-29 21:05:52  
**評価対象**: src/ディレクトリ内の全C言語ソースコード

## 評価サマリー

本レポートは、C言語学習教材に含まれるサンプルコードおよび演習解答例の静的解析結果をまとめたものです。

### 評価基準

cppcheckは以下の項目をチェックします：
- **error**: 明確なバグ
- **warning**: 防御的プログラミングの観点からの警告
- **style**: コーディングスタイルの問題
- **performance**: パフォーマンスの問題
- **portability**: 移植性の問題
- **information**: 情報提供

---

## 章別評価結果


### advanced

**検査ファイル数**: 20 個

**検出された問題**:
- Errors: 4
- Warnings: 21
- Style: 178
- Performance: 0
0
- Portability: 1
- Information: 10

**詳細**:
```
advanced/examples/memory_optimization.c:457: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:458: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:459: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:460: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:465: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:487: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:488: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:498: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:521: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:522: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:532: warning: If memory allocation fails, then there is a possible null pointer dereference: objects
advanced/examples/memory_optimization.c:156: style: Parameter 'ptr' can be declared as pointer to const
advanced/examples/memory_optimization.c:187: style: Parameter 'pool' can be declared as pointer to const
advanced/examples/memory_optimization.c:559: style: Variable 'leak_ptr' can be declared as pointer to const
advanced/examples/memory_optimization.c:604: style: Variable 's1' can be declared as pointer to const
advanced/examples/memory_optimization.c:605: style: Variable 's2' can be declared as pointer to const
advanced/examples/memory_optimization.c:606: style: Variable 's3' can be declared as pointer to const
advanced/examples/memory_optimization.c:431: style: Unused variable: ts
advanced/examples/memory_optimization.c:604: style: Variable 's1' is assigned a value that is never used.
advanced/examples/memory_optimization.c:605: style: Variable 's2' is assigned a value that is never used.
advanced/examples/memory_optimization.c:606: style: Variable 's3' is assigned a value that is never used.
advanced/examples/preprocessor_advanced.c:236: error: Array 'array[5]' accessed at index 10, which is out of bounds.
advanced/examples/preprocessor_advanced.c:237: error: Array 'array[5]' accessed at index -1, which is out of bounds.
advanced/examples/preprocessor_advanced.c:259: warning: %d in format string (no. 1) requires 'int' but the argument type is 'unsigned int'.
advanced/examples/preprocessor_advanced.c:260: warning: %d in format string (no. 1) requires 'int' but the argument type is 'unsigned int'.
advanced/examples/preprocessor_advanced.c:348: style: The comparison 'value == 42' is always true.
advanced/examples/preprocessor_advanced.c:195: style: Variable 'value' is assigned a value that is never used.
advanced/solutions/ex13_1_macro_basics_c99.c:104: style: struct member 'benchmark_t::name' is never used.
advanced/solutions/ex13_2_safe_memory.c:224: style: Condition 'count!=0' is always true
advanced/solutions/ex13_2_safe_memory.c:439: warning: Either the condition 'buffer' is redundant or there is possible null pointer dereference: buffer.
advanced/solutions/ex13_2_safe_memory.c:443: warning: Either the condition 'buffer' is redundant or there is possible null pointer dereference: buffer.
advanced/solutions/ex13_2_safe_memory.c:293: style: The scope of the variable 'leak_total' can be reduced.
advanced/solutions/ex13_2_safe_memory.c:294: style: The scope of the variable 'leak_count' can be reduced.
advanced/solutions/ex13_2_safe_memory.c:167: style: Parameter 'ptr' can be declared as pointer to const
advanced/solutions/ex13_2_safe_memory.c:458: style: Variable 'leak1' can be declared as pointer to const
advanced/solutions/ex13_2_safe_memory.c:459: style: Variable 'leak2' can be declared as pointer to const
advanced/solutions/ex13_2_safe_memory_c99.c:196: style: Parameter 'ptr' can be declared as pointer to const
advanced/solutions/ex13_2_safe_memory_c99.c:497: style: Variable 'leak1' can be declared as pointer to const
advanced/solutions/ex13_2_safe_memory_c99.c:498: style: Variable 'leak2' can be declared as pointer to const
advanced/solutions/ex13_3_memory_pool.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_3_memory_pool.c:497: style: The scope of the variable 'ptr' can be reduced.
advanced/solutions/ex13_3_memory_pool.c:175: style: Variable 'pool_end' can be declared as pointer to const
advanced/solutions/ex13_3_memory_pool.c:176: style: Variable 'obj_ptr' can be declared as pointer to const
advanced/solutions/ex13_3_memory_pool_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_3_memory_pool_c99.c:214: style: Variable 'pool_end' can be declared as pointer to const
advanced/solutions/ex13_3_memory_pool_c99.c:215: style: Variable 'obj_ptr' can be declared as pointer to const
advanced/solutions/ex13_4_generic_macros.c:270: warning: %d in format string (no. 1) requires 'int' but the argument type is 'unsigned int'.
advanced/solutions/ex13_4_generic_macros.c:309: style: The scope of the variable 'j' can be reduced.
advanced/solutions/ex13_4_generic_macros.c:310: style: The scope of the variable 'dummy' can be reduced.
advanced/solutions/ex13_4_generic_macros.c:338: style: The scope of the variable 'j' can be reduced.
advanced/solutions/ex13_4_generic_macros.c:215: style: Variable 'array' can be declared as const array
advanced/solutions/ex13_4_generic_macros.c:167: style: Variable 's1' is assigned a value that is never used.
advanced/solutions/ex13_4_generic_macros.c:168: style: Variable 's2' is assigned a value that is never used.
advanced/solutions/ex13_4_generic_macros.c:296: style: Unused variable: array
advanced/solutions/ex13_4_generic_macros_c99.c:212: error: syntax error: 3.0 =
advanced/solutions/ex13_5_allocator.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_5_allocator.c:157: style: Variable 'pool_end' can be declared as pointer to const
advanced/solutions/ex13_5_allocator.c:158: style: Variable 'obj_ptr' can be declared as pointer to const
advanced/solutions/ex13_5_allocator.c:373: style: Variable 'stats' can be declared as pointer to const
advanced/solutions/ex13_5_allocator_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_5_allocator_c99.c:226: warning: %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'.
advanced/solutions/ex13_5_allocator_c99.c:227: warning: %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'.
advanced/solutions/ex13_5_allocator_c99.c:228: warning: %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'.
advanced/solutions/ex13_5_allocator_c99.c:165: style: Variable 'pool_end' can be declared as pointer to const
advanced/solutions/ex13_5_allocator_c99.c:166: style: Variable 'obj_ptr' can be declared as pointer to const
advanced/solutions/ex13_5_allocator_c99.c:488: style: Variable 'bytes' can be declared as pointer to const
advanced/solutions/ex13_5_allocator_c99.c:479: style: struct member 'TestObject::id' is never used.
advanced/solutions/ex13_5_allocator_c99.c:480: style: struct member 'TestObject::name' is never used.
advanced/solutions/ex13_5_allocator_c99.c:481: style: struct member 'TestObject::value' is never used.
advanced/solutions/ex13_5_allocator_c99.c:482: style: struct member 'TestObject::active' is never used.
advanced/solutions/ex13_6_cache_vector.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_6_cache_vector.c:365: style: Variable 'data' can be declared as pointer to const
advanced/solutions/ex13_6_cache_vector.c:396: style: Variable 'p' can be declared as pointer to const
advanced/solutions/ex13_6_cache_vector.c:434: style: Variable 'p' can be declared as pointer to const
advanced/solutions/ex13_6_cache_vector.c:541: style: Variable 'p' can be declared as pointer to const
advanced/solutions/ex13_6_cache_vector_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_6_cache_vector_c99.c:432: style: Variable 'data' can be declared as pointer to const
advanced/solutions/ex13_6_cache_vector_c99.c:462: style: Variable 'p' can be declared as pointer to const
advanced/solutions/ex13_6_cache_vector_c99.c:365: style: Variable 'optimal_prefetch' is assigned a value that is never used.
advanced/solutions/ex13_7_dsl.c:128: style: Parameter 'machine' can be declared as pointer to const
advanced/solutions/ex13_7_dsl.c:133: style: Parameter 'machine' can be declared as pointer to const
advanced/solutions/ex13_7_dsl.c:138: style: Parameter 'machine' can be declared as pointer to const
advanced/solutions/ex13_7_dsl.c:143: style: Parameter 'machine' can be declared as pointer to const
advanced/solutions/ex13_7_dsl.c:364: style: Parameter 'context' can be declared as pointer to const. However it seems that 'always_true' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s).
advanced/solutions/ex13_7_dsl.c:366: style: Variable 'amount' can be declared as pointer to const
advanced/solutions/ex13_7_dsl.c:371: style: Parameter 'context' can be declared as pointer to const. However it seems that 'process_order' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s).
advanced/solutions/ex13_7_dsl.c:372: style: Parameter 'context' can be declared as pointer to const. However it seems that 'check_inventory' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s).
advanced/solutions/ex13_7_dsl.c:373: style: Parameter 'context' can be declared as pointer to const. However it seems that 'charge_payment' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s).
advanced/solutions/ex13_7_dsl.c:374: style: Parameter 'context' can be declared as pointer to const. However it seems that 'ship_product' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s).
advanced/solutions/ex13_7_dsl_c99.c:137: error: syntax error
advanced/solutions/ex13_8_gc_framework.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_8_gc_framework.c:575: style: The scope of the variable 'len' can be reduced.
advanced/solutions/ex13_8_gc_framework.c:517: style: Variable 'g' can be declared as pointer to const
advanced/solutions/ex13_8_gc_framework.c:594: style: Variable 'obj3' can be declared as pointer to const
advanced/solutions/ex13_8_gc_framework.c:601: style: Variable 'obj3' is assigned a value that is never used.
advanced/solutions/ex13_8_gc_framework_c99.c:186: warning: %zu in format string (no. 2) requires 'size_t' but the argument type is 'signed int'.
advanced/solutions/ex13_8_gc_framework_c99.c:627: style: Variable 'g' can be declared as pointer to const
advanced/solutions/ex13_9_realtime.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_9_realtime.c:212: style: Condition 'rt_partition_heap()<0' is always false
advanced/solutions/ex13_9_realtime.c:183: portability: %lu in format string (no. 2) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
advanced/solutions/ex13_9_realtime.c:550: style: The scope of the variable 'current_time' can be reduced.
advanced/solutions/ex13_9_realtime.c:664: style: The scope of the variable 'p' can be reduced.
advanced/solutions/ex13_9_realtime.c:450: style: Variable 'sc' can be declared as pointer to const
advanced/solutions/ex13_9_realtime.c:679: style: Variable 'times[i]' is assigned a value that is never used.
advanced/solutions/ex13_9_realtime_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
advanced/solutions/ex13_9_realtime_c99.c:280: style: Condition 'rt_partition_heap()<0' is always false
advanced/solutions/ex13_9_realtime_c99.c:286: warning: %zu in format string (no. 2) requires 'size_t' but the argument type is 'signed int'.
advanced/solutions/ex13_9_realtime_c99.c:190: style: Variable 'sc' can be declared as pointer to const
advanced/solutions/ex13_9_realtime_c99.c:537: style: Variable 'sc' can be declared as pointer to const
advanced/solutions/ex13_9_realtime_c99.c:186: style: Variable 'total_needed' is assigned a value that is never used.
advanced/solutions/ex13_9_realtime_c99.c:206: style: Variable 'total_needed' is assigned a value that is never used.
advanced/solutions/ex13_1_macro_basics_c99.c:132: style: The function 'get_grade' is never used.
advanced/solutions/ex13_2_safe_memory.c:212: style: The function 'safe_calloc_impl' is never used.
advanced/solutions/ex13_2_safe_memory_c99.c:354: style: The function 'swap_double' is never used.
advanced/solutions/ex13_3_memory_pool_c99.c:362: style: The function 'point_alloc' is never used.
advanced/solutions/ex13_3_memory_pool_c99.c:362: style: The function 'point_free' is never used.
advanced/solutions/ex13_3_memory_pool_c99.c:362: style: The function 'point_pool_create' is never used.
advanced/solutions/ex13_3_memory_pool_c99.c:362: style: The function 'point_pool_destroy' is never used.
advanced/solutions/ex13_6_cache_vector.c:188: style: The function 'vector_pop_back' is never used.
advanced/solutions/ex13_8_gc_framework_c99.c:596: style: The function 'gc_enable' is never used.
advanced/solutions/ex13_9_realtime_c99.c:123: style: The function 'is_power_of_two' is never used.
advanced/examples/memory_optimization.c:77: style: The function 'init_memory_pool' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:187: style: The function 'print_pool_status' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:206: style: The function 'cleanup_memory_pool' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:221: style: The function 'init_stack_allocator' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:238: style: The function 'stack_alloc' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:256: style: The function 'stack_reset' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:263: style: The function 'cleanup_stack_allocator' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:274: style: The function 'init_object_pool' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:307: style: The function 'object_pool_get' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:326: style: The function 'object_pool_return' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:338: style: The function 'cleanup_object_pool' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:357: style: The function 'debug_malloc' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:369: style: The function 'debug_free' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:380: style: The function 'debug_realloc' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:402: style: The function 'print_memory_stats' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:414: style: The function 'test_memory_alignment' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:448: style: The function 'benchmark_standard_alloc' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:475: style: The function 'benchmark_pool_alloc' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:509: style: The function 'benchmark_object_pool' should have static linkage since it is not used outside of its translation unit.
advanced/examples/memory_optimization.c:543: style: The function 'simulate_memory_leak' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:109: style: The function 'add_int_operation' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:110: style: The function 'sub_int_operation' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:111: style: The function 'mul_int_operation' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:112: style: The function 'add_double_operation' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:113: style: The function 'sub_double_operation' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:114: style: The function 'mul_double_operation' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:171: style: The function 'test_basic_macros' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:211: style: The function 'test_safe_operations' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:266: style: The function 'test_dynamic_functions' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:286: style: The function 'test_generic_macros' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:304: style: The function 'test_benchmarks' should have static linkage since it is not used outside of its translation unit.
advanced/examples/preprocessor_advanced.c:339: style: The function 'test_assertions' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_1_macro_basics.c:218: style: The function 'test_benchmark' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_2_safe_memory.c:426: style: The function 'test_string_operations' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_3_memory_pool.c:358: style: The function 'test_struct_pool' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_3_memory_pool.c:395: style: The function 'test_pool_exhaustion' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_3_memory_pool_c99.c:419: style: The function 'test_vla_integration' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_4_generic_macros.c:139: style: The function 'test_type_checking' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_4_generic_macros.c:163: style: The function 'test_generic_swap' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_4_generic_macros.c:212: style: The function 'test_loop_unrolling' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_4_generic_macros.c:287: style: The function 'test_static_assertions' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_4_generic_macros.c:307: style: The function 'test_benchmark_macros' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_4_generic_macros.c:334: style: The function 'test_macro_composition' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_5_allocator.c:517: style: The function 'test_fragmentation' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector.c:301: style: The function 'vector_cache_optimized_iterate' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector.c:450: style: The function 'test_bulk_operations' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector_c99.c:334: style: The function 'vector_foreach' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector_c99.c:358: style: The function 'vector_optimize_cache' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector_c99.c:495: style: The function 'test_int_vector' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector_c99.c:496: style: The function 'test_double_vector' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector_c99.c:497: style: The function 'test_float_vector' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_6_cache_vector_c99.c:544: style: The function 'test_bulk_operations_vla' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:128: style: The function 'traffic_light_to_yellow' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:133: style: The function 'traffic_light_to_green' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:138: style: The function 'traffic_light_to_red' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:143: style: The function 'traffic_light_emergency' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:162: style: The function 'get_state_name_TrafficLight' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:173: style: The function 'process_event_TrafficLight' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:207: style: The function 'on_button_press' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:214: style: The function 'on_sensor_detect' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:221: style: The function 'on_timer_expire' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:235: style: The function 'dispatch_event' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:283: style: The function 'test_traffic_light' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:310: style: The function 'test_event_system' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:327: style: The function 'test_macro_expansion' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:364: style: The function 'always_true' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:365: style: The function 'check_payment' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:371: style: The function 'process_order' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:372: style: The function 'check_inventory' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:373: style: The function 'charge_payment' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:374: style: The function 'ship_product' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_7_dsl.c:384: style: The function 'test_workflow' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework.c:592: style: The function 'test_basic_gc' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework.c:623: style: The function 'test_reference_counting' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework.c:651: style: The function 'test_generational_gc' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework.c:689: style: The function 'test_circular_reference' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework.c:725: style: The function 'test_gc_performance' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework_c99.c:602: style: The function 'gc_set_time_limit' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework_c99.c:699: style: The function 'gc_new_closure' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework_c99.c:715: style: The function 'test_basic_gc_c99' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework_c99.c:747: style: The function 'test_incremental_gc' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_8_gc_framework_c99.c:773: style: The function 'test_closure_gc' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime.c:491: style: The function 'test_basic_realtime' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime.c:519: style: The function 'test_wcet_measurement' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime.c:546: style: The function 'test_periodic_tasks' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime.c:614: style: The function 'test_stress_realtime' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime.c:662: style: The function 'test_determinism' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime_c99.c:523: style: The function 'rt_get_stats' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime_c99.c:612: style: The function 'test_basic_realtime_c99' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime_c99.c:645: style: The function 'test_wcet_measurement_c99' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime_c99.c:676: style: The function 'test_periodic_tasks_c99' should have static linkage since it is not used outside of its translation unit.
advanced/solutions/ex13_9_realtime_c99.c:757: style: The function 'test_cache_effects' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: There was critical errors (use --checkers-report=<filename> to see details)
```

### arrays

**検査ファイル数**: 20 個

**検出された問題**:
- Errors: 0
0
- Warnings: 10
- Style: 76
- Performance: 0
0
- Portability: 14
- Information: 15

**詳細**:
```
arrays/examples/array_basics.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/examples/array_basics.c:160: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/array_basics.c:161: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/array_basics.c:162: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/array_basics.c:16: style: Variable 'scores' can be declared as const array
arrays/examples/array_basics.c:17: style: Variable 'partial' can be declared as const array
arrays/examples/array_basics.c:25: style: Variable 'search_array' can be declared as const array
arrays/examples/array_basics.c:29: style: Variable 'original' can be declared as const array
arrays/examples/array_basics.c:30: style: Variable 'source' can be declared as const array
arrays/examples/array_basics_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/examples/array_basics_c99.c:159: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/array_basics_c99.c:160: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/array_basics_c99.c:161: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/array_basics_c99.c:36: style: Variable 'scores' can be declared as const array
arrays/examples/array_basics_c99.c:44: style: Variable 'partial' can be declared as const array
arrays/examples/array_basics_c99.c:94: style: Variable 'search_array' can be declared as const array
arrays/examples/array_basics_c99.c:118: style: Variable 'original' can be declared as const array
arrays/examples/array_basics_c99.c:135: style: Variable 'source' can be declared as const array
arrays/examples/multidimensional_arrays.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/examples/multidimensional_arrays.c:13: style: Variable 'matrix' can be declared as const array
arrays/examples/multidimensional_arrays.c:24: style: Variable 'subjects' can be declared as const array
arrays/examples/multidimensional_arrays.c:25: style: Variable 'partial' can be declared as const array
arrays/examples/multidimensional_arrays_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/examples/multidimensional_arrays_c99.c:18: style: Variable 'matrix' can be declared as const array
arrays/examples/multidimensional_arrays_c99.c:47: style: Variable 'subjects' can be declared as const array
arrays/examples/multidimensional_arrays_c99.c:88: style: Variable 'partial' can be declared as const array
arrays/examples/multidimensional_arrays_c99.c:12: style: Unused variable: k
arrays/examples/string_arrays.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/examples/string_arrays.c:54: portability: %lu in format string (no. 2) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays.c:55: portability: %lu in format string (no. 2) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays.c:89: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays.c:90: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays.c:99: warning: scanf() without field width limits can crash with huge input data.
arrays/examples/string_arrays.c:23: style: Variable 'months' can be declared as const array
arrays/examples/string_arrays_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/examples/string_arrays_c99.c:21: portability: %lu in format string (no. 2) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays_c99.c:22: portability: %lu in format string (no. 2) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays_c99.c:78: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays_c99.c:79: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
arrays/examples/string_arrays_c99.c:93: warning: scanf() without field width limits can crash with huge input data.
arrays/examples/string_arrays_c99.c:57: style: Variable 'months' can be declared as const array
arrays/solutions/ex6_1.c:65: style: The scope of the variable 'temp' can be reduced.
arrays/solutions/ex6_1.c:12: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1.c:23: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1.c:37: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1.c:51: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1.c:76: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1_c99.c:13: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1_c99.c:23: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1_c99.c:36: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1_c99.c:49: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_1_c99.c:70: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_2.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_2.c:52: style: The scope of the variable 'total' can be reduced.
arrays/solutions/ex6_2.c:91: style: Unused variable: k
arrays/solutions/ex6_2_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_3.c:38: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_3.c:50: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_3.c:70: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_3_c99.c:38: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_3_c99.c:48: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_3_c99.c:67: style: Parameter 'arr' can be declared as const array
arrays/solutions/ex6_4.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_4.c:13: style: Parameter 'matrix' can be declared as const array
arrays/solutions/ex6_4.c:28: style: Parameter 'a' can be declared as const array
arrays/solutions/ex6_4.c:28: style: Parameter 'b' can be declared as const array
arrays/solutions/ex6_4.c:40: style: Parameter 'a' can be declared as const array
arrays/solutions/ex6_4.c:40: style: Parameter 'b' can be declared as const array
arrays/solutions/ex6_4.c:52: style: Parameter 'a' can be declared as const array
arrays/solutions/ex6_4.c:52: style: Parameter 'b' can be declared as const array
arrays/solutions/ex6_4.c:86: style: Parameter 'matrix' can be declared as const array
arrays/solutions/ex6_4_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_4_c99.c:14: style: Parameter 'matrix' can be declared as const array
arrays/solutions/ex6_4_c99.c:27: style: Parameter 'a' can be declared as const array
arrays/solutions/ex6_4_c99.c:27: style: Parameter 'b' can be declared as const array
arrays/solutions/ex6_4_c99.c:37: style: Parameter 'a' can be declared as const array
arrays/solutions/ex6_4_c99.c:37: style: Parameter 'b' can be declared as const array
arrays/solutions/ex6_4_c99.c:47: style: Parameter 'a' can be declared as const array
arrays/solutions/ex6_4_c99.c:47: style: Parameter 'b' can be declared as const array
arrays/solutions/ex6_4_c99.c:77: style: Parameter 'matrix' can be declared as const array
arrays/solutions/ex6_5.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_5.c:77: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5.c:100: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5.c:128: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5.c:139: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_5_c99.c:73: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5_c99.c:94: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5_c99.c:120: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_5_c99.c:132: warning: scanf() without field width limits can crash with huge input data.
arrays/solutions/ex6_challenge1.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_challenge1.c:87: style: The scope of the variable 'min_idx' can be reduced.
arrays/solutions/ex6_challenge1.c:116: style: The scope of the variable 'j' can be reduced.
arrays/solutions/ex6_challenge1.c:117: style: The scope of the variable 'key' can be reduced.
arrays/solutions/ex6_challenge1.c:24: style: Parameter 'source' can be declared as const array
arrays/solutions/ex6_challenge1.c:143: style: Parameter 'stats' can be declared as pointer to const
arrays/solutions/ex6_challenge1.c:189: style: Variable 'max_time' is assigned a value that is never used.
arrays/solutions/ex6_challenge1_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
arrays/solutions/ex6_challenge1_c99.c:25: style: Parameter 'source' can be declared as const array
arrays/solutions/ex6_challenge1_c99.c:131: style: Parameter 'stats' can be declared as pointer to const
arrays/solutions/ex6_challenge1_c99.c:167: style: Variable 'max_time' is assigned a value that is never used.
arrays/solutions/ex6_challenge2.c:223: style: The scope of the variable 'choice' can be reduced.
arrays/solutions/ex6_challenge2.c:15: style: Parameter 'grid' can be declared as const array
arrays/solutions/ex6_challenge2.c:46: style: Variable 'dr' can be declared as const array
arrays/solutions/ex6_challenge2.c:47: style: Variable 'dc' can be declared as const array
arrays/solutions/ex6_challenge2.c:203: style: Parameter 'grid1' can be declared as const array
arrays/solutions/ex6_challenge2.c:203: style: Parameter 'grid2' can be declared as const array
arrays/solutions/ex6_challenge2.c:44: style: Unused variable: j
arrays/solutions/ex6_challenge2.c:156: style: Unused variable: input
arrays/solutions/ex6_challenge2_c99.c:17: style: Parameter 'grid' can be declared as const array
arrays/solutions/ex6_challenge2_c99.c:44: style: Variable 'dr' can be declared as const array
arrays/solutions/ex6_challenge2_c99.c:45: style: Variable 'dc' can be declared as const array
arrays/solutions/ex6_challenge2_c99.c:192: style: Parameter 'grid1' can be declared as const array
arrays/solutions/ex6_challenge2_c99.c:192: style: Parameter 'grid2' can be declared as const array
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### basics-syntax

**検査ファイル数**: 16 個

**検出された問題**:
- Errors: 0
0
- Warnings: 0
0
- Style: 1
- Performance: 0
0
- Portability: 0
0
- Information: 3

**詳細**:
```
basics-syntax/examples/formatted_output_c99.c:47: style: Variable 'name' can be declared as const array
basics-syntax/solutions/ex2_6_ascii_explorer.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
basics-syntax/solutions/ex2_6_ascii_explorer_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### basics

**検査ファイル数**: 32 個

**検出された問題**:
- Errors: 0
0
- Warnings: 0
0
- Style: 10
- Performance: 0
0
- Portability: 0
0
- Information: 1

**詳細**:
```
basics/solutions/ex1_1_self_introduction.c:13: style: Variable 'name' can be declared as const array
basics/solutions/ex1_1_self_introduction.c:15: style: Variable 'hobby' can be declared as const array
basics/solutions/ex1_1_self_introduction.c:16: style: Variable 'language' can be declared as const array
basics/solutions/ex1_1_self_introduction_c99.c:13: style: Variable 'name' can be declared as const array
basics/solutions/ex1_1_self_introduction_c99.c:15: style: Variable 'hobby' can be declared as const array
basics/solutions/ex1_1_self_introduction_c99.c:16: style: Variable 'language' can be declared as const array
basics/solutions/ex2_1_personal_info.c:13: style: Variable 'name' can be declared as const array
basics/solutions/ex2_1_personal_info_c99.c:13: style: Variable 'name' can be declared as const array
basics/solutions/ex4_3_ternary_operator.c:38: style: Condition 'test_score>=60' is always true
basics/solutions/ex4_3_ternary_operator_c99.c:35: style: Condition 'test_score>=60' is always true
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### control-if

**検査ファイル数**: 18 個

**検出された問題**:
- Errors: 0
0
- Warnings: 0
0
- Style: 28
- Performance: 0
0
- Portability: 0
0
- Information: 13

**詳細**:
```
control-if/examples/conditional_operator.c:20: style: Variable 'result' can be declared as pointer to const
control-if/examples/conditional_operator.c:21: style: Variable 'status' can be declared as pointer to const
control-if/examples/conditional_operator_c99.c:29: style: Variable 'status' can be declared as pointer to const
control-if/examples/conditional_operator_c99.c:37: style: Variable 'result' can be declared as pointer to const
control-if/examples/if_basic.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/examples/if_basic_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_1_ticket_pricing.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_1_ticket_pricing.c:35: style: Condition 'age>=3' is always true
control-if/solutions/ex4_1_ticket_pricing.c:14: style: Variable 'category' can be declared as pointer to const
control-if/solutions/ex4_1_ticket_pricing_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_1_ticket_pricing_c99.c:35: style: Condition 'age>=3' is always true
control-if/solutions/ex4_1_ticket_pricing_c99.c:30: style: Variable 'category' can be declared as pointer to const
control-if/solutions/ex4_3_bmi_judge.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_3_bmi_judge.c:13: style: Variable 'category' can be declared as pointer to const
control-if/solutions/ex4_3_bmi_judge.c:14: style: Variable 'advice' can be declared as pointer to const
control-if/solutions/ex4_3_bmi_judge_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_3_bmi_judge_c99.c:41: style: Variable 'category' can be declared as pointer to const
control-if/solutions/ex4_3_bmi_judge_c99.c:42: style: Variable 'advice' can be declared as pointer to const
control-if/solutions/ex4_4_leap_year.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_4_leap_year_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_5_grade_system.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_5_grade_system.c:16: style: Variable 'evaluation' can be declared as pointer to const
control-if/solutions/ex4_5_grade_system.c:18: style: Variable 'result' can be declared as pointer to const
control-if/solutions/ex4_5_grade_system_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_5_grade_system_c99.c:48: style: Variable 'evaluation' can be declared as pointer to const
control-if/solutions/ex4_5_grade_system_c99.c:69: style: Variable 'result' can be declared as pointer to const
control-if/solutions/ex4_6_janken_game.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_6_janken_game.c:14: style: The scope of the variable 'computer_choice' can be reduced.
control-if/solutions/ex4_6_janken_game.c:18: style: The scope of the variable 'result_message' can be reduced.
control-if/solutions/ex4_6_janken_game.c:17: style: Variable 'hands' can be declared as const array
control-if/solutions/ex4_6_janken_game.c:18: style: Variable 'result_message' can be declared as pointer to const
control-if/solutions/ex4_6_janken_game.c:56: style: Variable 'result_message' is assigned a value that is never used.
control-if/solutions/ex4_6_janken_game.c:62: style: Variable 'result_message' is assigned a value that is never used.
control-if/solutions/ex4_6_janken_game.c:66: style: Variable 'result_message' is assigned a value that is never used.
control-if/solutions/ex4_6_janken_game_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-if/solutions/ex4_6_janken_game_c99.c:18: style: Variable 'hands' can be declared as const array
control-if/solutions/ex4_6_janken_game_c99.c:50: style: Variable 'result_message' can be declared as pointer to const
control-if/solutions/ex4_6_janken_game_c99.c:53: style: Variable 'result_message' is assigned a value that is never used.
control-if/solutions/ex4_6_janken_game_c99.c:59: style: Variable 'result_message' is assigned a value that is never used.
control-if/solutions/ex4_6_janken_game_c99.c:63: style: Variable 'result_message' is assigned a value that is never used.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### control-loop

**検査ファイル数**: 15 個

**検出された問題**:
- Errors: 0
0
- Warnings: 0
0
- Style: 7
- Performance: 0
0
- Portability: 0
0
- Information: 8

**詳細**:
```
control-loop/examples/break_continue.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_1_fibonacci.c:32: style: Condition 'n>=1' is always true
control-loop/solutions/ex5_1_fibonacci.c:13: style: The scope of the variable 'next' can be reduced.
control-loop/solutions/ex5_1_fibonacci_c99.c:29: style: Condition 'n>=1' is always true
control-loop/solutions/ex5_2_number_guess.c:15: style: The scope of the variable 'guess' can be reduced.
control-loop/solutions/ex5_2_number_guess.c:38: style: Unused variable: i
control-loop/solutions/ex5_3_prime_list.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_3_prime_list.c:15: style: The scope of the variable 'is_prime' can be reduced.
control-loop/solutions/ex5_3_prime_list_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_4_draw_shapes.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_4_draw_shapes_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_6_factorial.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_6_factorial_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
control-loop/solutions/ex5_6_factorial_c99.c:30: style: The scope of the variable 'i' can be reduced.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### data-types

**検査ファイル数**: 16 個

**検出された問題**:
- Errors: 0
0
- Warnings: 11
- Style: 6
- Performance: 0
0
- Portability: 80
- Information: 1

**詳細**:
```
data-types/examples/data_types_demo.c:25: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo.c:27: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo.c:29: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo.c:31: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo.c:33: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo.c:35: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo.c:37: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:15: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:19: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:23: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:27: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:31: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:36: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/examples/data_types_demo_c99.c:40: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:45: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:46: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:47: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:48: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:49: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:50: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration.c:51: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:45: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:46: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:47: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:48: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:49: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:50: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_1_variable_declaration_c99.c:51: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:17: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:18: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:19: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:20: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:21: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:22: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:23: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:24: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:25: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:26: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:27: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:28: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:38: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:39: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:40: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:41: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:42: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:47: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:48: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:49: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:50: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo.c:61: warning: %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed int'.
data-types/solutions/ex3_3_sizeof_demo.c:67: warning: %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed int'.
data-types/solutions/ex3_3_sizeof_demo.c:73: warning: %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed long'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:18: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:19: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:20: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:21: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:22: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:23: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:24: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:25: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:26: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:27: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:28: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:29: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:30: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:31: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:35: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:36: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:37: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:38: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:39: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:40: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:41: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:42: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:47: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:50: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:53: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:56: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:57: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:61: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:62: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:63: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:64: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:70: warning: %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed int'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:72: warning: %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed int'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:74: warning: %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed long'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:86: warning: %d in format string (no. 1) requires 'int' but the argument type is 'signed long'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:88: warning: %lld in format string (no. 1) requires 'long long' but the argument type is 'unsigned long long'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:88: warning: %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'.
data-types/solutions/ex3_3_sizeof_demo_c99.c:89: warning: %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'.
data-types/solutions/ex3_4_type_conversion_c99.c:74: warning: %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'.
data-types/solutions/ex3_5_scope_experiment.c:123: style: Local variable 'global_counter' shadows outer variable
data-types/solutions/ex3_5_scope_experiment.c:129: style: Local variable 'global_counter' shadows outer variable
data-types/solutions/ex3_5_scope_experiment_c99.c:140: style: Local variable 'global_counter' shadows outer variable
data-types/solutions/ex3_5_scope_experiment_c99.c:146: style: Local variable 'global_counter' shadows outer variable
data-types/solutions/ex3_6_constants_demo.c:67: style: float result is assigned to double variable. If the variable is double to avoid loss of information, then you have loss of information.
data-types/solutions/ex3_6_constants_demo_c99.c:69: style: float result is assigned to double variable. If the variable is double to avoid loss of information, then you have loss of information.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### function-pointers

**検査ファイル数**: 14 個

**検出された問題**:
- Errors: 0
0
- Warnings: 0
0
- Style: 48
- Performance: 0
0
- Portability: 0
0
- Information: 8

**詳細**:
```
function-pointers/examples/callback_functions.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/examples/callback_functions.c:46: style: Parameter 'arr' can be declared as const array
function-pointers/examples/callback_functions_c99.c:122: style: struct member 'Event::name' is never used.
function-pointers/examples/function_pointer_arrays.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/examples/function_pointer_arrays.c:323: style: Condition 'op_index>=0' is always true
function-pointers/examples/function_pointer_arrays.c:157: style: Parameter 'arr' can be declared as const array
function-pointers/examples/function_pointer_arrays.c:284: style: Variable 'original' can be declared as const array
function-pointers/examples/function_pointer_arrays_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/examples/function_pointer_arrays_c99.c:318: style: Condition 'use_multiply' is always true
function-pointers/examples/function_pointer_arrays_c99.c:272: style: Variable 'original' can be declared as const array
function-pointers/examples/function_pointer_basic.c:83: style: Variable 'operators' can be declared as const array
function-pointers/examples/function_pointer_basic_c99.c:82: style: Variable 'operators' can be declared as const array
function-pointers/solutions/ex12_1_basic_function_pointer.c:69: style: Variable 'names' can be declared as const array
function-pointers/solutions/ex12_1_basic_function_pointer_c99.c:63: style: Variable 'names' can be declared as const array
function-pointers/solutions/ex12_2_function_selector.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/solutions/ex12_2_function_selector.c:92: style: Variable 'operators' can be declared as const array
function-pointers/solutions/ex12_2_function_selector.c:93: style: Variable 'names' can be declared as const array
function-pointers/solutions/ex12_2_function_selector_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/solutions/ex12_2_function_selector_c99.c:91: style: Variable 'operators' can be declared as const array
function-pointers/solutions/ex12_2_function_selector_c99.c:92: style: Variable 'names' can be declared as const array
function-pointers/solutions/ex12_3_array_callback.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/solutions/ex12_3_array_callback.c:28: style: Parameter 'arr' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback.c:28: style: Parameter 'description' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback.c:43: style: Parameter 'operation_name' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback.c:58: style: Parameter 'original' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback.c:118: style: Variable 'selection_pattern' can be declared as const array
function-pointers/solutions/ex12_3_array_callback_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
function-pointers/solutions/ex12_3_array_callback_c99.c:28: style: Parameter 'arr' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback_c99.c:28: style: Parameter 'description' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback_c99.c:41: style: Parameter 'operation_name' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback_c99.c:54: style: Parameter 'original' can be declared as pointer to const
function-pointers/solutions/ex12_3_array_callback_c99.c:111: style: Variable 'selection_pattern' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array.c:46: style: Parameter 'history' can be declared as pointer to const
function-pointers/solutions/ex12_4_calculator_function_array.c:67: style: Parameter 'history' can be declared as pointer to const
function-pointers/solutions/ex12_4_calculator_function_array.c:71: style: Variable 'operations' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array.c:72: style: Variable 'operation_names' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array.c:99: style: Variable 'op_symbols' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array.c:100: style: Variable 'op_names' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array_c99.c:46: style: Parameter 'history' can be declared as pointer to const
function-pointers/solutions/ex12_4_calculator_function_array_c99.c:65: style: Parameter 'history' can be declared as pointer to const
function-pointers/solutions/ex12_4_calculator_function_array_c99.c:72: style: Variable 'operations' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array_c99.c:73: style: Variable 'operation_names' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array_c99.c:97: style: Variable 'op_symbols' can be declared as const array
function-pointers/solutions/ex12_4_calculator_function_array_c99.c:98: style: Variable 'op_names' can be declared as const array
function-pointers/examples/callback_functions.c:10: style: The function 'increment' is never used.
function-pointers/examples/callback_functions.c:16: style: The function 'is_negative' is never used.
function-pointers/examples/callback_functions_c99.c:141: style: The function 'on_warning_event' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:167: style: The function 'subtract_for_logging' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:168: style: The function 'divide_for_logging' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:171: style: The function 'map_array' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:180: style: The function 'reduce_array' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:191: style: The function 'sum_reducer' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:192: style: The function 'product_reducer' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:193: style: The function 'max_reducer' should have static linkage since it is not used outside of its translation unit.
function-pointers/examples/callback_functions_c99.c:194: style: The function 'min_reducer' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### functions

**検査ファイル数**: 22 個

**検出された問題**:
- Errors: 0
0
- Warnings: 1
- Style: 87
- Performance: 0
0
- Portability: 0
0
- Information: 13

**詳細**:
```
functions/examples/advanced_functions.c:43: style: Parameter 'arr' can be declared as const array
functions/examples/advanced_functions.c:54: style: Parameter 'arr' can be declared as const array
functions/examples/function_basics.c:144: style: Condition 'num2!=0' is always true
functions/examples/function_basics_c99.c:120: style: Condition 'is_even(x)' is always false
functions/examples/function_basics_c99.c:121: style: Condition 'is_even(y)' is always false
functions/examples/function_basics_c99.c:151: style: Condition 'num2!=0' is always true
functions/solutions/ex9_1_prime_functions.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_1_prime_functions_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_1_prime_functions_c99.c:265: style: Variable 'test_numbers' can be declared as const array
functions/solutions/ex9_2_array_operations.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_2_array_operations.c:29: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_2_array_operations.c:54: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_2_array_operations.c:76: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_2_array_operations.c:120: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_2_array_operations.c:146: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_2_array_operations.c:192: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_2_array_operations_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_2_array_operations_c99.c:96: style: The scope of the variable 'swapped' can be reduced.
functions/solutions/ex9_2_array_operations_c99.c:285: style: Variable 'targets' can be declared as const array
functions/solutions/ex9_3_string_processing.c:138: style: The scope of the variable 'temp' can be reduced.
functions/solutions/ex9_4_multiple_returns.c:117: style: Parameter 'data' can be declared as const array
functions/solutions/ex9_4_multiple_returns.c:147: style: Parameter 'data' can be declared as const array
functions/solutions/ex9_4_multiple_returns.c:174: style: Parameter 'sorted_data' can be declared as const array
functions/solutions/ex9_4_multiple_returns_c99.c:286: style: The scope of the variable 'swapped' can be reduced.
functions/solutions/ex9_5_error_handling.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_5_error_handling.c:255: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_5_error_handling.c:280: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_5_error_handling_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_5_error_handling_c99.c:258: warning: Expression 'temp_base' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation.
functions/solutions/ex9_6_struct_functions.c:441: style: Condition 'is_leap_year(2024)' is always true
functions/solutions/ex9_6_struct_functions.c:442: style: Condition 'is_leap_year(2023)' is always false
functions/solutions/ex9_6_struct_functions.c:261: style: Variable 'days' can be declared as const array
functions/solutions/ex9_6_struct_functions_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_6_struct_functions_c99.c:562: style: Condition 'is_leap_year(2024)' is always true
functions/solutions/ex9_6_struct_functions_c99.c:563: style: Condition 'is_leap_year(2023)' is always false
functions/solutions/ex9_6_struct_functions_c99.c:247: style: The scope of the variable 'swapped' can be reduced.
functions/solutions/ex9_6_struct_functions_c99.c:507: style: Variable 'most_valuable' can be declared as pointer to const
functions/solutions/ex9_7_recursive_functions.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_7_recursive_functions_c99.c:131: style: Variable 'gcd_pairs' can be declared as const array
functions/solutions/ex9_7_recursive_functions_c99.c:195: style: Variable 'sizes' can be declared as const array
functions/solutions/ex9_7_recursive_functions_c99.c:208: style: Variable 'numbers' can be declared as const array
functions/solutions/ex9_8_advanced_strings.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_8_advanced_strings.c:25: style: Parameter 'str' can be declared as const array
functions/solutions/ex9_8_advanced_strings.c:460: style: Variable 'widths' can be declared as const array
functions/solutions/ex9_8_advanced_strings_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_8_advanced_strings_c99.c:21: style: Parameter 'str' can be declared as const array
functions/solutions/ex9_8_advanced_strings_c99.c:303: style: Variable 'widths' can be declared as const array
functions/solutions/ex9_9_sorting_algorithms.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_9_sorting_algorithms.c:25: style: The scope of the variable 'swapped' can be reduced.
functions/solutions/ex9_9_sorting_algorithms.c:49: style: The scope of the variable 'min_idx' can be reduced.
functions/solutions/ex9_9_sorting_algorithms.c:75: style: The scope of the variable 'j' can be reduced.
functions/solutions/ex9_9_sorting_algorithms.c:75: style: The scope of the variable 'key' can be reduced.
functions/solutions/ex9_9_sorting_algorithms.c:149: style: The scope of the variable 'mid' can be reduced.
functions/solutions/ex9_9_sorting_algorithms.c:194: style: The scope of the variable 'pivot_index' can be reduced.
functions/solutions/ex9_9_sorting_algorithms.c:267: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_9_sorting_algorithms.c:280: style: Parameter 'src' can be declared as const array
functions/solutions/ex9_9_sorting_algorithms_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
functions/solutions/ex9_9_sorting_algorithms_c99.c:329: style: Condition 'should_sort_ascending' is always true
functions/solutions/ex9_9_sorting_algorithms_c99.c:172: style: Parameter 'arr' can be declared as const array
functions/solutions/ex9_9_sorting_algorithms_c99.c:183: style: Parameter 'src' can be declared as const array
functions/solutions/ex9_9_sorting_algorithms_c99.c:288: style: Variable 'size_variations' can be declared as const array
functions/solutions/ex9_5_error_handling.c:71: style: The function 'get_last_error' is never used.
functions/solutions/ex9_5_error_handling.c:83: style: The function 'clear_error' is never used.
functions/solutions/ex9_5_error_handling.c:140: style: The function 'safe_multiply' is never used.
functions/solutions/ex9_5_error_handling.c:365: style: The function 'safe_string_concat' is never used.
functions/solutions/ex9_5_error_handling.c:423: style: The function 'safe_file_read_line' is never used.
functions/solutions/ex9_5_error_handling.c:455: style: The function 'safe_file_write_int' is never used.
functions/solutions/ex9_5_error_handling_c99.c:99: style: The function 'get_last_error_code' is never used.
functions/solutions/ex9_5_error_handling_c99.c:105: style: The function 'get_last_error_info' is never used.
functions/solutions/ex9_6_struct_functions.c:116: style: The function 'update_stock' is never used.
functions/solutions/ex9_6_struct_functions.c:159: style: The function 'update_score' is never used.
functions/solutions/ex9_6_struct_functions.c:277: style: The function 'date_difference' is never used.
functions/examples/advanced_functions_c99.c:112: style: The function 'min' should have static linkage since it is not used outside of its translation unit.
functions/examples/advanced_functions_c99.c:118: style: The function 'process_variable_array' should have static linkage since it is not used outside of its translation unit.
functions/examples/function_basics_c99.c:75: style: The function 'is_even' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_1_prime_functions_c99.c:123: style: The function 'analyze_prime_gaps' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_2_array_operations_c99.c:197: style: The function 'is_sorted' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_2_array_operations_c99.c:216: style: The function 'find_second_max' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_3_string_processing_c99.c:216: style: The function 'trim_spaces' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_3_string_processing_c99.c:244: style: The function 'starts_with' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_3_string_processing_c99.c:257: style: The function 'ends_with' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_4_multiple_returns_c99.c:70: style: The function 'seconds_to_time_struct' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_4_multiple_returns_c99.c:123: style: The function 'polar_to_point' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_4_multiple_returns_c99.c:185: style: The function 'calculate_statistics' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling.c:56: style: The function 'set_error' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling.c:77: style: The function 'get_error_message' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling.c:90: style: The function 'error_to_string' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:79: style: The function 'set_error_with_location' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:120: style: The function 'error_code_to_string' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:141: style: The function 'register_error_handler' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:146: style: The function 'trigger_error_handler' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:366: style: The function 'safe_array_minmax' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:478: style: The function 'safe_string_format' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_5_error_handling_c99.c:563: style: The function 'custom_error_handler' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_6_struct_functions_c99.c:160: style: The function 'find_most_valuable_product' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_6_struct_functions_c99.c:269: style: The function 'calculate_class_statistics' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_6_struct_functions_c99.c:467: style: The function 'rectangles_overlap' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_8_advanced_strings.c:345: style: The function 'my_strncmp' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_8_advanced_strings.c:362: style: The function 'is_digit' should have static linkage since it is not used outside of its translation unit.
functions/solutions/ex9_9_sorting_algorithms_c99.c:194: style: The function 'measure_sort_performance' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### introduction

**検査ファイル数**: 5 個

**検出された問題**:
- Errors: 0
0
- Warnings: 2
- Style: 9
- Performance: 0
0
- Portability: 0
0
- Information: 1

**詳細**:
```
introduction/examples/environment_check.c:37: warning: %ld in format string (no. 1) requires 'long' but the argument type is 'signed int'.
introduction/solutions/ex1_6_system_info_c99.c:45: style: Condition 'ptr_size==4' is always false
introduction/solutions/ex1_6_system_info_c99.c:49: style: Condition 'ptr_size==8' is always true
introduction/solutions/ex1_6_system_info_c99.c:81: style: Condition '!os_detected' is always true
introduction/solutions/ex1_6_system_info_c99.c:179: style: Condition 'test' is always true
introduction/solutions/ex1_6_system_info_c99.c:174: style: Unused variable: vla
introduction/solutions/ex1_6_system_info_c99.c:163: warning: %lld in format string (no. 2) requires 'long long' but the argument type is 'signed int'.
introduction/solutions/ex1_6_system_info_c99.c:81: style: Condition '!os_detected' is always false
introduction/examples/environment_check.c:14: style: The function 'print_environment_info' should have static linkage since it is not used outside of its translation unit.
introduction/examples/environment_check.c:72: style: The function 'test_basic_operations' should have static linkage since it is not used outside of its translation unit.
introduction/solutions/ex1_6_system_info_c99.c:168: style: The function 'show_c99_features' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### operators

**検査ファイル数**: 18 個

**検出された問題**:
- Errors: 0
0
- Warnings: 1
- Style: 159
- Performance: 0
0
- Portability: 0
0
- Information: 6

**詳細**:
```
operators/examples/bitwise_demo_c99.c:172: style: Condition 'flag_a_on' is always true
operators/examples/bitwise_demo_c99.c:175: style: Condition '!flag_b_on' is always true
operators/examples/operators_demo.c:57: style: Condition 'a==b' is always false
operators/examples/operators_demo.c:58: style: Condition 'a!=b' is always true
operators/examples/operators_demo.c:59: style: Condition 'a<b' is always false
operators/examples/operators_demo.c:60: style: Condition 'a<=b' is always false
operators/examples/operators_demo.c:61: style: Condition 'a>b' is always true
operators/examples/operators_demo.c:62: style: Condition 'a>=b' is always true
operators/examples/operators_demo.c:76: style: Condition 'a!=0' is always false
operators/examples/operators_demo.c:84: style: Condition 'a>b' is always false
operators/examples/operators_demo.c:68: style: Argument 'a||b' to function printf is always 1. It does not matter what value 'b' has.
operators/examples/operators_demo_c99.c:59: style: Condition 'a==b' is always false
operators/examples/operators_demo_c99.c:60: style: Condition 'a!=b' is always true
operators/examples/operators_demo_c99.c:61: style: Condition 'a<b' is always true
operators/examples/operators_demo_c99.c:62: style: Condition 'a<=b' is always true
operators/examples/operators_demo_c99.c:63: style: Condition 'a>b' is always false
operators/examples/operators_demo_c99.c:64: style: Condition 'a>=b' is always false
operators/examples/operators_demo_c99.c:69: style: Condition 'p' is always true
operators/examples/operators_demo_c99.c:69: style: Condition 'q' is always false
operators/examples/operators_demo_c99.c:70: style: Condition '!p' is always false
operators/examples/operators_demo_c99.c:71: style: Condition 'p' is always true
operators/examples/operators_demo_c99.c:71: style: Condition 'q' is always false
operators/examples/operators_demo_c99.c:72: style: Condition 'p' is always true
operators/examples/operators_demo_c99.c:90: style: Condition 'a>b' is always false
operators/examples/operators_demo_c99.c:96: style: Condition 'score>=90' is always false
operators/examples/operators_demo_c99.c:97: style: Condition 'score>=80' is always true
operators/examples/precedence_demo.c:45: style: Condition 'a<b' is always true
operators/examples/precedence_demo.c:45: style: Condition 'c>d' is always false
operators/examples/precedence_demo.c:48: style: Condition 'a<b' is always true
operators/examples/precedence_demo.c:49: style: Condition 'c>d' is always false
operators/examples/precedence_demo.c:50: style: Condition 'a<b' is always true
operators/examples/precedence_demo.c:50: style: Condition 'c>d' is always false
operators/examples/precedence_demo.c:56: style: Condition '(a&b)==2' is always true
operators/examples/precedence_demo_c99.c:45: style: Condition 'a<b' is always true
operators/examples/precedence_demo_c99.c:45: style: Condition 'c>d' is always false
operators/examples/precedence_demo_c99.c:47: style: Condition 'comparison_result' is always false
operators/examples/precedence_demo_c99.c:49: style: Condition 'a<b' is always true
operators/examples/precedence_demo_c99.c:50: style: Condition 'c>d' is always false
operators/examples/precedence_demo_c99.c:52: style: Condition 'a<b' is always true
operators/examples/precedence_demo_c99.c:53: style: Condition 'c>d' is always false
operators/examples/precedence_demo_c99.c:54: style: Condition 'comparison_result' is always false
operators/examples/precedence_demo_c99.c:60: style: Condition '(a&b)==2' is always true
operators/examples/precedence_demo_c99.c:61: style: Condition 'bit_comparison' is always true
operators/examples/precedence_demo_c99.c:64: style: Condition 'bit_comparison' is always true
operators/solutions/ex4_3_increment.c:110: style: Variable 'ptr' can be declared as pointer to const
operators/solutions/ex4_3_increment_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
operators/solutions/ex4_3_increment_c99.c:134: style: Condition 'should_increment' is always true
operators/solutions/ex4_3_increment_c99.c:139: style: Condition 'should_increment' is always false
operators/solutions/ex4_3_increment_c99.c:22: style: Variable 'a' is assigned an expression that holds the same value.
operators/solutions/ex4_3_increment_c99.c:37: style: Variable 'a' is assigned an expression that holds the same value.
operators/solutions/ex4_3_increment_c99.c:147: style: Variable 'ptr' can be declared as pointer to const
operators/solutions/ex4_3_increment_c99.c:148: style: Variable 'end' can be declared as pointer to const
operators/solutions/ex4_3_increment_c99.c:166: style: Variable 'p' can be declared as pointer to const
operators/solutions/ex4_4_bitwise.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
operators/solutions/ex4_4_bitwise.c:16: warning: %d in format string (no. 1) requires 'int' but the argument type is 'unsigned int'.
operators/solutions/ex4_4_bitwise_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
operators/solutions/ex4_4_bitwise_c99.c:252: style: The if condition is the same as the previous if condition
operators/solutions/ex4_4_bitwise_c99.c:224: style: The scope of the variable 'color' can be reduced.
operators/solutions/ex4_4_bitwise_c99.c:137: style: struct member 'BitManipulation::operation' is never used.
operators/solutions/ex4_4_bitwise_c99.c:138: style: struct member 'BitManipulation::func' is never used.
operators/solutions/ex4_4_bitwise_c99.c:139: style: struct member 'BitManipulation::description' is never used.
operators/solutions/ex4_4_bitwise_c99.c:224: style: Variable 'color' is assigned a value that is never used.
operators/solutions/ex4_5_conditional.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
operators/solutions/ex4_5_conditional.c:66: style: Condition 'number>=0' is always true
operators/solutions/ex4_5_conditional.c:67: style: Condition 'number>=0' is always true
operators/solutions/ex4_5_conditional.c:68: style: Condition 'number>0' is always true
operators/solutions/ex4_5_conditional.c:70: style: Condition 'number%2==0' is always false
operators/solutions/ex4_5_conditional.c:76: style: Condition 'score>=90' is always false
operators/solutions/ex4_5_conditional.c:76: style: Condition 'score>=80' is always true
operators/solutions/ex4_5_conditional.c:133: style: Condition 'is_student' is always true
operators/solutions/ex4_5_conditional.c:136: style: Condition 'is_student' is always true
operators/solutions/ex4_5_conditional.c:136: style: Condition 'age<25' is always true
operators/solutions/ex4_5_conditional.c:139: style: Condition 'is_student' is always true
operators/solutions/ex4_5_conditional.c:139: style: Condition 'age<25' is always true
operators/solutions/ex4_5_conditional.c:53: style: The scope of the variable 'ch' can be reduced.
operators/solutions/ex4_5_conditional.c:54: style: The scope of the variable 'type' can be reduced.
operators/solutions/ex4_5_conditional.c:55: style: The scope of the variable 'idx' can be reduced.
operators/solutions/ex4_5_conditional.c:56: style: The scope of the variable 'safe_idx' can be reduced.
operators/solutions/ex4_5_conditional.c:57: style: The scope of the variable 'safe_value' can be reduced.
operators/solutions/ex4_5_conditional.c:66: style: Argument '(number>=0)?number:-number' to function printf is always 15. It does not matter what value 'number' has.
operators/solutions/ex4_5_conditional.c:47: style: Variable 'text' can be declared as const array
operators/solutions/ex4_5_conditional.c:48: style: Variable 'months' can be declared as const array
operators/solutions/ex4_5_conditional.c:49: style: Variable 'indices' can be declared as const array
operators/solutions/ex4_5_conditional.c:51: style: Variable 'safe_array' can be declared as const array
operators/solutions/ex4_5_conditional_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
operators/solutions/ex4_5_conditional_c99.c:36: style: Condition 'number>=0' is always true
operators/solutions/ex4_5_conditional_c99.c:37: style: Condition 'number>=0' is always true
operators/solutions/ex4_5_conditional_c99.c:38: style: Condition 'number>0' is always true
operators/solutions/ex4_5_conditional_c99.c:39: style: Condition 'number%2==0' is always false
operators/solutions/ex4_5_conditional_c99.c:45: style: Condition 'score>=90' is always false
operators/solutions/ex4_5_conditional_c99.c:46: style: Condition 'score>=80' is always true
operators/solutions/ex4_5_conditional_c99.c:99: style: Condition 'is_student' is always true
operators/solutions/ex4_5_conditional_c99.c:102: style: Condition 'is_student' is always true
operators/solutions/ex4_5_conditional_c99.c:102: style: Condition 'age<25' is always true
operators/solutions/ex4_5_conditional_c99.c:105: style: Condition 'is_student' is always true
operators/solutions/ex4_5_conditional_c99.c:105: style: Condition 'age<25' is always true
operators/solutions/ex4_5_conditional_c99.c:166: style: Condition 'byte_val<128' is always false
operators/solutions/ex4_5_conditional_c99.c:36: style: Argument '(number>=0)?number:-number' to function printf is always 15. It does not matter what value 'number' has.
operators/solutions/ex4_5_conditional_c99.c:122: style: Variable 'text' can be declared as const array
operators/solutions/ex4_5_conditional_c99.c:140: style: Variable 'months' can be declared as const array
operators/solutions/ex4_5_conditional_c99.c:148: style: Variable 'indices' can be declared as const array
operators/solutions/ex4_5_conditional_c99.c:150: style: Variable 'safe_array' can be declared as const array
operators/solutions/ex4_6_precedence.c:168: style: Boolean result is used in bitwise operation. Clarify expression with parentheses.
operators/solutions/ex4_6_precedence.c:37: style: Condition 'a>b' is always true
operators/solutions/ex4_6_precedence.c:37: style: Condition 'b<c' is always true
operators/solutions/ex4_6_precedence.c:38: style: Condition 'a>b+1' is always true
operators/solutions/ex4_6_precedence.c:69: style: Condition 'score>=60' is always true
operators/solutions/ex4_6_precedence.c:69: style: Condition 'score<=100' is always true
operators/solutions/ex4_6_precedence.c:110: style: Condition 'p<q' is always true
operators/solutions/ex4_6_precedence.c:110: style: Condition 'r>s' is always false
operators/solutions/ex4_6_precedence.c:110: style: Condition 'p==q' is always false
operators/solutions/ex4_6_precedence.c:113: style: Condition 'p<q' is always true
operators/solutions/ex4_6_precedence.c:113: style: Condition 'r>s' is always false
operators/solutions/ex4_6_precedence.c:113: style: Condition 'p==q' is always false
operators/solutions/ex4_6_precedence.c:114: style: Condition 'p<q' is always true
operators/solutions/ex4_6_precedence.c:114: style: Condition 'r>s' is always false
operators/solutions/ex4_6_precedence.c:114: style: Condition 'p==q' is always false
operators/solutions/ex4_6_precedence.c:119: style: Condition 'p+++++q*r-->s' is always true
operators/solutions/ex4_6_precedence.c:119: style: Condition 'q!=r' is always true
operators/solutions/ex4_6_precedence.c:151: style: Condition 'x>0' is always true
operators/solutions/ex4_6_precedence.c:151: style: Condition 'x>10' is always false
operators/solutions/ex4_6_precedence.c:169: style: Condition '(flags&mask)==1' is always true
operators/solutions/ex4_6_precedence.c:205: style: Condition 'score>=90' is always false
operators/solutions/ex4_6_precedence.c:205: style: Condition 'score>=80' is always true
operators/solutions/ex4_6_precedence.c:207: style: Condition 'score>=90' is always false
operators/solutions/ex4_6_precedence.c:207: style: Condition 'score>=80' is always true
operators/solutions/ex4_6_precedence.c:168: style: The comparison 'mask == 1' is always true.
operators/solutions/ex4_6_precedence.c:81: style: Variable 'array' can be declared as const array
operators/solutions/ex4_6_precedence_c99.c:212: style: Boolean result is used in bitwise operation. Clarify expression with parentheses.
operators/solutions/ex4_6_precedence_c99.c:48: style: Condition 'a>b' is always true
operators/solutions/ex4_6_precedence_c99.c:48: style: Condition 'b<c' is always true
operators/solutions/ex4_6_precedence_c99.c:49: style: Condition 'a>b+1' is always true
operators/solutions/ex4_6_precedence_c99.c:51: style: Condition 'result5' is always true
operators/solutions/ex4_6_precedence_c99.c:53: style: Condition 'result6' is always true
operators/solutions/ex4_6_precedence_c99.c:82: style: Condition 'score>=60' is always true
operators/solutions/ex4_6_precedence_c99.c:82: style: Condition 'score<=100' is always true
operators/solutions/ex4_6_precedence_c99.c:84: style: Condition 'is_passing' is always true
operators/solutions/ex4_6_precedence_c99.c:133: style: Condition 'p<q' is always true
operators/solutions/ex4_6_precedence_c99.c:133: style: Condition 'r>s' is always false
operators/solutions/ex4_6_precedence_c99.c:133: style: Condition 'p==q' is always false
operators/solutions/ex4_6_precedence_c99.c:137: style: Condition 'p<q' is always true
operators/solutions/ex4_6_precedence_c99.c:138: style: Condition 'r>s' is always false
operators/solutions/ex4_6_precedence_c99.c:139: style: Condition 'p==q' is always false
operators/solutions/ex4_6_precedence_c99.c:141: style: Condition 'p<q' is always true
operators/solutions/ex4_6_precedence_c99.c:141: style: Condition 'r>s' is always false
operators/solutions/ex4_6_precedence_c99.c:142: style: Condition 'p==q' is always false
operators/solutions/ex4_6_precedence_c99.c:143: style: Condition 'expr2' is always false
operators/solutions/ex4_6_precedence_c99.c:147: style: Condition 'p+++++q*r-->s' is always true
operators/solutions/ex4_6_precedence_c99.c:147: style: Condition 'q!=r' is always true
operators/solutions/ex4_6_precedence_c99.c:148: style: Condition 'expr3' is always true
operators/solutions/ex4_6_precedence_c99.c:186: style: Condition 'x>0' is always true
operators/solutions/ex4_6_precedence_c99.c:186: style: Condition 'x>10' is always false
operators/solutions/ex4_6_precedence_c99.c:213: style: Condition '(flags&mask)==1' is always true
operators/solutions/ex4_6_precedence_c99.c:217: style: Condition 'wrong' is always true
operators/solutions/ex4_6_precedence_c99.c:219: style: Condition 'correct' is always true
operators/solutions/ex4_6_precedence_c99.c:251: style: Condition 'score>=90' is always false
operators/solutions/ex4_6_precedence_c99.c:252: style: Condition 'score>=80' is always true
operators/solutions/ex4_6_precedence_c99.c:253: style: Condition 'score>=90' is always false
operators/solutions/ex4_6_precedence_c99.c:253: style: Condition 'score>=80' is always true
operators/solutions/ex4_6_precedence_c99.c:212: style: The comparison 'mask == 1' is always true.
operators/solutions/ex4_6_precedence_c99.c:94: style: Variable 'array' can be declared as const array
operators/solutions/ex4_5_conditional.c:219: style: The function 'absolute' is never used.
operators/solutions/ex4_5_conditional.c:224: style: The function 'get_grade' is never used.
operators/examples/bitwise_demo_c99.c:20: style: The function 'print_bits16' should have static linkage since it is not used outside of its translation unit.
operators/solutions/ex4_4_bitwise_c99.c:51: style: The function 'print_bits_detailed' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### pointers

**検査ファイル数**: 14 個

**検出された問題**:
- Errors: 0
0
- Warnings: 1
- Style: 92
- Performance: 0
0
- Portability: 5
- Information: 5

**詳細**:
```
pointers/examples/pointer_arrays.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
pointers/examples/pointer_arrays.c:86: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
pointers/examples/pointer_arrays.c:105: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
pointers/examples/pointer_arrays.c:106: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
pointers/examples/pointer_arrays.c:72: style: Variable 'ptr' is assigned an expression that holds the same value.
pointers/examples/pointer_arrays.c:76: style: Variable 'ptr' is assigned an expression that holds the same value.
pointers/examples/pointer_arrays.c:9: style: Parameter 'arr' can be declared as const array
pointers/examples/pointer_arrays.c:19: style: Parameter 'ptr' can be declared as pointer to const
pointers/examples/pointer_arrays.c:29: style: Parameter 'ptr' can be declared as pointer to const
pointers/examples/pointer_arrays.c:49: style: Variable 'str_ptr' can be declared as pointer to const
pointers/examples/pointer_arrays.c:56: style: Variable 'matrix_ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
pointers/examples/pointer_arrays_c99.c:91: style: Variable 'ptr' is assigned an expression that holds the same value.
pointers/examples/pointer_arrays_c99.c:95: style: Variable 'ptr' is assigned an expression that holds the same value.
pointers/examples/pointer_arrays_c99.c:13: style: Parameter 'arr' can be declared as const array
pointers/examples/pointer_arrays_c99.c:22: style: Parameter 'ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:31: style: Parameter 'ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:61: style: Variable 'vla_ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:131: style: Variable 'str_ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:152: style: Variable 'matrix_ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:165: style: Variable 'ptr_array' can be declared as const array
pointers/examples/pointer_arrays_c99.c:175: style: Variable 'compound_ptr' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:183: style: Variable 'designated' can be declared as const array
pointers/examples/pointer_basic.c:71: style: Condition 'null_ptr==NULL' is always true
pointers/examples/pointer_basic.c:17: style: Variable 'char_ptr' can be declared as pointer to const
pointers/examples/pointer_basic.c:18: style: Variable 'float_ptr' can be declared as pointer to const
pointers/examples/pointer_basic.c:19: style: Variable 'double_ptr' can be declared as pointer to const
pointers/examples/pointer_basic.c:20: style: Variable 'null_ptr' can be declared as pointer to const
pointers/examples/pointer_basic.c:21: style: Variable 'generic_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:65: style: Condition 'null_ptr==NULL' is always true
pointers/examples/pointer_basic_c99.c:66: style: Condition 'is_null' is always true
pointers/examples/pointer_basic_c99.c:46: style: Variable 'char_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:47: style: Variable 'float_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:48: style: Variable 'double_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:61: style: Variable 'null_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:72: style: Variable 'generic_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:88: style: Variable 'byte_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:89: style: Variable 'short_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:90: style: Variable 'int_ptr32' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:99: style: Variable 'num_ptr' can be declared as pointer to const
pointers/examples/pointer_basic_c99.c:111: style: Variable 'src_ptr' can be declared as pointer to const
pointers/examples/pointer_functions.c:205: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
pointers/examples/pointer_functions.c:213: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
pointers/examples/pointer_functions.c:161: style: The scope of the variable 'array_sum' can be reduced.
pointers/examples/pointer_functions.c:33: style: Parameter 'arr' can be declared as pointer to const
pointers/examples/pointer_functions.c:97: style: Parameter 'str' can be declared as pointer to const
pointers/examples/pointer_functions.c:110: style: Parameter 'src' can be declared as pointer to const
pointers/examples/pointer_functions.c:131: style: Parameter 'label' can be declared as pointer to const
pointers/examples/pointer_functions.c:131: style: Parameter 'arr' can be declared as pointer to const
pointers/examples/pointer_functions.c:160: style: Variable 'labels' can be declared as const array
pointers/examples/pointer_functions_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
pointers/examples/pointer_functions_c99.c:33: style: Parameter 'arr' can be declared as pointer to const
pointers/examples/pointer_functions_c99.c:126: style: Parameter 'arr' can be declared as pointer to const
pointers/examples/pointer_functions_c99.c:153: style: Parameter 'src' can be declared as pointer to const
pointers/examples/pointer_functions_c99.c:162: style: Parameter 'arr' can be declared as pointer to const
pointers/examples/pointer_functions_c99.c:238: style: Variable 'original' can be declared as const array
pointers/examples/pointer_functions_c99.c:262: style: Variable 'sizes' can be declared as const array
pointers/examples/pointer_functions_c99.c:263: style: Variable 'labels' can be declared as const array
pointers/examples/pointer_functions_c99.c:130: warning: Uninitialized variable: arr
pointers/solutions/ex10_1_pointer_swap_c99.c:42: style: Parameter 'ptr1' can be declared as pointer to const
pointers/solutions/ex10_1_pointer_swap_c99.c:42: style: Parameter 'ptr2' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:114: style: The scope of the variable 'temp' can be reduced.
pointers/solutions/ex10_2_array_reverse.c:11: style: Parameter 'arr' can be declared as const array
pointers/solutions/ex10_2_array_reverse.c:11: style: Parameter 'label' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:23: style: Parameter 'ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:23: style: Parameter 'label' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:38: style: Variable 'last_ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:51: style: Variable 'reverse_ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:89: style: Variable 'ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse.c:184: style: Variable 'partial_end' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse_c99.c:14: style: Parameter 'arr' can be declared as const array
pointers/solutions/ex10_2_array_reverse_c99.c:24: style: Parameter 'ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse_c99.c:36: style: Variable 'last_ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse_c99.c:49: style: Variable 'reverse_ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse_c99.c:88: style: Variable 'ptr' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse_c99.c:152: style: Parameter 'src' can be declared as pointer to const
pointers/solutions/ex10_2_array_reverse_c99.c:221: style: Variable 'partial_end' can be declared as pointer to const
pointers/solutions/ex10_3_string_manipulation.c:34: style: The scope of the variable 'temp' can be reduced.
pointers/solutions/ex10_4_array_functions.c:70: style: Parameter 'arr' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions.c:88: style: Variable 'max_ptr' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions.c:88: style: Variable 'min_ptr' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions.c:150: style: Variable 'max' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions.c:157: style: Variable 'min' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
pointers/solutions/ex10_4_array_functions_c99.c:58: style: Parameter 'arr' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:92: style: Variable 'max_ptr' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:102: style: Variable 'min_ptr' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:153: style: Variable 'max' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:154: style: Variable 'min' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:183: style: Variable 'max' can be declared as pointer to const
pointers/solutions/ex10_4_array_functions_c99.c:187: style: Variable 'min' can be declared as pointer to const
pointers/examples/pointer_arrays_c99.c:42: style: The function 'demonstrate_vla' should have static linkage since it is not used outside of its translation unit.
pointers/examples/pointer_functions_c99.c:136: style: The function 'process_vla' should have static linkage since it is not used outside of its translation unit.
pointers/examples/pointer_functions_c99.c:153: style: The function 'copy_array_restrict' should have static linkage since it is not used outside of its translation unit.
pointers/examples/pointer_functions_c99.c:162: style: The function 'is_array_sorted' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_1_pointer_swap_c99.c:48: style: The function 'swap_with_restrict' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_1_pointer_swap_c99.c:62: style: The function 'swap_generic' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_2_array_reverse_c99.c:133: style: The function 'demonstrate_vla_reverse' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_2_array_reverse_c99.c:152: style: The function 'reverse_copy_restrict' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_3_string_manipulation_c99.c:59: style: The function 'show_string_details' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_3_string_manipulation_c99.c:69: style: The function 'test_string_mutability' should have static linkage since it is not used outside of its translation unit.
pointers/solutions/ex10_4_array_functions_c99.c:148: style: The function 'test_with_compound_literal' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### strings

**検査ファイル数**: 12 個

**検出された問題**:
- Errors: 1
- Warnings: 0
0
- Style: 108
- Performance: 0
0
- Portability: 8
- Information: 10

**詳細**:
```
strings/examples/advanced_string_processing.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/examples/advanced_string_processing.c:61: style: Parameter 'arr' can be declared as const array
strings/examples/advanced_string_processing.c:61: style: Parameter 'target' can be declared as pointer to const
strings/examples/advanced_string_processing.c:77: style: Variable 'input' can be declared as const array
strings/examples/advanced_string_processing.c:80: style: Variable 'token' can be declared as pointer to const
strings/examples/advanced_string_processing.c:102: style: Variable 'original' can be declared as const array
strings/examples/advanced_string_processing.c:175: style: Variable 'employee_names' can be declared as const array
strings/examples/advanced_string_processing.c:178: style: Variable 'departments' can be declared as const array
strings/examples/advanced_string_processing.c:181: style: Variable 'positions' can be declared as const array
strings/examples/advanced_string_processing.c:184: style: Variable 'salaries' can be declared as const array
strings/examples/advanced_string_processing.c:199: style: Variable 'unique_depts' can be declared as const array
strings/examples/advanced_string_processing.c:200: style: Unused variable: dept_count
strings/examples/advanced_string_processing_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/examples/advanced_string_processing_c99.c:39: style: Parameter 'data' can be declared as const array
strings/examples/advanced_string_processing_c99.c:89: style: Variable 'token' can be declared as pointer to const
strings/examples/string_array_operations.c:105: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
strings/examples/string_array_operations.c:63: style: Variable 'categories' can be declared as const array
strings/examples/string_array_operations_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/examples/string_array_operations_c99.c:17: style: Parameter 'arr' can be declared as const array
strings/examples/string_array_operations_c99.c:167: style: Variable 'efficient_strings' can be declared as const array
strings/examples/string_array_operations_c99.c:215: style: Variable 'sample' can be declared as const array
strings/examples/string_basic.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/examples/string_basic.c:90: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/examples/string_basic.c:96: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/examples/string_basic.c:103: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/examples/string_basic.c:13: style: Variable 'str1' can be declared as const array
strings/examples/string_basic.c:15: style: Variable 'str3' can be declared as const array
strings/examples/string_basic.c:16: style: Variable 'str4' can be declared as pointer to const
strings/examples/string_basic.c:32: style: Variable 'source' can be declared as const array
strings/examples/string_basic.c:46: style: Variable 'str_b' can be declared as const array
strings/examples/string_basic.c:47: style: Variable 'str_c' can be declared as const array
strings/examples/string_basic.c:58: style: Variable 'apple' can be declared as const array
strings/examples/string_basic.c:59: style: Variable 'banana' can be declared as const array
strings/examples/string_basic.c:60: style: Variable 'apple2' can be declared as const array
strings/examples/string_basic.c:85: style: Variable 'found' can be declared as pointer to const
strings/examples/string_basic_c99.c:193: style: Same expression on both sides of '-'.
strings/examples/string_basic_c99.c:23: style: The scope of the variable 'buffer' can be reduced.
strings/examples/string_basic_c99.c:28: style: Variable 'sample' can be declared as pointer to const
strings/examples/string_basic_c99.c:48: style: Variable 'str1' can be declared as const array
strings/examples/string_basic_c99.c:49: style: Variable 'str2' can be declared as const array
strings/examples/string_basic_c99.c:50: style: Variable 'str3' can be declared as const array
strings/examples/string_basic_c99.c:51: style: Variable 'str4' can be declared as pointer to const
strings/examples/string_basic_c99.c:100: style: Variable 'source' can be declared as const array
strings/examples/string_basic_c99.c:118: style: Variable 'str_b' can be declared as const array
strings/examples/string_basic_c99.c:119: style: Variable 'str_c' can be declared as const array
strings/examples/string_basic_c99.c:133: style: Variable 'apple' can be declared as const array
strings/examples/string_basic_c99.c:134: style: Variable 'banana' can be declared as const array
strings/examples/string_basic_c99.c:135: style: Variable 'apple2' can be declared as const array
strings/examples/string_basic_c99.c:158: style: Variable 'found' can be declared as pointer to const
strings/examples/string_basic_c99.c:192: style: Variable 'vowels' can be declared as const array
strings/examples/string_basic_c99.c:222: style: Variable 'sample' can be declared as const array
strings/solutions/ex8_1_string_operations.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/solutions/ex8_1_string_operations.c:203: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/solutions/ex8_1_string_operations.c:215: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/solutions/ex8_1_string_operations.c:245: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/solutions/ex8_1_string_operations.c:248: portability: %ld in format string (no. 1) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'.
strings/solutions/ex8_1_string_operations.c:172: style: Variable 'result' can be declared as pointer to const
strings/solutions/ex8_1_string_operations.c:241: style: Variable 'first_a' can be declared as pointer to const
strings/solutions/ex8_1_string_operations.c:242: style: Variable 'last_a' can be declared as pointer to const
strings/solutions/ex8_1_string_operations_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/solutions/ex8_2_string_arrays.c:15: style: Parameter 'students' can be declared as const array
strings/solutions/ex8_2_string_arrays.c:114: style: Parameter 'students' can be declared as const array
strings/solutions/ex8_2_string_arrays_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/solutions/ex8_2_string_arrays_c99.c:43: style: Parameter 'students' can be declared as const array
strings/solutions/ex8_2_string_arrays_c99.c:271: style: Parameter 'students' can be declared as const array
strings/solutions/ex8_3_string_search.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/solutions/ex8_3_string_search.c:38: error: Array 'target[6]' accessed at index 98, which is out of bounds.
strings/solutions/ex8_3_string_search.c:37: style: Array index 'j' is used before limits check.
strings/solutions/ex8_3_string_search.c:16: style: Parameter 'strings' can be declared as const array
strings/solutions/ex8_3_string_search.c:30: style: Parameter 'strings' can be declared as const array
strings/solutions/ex8_3_string_search.c:75: style: Parameter 'strings' can be declared as const array
strings/solutions/ex8_3_string_search.c:93: style: Parameter 'strings' can be declared as const array
strings/solutions/ex8_3_string_search.c:175: style: Parameter 'strings' can be declared as const array
strings/solutions/ex8_3_string_search.c:175: style: Parameter 'results' can be declared as const array
strings/solutions/ex8_3_string_search_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
strings/solutions/ex8_3_string_search_c99.c:69: style: The function 'my_strstr_optimized' is never used.
strings/solutions/ex8_3_string_search_c99.c:99: style: The function 'find_pattern_advanced' is never used.
strings/examples/advanced_string_processing.c:16: style: The function 'to_uppercase' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing.c:30: style: The function 'to_lowercase' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing.c:44: style: The function 'bubble_sort_strings' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing.c:61: style: The function 'search_string' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing_c99.c:39: style: The function 'process_vla_strings' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing_c99.c:60: style: The function 'optimized_string_sort' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing_c99.c:74: style: The function 'advanced_tokenize' should have static linkage since it is not used outside of its translation unit.
strings/examples/advanced_string_processing_c99.c:103: style: The function 'advanced_string_search' should have static linkage since it is not used outside of its translation unit.
strings/examples/string_array_operations_c99.c:26: style: The function 'safe_string_copy' should have static linkage since it is not used outside of its translation unit.
strings/examples/string_array_operations_c99.c:35: style: The function 'demonstrate_vla_string_array' should have static linkage since it is not used outside of its translation unit.
strings/examples/string_basic_c99.c:21: style: The function 'demonstrate_vla_strings' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations.c:12: style: The function 'my_strlen' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations.c:28: style: The function 'my_strcpy' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations.c:78: style: The function 'my_strcat' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations.c:169: style: The function 'test_string_functions' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:26: style: The function 'my_strcpy_optimized' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:39: style: The function 'my_strcmp_bool' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:79: style: The function 'my_strcat_safe' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:110: style: The function 'my_strchr_advanced' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:143: style: The function 'my_strrchr_advanced' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:179: style: The function 'count_char_detailed' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:207: style: The function 'test_vla_string_functions' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_1_string_operations_c99.c:228: style: The function 'comprehensive_string_test' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:15: style: The function 'display_students' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:32: style: The function 'add_student' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:62: style: The function 'remove_student_by_name' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:90: style: The function 'remove_student_by_index' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:114: style: The function 'search_student' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:128: style: The function 'sort_students' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays.c:148: style: The function 'search_partial' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:43: style: The function 'display_students_vla' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:59: style: The function 'display_detailed_students' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:84: style: The function 'add_student_safe' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:125: style: The function 'remove_student_advanced' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:188: style: The function 'search_students_advanced' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:250: style: The function 'sort_students_advanced' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_2_string_arrays_c99.c:271: style: The function 'calculate_statistics' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:16: style: The function 'exact_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:30: style: The function 'case_insensitive_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:58: style: The function 'partial_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:75: style: The function 'prefix_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:93: style: The function 'suffix_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:115: style: The function 'wildcard_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:158: style: The function 'wildcard_search_array' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search.c:194: style: The function 'display_statistics' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search_c99.c:150: style: The function 'find_all_matches' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search_c99.c:221: style: The function 'wildcard_match_vla' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search_c99.c:271: style: The function 'multi_pattern_search' should have static linkage since it is not used outside of its translation unit.
strings/solutions/ex8_3_string_search_c99.c:305: style: The function 'free_search_results' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

### structures

**検査ファイル数**: 12 個

**検出された問題**:
- Errors: 0
0
- Warnings: 0
0
- Style: 63
- Performance: 0
0
- Portability: 3
- Information: 8

**詳細**:
```
structures/examples/struct_arrays.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/examples/struct_arrays.c:157: style: Parameter 'lib' can be declared as pointer to const
structures/examples/struct_arrays.c:277: style: Variable 'book_ptr' can be declared as pointer to const
structures/examples/struct_arrays.c:278: style: Variable 'book_end' can be declared as pointer to const
structures/examples/struct_arrays_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/examples/struct_arrays_c99.c:52: style: struct member 'DynamicLibrary::book_count' is never used.
structures/examples/struct_arrays_c99.c:53: style: struct member 'DynamicLibrary::student_count' is never used.
structures/examples/struct_arrays_c99.c:54: style: struct member 'DynamicLibrary::stats' is never used.
structures/examples/struct_arrays_c99.c:55: style: struct member 'DynamicLibrary::books' is never used.
structures/examples/struct_basics.c:156: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
structures/examples/struct_basics.c:157: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
structures/examples/struct_basics.c:158: portability: %lu in format string (no. 1) requires 'unsigned long' but the argument type is 'size_t {aka unsigned long}'.
structures/examples/struct_basics.c:43: style: Parameter 'p' can be declared as pointer to const
structures/examples/struct_basics_c99.c:175: style: Condition 'use_default' is always false
structures/examples/struct_pointers.c:42: style: Parameter 'emp' can be declared as pointer to const
structures/examples/struct_pointers.c:94: style: Parameter 'proj' can be declared as pointer to const
structures/examples/struct_pointers.c:197: style: Variable 'highest_paid' can be declared as pointer to const
structures/examples/struct_pointers_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/examples/struct_pointers_c99.c:232: style: Variable 'stats' can be declared as pointer to const
structures/examples/struct_pointers_c99.c:292: style: Variable 'highest_paid_manager' can be declared as pointer to const
structures/solutions/ex11_1_student.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/solutions/ex11_1_student.c:156: style: Variable 'top_student' can be declared as pointer to const
structures/solutions/ex11_2_coordinate.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/solutions/ex11_3_product.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/solutions/ex11_3_product.c:198: style: Unused variable: choice
structures/solutions/ex11_3_product_c99.c:0: information: Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches.
structures/examples/struct_pointers_c99.c:47: style: The function 'is_date_later' is never used.
structures/solutions/ex11_2_coordinate_c99.c:95: style: The function 'from_polar' is never used.
structures/solutions/ex11_3_product_c99.c:150: style: The function 'search_product' is never used.
structures/solutions/ex11_3_product_c99.c:168: style: The function 'search_by_code_predicate' is never used.
structures/examples/struct_arrays.c:47: style: The function 'calculate_average' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays.c:73: style: The function 'print_student' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays.c:87: style: The function 'sort_students_by_average' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays.c:104: style: The function 'add_book' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays.c:124: style: The function 'find_book_by_isbn' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays.c:136: style: The function 'borrow_book' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays.c:157: style: The function 'show_borrowed_books' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays_c99.c:79: style: The function 'update_student' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays_c99.c:87: style: The function 'print_student_info' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays_c99.c:102: style: The function 'analyze_scores' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_arrays_c99.c:154: style: The function 'compare_books_by_popularity' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_basics.c:37: style: The function 'print_point_by_value' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_basics.c:43: style: The function 'print_point_by_pointer' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_basics_c99.c:70: style: The function 'update_product_status' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers.c:59: style: The function 'update_salary' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers.c:75: style: The function 'find_highest_paid' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers.c:94: style: The function 'print_project' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers.c:120: style: The function 'calculate_department_stats' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers.c:148: style: The function 'swap_employees' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers_c99.c:55: style: The function 'copy_employee' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers_c99.c:101: style: The function 'calculate_all_stats' should have static linkage since it is not used outside of its translation unit.
structures/examples/struct_pointers_c99.c:153: style: The function 'calculate_project_days' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_1_student.c:59: style: The function 'update_score' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_1_student.c:89: style: The function 'display_detailed_info' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_1_student_c99.c:83: style: The function 'update_score_with_history' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_1_student_c99.c:122: style: The function 'analyze_student_group' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate.c:57: style: The function 'calculate_midpoint' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate.c:74: style: The function 'distance_from_origin' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate.c:81: style: The function 'get_quadrant' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate_c99.c:62: style: The function 'add_points' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate_c99.c:72: style: The function 'scale_point' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate_c99.c:82: style: The function 'to_polar' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate_c99.c:120: style: The function 'process_points_vla' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_2_coordinate_c99.c:138: style: The function 'check_line_intersection' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product.c:23: style: The function 'add_product' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product.c:70: style: The function 'display_all_products' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product.c:140: style: The function 'display_low_stock' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product.c:167: style: The function 'search_by_price_range' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product_c99.c:75: style: The function 'add_product_extended' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product_c99.c:114: style: The function 'display_all_products_detailed' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product_c99.c:186: style: The function 'update_stock_with_history' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product_c99.c:225: style: The function 'summarize_by_category' should have static linkage since it is not used outside of its translation unit.
structures/solutions/ex11_3_product_c99.c:258: style: The function 'analyze_prices' should have static linkage since it is not used outside of its translation unit.
nofile:0: information: Active checkers: 109/856 (use --checkers-report=<filename> to see details)
```

---

## 総合評価

**総検査ファイル数**: 234 個

**検出された問題の総数**:
- Errors: 5
- Warnings: 47
- Style: 851
- Performance: 0
0
- Portability: 111
- Information: 89

### 評価結果

⚠️ **要確認**: いくつかの問題が検出されました。

検出された問題の多くは、教育目的のシンプルなコード例であることに起因する可能性があります。

### 備考

- 本教材は教育目的のため、エラーハンドリングを簡略化している箇所があります
- C90準拠のコードも含まれるため、一部の最新のコーディング規約とは異なる場合があります
- システムヘッダーに関する警告は除外しています（--suppress=missingIncludeSystem）
