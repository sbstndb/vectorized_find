# Vectorized Find with SIMD and Benchmarking

This project demonstrates the use of SIMD intrinsics (AVX2) to optimize the process of finding the index of an integer in an array. It also includes a Google Benchmark setup to compare the performance of a vectorized implementation against a naïve loop-based implementation.

---

## Features

- **Vectorized Search**:
  - Uses AVX2 intrinsics to process multiple elements in parallel.
  - Significantly faster for large arrays compared to a naïve implementation.

- **Benchmarking**:
  - Google Benchmark is used to measure and compare the performance of both implementations.

---

## Requirements

### Hardware
- A processor with **AVX2 support**. 

### Software
- C++17 or later.
- CMake 3.28 or later.
- GCC/Clang with AVX2 support.

---

## Compilatiob

```
cmake -B build -S .         # Compile with CMake
./build/benchmark_find      # Run the benchmark
```

# Results : 

Here are the results on my AMD Ryzen R3900X :

```
--------------------------------------------------------------------------------
Benchmark                      Time             CPU   Iterations UserCounters...
--------------------------------------------------------------------------------
BM_NaiveFind/2             0.919 ns        0.916 ns    305405212 items_per_second=2.18382G/s
BM_NaiveFind/4              1.46 ns         1.45 ns    192222961 items_per_second=2.75688G/s
BM_NaiveFind/8              2.86 ns         2.85 ns     92180466 items_per_second=2.80537G/s
BM_NaiveFind/16             5.00 ns         4.98 ns     60587199 items_per_second=3.21083G/s
BM_NaiveFind/32             8.46 ns         8.43 ns     33286918 items_per_second=3.79546G/s
BM_NaiveFind/64             23.9 ns         23.8 ns     11660289 items_per_second=2.69135G/s
BM_NaiveFind/128            35.8 ns         35.7 ns      7073468 items_per_second=3.58382G/s
BM_NaiveFind/256            68.3 ns         68.1 ns      4231949 items_per_second=3.75962G/s
BM_NaiveFind/512             120 ns          120 ns      2264753 items_per_second=4.27311G/s
BM_NaiveFind/1024            236 ns          235 ns      1207154 items_per_second=4.36066G/s
BM_NaiveFind/2048            460 ns          459 ns       610044 items_per_second=4.46261G/s
BM_NaiveFind/4096            918 ns          915 ns       306829 items_per_second=4.47566G/s
BM_NoBreakFind/2            1.99 ns         1.98 ns    141670400 items_per_second=1.01047G/s
BM_NoBreakFind/4            1.79 ns         1.79 ns    156437123 items_per_second=2.23912G/s
BM_NoBreakFind/8            2.03 ns         2.02 ns    138141568 items_per_second=3.96384G/s
BM_NoBreakFind/16           2.25 ns         2.24 ns    118318471 items_per_second=7.13211G/s
BM_NoBreakFind/32           2.95 ns         2.94 ns     95116023 items_per_second=10.872G/s
BM_NoBreakFind/64           4.38 ns         4.36 ns     64200661 items_per_second=14.6738G/s
BM_NoBreakFind/128          8.50 ns         8.46 ns     31886901 items_per_second=15.1244G/s
BM_NoBreakFind/256          15.4 ns         15.3 ns     18091339 items_per_second=16.6785G/s
BM_NoBreakFind/512          28.7 ns         28.5 ns      9788088 items_per_second=17.9548G/s
BM_NoBreakFind/1024         58.1 ns         57.9 ns      4784762 items_per_second=17.6934G/s
BM_NoBreakFind/2048          116 ns          116 ns      2426830 items_per_second=17.718G/s
BM_NoBreakFind/4096          231 ns          230 ns      1211683 items_per_second=17.8073G/s
BM_IntrinsicFind/2         0.893 ns        0.890 ns    313818521 items_per_second=2.24746G/s
BM_IntrinsicFind/4         0.892 ns        0.890 ns    314603935 items_per_second=4.49641G/s
BM_IntrinsicFind/8         0.893 ns        0.890 ns    314942066 items_per_second=8.98992G/s
BM_IntrinsicFind/16         1.15 ns         1.14 ns    234266328 items_per_second=13.9829G/s
BM_IntrinsicFind/32         1.91 ns         1.90 ns    147737571 items_per_second=16.8246G/s
BM_IntrinsicFind/64         3.37 ns         3.35 ns     83471337 items_per_second=19.0783G/s
BM_IntrinsicFind/128        6.28 ns         6.26 ns     41552347 items_per_second=20.4576G/s
BM_IntrinsicFind/256        12.0 ns         11.9 ns     23372660 items_per_second=21.4674G/s
BM_IntrinsicFind/512        23.5 ns         23.4 ns     11652073 items_per_second=21.8743G/s
BM_IntrinsicFind/1024       54.9 ns         54.8 ns      5131342 items_per_second=18.6945G/s
BM_IntrinsicFind/2048        102 ns          102 ns      2761901 items_per_second=20.1623G/s
BM_IntrinsicFind/4096        195 ns          194 ns      1452151 items_per_second=21.0601G/s
```

