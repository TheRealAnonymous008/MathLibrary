#pragma once

namespace MathLib {
	template<typename T>
	constexpr T Identity() {
		return T();
	}

	template<>
	constexpr int Identity<int>() {
		return 1;
	}

	template<>
	constexpr float Identity<float>() {
		return 1.0f;
	}

	template<>
	constexpr double Identity<double>() {
		return 1.0;
	}
}