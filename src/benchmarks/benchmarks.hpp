#ifndef BENCHMARKS_HPP
#define BENCHMARKS_HPP

#include <benchmark/benchmark.h>

// Déclarations des fonctions de benchmark
void FIND_NaiveFind(benchmark::State& state);
void FIND_NaiveStridedFind(benchmark::State& state);
void FIND_NoBreakFind(benchmark::State& state);
void FIND_CompareFind(benchmark::State& state);
void FIND_CompareFloatFind(benchmark::State& state);
void FIND_CppFind(benchmark::State& state);
void FIND_CppVectorFind(benchmark::State& state);
void FIND_IntrinsicFind(benchmark::State& state);
void FIND_IntrinsicFloatFind(benchmark::State& state);
void FIND_Intrinsic2Find(benchmark::State& state);

#endif // BENCHMARKS_HPP
