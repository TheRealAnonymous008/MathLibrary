#pragma once

#define ENABLE_OPENMP

#ifdef ENABLE_OPENMP
#define OPENMP_PARALLELIZE _Pragma("omp parallel for")
#else
#define OPENMP_PARALLELIZE 
#endif