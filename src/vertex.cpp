#include "vertex.hpp"

using namespace math;

Vertex::Vertex (float x, float y, float z, float nx, float ny, float nz, ubyte r, ubyte g, ubyte b, ubyte a)
	: 	position_	(x, y, z),
		normal_		(nx, ny, nz),
		color_		{r, g, b, a}
{}

Vertex::Vertex (const Vec3& position, const Vec3& normal, ColorRGBA color)
	: 	position_	(position),
		normal_		(normal),
		color_		{color.r, color.g, color.b, color.a}
{}
