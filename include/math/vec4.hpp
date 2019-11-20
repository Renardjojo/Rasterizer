#ifndef _VEC_4D_H
#define _VEC_4D_H

#include <iostream>
#include <string>
#include <math.h>
#include <cassert>

#include "vec3.hpp"

using namespace std;

namespace math
{

class Vec4
{	
	public :

	Vec4();
	Vec4(float x, float y, float z, float w);
	Vec4(float bothValue);
	Vec4(const Vec4& other) = default;
	Vec4(const Vec3& other, float w = 1.f);

	~Vec4() = default;


	 /*----------*/
	/* methode  */
   /*----------*/

	float 		dot_product	 	(const Vec4& other) const;

	//same as get magnitude
	float 		length		 	() 					const;

	//divise each component by w execpt if w == 0
	void 		homogenize		(); 

	//creat unit vector
	Vec4& 	normalize		();
	Vec4 	getNormalize	() const;

	

	 /*----------*/
	/* operator */
   /*----------*/

	Vec4& 	operator++	();
	Vec4 	operator++	(int);
	Vec4& 	operator--	();
	Vec4 	operator--	(int);
	Vec4 	operator-	() const;
	Vec4& 	operator=	(const Vec4& vec);
	Vec4& 	operator+=	(const Vec4& vec);
	Vec4& 	operator-=	(const Vec4& vec);
	Vec4& 	operator*=	(const float& scale);
	Vec4& 	operator/=	(const float& scale);
	float& 	operator[]	(unsigned int val);

	friend void operator>>(istream& in, Vec4& vec);
	friend ostream& operator<<(ostream& out, const Vec4& vec);

	//global value
	static const Vec4 zero;

	 /*----------*/
	/* convertor*/ 
   /*----------*/

	float x_, y_, z_, w_;

	protected :

	 //brief : convert rad to degres
	float		rad_to_degrees		(float rad) const;

	//brief : converte dregres to rad
	float		degres_to_rad		(float degres) const;
};

float 		operator,		(Vec4 vec1, Vec4 const& vec2); //dot product
Vec4 		operator-		(Vec4 vec1, Vec4 const& vec2);
Vec4 		operator+		(Vec4 vec1, Vec4 const& vec2);
Vec4		operator*		(Vec4 vec, const float& scale);
Vec4 		operator*		(const float& scale, Vec4 vec);
Vec4 		operator/		(Vec4 vec, const float& scale);
Vec4 		operator/		(const float& scale, Vec4 vec);
bool 		operator==		(Vec4 const& vec1, Vec4 const& vec2);
bool 		operator!=		(Vec4 const& vec1, Vec4 const& vec2);
bool 		operator<		(Vec4 const& vec1, Vec4 const& vec2);
bool 		operator<=		(Vec4 const& vec1, Vec4 const& vec2);
bool 		operator>		(Vec4 const& vec1, Vec4 const& vec2);
bool 		operator>=		(Vec4 const& vec1, Vec4 const& vec2);
string 		operator+		(string const& str, Vec4 const& vec);
void 		operator+=		(string& str, Vec4 const& vec);

ostream& 	operator<<		(ostream& out, const Vec4& vec);

}

#endif // _VEC_4D_H

