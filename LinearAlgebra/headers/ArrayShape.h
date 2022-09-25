#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		class ArrayShapeBase {
		public:
			virtual unsigned GetRank() const = 0;
		};

		template<const unsigned N, const unsigned ...Ns>
		class ArrayShape<N, Ns...> : public ArrayShapeBase{

		public:
			constexpr static unsigned Size() {
				return N * ArrayShape<Ns...>::Size();
			}			
			
			constexpr static const unsigned Rank() {
				return 1 + ArrayShape<Ns...>::Rank();
			}

			static unsigned Index(const std::initializer_list<const unsigned>& list, const unsigned from = 0){
				auto itr = list.begin() + from;
				if (N < 0 || *itr >= N) {
					throw Exceptions::InvalidTensorAccess();
				}
				
				return *itr * Size() / N + ArrayShape<Ns...>::Index(list, from + 1);
			}

			unsigned GetRank() const override {
				return Rank();
			}
		};

		template<const unsigned N>
		class ArrayShape<N> : public ArrayShapeBase {
		public:
			constexpr static unsigned Size() noexcept{
				return N;
			}

			constexpr static const unsigned Rank() {
				return 1;
			}

			static unsigned Index(const std::initializer_list<const unsigned> list, const unsigned from = 0) {
				auto itr = list.begin() + from;
				if (N < 0 || *itr >= N) {
					throw Exceptions::InvalidTensorAccess();
				}
				return *itr;
			}

			unsigned GetRank() const override {
				return 1;
			}
		};
	}
}