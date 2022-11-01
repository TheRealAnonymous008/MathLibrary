#pragma once

#ifdef _OPENMP_LLVM_RUNTIME 
#define OPENMP_PARALLELIZE _Pragma("omp parallel for")
#elif _OPENMP > 200805
#define OPENMP_PARALLELIZE _Pragma("omp parallel for")
#else
#define OPENMP_PARALLELIZE 
#endif