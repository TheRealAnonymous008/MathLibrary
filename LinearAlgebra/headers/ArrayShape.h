#include "../fwd.h"
#include <vector>

#ifndef OUT_OF_SHAPE
#define OUT_OF_SHAPE -1
#endif 

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<const unsigned N, const unsigned ...Ns>
			struct SizeClass {
				constexpr unsigned static Size() {
					return N * SizeClass<Ns...>::Size();
				}
			};

			template<const unsigned N>
			struct SizeClass<N> {
				constexpr unsigned static Size() {
					return N;
				}
			};

			class SliceInformation {
			private:
				unsigned lower = 0;
				unsigned upper = 0;
				unsigned size;
				unsigned sliceSize = 1;

			public:
				SliceInformation(unsigned N) {
					SetLower(0);
					SetUpper(N);
					size = N;
				}

				void SetLower(unsigned l) {
					lower = l;
				}

				void SetUpper(unsigned u) {
					upper = u;
				}

				int GetIndex(unsigned u) const{
					return lower + u;
				}

				const unsigned Size() const {
					return size;
				}

				const unsigned SliceSize() const {
					return sliceSize;
				}

				void SetSliceSize(unsigned s) {
					sliceSize = s;
				}

				bool IsInRange(const unsigned idx) const {
					return idx >= lower && idx <= upper;
				}
			};
		}

		using namespace detail;
		class ArrayShape{
		private:
			std::vector<SliceInformation> dims = std::vector<SliceInformation>();
			unsigned rank = 1;
			unsigned size = 0;


		public:
			ArrayShape(std::initializer_list<const unsigned> ns) {
				rank = (unsigned) ns.size();

				int currsize = 1;

				for (unsigned i = 0; i < rank; ++i) {
					auto* itr = ns.begin() + i;
					dims.push_back(SliceInformation(*itr));
					currsize *= *itr;
				}

				size = currsize;

				for (unsigned i = 0; i < rank; ++i) {
					currsize /= dims[i].Size();
					dims[i].SetSliceSize(currsize);
				}
			}

			~ArrayShape() {

			}

			const unsigned Size() const {
				return size;
			}			
			
			const unsigned Rank() const {
				return rank;
			}

			const int Index(const std::initializer_list<const unsigned>& list) const{
				if (list.size() != rank) {
					throw Exceptions::InvalidTensorAccess();
				}

				unsigned idx = 0;
				auto itr = list.begin();

				for (unsigned i = 0; i < rank - 1; ++i) {
					itr = list.begin() + i;
					unsigned shindex = dims[i].GetIndex(*itr);

					if (*itr < 0 || shindex >= dims[i].Size()) {
						throw Exceptions::InvalidTensorAccess();
					}
					if (!dims[i].IsInRange(shindex)) {
						return OUT_OF_SHAPE;
					}
					idx += shindex * dims[i].SliceSize();
				}

				itr++;
				int shindex = dims[rank - 1].GetIndex(*itr);
				if (!dims[rank - 1].IsInRange(shindex))
					return -1;

				idx += shindex;
				return idx;
			}

			void Slice(const std::initializer_list<const unsigned>& lower, const std::initializer_list<const unsigned>& upper) {
				
				if (lower.size() != rank || upper.size() != rank)
					throw Exceptions::InvalidTensorSlice();

				for (unsigned i = 0; i < rank; ++i) {
					auto litr = lower.begin() + i;
					auto uitr = upper.begin() + i;

					if (*litr >= *uitr || *litr < 0 || *uitr >= dims[i].Size()) {
						throw Exceptions::InvalidTensorSlice();
					}

					dims[i].SetLower(*litr);
					dims[i].SetUpper(*uitr);
				}
			}
		};
	}
}