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
		topLeft.x = serializer["x"].asInt();
		topLeft.y = serializer["y"].asInt();

		size.x = serializer["w"].asInt();
		size.y = serializer["h"].asInt();
	}
	void Rectangle::Serialize(const Json::Value & serializer) {}
}