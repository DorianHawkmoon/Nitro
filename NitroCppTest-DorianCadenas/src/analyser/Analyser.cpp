#include "precompiled.h"
#include "Analyser.h"
#include "shapes/Shape.h"
#include <utility> // std::swap

namespace ShapeOverlay {
	bool Analyser::Analyze(const std::vector<std::shared_ptr<Shape>>& shapes) {
		result.clear();
		
		std::queue<StateIntersection> empty;
		std::swap(stateLastIntersections, empty);

		if (shapes.size() > 1) {
			for (unsigned int i = 0; i <= shapes.size() - 1; ++i) {
				recursive(i, i+1, nullptr, shapes);
			}
			//now we iterate all the intersections achieved and see if they have more intersections
			while (!stateLastIntersections.empty()) {
				//get the next state
				StateIntersection state = stateLastIntersections.front();
				//see intersections
				recursive(state.outerIt, state.innerIt, state.intersection, shapes);
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
			toString << "No intersections";
		}
		return toString.str();
	}

	//intersection is a pointer because can be null
	void Analyser::recursive(unsigned int outerIt, unsigned int innerIt, const Intersection* intersection, const std::vector<std::shared_ptr<Shape>>& shapes) {
		if (innerIt >= shapes.size()) return;

		//if its a normal iteration (looking with the shapes from the list)
		//or we are checking with a generated intersection
		std::shared_ptr<Shape> outerShape = (intersection==nullptr) ? 
			shapes[outerIt] : std::move(intersection->GetIntersectionShape());

		for (innerIt; innerIt <= shapes.size()-1; ++innerIt) {
			//check if there is an intersection
			std::unique_ptr<Shape> checkedIntersection = outerShape->Intersection(*(shapes[innerIt]));

			if (checkedIntersection != nullptr) {
				if (intersection == nullptr) {
					//new intersection, create one and store
					result.push_back(std::unique_ptr<Intersection>(new Intersection(outerIt+1, innerIt+1, std::move(checkedIntersection))));

				} else {
					//an intersection with existence intersection, get a clone and add the shape colliding
					result.push_back(intersection->AddShapeIntersection(innerIt+1, std::move(checkedIntersection)));
				}
				//for both cases, we store the state of the recursion to the end of the iteration
				//in case of true iteration, we should be calling again the method now
				//recursive(outerIt, innerIt+1, result[result.size()-1].get(), shapes);
				//but the order of the desired result is diferent, so we need to store it and call the method at the end
				stateLastIntersections.push(StateIntersection(outerIt, innerIt + 1, result[result.size() - 1].get()));
			}
		}
	}
}