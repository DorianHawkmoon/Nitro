#pragma once
#ifndef INTERSECTION_CHECKER_ORCHESTRARION_H
#define INTERSECTION_CHECKER_ORCHESTRARION_H

#include "precompiled.h"
#include "shapes/ShapeFactory.h"
#include "utils/Config.h"

namespace IntersectionChecker {
	/// <summary>
	/// Main class of the program, it control the flow
	/// </summary>
	class IntersectionCheckerOrchestration {
	public:
		/// <summary>
		/// Create object and register all the shapes
		/// </summary>
		IntersectionCheckerOrchestration(std::shared_ptr<Config> config);
		~IntersectionCheckerOrchestration() = default;

		/// <summary>
		/// It doesn't mean to be copyable
		/// </summary>
		IntersectionCheckerOrchestration(const IntersectionCheckerOrchestration&) = delete;
		IntersectionCheckerOrchestration& operator=(const IntersectionCheckerOrchestration&) = delete;

	private:
		ShapeFactory shapeFactory; //factory of all shapes
		std::shared_ptr<Config> config; //reference for configuration

	public:
		/// <summary>
		/// Read the file and compute the intersections
		/// </summary>
		/// <param name="filenameShapes">json filename/path</param>
		void ReportIntersections(const std::string& filenameShapes);

	};

}

#endif // !INTERSECTION_CHECKER_ORCHESTRARION_H
