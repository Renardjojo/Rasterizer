#include "vec2.hpp"

using namespace std;
using namespace math;

Vec2::Vec2()
	: 	x_ (0.),
		y_ (0.)
{}

Vec2::Vec2(float x, float y)
	: 	x_ (x),
		y_ (y)
{}

Vec2::Vec2(float bothValue) 
	: 	x_(bothValue),
		y_(bothValue)
{}

Vec2::Vec2(const Vec2& other)
	: 	x_ (other.x_),
		y_ (other.y_)
{}

float Vec2::dot_product (const Vec2& other) const
{
	return (x_ * other.x_) + (y_ * other.y_);
}

float Vec2::length () const
{
	return sqrt(pow(x_, 2) + pow(y_, 2));
}

float Vec2::cross_product (const Vec2& other) const
{
	return (x_ * other.y_) - (y_ * other.x_);
}

Vec2&  Vec2::rotate (float angleDeg)
{
	float angleRad = degres_to_rad(angleDeg);
	float x = x_;
	float cosAngle = cos(angleRad);
	float sinAngle = sin(angleRad);
	x_ = (cosAngle * x) - (sinAngle * y_);
	y_ = (sinAngle * x) + (cosAngle * y_);

	return *this;
}

Vec2  	Vec2::getRotate 	(float angleDeg) const
{
	float angleRad = degres_to_rad(angleDeg);
	float cosAngle = cos(angleRad);
	float sinAngle = sin(angleRad);


	return (Vec2){	(cosAngle * x_) - (sinAngle * y_),
						(sinAngle * x_) + (cosAngle * y_)};
}

Vec2&  Vec2::rotated90 () 
{
	swap(x_, y_);
	x_ *= -1;
	return *this;
}

Vec2  	Vec2::getRotated90 		() const
{
	return (Vec2){-y_, x_};
}

Vec2&  Vec2::rotated180 () 
{
	x_ *= -1;
	y_ *= -1;
	return *this;
}

Vec2  	Vec2::getRotated180 		() const
{
	return (Vec2){-x_, -y_};
}

Vec2&  Vec2::rotated270 () 
{
	swap(x_, y_);
	y_ *= -1;
	return *this;
}

Vec2  	Vec2::getRotated270 		() const
{
	return (Vec2){y_, -x_};
}

int Vec2::foundAngleType (const Vec2& other) const
{
	float rst_dotProduct = dot_product(other);
	return rst_dotProduct == 0 ? 0 : ( rst_dotProduct > 0 ? 1 : -1);
}

float Vec2::angle_between_vectors	(Vec2 other) const
{
	Vec2 vec1 = getNormalize();
	return rad_to_degrees(acos(vec1.dot_product(other.getNormalize())));
}

float Vec2::signedAngle_between_vectors	(Vec2 other) const
{/*
	Vec2 PA = segment1.point1 - segment2.point1; //P is point of line  and A a point of segment
 	Vec2 PB = segment1.point1 - segment2.point2; //P is point of line and B a point of segment
	Vec2 VecOrthogonalToLine = (segment1.point2 - segment1.point1).getRotated90();
	
	float dot_productPAVecOrtho = PA.dot_product(VecOrthogonalToLine);
	float dot_productPBVecOrtho = PB.dot_product(VecOrthogonalToLine);

	//if point of seg1 is in same side to line of semgnent2 so not colision
	if(dot_productPAVecOrtho * dot_productPBVecOrtho >= error_marge)
		return false;*/

	Vec2 vec1 = {1,0};
	other -= (*this);
	return rad_to_degrees(acos(vec1.dot_product(other.getNormalize())));
}

Vec2 Vec2::projection (const Vec2& other) const
{
	float prod1 = dot_product(other);

	if(prod1 == 0) //suppress possibility of division by 0
		return Vec2(0., 0.);

	return other.getNormalize() * prod1;
}

Vec2 	Vec2::getNormalize		() const
{
	float normeVec = length();
	return normeVec == 0 ? Vec2::zero : Vec2(x_ / normeVec, y_ / normeVec);
}

Vec2& 	Vec2::normalize		()
{
	float normeVec = length();
	x_ = normeVec == 0 ? 0 : x_ / normeVec;
	y_ = normeVec == 0 ? 0 : y_ / normeVec;
	return *this;
}

Vec2& Vec2::operator++ ()
{
	float len = length();
	x_ *=  (len + 1) / len;
	y_ *=  (len + 1) / len;
	return *this;
}

Vec2 Vec2::operator++ (int)
{
	return ++(*this);
}

Vec2& Vec2::operator-- ()
{
	float len = length();
	x_ *=  (len - 1) / len;
	y_ *=  (len - 1) / len;
	return *this;
}

Vec2 Vec2::operator-- (int)
{
	return --(*this);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x_, -y_);
}

Vec2& Vec2::operator+=(const Vec2& vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	return *this;
}

Vec2& Vec2::operator*=(const float& scale)
{
	x_ *= scale;
	y_ *= scale;
	return *this;
}

Vec2& Vec2::operator/=(const float& scale)
{
	x_ /= scale;
	y_ /= scale;
	return *this;
}

Vec2& Vec2::operator=(const Vec2 & vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	return *this;
}

float& Vec2::operator[](int val)
{
	if(val == 0)
		return x_;
	
	return y_;
}

float& Vec2::operator[](char val)
{
	if(val == 'x')
		return x_;
	
	return y_;
}

float& Vec2::operator[](string val)
{
	if(val == "x")
		return x_;
	
	return y_;
}

const Vec2 Vec2::zero 	{0., 0.};
const Vec2 Vec2::up		{0., 1.};
const Vec2 Vec2::down	{0., -1.};
const Vec2 Vec2::left	{-1., 0.f};
const Vec2 Vec2::right	{1., 0.};

float Vec2::rad_to_degrees (float rad) const
{
	return rad * 180 / M_PI;
}

float Vec2::degres_to_rad (float degres) const
{
	return degres * M_PI / 180;
}

float Vec2_dotProductNormeAngle (float normevector1, float normevector2, float angleDeg)
{
	return normevector1 * normevector2 * cos(angleDeg * M_PI / 180);
}


Vec2 math::operator- (Vec2 vec1, const Vec2& vec2)
{
	vec1 -= vec2;
	return vec1;
}

Vec2 math::operator+ (Vec2 vec1, const Vec2& vec2)
{
	vec1 += vec2;
	return vec1;
}

Vec2 math::operator*		(Vec2 vec, const float& scale)
{
	return vec *= scale;
}

Vec2 math::operator*		(const float& scale, Vec2 vec)
{
	return vec *= scale;
}

Vec2 math::operator/		(Vec2 vec, const float& scale)
{
	return vec /= scale;
}

Vec2 math::operator/		(const float& scale, Vec2 vec)
{
	vec.x_ = scale / vec.x_;
	vec.y_ = scale / vec.y_;
	return vec;
}


void math::operator>>(istream& in, Vec2& vec)
{
	string line, leftVal, rightVal;
	in >> line;

	size_t curs = line.find(',');

	if (curs == string::npos)
		vec = Vec2::zero;

	leftVal = line.substr(0, curs);
	rightVal = line.substr(curs + 1);
	
	vec.x_ = stof(leftVal);
	vec.y_ = stof(rightVal);
}

float math::operator, (Vec2 vec1, const Vec2& vec2)
{
	return vec1.dot_product(vec2);
}

bool math::operator==(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.x_ == vec2.x_ && vec1.y_ == vec2.y_;
}

bool math::operator!=(Vec2 const& vec1, Vec2 const& vec2)
{
	return !(vec1 == vec2);
}

bool math::operator<(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() < vec2.length();
}

bool math::operator<=(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() <= vec2.length();
}

bool math::operator>(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() > vec2.length();
}

bool math::operator>=(Vec2 const& vec1, Vec2 const& vec2)
{
	return vec1.length() >= vec2.length();
}

string math::operator+(string const& str, Vec2 const& vec)
{
	return str + "x:" + to_string(vec.x_) + ", y:" + to_string(vec.y_);
}

void math::operator+=(string& str, Vec2 const& vec)
{
	str += "x:" + to_string(vec.x_) + ", y:" + to_string(vec.y_);
}

ostream& math::operator<<(ostream& out, const Vec2& vec)
{
	out << vec.x_ << "," << vec.y_;
	return out;
}
