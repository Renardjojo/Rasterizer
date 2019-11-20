#ifndef _VEC_2D_H
#define _VEC_2D_H

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

namespace math
{

class Vec2
{	
	public :

	Vec2();
	Vec2(float x, float y);
	Vec2(float bothValue);
	Vec2(const Vec2& other);

	~Vec2(){}


	 /*----------*/
	/* methode  */
   /*----------*/

	float 		dot_product	 	(const Vec2& other) const;
	float 		length		 	() 						const;
	float 		cross_product	(const Vec2& other) const;

	/**
	 * function : rotate
	 *
	 * parameter : 
	 * float angleDeg : in degres
	 *
	 * return : Vec2&
	 *
	 * brief : turn Vec2 in sens of trigono
	 */
	Vec2& 		rotate			(float angleDeg);
	Vec2  		getRotate 		(float angleDeg) const;

	Vec2&  		rotated90 		();
	Vec2  		getRotated90 	() const;

	Vec2&  		rotated180 		(); 
	Vec2  		getRotated180	() const;

	Vec2&  		rotated270 		();
	Vec2  		getRotated270 	() const;

	/**
	 * function : foundAngleType
	 *
	 * parameter : 
	 * const Vec2& other
	 *
	 * return (type int) :
	 * -1 if angle is the angle is obtuse
	 *  0 if angle is the angle valu is 90 degres or pi/2 
	 *  1 if angle is the angle is aigu 
	 *
	 * brief : this function found the angle type and return it. The angle found is the shortess angle between two point
	 */
	int		foundAngleType		(const Vec2& other) const;

	/**
	 * function : foundAngle
	 *
	 * parameter : 
	 * const Vec2& other
	 *
	 * return (type float): angle between two Vec2 in deg
	 *
	 * brief : calcul the angle between two Vec2 of center 0. The angle found is the shortess angle between two point
	 */
	virtual float		angle_between_vectors				(Vec2 other) const;
	virtual float		signedAngle_between_vectors		(Vec2 other) const;

	/**
	 * function : projection
	 *
	 * parameter : 
	 * Vec2 other
	 *
	 * return (type Vec2):
	 *
	 * brief : create Vec2 projection between two Vec2. Vector this is project on vector other
	 * Formule : vect(vp) = ((vect(u)*vect(v))/vect(u)*vect(u)) * vect(u)
	 */
	Vec2		projection		(const Vec2& other) const;


	//creat unit vector
	Vec2& 	normalize		();
	Vec2 	getNormalize	() const;

	 /*----------*/
	/* operator */
   /*----------*/

	Vec2& 	operator++	();
	Vec2 	operator++	(int);
	Vec2& 	operator--	();
	Vec2 	operator--	(int);
	Vec2 	operator-	() const;
	Vec2& 	operator=	(const Vec2& vec);
	Vec2& 	operator+=	(const Vec2& vec);
	Vec2& 	operator-=	(const Vec2& vec);
	Vec2& 	operator*=	(const float& scale);
	Vec2& 	operator/=	(const float& scale);
	float& 	operator[]	(int val);
	float& 	operator[]	(char val);
	float& 	operator[]	(string val);

	friend void operator>>(istream& in, Vec2& vec);
	friend ostream& operator<<(ostream& out, const Vec2& vec);

	 /*----------*/
	/* convertor*/ 
   /*----------*/


	//global value
	static const Vec2 zero;
	static const Vec2 up;
	static const Vec2 down;
	static const Vec2 left;
	static const Vec2 right;

	float x_, y_;

	protected:

	 //brief : convert rad to degres
	float		rad_to_degrees		(float rad) const;

	//brief : converte dregres to rad
	float		degres_to_rad		(float degres) const;
};

/**
 * function : Vec2_dotProductNormeAngle
 *
 * parameter : 
 * float normeVec21 : magnitude of vec 2 (can use Vec2_getMagnitude)
 * float normeVec22 : magnitude of vec 1
 * float angleRad : angle in deg
 *
 * return : float
 *
 * brief : calcul dot product between two Vec2
 */
float Vec2_dotProductNormeAngle (float normeVec21, float normeVec22, float angleDeg);


float 		operator,		(Vec2 vec1, const Vec2& vec2); //dot product
Vec2 		operator-		(Vec2 vec1, const Vec2& vec2);
Vec2 		operator+		(Vec2 vec1, const Vec2& vec2);
Vec2		operator*		(Vec2 vec, const float& scale);
Vec2 		operator*		(const float& scale, Vec2 vec);
Vec2 		operator/		(Vec2 vec, const float& scale);
Vec2 		operator/		(const float& scale, Vec2 vec);
bool 		operator==		(Vec2 const& vec1, Vec2 const& vec2);
bool 		operator!=		(Vec2 const& vec1, Vec2 const& vec2);
bool 		operator<		(Vec2 const& vec1, Vec2 const& vec2);
bool 		operator<=		(Vec2 const& vec1, Vec2 const& vec2);
bool 		operator>		(Vec2 const& vec1, Vec2 const& vec2);
bool 		operator>=		(Vec2 const& vec1, Vec2 const& vec2);
string 		operator+		(string const& str, Vec2 const& vec);
void 		operator+=		(string& str, Vec2 const& vec);

void 		operator>>		(istream& in, Vec2& vec);
ostream& 	operator<<		(ostream& out, const Vec2& vec);

}

#endif // _VEC_2D_H

