#pragma once
#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include "precompiled.h"
#include "json/forwards.h"

namespace IntersectionChecker {
	class ISerializable {
		virtual void Serialize(const Json::Value& serializer) = 0;
		virtual void Deserialize(const Json::Value& serializer) = 0;
	};
}

#endif // !I_SERIALIZABLE_H
