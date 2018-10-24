#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

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
}

#endif // !UTILS_H