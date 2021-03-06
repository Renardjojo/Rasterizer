#include "vec.hpp"

using namespace math;
using namespace std;

//////////////////////
//VEC2
/////////////////////


inline float rad_to_degrees (float rad)
{
	return rad * 180.f / M_PI;
}

inline float degres_to_rad (float degres)
{
	return degres * M_PI / 180.f;
}

inline float Vec2::dot_product (const Vec2& other) const
{
	return x * other.x + y * other.y;
}

inline float Vec2::length () const
{
	return sqrt(x * x + y * y);
}

inline float Vec2::cross_product (const Vec2& other) const
{
	return (x * other.y) - (y * other.x);
}

inline Vec2&  Vec2::rotate (float angleDeg)
{
	float angleRad = degres_to_rad(angleDeg);
	float xTemp = x;
	float cosAngle = cos(angleRad);
	float sinAngle = sin(angleRad);

	x = (cosAngle * xTemp) - (sinAngle * y);
	y = (sinAngle * xTemp) + (cosAngle * y);

	return *this;
}

inline Vec2  	Vec2::getRotate 	(float angleDeg) const
{
	float angleRad = degres_to_rad(angleDeg);
	float cosAngle = cos(angleRad);
	float sinAngle = sin(angleRad);

	return {cosAngle * x - sinAngle * y, sinAngle * x + cosAngle * y};
}

inline Vec2&  Vec2::rotated90 () 
{
	swap(x, y);
	x *= -1;
	return *this;
}

inline Vec2  	Vec2::getRotated90 		() const
{
	return (Vec2){-y, x};
}

inline Vec2&  Vec2::rotated180 () 
{
	x *= -1;
	y *= -1;
	return *this;
}

inline Vec2  	Vec2::getRotated180 		() const
{
	return (Vec2){-x, -y};
}

inline Vec2&  Vec2::rotated270 () 
{
	swap(x, y);
	y *= -1;
	return *this;
}

inline Vec2  	Vec2::getRotated270 		() const
{
	return (Vec2){y, -x};
}

inline int Vec2::foundAngleType (const Vec2& other) const
{
	float rst_dotProduct = dot_product(other);
	return rst_dotProduct == 0 ? 0 : ( rst_dotProduct > 0 ? 1 : -1);
}

inline float Vec2::angle_between_vectors	(Vec2 other) const
{
	Vec2 vec1 = getNormalize();
	return rad_to_degrees(acos(vec1.dot_product(other.getNormalize())));
}

inline float Vec2::signedAngle_between_vectors	(Vec2 other) const
{
	Vec2 vec1 {1.f, 0.f};
	other -= (*this);
	return rad_to_degrees(acos(vec1.dot_product(other.getNormalize())));
}

inline Vec2 Vec2::projection (const Vec2& other) const
{
	float prod1 = dot_product(other);

	if(prod1 == 0) //suppress possibility of division by 0
		return {0.f, 0.f};

	return other.getNormalize() * prod1;
}

inline Vec2 	Vec2::getNormalize		() const
{
	float normeVec = length();
	return normeVec == 0.f ? Vec2{0.f, 0.f} : Vec2{x / normeVec, y / normeVec};
}

inline Vec2& 	Vec2::normalize		()
{
	float normeVec = length();
	x = (normeVec == 0.f ? 0.f : x / normeVec);
	y = (normeVec == 0.f ? 0.f : y / normeVec);
	return *this;
}

inline Vec2& Vec2::operator++ ()
{
	float len = length();
	x *=  (len + 1) / len;
	y *=  (len + 1) / len;
	return *this;
}

inline Vec2 Vec2::operator++ (int)
{
	return ++(*this);
}

inline Vec2& Vec2::operator-- ()
{
	float len = length();
	x *=  (len - 1) / len;
	y *=  (len - 1) / len;
	return *this;
}

inline Vec2 Vec2::operator-- (int)
{
	return --(*this);
}

inline Vec2 Vec2::operator-() const
{
	return {-x, -y};
}

inline Vec2& Vec2::operator+=(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

inline Vec2& Vec2::operator-=(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

inline Vec2& Vec2::operator*=(const float& scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

inline Vec2& Vec2::operator/=(const float& scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

inline Vec2& Vec2::operator=(const Vec2 & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

inline float& Vec2::operator[](int val)
{
	assert(val < 2);
	return e[val]; 
}

inline float Vec2_dotProductNormeAngle (float normevector1, float normevector2, float angleDeg)
{
	return normevector1 * normevector2 * cosf(angleDeg * M_PI / 180.f);
}

inline Vec2 operator- (Vec2 vec1, const Vec2& vec2)
{
	vec1 -= vec2;
	return vec1;
}

inline Vec2 operator+ (Vec2 vec1, const Vec2& vec2)
{
	vec1 += vec2;
	return vec1;
}

inline Vec2 operator*		(Vec2 vec, const float& scale)
{
	return vec *= scale;
}

inline Vec2 operator*		(const float& scale, Vec2 vec)
{
	return vec *= scale;
}

inline Vec2 operator/		(Vec2 vec, const float& scale)
{
	return vec /= scale;
}

inline Vec2 operator/		(const float& scale, Vec2 vec)
{
	vec.x = scale / vec.x;
	vec.y = scale / vec.y;
	return vec;
}


inline void operator>>(istream& in, Vec2& vec)
{
	string line, leftVal, rightVal;
	in >> line;

	size_t curs = line.find(',');

	if (curs == string::npos)
		vec = {0.f, 0.f};

	leftVal = line.substr(0, curs);
	rightVal = line.substr(curs + 1);
	
	vec.x = stof(leftVal);
	vec.y = stof(rightVal);
}

inline float operator, (Vec2 vec1, const Vec2& vec2)
{
	return vec1.dot_product(vec2);
}

inline bool operator==(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

inline bool operator!=(Vec2 const& vec1, Vec2 const& vec2)
{
	return !(vec1 == vec2);
}

inline bool operator<(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() < vec2.length();
}

inline bool operator<=(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() <= vec2.length();
}

inline bool operator>(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() > vec2.length();
}

inline bool operator>=(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() >= vec2.length();
}

inline ostream& operator<<(ostream& out, const Vec2& vec)
{
	out << vec.x << "," << vec.y;
	return out;
}

//////////////////////
//VEC3
/////////////////////

inline float Vec3::dot_product (const Vec3& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

inline float Vec3::length () const
{
	return sqrt(x * x + y * y + z * z);
}

inline Vec3& 	Vec3::normalize		()
{
	float normeVec = length();
	x = normeVec == 0 ? 0 : x / normeVec;
	y = normeVec == 0 ? 0 : y / normeVec;
	z = normeVec == 0 ? 0 : z / normeVec;
	return *this;
}

inline Vec3 	Vec3::getNormalize		() const
{
	float normeVec = length();
	return normeVec == 0 ? Vec3{0.f, 0.f, 0.f} : Vec3{x / normeVec, y / normeVec, z / normeVec};
}

inline Vec3& Vec3::operator++ ()
{
	float len = length();
	x *=  (len + 1) / len;
	y *=  (len + 1) / len;
	z *=  (len + 1) / len;
	return *this;
}

inline Vec3 Vec3::operator++ (int)
{
	return ++(*this);
}

inline Vec3& Vec3::operator-- ()
{
	float len = length();
	x *=  (len - 1) / len;
	y *=  (len - 1) / len;
	z *=  (len - 1) / len;
	return *this;
}

inline Vec3 Vec3::operator-- (int)
{
	return --(*this);
}

inline Vec3 Vec3::operator-() const
{
	return {-x, -y, -z};
}

inline Vec3& Vec3::operator+=(const Vec3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

inline Vec3& Vec3::operator*=(const float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

inline Vec3& Vec3::operator/=(const float& scale)
{
	x /= scale;
	y /= scale;
	z /= scale;
	return *this;
}

inline Vec3& Vec3::operator=(const Vec3 & vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

inline float& Vec3::operator[](unsigned int val)
{
	assert(val < 3);
	return e[val]; 
}

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

inline Vec3 operator*		(Vec3 vec, const float scale)
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
	vec.x = scale / vec.x;
	vec.y = scale / vec.y;
	vec.z = scale / vec.z;
	return vec;
}

inline float operator, (Vec3 vec1, const Vec3& vec2)
{
	return vec1.dot_product(vec2);
}

inline bool operator==(Vec3 const& vec1, Vec3 const& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
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

inline ostream& operator<<(ostream& out, const Vec3& vec)
{
	out << vec.x << "," << vec.y << "," << vec.z;
	return out;
}

//////////////////////
//VEC4
/////////////////////

inline float Vec4::dot_product (const Vec4& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

inline float Vec4::length () const
{
	assert (w != 0);

	float xHomo = x / w;
	float yHomo = y / w;
	float zHomo = z / w;

	return sqrt(xHomo*xHomo + yHomo*yHomo + zHomo*zHomo);
}

inline void Vec4::homogenize		()
{
	assert (w != 0);
	(*this) /= w;
}

inline Vec4& 	Vec4::normalize		()
{
	float normeVec = length();
	x = normeVec == 0 ? 0 : x / normeVec;
	y = normeVec == 0 ? 0 : y / normeVec;
	z = normeVec == 0 ? 0 : z / normeVec;
	w = normeVec == 0 ? 0 : w / normeVec;
	return *this;
}

inline Vec4 	Vec4::getNormalize		() const
{
	float normeVec = length();
	return normeVec == 0 ? Vec4{0.f, 0.f, 0.f, 0.f}: Vec4{x / normeVec, y / normeVec, z / normeVec, w / normeVec};
}

inline Vec4& Vec4::operator++ ()
{
	float len = length();
	x *=  (len + 1) / len;
	y *=  (len + 1) / len;
	z *=  (len + 1) / len;
	w *=  (len + 1) / len;
	return *this;
}

inline Vec4 Vec4::operator++ (int)
{
	return ++(*this);
}

inline Vec4& Vec4::operator-- ()
{
	float len = length();
	x *=  (len - 1) / len;
	y *=  (len - 1) / len;
	z *=  (len - 1) / len;
	w *=  (len - 1) / len;
	return *this;
}

inline Vec4 Vec4::operator-- (int)
{
	return --(*this);
}

inline Vec4 Vec4::operator-() const
{
	return {-x, -y, -z, -w};
}

inline Vec4& Vec4::operator+=(const Vec4& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}

inline Vec4& Vec4::operator-=(const Vec4& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}

inline Vec4& Vec4::operator*=(const float& scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
	return *this;
}

inline Vec4& Vec4::operator/=(const float& scale)
{
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
	return *this;
}

inline Vec4& Vec4::operator=(const Vec4 & vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
	return *this;
}

inline float& Vec4::operator[](unsigned int val)
{
	assert(val < 4);
	return e[val];
}

inline Vec4 operator- (Vec4 vec1, const Vec4& vec2)
{
	vec1 -= vec2;
	return vec1;
}

inline Vec4 operator+ (Vec4 vec1, const Vec4& vec2)
{
	vec1 += vec2;
	return vec1;
}

inline Vec4 operator*		(Vec4 vec, const float& scale)
{
	return vec *= scale;
}

inline Vec4 operator*		(const float& scale, Vec4 vec)
{
	return vec *= scale;
}

inline Vec4 operator/		(Vec4 vec, const float& scale)
{
	return vec /= scale;
}

inline Vec4 operator/		(const float& scale, Vec4 vec)
{
	vec.x = scale / vec.x;
	vec.y = scale / vec.y;
	vec.z = scale / vec.z;
	vec.w = scale / vec.w;
	return vec;
}

inline float operator, (Vec4 vec1, const Vec4& vec2)
{
	return vec1.dot_product(vec2);
}

inline bool operator==(Vec4 const& vec1, Vec4 const& vec2)
{
	return 	vec1.x == vec2.x && 
			vec1.y == vec2.y && 
			vec1.z == vec2.z && 
			vec1.w == vec2.w;
}

inline bool operator!=(Vec4 const& vec1, Vec4 const& vec2)
{
	return !(vec1 == vec2);
}

inline bool operator<(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() < vec2.length();
}

inline bool operator<=(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() <= vec2.length();
}

inline bool operator>(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() > vec2.length();
}

inline bool operator>=(Vec4 const& vec1, Vec4 const& vec2)
{
	return vec1.length() >= vec2.length();
}

inline ostream& operator<<(ostream& out, const Vec4& vec)
{
	out << vec.x << "," << vec.y << "," << vec.z << "," << vec.w;
	return out;
}
