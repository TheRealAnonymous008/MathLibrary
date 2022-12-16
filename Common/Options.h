#pragma once

#ifdef _OPENMP_LLVM_RUNTIME 
#define OPENMP_PARALLELIZE _Pragma("omp parallel for")
#define OPENMP_CRITICAL_SECTION _Pragma("omp critical")
#elif _OPENMP > 200805
#define OPENMP_PARALLELIZE _Pragma("omp parallel for")
#define OPENMP_CRITICAL_SECTION _Pragma("omp critical")
#else
#define OPENMP_PARALLELIZE 
#define OPENMP_CRITICAL_SECTION 
#endif