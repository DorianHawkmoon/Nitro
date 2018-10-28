#pragma once
#ifndef SHAPE_INTERSECTION_H
#define SHAPE_INTERSECTION_H

#include "precompiled.h"
#include "shapes/ShapeFactory.h"
#include "serialization/Reader.h"
#include "utils/Config.h"

namespace ShapeOverlay {
	/// <summary>
	/// Main class of the program, it control the flow
	/// </summary>
	class ShapeIntersection {
	public:
		/// <summary>
		/// Create object and register all the shapes
		/// </summary>
		ShapeIntersection(std::shared_ptr<Config> config);
		~ShapeIntersection() = default;

		/// <summary>
		/// It doesn't mean to be copyable
		/// </summary>
		NO_COPY_CLASS(ShapeIntersection);

	private:
		ShapeFactory shapeFactory; //factory of all shapes
		std::shared_ptr<Config> config; //reference for configuration

	public:
		/// <summary>
		/// Read the file and compute the intersections
		/// </summary>
		/// <param name="filenameShapes">json filename/path</param>
		void ReportIntersections(const std::string& filenameShapes);

	};

}

#endif // !SHAPE_INTERSECTION_H
