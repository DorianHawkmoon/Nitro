#include "precompiled.h"
#include "Analyser.h"
#include "shapes/Shape.h"
#include <utility> // std::swap

namespace IntersectionChecker {
	bool Analyser::Analyze(const std::vector<std::shared_ptr<Shape>>& shapes) {
		result.clear();
		
		std::queue<AnalysisIntersectionState> empty;
		std::swap(stateLastIntersections, empty);

		if (shapes.size() > 1) {
			for (unsigned int i = 0; i <= shapes.size() - 1; ++i) {
				CheckIntersections(i, i+1, nullptr, shapes);
			}
			//now we iterate all the intersections achieved and see if they have more intersections
			while (!stateLastIntersections.empty()) {
				//get the next state
				AnalysisIntersectionState state = stateLastIntersections.front();
				//see intersections
				CheckIntersections(state.outerIndex, state.innerIndex, state.intersection, shapes);
				//delete the procesed state
				stateLastIntersections.pop();
			}
		}
		return result.size() > 0;
	}

	const std::string Analyser::GetResults() const {
		std::stringstream toString;
		if (result.size() > 0) {
			for (auto& intersection : result) {
				toString << intersection->ToString() << ".\n";
			}
		} else {
			toString << "No intersections.\n";
		}
		return toString.str();
	}

	
	void Analyser::CheckIntersections(unsigned int outerIndex, unsigned int innerIndex, const Intersection* intersection, const std::vector<std::shared_ptr<Shape>>& shapes) {
		if (innerIndex >= shapes.size()) return;

		//if its a normal iteration (looking with the shapes from the list)
		//or we are checking with a generated intersection
		std::shared_ptr<Shape> outerShape = (intersection==nullptr) ? 
			shapes[outerIndex] : std::move(intersection->GetIntersectionShape());

		for (innerIndex; innerIndex <= shapes.size()-1; ++innerIndex) {
			//check if there is an intersection
			std::unique_ptr<Shape> checkedIntersection = outerShape->Intersection(*(shapes[innerIndex]));

			if (checkedIntersection != nullptr) {
				if (intersection == nullptr) {
					//new intersection, create one and store
					result.push_back(std::unique_ptr<Intersection>(new Intersection(outerIndex+1, innerIndex+1, std::move(checkedIntersection))));

				} else {
					//an intersection with existence intersection, get a clone and add the shape colliding
					result.push_back(intersection->AddShapeIntersection(innerIndex+1, std::move(checkedIntersection)));
				}
				//for both cases, we store the state of the recursion to the end of the iteration
				//in case of true iteration, we should be calling again the method now
				//recursive(outerIt, innerIt+1, result[result.size()-1].get(), shapes);
				//but the order of the desired result is diferent, so we need to store it and call the method at the end
				stateLastIntersections.push(AnalysisIntersectionState(outerIndex, innerIndex + 1, result[result.size() - 1].get()));
			}
		}
	}
}