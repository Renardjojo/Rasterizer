#include "vertex.hpp"

using namespace math;

Vertex::Vertex (float x, float y, float z, float nx, float ny, float nz)
	: 	position_	(x, y, z),
		normal_		(nx, ny, nz)
{}

Vertex::Vertex (const Vec3& position, const Vec3& normal)
	: 	position_	(position),
		normal_		(normal)
{}
