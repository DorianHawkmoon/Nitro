#include "precompiled.h"
#include "Analyser.h"
#include "shapes/Shape.h"

namespace ShapeOverlay {
	bool Analyser::Analyze(const std::vector<std::shared_ptr<Shape>>& shapes) {
		result.clear();

		for (unsigned int i=0; i <= shapes.size()-1; ++i) {
			recursive(i, 1, nullptr, shapes);
		}

		return result.size() > 0;
	}

	const std::string Analyser::GetResults() const {
		std::stringstream toString;
		for (auto& intersection : result) {
			toString << intersection->ToString();
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
			std::unique_ptr<Shape> checkecIntersection = outerShape->Intersection(*(shapes[innerIt]));

			if (checkecIntersection != nullptr) {
				if (intersection == nullptr) {
					Intersection(outerIt, innerIt, std::move(checkecIntersection));
					//new intersection, create one and store
					result.push_back(std::unique_ptr<Intersection>(new Intersection(outerIt, innerIt, std::move(checkecIntersection))));

				} else {
					//an intersection with existence intersection, get a clone and add the shape colliding
					result.push_back(intersection->AddShapeIntersection(innerIt, std::move(checkecIntersection)));
				}
				//for both cases, get the intersection and start a recursive search for more intersections
				recursive(outerIt, innerIt+1, result[result.size()-1].get(), shapes);
			}
		}
	}
}