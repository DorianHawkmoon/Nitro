#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "serialization/ISerializable.h"
#include "json/json.h"

namespace ShapeOverlay {
	//fast-forward declaration of specific shapes
	class Rectangle;

	/// <summary>
	/// Base class for a shape (rectangle, circle...)
	/// </summary>
	class Shape : public ISerializable {
	public:
		Shape() = default;
		virtual ~Shape() = default;

		//TODO make tests
		/// <summary>
		/// String representation of the shape
		/// </summary>
		virtual std::string ToString() = 0;
		virtual std::string PositionString() = 0;
		virtual std::string NameShape() = 0;

		virtual std::unique_ptr<Shape> GetClone() const = 0;

		virtual void Serialize(const Json::Value& serializer) = 0;
		virtual void Deserialize(const Json::Value& serializer) = 0;

	public:
		//TODO test
		/// <summary>
		/// Generic method to call when trying
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		virtual std::unique_ptr<Shape> Intersection(const Shape& other) const = 0;

		/// <summary>
		/// Because this method is pure virtual, it's going to be called from the
		/// specific class of the instance, useful for calling an specific Intersection
		/// method (see implementation of method for details)
		/// </summary>
		/// <param name="self"></param>
		/// <returns></returns>
		virtual std::unique_ptr<Shape> SpecificIntersectionShape(const Shape& self) const = 0;

		/// <summary>
		/// Specific intersection test against a rectangle
		/// </summary>
		virtual std::unique_ptr<Shape> Intersection(const Rectangle& other) const = 0;
	};

}

#endif // !SHAPE_H