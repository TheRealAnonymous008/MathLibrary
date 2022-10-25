//#pragma once
//#include "fwd.h"
//
//namespace MathLib {
//	namespace LinearAlgebra {
//
//		namespace detail {
//			template<typename T, typename Expr, const unsigned _Rows, const unsigned _Columns>
//			class MatrixSlice : public MatrixExpression<T, MatrixSlice<T, Expr, _Rows, _Columns>> {
//			private:
//				const Expr& expr;
//
//			public:
//				MatrixTranspose(const Expr& expr) : expr(expr) {
//
//				}
//
//				T At(const unsigned& r, const unsigned& c) const {
//					if (isEvaluated) {
//						return body[r][c];
//					}
//					return  expr.At(c, r);
//				}
//
//				constexpr unsigned Rows() const {
//					return  _Rows;
//				}
//
//				constexpr unsigned Columns() const {
//					return _Columns
//				}
//
//				const MatrixTranspose& Evaluate() {
//
//					body = std::vector<std::vector<T>>(Rows(), std::vector<T>(Columns()));
//
//					for (unsigned i = 0; i < Rows(); ++i) {
//						for (unsigned j = 0; j < Columns(); ++j) {
//							body[i][j] = expr.At(j, i);
//						}
//					}
//
//					return *this;
//				}
//			};
//		}
//
//	}
//}