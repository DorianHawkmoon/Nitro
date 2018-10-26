#pragma once
#ifndef BASIC_ANALYSER_H
#define BASIC_ANALYSER_H

#include "Analyser.h"

namespace ShapeOverlay {

	class BasicAnalyser : public Analyser {
	public:
		BasicAnalyser() = default;
		~BasicAnalyser() = default;

		//need to put id to those shapes (quick struct idHandler?)
		//sort them? use a quadtree map?
		//make the comparisons using delegated functions (templates per shapes? template for automatically find the right method to call?)
		//the comparison order and check with algorithm
	};
}

#endif // !BASIC_ANALYSER_H
