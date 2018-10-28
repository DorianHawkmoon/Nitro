#pragma once
#ifndef READER_H
#define READER_H

#include "precompiled.h"
#include "json/json.h"

#include "shapes/ShapeFactory.h"
#include "shapes/Shape.h"

namespace ShapeOverlay {
	/// <summary>
	/// Base class reader
	/// Given json filenames can read the shapes
	/// and store in a vector to be returned
	/// </summary>
	class Reader {
	public:
		Reader() = default;
		~Reader() = default; //no need for special code for std::vector

	private:
		std::vector<std::shared_ptr<Shape>> readShapes;

	public:

		/// <summary>
		/// Open the file, check the syntax and parse the shapes
		/// Consecutive calls of this method add to the list of read shapes
		/// Getting the list does not clean it
		/// </summary>
		/// <param name="filename">filename to read</param>
		void ParseFileShapes(const std::string& filename, const ShapeFactory& factory, int maxNumberShapes);

		/// <summary>
		/// Return a copy of the vector (will not copy the shapes itself)
		/// Will not clean the actual shape of the reader
		/// </summary>
		/// <returns>A copy of the vector with shapes read on it</returns>
		std::vector<std::shared_ptr<Shape>> GetReadShapes() const { return readShapes; }

		/// <summary>
		/// Clear the list of read shapes
		/// </summary>
		void ClearReadShapes() { readShapes.clear(); }
	};

}

#endif // !READER_H
