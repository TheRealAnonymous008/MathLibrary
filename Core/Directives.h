#pragma once

namespace MathLib {

	#ifndef PARALLEL_THREADS
	#define PARALLEL_THREADS 128
	#endif

	#ifndef NO_PARALLELIZATION
	#define NO_PARALLELIZATION 0
	#endif

	#ifdef MATHLIBRARY_EXPORTS
	#define MATHLIBRARY_API __declspec(dllexport)
	#else
	#define MATHLIBRARY_API __declspec(dllimport)
	#endif
}