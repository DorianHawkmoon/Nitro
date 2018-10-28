#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "precompiled.h"
#include "shapes/Shape.h"

namespace ShapeOverlay {
	/// <summary>
	/// Class for details about the intersection between shapes
	/// It store a shape result of the intersection and the identity of the shapes involved
	/// 
	/// Should take some care about difference shapes in the same intersection (for example, to change
	/// the toString method) but due to especifications, we ignore it at the moment.
	/// </summary>
	class Intersection {
	public:
		Intersection(int id1, int id2, std::unique_ptr<Shape> shapeIntersection = nullptr);
		~Intersection() = default;
		NO_COPY_CLASS(Intersection);

	private:
		Intersection(const std::vector<int> idShapesIntersection, std::unique_ptr<Shape> intersection);

	private:
		std::unique_ptr<Shape> intersection;
		/// <summary>
		/// ID of all the shapes who are in this intersection
		/// </summary>
		std::vector<int> idShapesIntersection;

	public:
		/// <summary>
		/// Return a copy of the shape who made the intersection
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<Shape> GetIntersectionShape() const;

		/// <summary>
		/// Return a instance
		/// </summary>
		/// <param name="IdShape"></param>
		/// <param name="newIntersection"></param>
		/// <returns></returns>
		std::unique_ptr <Intersection> AddShapeIntersection(int IdShape, std::unique_ptr<Shape> newIntersection) const;

		/// <summary>
		/// Representation of the intersection
		/// </summary>
		/// <returns></returns>
		std::string ToString() const;
	};

}

#endif // !INTERSECTION_H