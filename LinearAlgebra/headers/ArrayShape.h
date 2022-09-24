
#include "../fwd.h"
#include <vector>

namespace MathLib {
	namespace LinearAlgebra {
		

		class ArrayShape : public Stringable {
		private:
			unsigned int N = 1;
			std::vector<unsigned int> shape = std::vector<unsigned int>();
			std::vector<unsigned int> sliceSizes = std::vector<unsigned int>();
			unsigned int rank = 1;

			void _Reshape(std::initializer_list<const unsigned int> list) {
				shape.clear();
				sliceSizes.clear();

				int i = 0;
				for (auto itr = list.begin(); itr != list.end(); ++itr) {
					shape.push_back(*itr);
					sliceSizes.push_back(0);
					++i;
				}

				unsigned int prod = 1;
				this->rank = (unsigned int) shape.size();

				for (int i = rank - 1; i >= 0; --i) {
					sliceSizes[i] = prod;
					prod *= shape[i];
				}

				if (prod != N) {
					throw Exceptions::InvalidTensorReshape();
				}
			}

		public:
			ArrayShape(const unsigned int n) : N(n) {
				shape.push_back(n);
				sliceSizes.push_back(1);
			}

			ArrayShape(std::initializer_list<const unsigned int> list) {
				int i = 0;
				for (auto itr = list.begin(); itr != list.end(); ++itr) {
					N *= *itr;
					++i;
				}

				_Reshape(list);
			}

			const unsigned int Rank() const {
				return rank;
			}

			const unsigned int Count() const {
				return N;
			}

			const unsigned int GetTargetIndex(const ArrayShape& target) const {
				if (target.rank != this->rank)
					throw Exceptions::InvalidTensorAccess();

				unsigned int index = 0;

				for (unsigned int i = 0; i < rank; ++i) {
					if (target.shape[i] >= shape[i])
						throw Exceptions::InvalidTensorAccess();

					index += sliceSizes[i] * target.shape[i];
				}
				return index;
			}

			std::string ToString() override {
				std::string result = "";
				;
				for (unsigned int i = 0; i < rank - 1; ++i) {
					result += std::to_string(shape[i]);
				}
				if (rank - 1 >= 0)
					result += std::to_string(shape[rank - 1]) + " ";

				result += "\n";
				return result;
			}
		};
	}
}