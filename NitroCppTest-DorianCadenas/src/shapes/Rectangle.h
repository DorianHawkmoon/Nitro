#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "precompiled.h"
#include "Shape.h"
#include "json/json.h"

namespace ShapeOverlay {
	/// <summary>
	/// A rectangle shape class
	/// </summary>
	class Rectangle : public Shape {

	public:
		Rectangle();
		//TODO test
		Rectangle(Maths::Vector2<int> topLeft, Maths::Vector2<int> size);
		Rectangle(int top, int left, int width, int height);
		~Rectangle() = default;

	private:
		Maths::Vector2<int> topLeft;
		Maths::Vector2<int> size;

	public:
		Maths::Vector2<int> GetTopLeft() const { return topLeft; }
		Maths::Vector2<int> GetBottomLeft() const;
		Maths::Vector2<int> GetTopRight() const;
		Maths::Vector2<int> GetBottomRight() const;
		Maths::Vector2<int> GetSize() const { return size; }

		//TODO test
		virtual std::string ToString() override;
		virtual std::string NameShape() override;

		virtual std::unique_ptr<Shape> GetClone() const override;

		virtual void Deserialize(const Json::Value& serializer) override;
		virtual void Serialize(const Json::Value& serializer) override;


	public:
		std::unique_ptr<Shape> Intersection(const Shape& other) const override;
		std::unique_ptr<Shape> SpecificIntersectionShape(const Shape& self) const override;

		std::unique_ptr<Shape> Intersection(const Rectangle& other) const override;
	};

}

#endif // !RECTANGLE_H
