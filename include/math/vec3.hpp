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

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(float bothValue);

	Vec3(const Vec4& other);
	Vec3(const Vec3& other) = default;
	Vec3(const Vec2& other, float z = 1.f);

	~Vec3() = default;


	 /*----------*/
	/* methode  */
   /*----------*/

	float 		dot_product	 	(const Vec3& other) const;

	//same as get magnitude
	float 		length		 	() 					const;

	//creat unit vector
	Vec3& 	normalize		();
	Vec3 	getNormalize	() const;

	 /*----------*/
	/* operator */
   /*----------*/

	Vec3& 	operator++	();
	Vec3 	operator++	(int);
	Vec3& 	operator--	();
	Vec3 	operator--	(int);
	Vec3 	operator-	() const;
	Vec3& 	operator=	(const Vec3& vec);
	Vec3& 	operator+=	(const Vec3& vec);
	Vec3& 	operator-=	(const Vec3& vec);
	Vec3& 	operator*=	(const float& scale);
	Vec3& 	operator/=	(const float& scale);
	float& 	operator[]	(unsigned int val);

	friend void operator>>(istream& in, Vec3& vec);
	friend ostream& operator<<(ostream& out, const Vec3& vec);

	//global value
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
Vec3 		operator-		(Vec3 vec1, Vec3 const& vec2);
Vec3 		operator+		(Vec3 vec1, Vec3 const& vec2);
Vec3		operator*		(Vec3 vec, const float& scale);
Vec3 		operator*		(const float& scale, Vec3 vec);
Vec3 		operator/		(Vec3 vec, const float& scale);
Vec3 		operator/		(const float& scale, Vec3 vec);
bool 		operator==		(Vec3 const& vec1, Vec3 const& vec2);
bool 		operator!=		(Vec3 const& vec1, Vec3 const& vec2);
bool 		operator<		(Vec3 const& vec1, Vec3 const& vec2);
bool 		operator<=		(Vec3 const& vec1, Vec3 const& vec2);
bool 		operator>		(Vec3 const& vec1, Vec3 const& vec2);
bool 		operator>=		(Vec3 const& vec1, Vec3 const& vec2);
string 		operator+		(string const& str, Vec3 const& vec);
void 		operator+=		(string& str, Vec3 const& vec);

ostream& 	operator<<		(ostream& out, const Vec3& vec);

}

#endif // _VEC_3D_H

