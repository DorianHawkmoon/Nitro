#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "precompiled.h"

namespace ShapeOverlay {
	/// <summary>
	/// Clase for possible configuration of the program
	/// such the limit of shapes to read from the json
	/// if it is a limit for all type of shapes or per shape...
	/// 
	/// Could be extended to read external configuration (data-driven design)
	/// 
	/// For now we have one static configuration
	/// </summary>
	class Config {
		static const int MAX_NUMBER_ELEMENTS = 10;

	public:
		int GetMaxNumberElements() const { return MAX_NUMBER_ELEMENTS; }
	};
}

#endif // !CONFIG_H
