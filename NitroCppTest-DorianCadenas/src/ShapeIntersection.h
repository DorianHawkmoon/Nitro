#pragma once
#ifndef SHAPE_INTERSECTION_H
#define SHAPE_INTERSECTION_H

#include "precompiled.h"
#include "shapes/ShapeFactory.h"
#include "serialization/Reader.h"
#include "utils/Config.h"

namespace ShapeOverlay {
	class ShapeIntersection {
	public:
		/// <summary>
		/// Create object and register all the shapes
		/// </summary>
		ShapeIntersection(Config config);
		~ShapeIntersection() = default;

		NO_COPY_CLASS(ShapeIntersection);

	private:
		Config config;
		ShapeFactory shapeFactory;

	public:
		/// <summary>
		/// Read the file and compute the intersections
		/// </summary>
		/// <param name="filenameShapes"></param>
		void ReportIntersections(const std::string& filenameShapes);

		/// <summary>
		/// Get a reference of the shape factory
		/// </summary>
		/// <returns></returns>
		const ShapeOverlay::ShapeFactory& ShapeFactory() const { return shapeFactory; }
		ShapeOverlay::ShapeFactory& ShapeFactory() { return shapeFactory; }

	};

}

#endif // !SHAPE_INTERSECTION_H
