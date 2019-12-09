#ifndef _VEC_3D_H
#define _VEC_3D_H

#include <iostream>
#include <string>
#include <math.h>
#include <cassert>

using namespace std;

namespace math
{

class Vec2;
class Vec4;

class Vec3
{	
	public :

Vec3()
	: 	x_ (0.f),
		y_ (0.f),
		z_ (0.f)
{}

Vec3(float x, float y, float z)
	: 	x_ (x),
		y_ (y),
		z_ (z)
{}

Vec3(float bothValue) 
	: 	x_(bothValue),
		y_(bothValue),
		z_(bothValue)
{}

Vec3(const Vec2& other, float z);

Vec3(const Vec4& other);

float dot_product (const Vec3& other) const
{
	return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_);
}

float length () const
{
	return sqrt(x_*x_ + y_*y_ + z_*z_);
}

Vec3& 	normalize		()
{
	float normeVec = length();
	x_ = normeVec == 0 ? 0 : x_ / normeVec;
	y_ = normeVec == 0 ? 0 : y_ / normeVec;
	z_ = normeVec == 0 ? 0 : z_ / normeVec;
	return *this;
}

Vec3 	getNormalize		() const
{
	float normeVec = length();
	return normeVec == 0 ? Vec3::zero : Vec3(x_ / normeVec, y_ / normeVec, z_ / normeVec);
}

Vec3& operator++ ()
{
	float len = length();
	x_ *=  (len + 1) / len;
	y_ *=  (len + 1) / len;
	z_ *=  (len + 1) / len;
	return *this;
}

Vec3 operator++ (int)
{
	return ++(*this);
}

Vec3& operator-- ()
{
	float len = length();
	x_ *=  (len - 1) / len;
	y_ *=  (len - 1) / len;
	z_ *=  (len - 1) / len;
	return *this;
}

Vec3 operator-- (int)
{
	return --(*this);
}

Vec3 operator-() const
{
	return Vec3(-x_, -y_, -z_);
}

Vec3& operator+=(const Vec3& vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	z_ += vec.z_;
	return *this;
}

Vec3& operator-=(const Vec3& vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	z_ -= vec.z_;
	return *this;
}

Vec3& operator*=(const float& scale)
{
	x_ *= scale;
	y_ *= scale;
	z_ *= scale;
	return *this;
}

Vec3& operator/=(const float& scale)
{
	x_ /= scale;
	y_ /= scale;
	z_ /= scale;
	return *this;
}

Vec3& operator=(const Vec3 & vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	z_ = vec.z_;
	return *this;
}

float& operator[](unsigned int val)
{
	assert(val < 3);

	if(val == 0)
		return x_;
	else if (val == 1)
		return y_;
	else
		return z_;
}


	static const Vec3 zero;

	 /*----------*/
	/* convertor*/ 
   /*----------*/

	float x_, y_, z_;

	protected :

	 //brief : convert rad to degres
	float		rad_to_degrees		(float rad) const;

	//brief : converte dregres to rad
	float		degres_to_rad		(float degres) const;
};

float 		operator,		(Vec3 vec1, Vec3 const& vec2); //dot product


inline Vec3 operator- (Vec3 vec1, const Vec3& vec2)
{
	vec1 -= vec2;
	return vec1;
}

inline Vec3 operator+ (Vec3 vec1, const Vec3& vec2)
{
	vec1 += vec2;
	return vec1;
}

inline Vec3 operator*		(Vec3 vec, const float& scale)
{
	return vec *= scale;
}

inline Vec3 operator*		(const float& scale, Vec3 vec)
{
	return vec *= scale;
}

inline Vec3 operator/		(Vec3 vec, const float& scale)
{
	return vec /= scale;
}

inline Vec3 operator/		(const float& scale, Vec3 vec)
{
	vec.x_ = scale / vec.x_;
	vec.y_ = scale / vec.y_;
	vec.z_ = scale / vec.z_;
	return vec;
}

inline float operator, (Vec3 vec1, const Vec3& vec2)
{
	return vec1.dot_product(vec2);
}

inline bool operator==(Vec3 const& vec1, Vec3 const& vec2)
{
	return vec1.x_ == vec2.x_ && vec1.y_ == vec2.y_ && vec1.z_ == vec2.z_;
}

inline bool operator!=(Vec3 const& vec1, Vec3 const& vec2)
{
	return !(vec1 == vec2);
}

inline bool operator<(Vec3 const& vec1, Vec3 const& vec2)
{
	return vec1.length() < vec2.length();
}

inline bool operator<=(Vec3 const& vec1, Vec3 const& vec2)
{
	return vec1.length() <= vec2.length();
}

inline bool operator>(Vec3 const& vec1, Vec3 const& vec2)
{
	return vec1.length() > vec2.length();
}

inline bool operator>=(Vec3 const& vec1, Vec3 const& vec2)
{
	return vec1.length() >= vec2.length();
}

inline string operator+(string const& str, Vec3 const& vec)
{
	return str + "x:" + to_string(vec.x_) + ", y:" + to_string(vec.y_) + ", z:" + to_string(vec.z_);
}

inline void operator+=(string& str, Vec3 const& vec)
{
	str += "x:" + to_string(vec.x_) + ", y:" + to_string(vec.y_) + ", z:" + to_string(vec.z_);
}

inline ostream& operator<<(ostream& out, const Vec3& vec)
{
	out << vec.x_ << "," << vec.y_ << "," << vec.z_;
	return out;
}


}

#endif // _VEC_3D_H

