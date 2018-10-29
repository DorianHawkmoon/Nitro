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

		template <typename T>
		struct Vector2 {
			static_assert(std::is_arithmetic<T>::value, "Vector2 => Type must be numeric.");

			Vector2() = default;
			Vector2(T x, T y) :x(x), y(y) {}

			T x = 0;
			T y = 0;
		};

		/// <summary>
		/// Invalidate char vectors
		/// </summary>
		template<>
		struct Vector2<char> {
			Vector2() { throw std::exception("Vector2 => Invalid data type."); };
			Vector2(char x, char y) { throw std::exception(); }
		};

		/// <summary>
		/// Invalidate strings
		/// </summary>
		template<>
		struct Vector2<std::string> {
			Vector2() { throw std::exception(); };
			Vector2(std::string x, std::string y) { throw std::exception("Vector2 => Invalid data type."); }
		};

		/// <summary>
		/// Invalidate bools
		/// </summary>
		template<>
		struct Vector2<bool> {
			Vector2() { throw std::exception(); };
			Vector2(bool x, bool y) { throw std::exception("Vector2 => Invalid data type."); }
		};
	}
}

#endif // !UTILS_H