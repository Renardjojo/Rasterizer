#include "vertex.hpp"

using namespace math;

Vertex::Vertex (float x, float y, float z)
	: 	position_(x, y, z)
{}

Vertex::Vertex (const Vec3& other)
	: 	position_(other)
{}
