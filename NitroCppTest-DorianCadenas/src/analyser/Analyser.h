#pragma once
#ifndef ANALYSER_H
#define ANALYSER_H

#include "precompiled.h"
#include "analyser/Intersection.h"
#include <queue>

namespace IntersectionChecker {
	//forward declaration
	class Shape;

	/// <summary>
	/// Base class for analyse the list of shapes and get the intersections
	/// It implements a basic analyse. Can be inherited for better algorithms
	/// </summary>
	class Analyser {

	private:
		struct AnalysisIntersectionState {
			AnalysisIntersectionState() = default;
			
			AnalysisIntersectionState(const AnalysisIntersectionState &other) = default; //copy constructor
			AnalysisIntersectionState(AnalysisIntersectionState &&) = default; //move constructor

			AnalysisIntersectionState & operator=(const AnalysisIntersectionState &other) = default; //copy assignment
			AnalysisIntersectionState & operator=(AnalysisIntersectionState &&) = default; //move assignment

			~AnalysisIntersectionState() = default;

			AnalysisIntersectionState(int outer, int inner, const Intersection* inter)
				: outerIndex(outer), innerIndex(inner), intersection(inter) {}

			int outerIndex;
			int innerIndex;
			const Intersection* intersection;
		};



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
		/// <summary>
		/// I put all intersections here
		/// </summary>
		std::queue<AnalysisIntersectionState> stateLastIntersections;

	private:
	/// <summary>
	/// Iterate the vector of shapes given the indexs where to start
	/// It adds the intersections found and store in the queue the state of the iteration
	/// to later look for more shapes intersecting the found intersection
	/// </summary>
	/// <param name="outerIndex"></param>
	/// <param name="innerIndex"></param>
	/// <param name="intersection">null if comparing between shapes of the given vector, or an intersection to compare with</param>
	/// <param name="shapes">vector of shapes to iterate</param>
		void CheckIntersections(unsigned int outerIt, unsigned int innerIt, const Intersection* intersection, const std::vector<std::shared_ptr<Shape>>& shapes);
	};

}

#endif // !ANALYSER_H
