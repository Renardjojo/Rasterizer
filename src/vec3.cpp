#include "vec3.hpp"
#include "vec2.hpp"
#include "vec4.hpp"

using namespace std;
using namespace math;


Vec3::Vec3(const Vec2& other, float z)
	: 	x_(other.x_),
		y_(other.y_),
		z_(z)
{}

Vec3::Vec3(const Vec4& other)
	: 	x_(other.x_),
		y_(other.y_),
		z_(other.z_)
{}

const Vec3 Vec3::zero 	{0.f, 0.f, 0.f};