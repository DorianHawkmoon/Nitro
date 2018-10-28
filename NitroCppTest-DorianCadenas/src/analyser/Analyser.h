#pragma once
#ifndef ANALYSER_H
#define ANALYSER_H

#include "precompiled.h"
#include "analyser/Intersection.h"

namespace ShapeOverlay {
	//forward declaration
	class Shape;

	/// <summary>
	/// Base class for analyse the list of shapes and get the intersections
	/// It implements a basic analyse. Can be inherited for better algorithms
	/// </summary>
	class Analyser {
	public:
		Analyser() : result() {};
		~Analyser() = default;

	public:
		/// <summary>
		/// Analyze the shapes and their intersections
		/// store them on a vector
		/// return true if any intersection found
		/// </summary>
		/// <param name="shapes"></param>
		/// <returns>true if any intersection found</returns>
		virtual bool Analyze(const std::vector<std::shared_ptr<Shape>>& shapes);
		/// <summary>
		/// Iterate all the intersections and store in a string their output
		/// </summary>
		/// <returns></returns>
		const std::string GetResults() const;

	private:
		/// <summary>
		/// Instead of passing it by parameter, or as a return value, as usual in a recursive function
		/// I use a member class
		/// </summary>
		std::vector<std::unique_ptr<Intersection>> result;

	private:
		void recursive(unsigned int outerIt, unsigned int innerIt, const Intersection* intersection, const std::vector<std::shared_ptr<Shape>>& shapes);
	};

}

#endif // !ANALYSER_H
