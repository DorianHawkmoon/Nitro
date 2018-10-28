#include "precompiled.h"
#include "Intersection.h"

namespace ShapeOverlay {
	Intersection::Intersection(int id1, int id2, std::unique_ptr<Shape> shapeIntersection) 
		: idShapesIntersection{id1,id2}, intersection(std::move(shapeIntersection))
	{	}

	Intersection::Intersection(const std::vector<int> idShapesIntersection, std::unique_ptr<Shape> intersection)
	: idShapesIntersection(idShapesIntersection), intersection(std::move(intersection))
	{
		
	}



	/// <summary>
	/// Return a copy of the shape who made the intersection
	/// </summary>
	/// <returns></returns>

	std::unique_ptr<Shape> Intersection::GetIntersectionShape() const {
		if (intersection == nullptr) return nullptr;
		return intersection->GetClone();
	}

	std::unique_ptr<Intersection> Intersection::AddShapeIntersection(int IdShape, std::unique_ptr<Shape> newIntersection) const{
		std::vector<int> ids = idShapesIntersection; //get a copy
		ids.push_back(IdShape);
		//return a new intersection
		return std::unique_ptr<Intersection>(new Intersection(ids, std::move(newIntersection)));
	}

	std::string Intersection::ToString() const {
		std::stringstream result;

		//check if we have intersections
		if (intersection == nullptr || idShapesIntersection.size() <= 1) {
			result << "No intersection";

		} else {
			result << "Between " << intersection->NameShape() << " ";

			//write all involved shapes id
			int size = idShapesIntersection.size()-1;
			for (int i = 0; i <= size; ++i) {
				result << idShapesIntersection[i];

				if (i == size - 1) {
					result << " and ";
				} else if (i == size) {
					result << " ";
				} else {
					result << ", ";
				}
			}

			//write the shape result of the intersection
			result << intersection->PositionString(); //"at some point and size"
		}
		return result.str();
	}
}