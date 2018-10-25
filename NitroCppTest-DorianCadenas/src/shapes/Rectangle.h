#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "precompiled.h"
#include "Shape.h"
#include "json/json.h"

using namespace ShapeOverlay::Maths;

namespace ShapeOverlay {
	class Rectangle : public Shape {

	public:
		Rectangle();
		~Rectangle() = default;

	private:
		Vector2<int> topLeft;
		Vector2<int> size;

	public:
		Vector2<int> GetTopLeft() const { return topLeft; }
		Vector2<int> GetBottomLeft() const;
		Vector2<int> GetTopRight() const;
		Vector2<int> GetBottomRight() const;

		virtual void Deserialize(const Json::Value& serializer) override;
		virtual void Serialize(const Json::Value& serializer) override;
	};

}

#endif // !RECTANGLE_H
