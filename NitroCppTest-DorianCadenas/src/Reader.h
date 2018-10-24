#pragma once
#ifndef READER_H
#define READER_H

#include "precompiled.h"
#include "json/json.h"

namespace ShapeOverlay {
	class Reader {
	public:
		Reader() = default;
		~Reader() = default;

	public:

		/// <summary>
		/// Open the file, check the syntax and parse the shapes
		/// </summary>
		/// <param name="filename"></param>
		/// <returns></returns>
		bool ParseFileShapes(const std::string& filename);


	private:
	};

}

#endif // !READER_H
