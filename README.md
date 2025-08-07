# Vectorized Find with SIMD and High-Performance Benchmarking

This project delves into various high-performance implementations for locating an element within an array, primarily focusing on optimizations utilizing Single Instruction, Multiple Data (SIMD) intrinsics (AVX2). It leverages Google Benchmark for a rigorous quantitative analysis of the computational efficiency across diverse algorithmic approaches.

---

## Features :

- **Optimized Search Implementations** :
  - **Naive** : Baseline linear search implementation for performance comparison.
  - **Stride** : Linear search employing a stride for memory access pattern analysis.
  - **No-Break** : Linear search without early exit, designed to analyze consistent loop overhead and branch prediction impact.
  - **Compare** : Implementations utilizing parallel comparison operations for index determination in integer and floating-point arrays.
  - **C++ STL (`std::find`)** : Standard Library algorithms for comparative performance analysis on contiguous C-style arrays and `std::vector`.
  - **Intrinsics (AVX2)** : Highly optimized, low-level implementations leveraging AVX2 instructions for explicit data parallelism in integer and floating-point element searches.
  - **Intrinsic2 (AVX2)** : An experimental intrinsic variant designed for enhanced throughput, showcasing advanced AVX2 utilization.

- **Integrated High-Resolution Benchmarking** :
  - Employs Google Benchmark for precise, micro-architectural performance measurements and comparative analysis of each implementation.
  - Benchmark results are automatically generated upon execution, providing empirical data on algorithmic throughput.

---

## Requirements : 

### Hardware
- A processor with **AVX2 instruction set support**.

### Software
- C++17 or later.
- CMake 3.28 or later.
- GCC/Clang with robust AVX2 instruction set support.

---

## Compilation and Execution :

To compile and execute the project for performance evaluation, follow these steps:

1.  **Create the build directory and configure CMake** :
    ```bash
    mkdir -p build && cd build
    cmake ..
    ```

2.  **Compile the project** :
    ```bash
    make
    ```

3.  **Execute Benchmarks** :
    ```bash
    ./vectorized_find
    ```
    Benchmark results, presented as computational throughput, will be streamed to the console. Raw performance data (text files) will be systematically archived in `docs/perf_results`.

---

## Benchmark Results and Performance Analysis :

Below is a summary of the measured computational throughput (in billions of elements processed per second - Giga-elements/s) for a vector size of 4096 elements, assessed using Google Benchmark. These metrics are indicative of operations per cycle (OPS) and overall data processing rate, crucial in HPC contexts.

| Implementation         | Throughput (G-elements/s) | Notes                                           |
|------------------------|---------------------------|-------------------------------------------------|
| `FIND_NaiveFind`         | ~4.6                      | Baseline sequential search.                       |
| `FIND_NaiveStridedFind`  | ~4.6                      | Explores memory access patterns; similar to naive. |
| `FIND_NoBreakFind`       | ~16.5                     | Demonstrates branch prediction resilience.      |
| `FIND_CompareFind`       | ~32.2                     | Efficient for integer-based comparisons.        |
| `FIND_CompareFloatFind`  | ~23.5                     | Optimized for floating-point comparisons.       |
| `FIND_CppFind`           | ~7.7                      | Standard C++ `std::find` on raw arrays.         |
| `FIND_CppVectorFind`     | ~8.1                      | Standard C++ `std::find` on `std::vector`.      |
| `FIND_IntrinsicFind`     | ~24.9                     | AVX2-optimized integer search.                  |
| `FIND_IntrinsicFloatFind`| ~25.3                     | AVX2-optimized floating-point search.           |
| `FIND_Intrinsic2Find`    | **~49.7**                 | **Peak Performance**: Highlights advanced AVX2 potential. |

**Key Performance Insight** : The intrinsic-based implementations, especially `FIND_Intrinsic2Find`, consistently demonstrate superior computational throughput compared to both naive and standard library approaches. This underscores the significant performance gains achievable through direct SIMD instruction leverage in data-intensive HPC workloads.

**Note on Worst-Case Benchmarking** : These benchmarks are designed to evaluate the **worst-case scenario** where the target element is located at the very end of the vector. Consequently, the reported performance metrics represent a lower bound for most real-world applications. Implementations without an early-exit condition (`No-Break`) inherently iterate through the entire dataset, thus their worst-case performance closely approximates their average performance.

---

## Deep Dive: Peak Performance Implementation Analysis

### FIND_Intrinsic2Find - The Fastest Implementation (~49.7 G-elements/s)

The `FIND_Intrinsic2Find` function represents the pinnacle of performance in our benchmark suite, achieving nearly **50 billion elements processed per second**. This implementation leverages advanced AVX2 intrinsics in a unique way compared to traditional search algorithms.

#### Algorithm Overview

Unlike conventional find operations that search for equality, `intrinsic2_find` employs a **counting-based approach** using vectorized comparison operations. The algorithm counts how many elements are less than the target value across the entire array. Because the array is sorted, this count is equivalent to the index of the first element that is greater than or equal to the target value. This makes the function behave like a `lower_bound` search, efficiently finding the position of an element (or its insertion point) in a sorted sequence.


#### Key AVX2 Instructions Used

| Instruction | Purpose | Impact |
|-------------|---------|---------|
| `_mm256_set1_epi32()` | Broadcast target value to all 8 lanes | Parallel comparison setup |
| `_mm256_loadu_si256()` | Load 8 integers from memory | Memory bandwidth utilization |
| `_mm256_cmpgt_epi32()` | Vectorized greater-than comparison | 8 comparisons in parallel |
| `_mm256_and_si256()` | Bitwise AND with mask | Conditional value selection |
| `_mm256_add_epi32()` | Vectorized addition | Parallel accumulation |
| `_mm256_hadd_epi32()` | Horizontal addition | Efficient reduction |

#### Register-Level Visualization

```
Initial State (searching for value=42 in array):
┌─────────────────────────────────────────────────────────────────────────────┐
│                       Input Array (32-bit integers)                        │
├─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┤
│   10    │   25    │   30    │   42    │   55    │   60    │   70    │   ...   │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

Step 1: Load 8 elements into AVX2 register (_mm256_loadu_si256)
┌─────────────────────────────────────────────────────────────────────────────┐
│                           __m256i chunk                                    │
├─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┤
│   10    │   25    │   30    │   42    │   55    │   60    │   70    │   80    │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
   L0        L1        L2        L3        L4        L5        L6        L7 

Step 2: Broadcast target value (_mm256_set1_epi32)
┌─────────────────────────────────────────────────────────────────────────────┐
│                          __m256i target                                    │
├─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┤
│   42    │   42    │   42    │   42    │   42    │   42    │   42    │   42    │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

Step 3: Vectorized comparison (_mm256_cmpgt_epi32: target > chunk)
┌─────────────────────────────────────────────────────────────────────────────┐
│                           __m256i mask                                     │
├─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┤
│0xFFFFFFFF│0xFFFFFFFF│0xFFFFFFFF│  0x0    │  0x0    │  0x0    │  0x0    │  0x0    │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
   TRUE      TRUE      TRUE     FALSE     FALSE     FALSE     FALSE     FALSE
  42>10     42>25     42>30    42>42     42>55     42>60     42>70     42>80

Step 4: Convert mask to count values (_mm256_and_si256)
┌─────────────────────────────────────────────────────────────────────────────┐
│                           __m256i ones                                     │
├─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┤
│    1    │    1    │    1    │    0    │    0    │    0    │    0    │    0    │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

Step 5: Accumulate counts across iterations (_mm256_add_epi32)
This is NOT a per-lane count! The algorithm processes 16 elements per iteration.
Each iteration adds 0 or 1 to the running count based on comparisons:

┌─────────────────────────────────────────────────────────────────────────────┐
│            `count_vec` Accumulation (Iteration on elems 0-15)               │
├─────────────────────────────────────────────────────────────────────────────┤
│ Initial `count_vec`:       [0, 0, 0, 0, 0, 0, 0, 0]                         │
│ + Mask (elems 0-7):        [1, 1, 1, 0, 0, 0, 0, 0]  (from Step 4)          │
│ + Mask (elems 8-15):       [0, 0, 0, 0, 0, 0, 0, 0]  (all >= 42)            │
│ --------------------------------------------------------------------------- │
│ Final `count_vec`:         [1, 1, 1, 0, 0, 0, 0, 0]                         │
│                                                                             │
│ (Further iterations add 0, as all remaining elements are >= 42)             │
└─────────────────────────────────────────────────────────────────────────────┘

Final Step: Horizontal reduction (_mm256_hadd_epi32)
┌─────────────────────────────────────────────────────────────────────────────┐
│                     Horizontal Sum Reduction                               │
├─────────────────────────────────────────────────────────────────────────────┤
│ The hadd operations sum all lane values together:                          │
│ Total = sum of all lanes = count of elements < target in entire array     │
│                                                                             │
│           │
└─────────────────────────────────────────────────────────────────────────────┘
```

#### Performance Advantages

1. **No Early Exit Overhead**: Unlike traditional find algorithms, this approach eliminates branch prediction penalties by processing the entire dataset consistently.

2. **Maximum SIMD Utilization**: Each AVX2 instruction operates on 8 elements simultaneously, achieving optimal instruction-level parallelism.

3. **Reduced Memory Access**: The algorithm processes two 256-bit chunks (16 elements) per iteration, maximizing cache line utilization.

4. **Efficient Reduction**: The horizontal addition instructions (`_mm256_hadd_epi32`) provide hardware-accelerated final summation.

#### Algorithmic Complexity

- **Time Complexity**: O(n/8) for AVX2 due to 8-way parallelism
- **Space Complexity**: O(1) - constant register usage
- **Memory Bandwidth**: ~64 bytes per iteration (2 × 32 bytes for dual chunk loading)

#### Why It's Fast

This implementation achieves superior benchmark performance through:
- **Elimination of conditional branches** within the main loop
- **Dual-chunk processing** (16 elements per iteration) 
- **Hardware-optimized reduction operations**
- **Consistent memory access patterns** that favor cache performance


---

## Conclusion : 
This project demonstrates that achieving optimal performance in high-performance computing requires a deep understanding of hardware architectures and low-level optimization techniques. While standard C++ constructs offer convenience, direct vectorization using SIMD intrinsics is paramount for maximizing computational throughput in data-parallel tasks. This optimization effort translates directly to reduced execution times and enhanced efficiency in HPC applications.

## Future Work / TODO :

- [ ] Conduct in-depth **Assembly Code Analysis** for critical sections to identify micro-architectural bottlenecks and further optimization opportunities.
- [ ] **Optimize Standard C++ Implementations** to approach intrinsic-level performance through compiler hints, algorithmic refinements, and data structure considerations.
- [ ] Explore the integration and benchmarking of **Advanced SIMD Libraries** such as Google's `Highway` or QuantStack's `xsimd` to abstract low-level intrinsics while retaining high performance.
- [ ] Implement and benchmark **Strided Data Access Patterns** to evaluate performance implications for non-contiguous memory layouts, a common challenge in HPC workflows.
- [ ] Investigate **Cache Locality and Memory Bandwidth Utilization** as primary performance factors, employing tools like `perf` for detailed profiling.
- [ ] Profile with hardware performance counters to analyze instruction retirement rates, cache miss ratios, and branch prediction efficiency.
- [ ] Implement and compare alternative vectorization strategies (e.g., AVX-512 if available, ARM NEON for cross-platform compatibility).
- [ ] Benchmark against GPU implementations using CUDA or OpenCL for massive parallelism scenarios.

