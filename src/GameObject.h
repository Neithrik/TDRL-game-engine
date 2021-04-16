#pragma once

#include <vector>
#include <utility>

namespace tdrl {

	using Coordinate = std::pair<int, int>;
	using CoordinateList = std::vector<Coordinate>;

	class GameObject {
	public:
		enum class Color {
			DEFAULT = 0,
			RED, GREEN, BLUE,
		};

		GameObject(Color color, CoordinateList coordinates)
			: color_(color), coordinates_(coordinates) {}

		Color GetColor() { return color_; }

		CoordinateList GetCoordinates() const {
			return coordinates_;
		};

	protected:
		Color color_;
		CoordinateList coordinates_;
	};

	class Point : public GameObject {
	public:
		Point::Point(Color color, Coordinate coordinate)
			: GameObject(color, { coordinate }) {}

		void SetPoint(Coordinate coordinate) {
			coordinates_ = CoordinateList({ coordinate });
		};
	};

	class MultiPoints : public GameObject {
	public:
		MultiPoints::MultiPoints(Color color, CoordinateList coordinates)
			: GameObject(color, coordinates) {}

		void SetCoordinates(CoordinateList coordinates) {
			coordinates_ = coordinates;
		};
	};

}