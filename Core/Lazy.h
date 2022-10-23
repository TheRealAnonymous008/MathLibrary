#pragma once
#include <vector>

namespace MathLib {
	

	class LazyManager;

	template<typename Result>
	class Lazy;

	template<typename Result>
	class Lazy {
	private:
		
	public:
		Lazy(){
			LazyManager::Cleanup();
		}

	};

	class LazyManager {
	private:
		static std::vector<void*> ptrs;

	public:

		static void Register(void* expression) {

		}

		static void Cleanup() {

		}
	};

}