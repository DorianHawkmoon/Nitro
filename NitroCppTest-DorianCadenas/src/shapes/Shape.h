#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "serialization/ISerializable.h"
#include "json/json.h"

namespace ShapeOverlay {
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
		/// <returns></returns>
		virtual std::string ToString() = 0;

		virtual void Serialize(const Json::Value& serializer) = 0;
		virtual void Deserialize(const Json::Value& serializer) = 0;
	};

}

#endif // !SHAPE_H