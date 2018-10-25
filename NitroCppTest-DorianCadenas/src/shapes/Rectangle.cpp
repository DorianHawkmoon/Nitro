#include "precompiled.h"
#include "Rectangle.h"

namespace ShapeOverlay {
	Rectangle::Rectangle()
		: topLeft(), size()
	{}

	Vector2<int> Rectangle::GetBottomLeft() const {
		Vector2<int> bottomLeft = topLeft;
		bottomLeft.y += size.y;
		return bottomLeft;
	}

	Vector2<int> Rectangle::GetTopRight() const {
		Vector2<int> topRigth = topLeft;
		topRigth.x += size.x;
		return topRigth;
	}

	Vector2<int> Rectangle::GetBottomRight() const {
		Vector2<int> bottomRight = topLeft;
		bottomRight.x += size.x;
		bottomRight.y += size.y;
		return bottomRight;
	}

	void Rectangle::Deserialize(const Json::Value & serializer) {
		//check members exists
		bool memberExists = serializer.isMember("x");
		memberExists &= serializer.isMember("y");
		memberExists &= serializer.isMember("w");
		memberExists &= serializer.isMember("h");

		if (!memberExists) {
			throw std::invalid_argument("Rectangle::Deserialize Lack of arguments");
		}

		topLeft.x = serializer["x"].asInt();
		topLeft.y = serializer["y"].asInt();

		size.x = serializer["w"].asInt();
		size.y = serializer["h"].asInt();

		//perfom checks
		//size higher than zero
		if (size.x <= 0 || size.y <= 0) {
			throw std::invalid_argument("Rectangle::Deserialize Size should be positive");
		}

		//top left zero or greater
		if (topLeft.x < 0 || topLeft.y < 0) {
			throw std::invalid_argument("Rectangle::Deserialize top left point should be positive");
		}

	}
	void Rectangle::Serialize(const Json::Value & serializer) {}
}