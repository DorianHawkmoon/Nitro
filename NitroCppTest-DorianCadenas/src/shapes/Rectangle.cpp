#include "precompiled.h"
#include "Rectangle.h"
#include <algorithm>
#include "utils/Utils.h"

namespace IntersectionChecker {
	Rectangle::Rectangle()
		: topLeft(), size()
	{}

	Rectangle::Rectangle(Maths::Vector2<int> topLeft, Maths::Vector2<int> size)
		: topLeft(topLeft),
		size(size)
	{
		//perfom checks
		//size higher than zero
		if (size.x <= 0 || size.y <= 0) {
			throw std::invalid_argument("Rectangle::Constructor => Size should be positive.");
		}

		//top left should be integer
		if (std::floor(topLeft.x) != topLeft.x || std::floor(topLeft.y) != topLeft.y) {
			throw std::invalid_argument("Rectangle::Constructor => top left point should be integers.");
		}
	}

	Rectangle::Rectangle(int top, int left, int width, int height)
		: Rectangle(Maths::Vector2<int>(top,left), Maths::Vector2<int>(width,height))
	{}

	Maths::Vector2<int> Rectangle::GetBottomLeft() const {
		Maths::Vector2<int> bottomLeft = topLeft;
		bottomLeft.y += size.y;
		return bottomLeft;
	}

	Maths::Vector2<int> Rectangle::GetTopRight() const {
		Maths::Vector2<int> topRigth = topLeft;
		topRigth.x += size.x;
		return topRigth;
	}

	Maths::Vector2<int> Rectangle::GetBottomRight() const {
		Maths::Vector2<int> bottomRight = topLeft;
		bottomRight.x += size.x;
		bottomRight.y += size.y;
		return bottomRight;
	}

	std::string Rectangle::PositionString() {
		std::stringstream result;
		result << "at (" << topLeft.x << "," << topLeft.y <<
			"), w=" << size.x << ", h=" << size.y;
		return result.str();
	}

	std::string Rectangle::ToString() {
		std::stringstream result;
		result << NameShape() << " " << PositionString();
		return result.str();
	}

	std::string Rectangle::NameShape() {
		return std::string("Rectangle");
	}

	std::unique_ptr<Shape> Rectangle::GetClone() const {
		return std::unique_ptr<Shape>(new Rectangle(topLeft, size));;
	}

	void Rectangle::Deserialize(const Json::Value & serializer) {
		//check members exists
		bool memberExists = serializer.isMember("x");
		memberExists &= serializer.isMember("y");
		memberExists &= serializer.isMember("w");
		memberExists &= serializer.isMember("h");

		if (!memberExists) {
			throw std::invalid_argument("Rectangle::Deserialize => Lack of arguments.");
		}

		bool isInteger = true;
		isInteger &= serializer["x"].isIntegral();
		isInteger &= serializer["y"].isIntegral();
		if (!isInteger) {
			throw std::invalid_argument("Rectangle::Deserialize => top left point should be integer.");
		}

		isInteger &= serializer["w"].isIntegral();
		isInteger &= serializer["h"].isIntegral();
		if (!isInteger) {
			throw std::invalid_argument("Rectangle::Deserialize => Size should be integers.");
		}


		topLeft.x = serializer["x"].asInt();
		topLeft.y = serializer["y"].asInt();

		size.x = serializer["w"].asInt();
		size.y = serializer["h"].asInt();

		//check size higher than or equal zero
		if (size.x <= 0 || size.y <= 0) {
			throw std::invalid_argument("Rectangle::Deserialize => Size should be positive.");
		}
	}

	void Rectangle::Serialize(const Json::Value & serializer) {}

	std::unique_ptr<Shape> Rectangle::Intersection(const Shape & other) const {
		//because in base class is virtual, this method is called
		//from the specific class of the instance
		//therefore, will call one of the specific Intersection
		//example, will call Intersection(rectangle) instead of intersection(shape)
		return other.SpecificIntersectionShape(*this);
	}

	std::unique_ptr<Shape> Rectangle::SpecificIntersectionShape(const Shape & self) const {
		//after callin specificIntersectionshape, this method
		//is the original calling with derived classes
		//example: for circle looking intersection in rectangle
		//shape->intersect(shape)
		//rectangle->specificIntersectionShape(shape)
		//circle->intersection(rectangle) => original call, can choose the specific intersect method
		return self.Intersection(*this);
	}

	std::unique_ptr<Shape> Rectangle::Intersection(const Rectangle & other) const {
		Maths::Vector2<int> otherTopLeft = other.GetTopLeft();
		Maths::Vector2<int> otherBottomRight = other.GetBottomRight();
		
		int left = std::max(topLeft.x, otherTopLeft.x);
		int top = std::max(topLeft.y, otherTopLeft.y);

		int right = std::min(GetBottomRight().x, otherBottomRight.x);
		int bottom = std::min(GetBottomRight().y, otherBottomRight.y);
		
		//is it an intersection?
		if (left < right && top < bottom) {
			Maths::Vector2<int> newTopLeft(left, top);
			Maths::Vector2<int> newSize(right - left, bottom - top);

			return std::unique_ptr<Rectangle>(new Rectangle(newTopLeft, newSize));
		} else {
			return nullptr;
		}
	}
}