#pragma once
#ifndef ANALYSER_H
#define ANALYSER_H

#include "precompiled.h"

namespace ShapeOverlay {
	//forward declaration
	class Shape;

	/// <summary>
	/// Base class for analyze the list of shapes and get the intersections
	/// Each specialize class has a different algorithm for it
	/// </summary>
	class Analyser {
	public:
		Analyser() = default;
		~Analyser() = default;

	public:
		virtual void Analyze(const std::vector<std::shared_ptr<Shape>>& shapes) = 0;
	};

}

#endif // !ANALYSER_H
