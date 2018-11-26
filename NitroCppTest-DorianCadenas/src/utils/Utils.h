#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <stdexcept>

// Delete copy constructor and assignment operator
// Note: Scott Meyers mentions in his Effective Modern C++ book, that deleted functions should generally
//       be public as it results in better error messages due to the compilers behavior to check accessibility
//       before deleted status
#define NO_COPY_CLASS(C) \
	C( const C& ) = delete; \
	C& operator=( const C& ) = delete


namespace ShapeOverlay {
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