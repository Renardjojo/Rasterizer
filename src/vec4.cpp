#include "vec4.hpp"
#include "vec3.hpp"
#include <stdexcept> // To use runtime_error 

using namespace std;
using namespace math;

Vec4::Vec4()
	: 	x_ (0.f),
		y_ (0.f),
		z_ (0.f),
		w_ (0.f)
{}

Vec4::Vec4(float x, float y, float z, float w)
	: 	x_ (x),
		y_ (y),
		z_ (z),
		w_ (w)
{}

Vec4::Vec4(float bothValue) 
	: 	x_(bothValue),
		y_(bothValue),
		z_(bothValue),
		w_(bothValue)
{}

Vec4::Vec4(const Vec3& other, float w)
	:	x_(other.x_),
		y_(other.y_),
		z_(other.z_),
		w_(w)
{}

float Vec4::dot_product (const Vec4& other) const
{
	return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_) + (w_ * other.w_);
}

float Vec4::length () const
{
	if (w_ == 0)
		throw runtime_error("Math error: Attempted to divide by Zero\n");

	float xHomo = x_ / w_;
	float yHomo = y_ / w_;
	float zHomo = z_ / w_;

	return sqrt(xHomo*xHomo + yHomo*yHomo + zHomo*zHomo);
}

void Vec4::homogenize		()
{
	if (w_ == 0)
		throw runtime_error("Math error: Attempted to divide by Zero\n");
	
	//use divise scale operator
	(*this) /= w_;
}

Vec4& 	Vec4::normalize		()
{
	float normeVec = length();
	x_ = normeVec == 0 ? 0 : x_ / normeVec;
	y_ = normeVec == 0 ? 0 : y_ / normeVec;
	z_ = normeVec == 0 ? 0 : z_ / normeVec;
	w_ = normeVec == 0 ? 0 : w_ / normeVec;
	return *this;
}

Vec4 	Vec4::getNormalize		() const
{
	float normeVec = length();
	return normeVec == 0 ? Vec4::zero : Vec4(x_ / normeVec, y_ / normeVec, z_ / normeVec, w_ / normeVec);
}

Vec4& Vec4::operator++ ()
{
	float len = length();
	x_ *=  (len + 1) / len;
	y_ *=  (len + 1) / len;
	z_ *=  (len + 1) / len;
	w_ *=  (len + 1) / len;
	return *this;
}

Vec4 Vec4::operator++ (int)
{
	return ++(*this);
}

Vec4& Vec4::operator-- ()
{
	float len = length();
	x_ *=  (len - 1) / len;
	y_ *=  (len - 1) / len;
	z_ *=  (len - 1) / len;
	w_ *=  (len - 1) / len;
	return *this;
}

Vec4 Vec4::operator-- (int)
{
	return --(*this);
}

Vec4 Vec4::operator-() const
{
	return Vec4(-x_, -y_, -z_, -w_);
}

Vec4& Vec4::operator+=(const Vec4& vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	z_ += vec.z_;
	w_ += vec.w_;
	return *this;
}

Vec4& Vec4::operator-=(const Vec4& vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	z_ -= vec.z_;
	w_ -= vec.w_;
	return *this;
}

Vec4& Vec4::operator*=(const float& scale)
{
	x_ *= scale;
	y_ *= scale;
	z_ *= scale;
	w_ *= scale;
	return *this;
}

Vec4& Vec4::operator/=(const float& scale)
{
	x_ /= scale;
	y_ /= scale;
	z_ /= scale;
	w_ /= scale;
	return *this;
}

Vec4& Vec4::operator=(const Vec4 & vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	z_ = vec.z_;
	w_ = vec.w_;
	return *this;
}

float& Vec4::operator[](unsigned int val)
{
	assert(val < 3);

	if(val == 0)
		return x_;
	else if (val == 1)
		return y_;
	else if (val == 2)
		return z_;
	else
		return w_;
}

const Vec4 Vec4::zero 	{0.f, 0.f, 0.f, 0.f};

Vec4 math::operator- (Vec4 vec1, const Vec4& vec2)
{
	vec1 -= vec2;
	return vec1;
}

Vec4 math::operator+ (Vec4 vec1, const Vec4& vec2)
{
	vec1 += vec2;
	return vec1;
}

Vec4 math::operator*		(Vec4 vec, const float& scale)
{
	return vec *= scale;
}

Vec4 math::operator*		(const float& scale, Vec4 vec)
{
	return vec *= scale;
}

Vec4 math::operator/		(Vec4 vec, const float& scale)
{
	return vec /= scale;
}

Vec4 math::operator/		(const float& scale, Vec4 vec)
{
	vec.x_ = scale / vec.x_;
	vec.y_ = scale / vec.y_;
	vec.z_ = scale / vec.z_;
	vec.w_ = scale / vec.w_;
	return vec;
}

float math::operator, (Vec4 vec1, const Vec4& vec2)
{
	return vec1.dot_product(vec2);
}

bool math::operator==(Vec4 const& vec1, Vec4 const& vec2)
{
	return 	vec1.x_ == vec2.x_ && 
			vec1.y_ == vec2.y_ && 
			vec1.z_ == vec2.z_ && 
			vec1.w_ == vec2.w_;
}

bool math::operator!=(Vec4 const& vec1, Vec4 const& vec2)
{
	return !(vec1 == vec2);
}

bool math::operator<(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() < vec2.length();
}

bool math::operator<=(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() <= vec2.length();
}

bool math::operator>(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() > vec2.length();
}

bool math::operator>=(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() >= vec2.length();
}

string math::operator+(string const& str, Vec4 const& vec)
{
	return str + 	"x:" + to_string(vec.x_) +
			 		", y:" + to_string(vec.y_) + 
					", z:" + to_string(vec.z_) + 
					", w:" + to_string(vec.w_);
}

void math::operator+=(string& str, Vec4 const& vec)
{
	str += 	"x:" + to_string(vec.x_) + 
			", y:" + to_string(vec.y_) + 
			", z:" + to_string(vec.z_) +
			", w:" + to_string(vec.w_);
}

ostream& math::operator<<(ostream& out, const Vec4& vec)
{
	out << vec.x_ << "," << vec.y_ << "," << vec.z_ << "," << vec.w_;
	return out;
}
