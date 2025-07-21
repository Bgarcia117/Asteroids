#include "physics.h"
#include <iostream>
#include <limits>

bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon) {
	size_t numOfVerticies = polygon.getVertexCount();
	size_t intersectionCount = 0;

	// Used for how long the ray starting at the bullet should be, wasn't used yet
	sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

	// Iterates over the vertex array
	for (size_t j = 0; j < numOfVerticies; j++) {
		// Treats the edge as a line
		// Turns the verticies into world coordinates
		sf::Vector2f p1 = polygon[j].position;

		// %numOfVerticies accounts for the edge case of the last one polygon[11] and connects
		// it to the first vertex
		sf::Vector2f p2 = polygon[(j + 1) % numOfVerticies].position;

		// Checks if the bullet would intersect if on the same level vertically
		if ((p1.y < point.y && p2.y >= point.y) ||
			(p2.y < point.y && p1.y >= point.y)) {

			// "Interpolation" used to check where bullet would hit along asteroid edge
			// Its a proportion, t=0 means its at p1, 1 = p2, and 0.5 is halfway
			float t = (point.y - p1.y) / (p2.y - p1.y);

			// Adds the t to find the edge x-axis would intersect with the bullet
			// p2.x - p1.x gives you the distance between them
			// Multiplying accounts for sloped edges
			float intersectX = p1.x + t * (p2.x - p1.x);

			// Checks if the asteroid intersects to the right and how many times
			if (intersectX < point.x) {
				intersectionCount++;
			}
		}
	}

	// Checks if the num  of intersections is even or odd
	// Imagine a line drawn over the shape, how many times does it overlap?
	return intersectionCount % 2 == 1;
}

// Test Driver Function
// Uses the Separating Aaxis Theorem (SAT) algorithm
// Only works on convex polygons, has issues with concave if they fit together like puzzle peices
bool physics::intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2) {

	// Get vertex counts of both polygons (Linestrip repeats first vertex to close shape
	size_t n1 = poly1.getVertexCount() - 1;
	size_t n2 = poly2.getVertexCount() - 1;

	// Test all edge normals from polygon 1 as potential separting axes
	for (size_t i = 0; i < n1; i++) {
		sf::Vector2f edge = poly1[i].position - poly1[(i + 1) % n1].position;
		sf::Vector2f normal(-edge.y, edge.x);

		// Normalize the vector
		float length = sqrt(normal.x * normal.x + normal.y * normal.y);
		normal /= length;

		float min1 = std::numeric_limits<float>::max();
		float max1 = std::numeric_limits<float>::min();
		float min2 = std::numeric_limits<float>::max();
		float max2 = std::numeric_limits<float>::min();

		for (size_t j = 0; j < n1; j++) {
			float projection =
				poly1[j].position.x * normal.x + poly1[j].position.y * normal.y;
			min1 = std::min(min1, projection);
			max1 = std::max(max1, projection);
		}

		for (size_t k = 0; k < n2; k++) {
			float projection =
				poly2[k].position.x * normal.x + poly2[k].position.y * normal.y;
			min2 = std::min(min2, projection);
			max2 = std::max(max2, projection);
		}

		if (max1 < min2 || max2 < min1) {
			return false;
		}
	}

	return true;
}

sf::VertexArray physics::getTransformed(const sf::VertexArray& polygon,
	                                     const sf::Transform& transform) {
	sf::VertexArray transformed = polygon;

	for (size_t i = 0; i < transformed.getVertexCount(); i++) {
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}