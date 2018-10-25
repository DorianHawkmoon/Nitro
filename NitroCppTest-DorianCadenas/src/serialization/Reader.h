#pragma once
#ifndef READER_H
#define READER_H

#include "precompiled.h"
#include "json/json.h"

#include "shapes/ShapeFactory.h"
#include "shapes/Shape.h"

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
		std::vector<std::shared_ptr<Shape>> ParseFileShapes(const std::string& filename, const ShapeFactory& factory, int maxNumberShapes);


	private:
	};

}

#endif // !READER_H
