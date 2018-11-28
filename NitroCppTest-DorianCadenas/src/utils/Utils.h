#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <stdexcept>


namespace IntersectionChecker {
	namespace Utils {

		template <typename T>
		std::string NumberToString(T const& number) {
			std::stringstream ss;
			ss << number;
			return ss.str();
		}
	}

	namespace Maths {

		/// <summary>
		/// Only arithmetic
		/// (SFINAE approach)
		/// </summary>
		template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value 
														&& !std::is_same<bool, T>::value
														&& !std::is_same<char, T>::value>>
		struct Vector2 {
			Vector2() = default;
			Vector2(T x, T y) :x(x), y(y) {}

			T x = 0;
			T y = 0;
		};
	}
}

#endif // !UTILS_H