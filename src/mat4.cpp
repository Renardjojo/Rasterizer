#include "mat4.hpp"

#include <iostream>
#include <cassert>
#include <utility>
#include <cmath>

using namespace std;
using namespace math;

Mat4::Mat4	()
	: 	Matrix(4)
{}

Mat4::Mat4 	(float value)
	: 	Matrix (4, 4, value)
{}

Mat4::Mat4 	(const Mat4& other)
	: 	Matrix(other)
{
	assert(other.get_nbLine() == 4 && other.get_nbColumn() == 4);
}

Mat4::Mat4 (const Matrix& other)
	: 	Matrix(other)
{
	assert(other.get_nbLine() == 4 && other.get_nbColumn() == 4);
}

Mat4::~Mat4 ()
{}

Mat4 Mat4::createScaleMatrix(float sx, float sy, float sz)
{
	return createScaleMatrix ({sx, sy, sz});
}

Mat4 Mat4::createScaleMatrix(const Vec3& sVec)
{
	Mat4 sMat;	
	sMat[0][0] = sVec.x_;
	sMat[1][1] = sVec.y_;
	sMat[2][2] = sVec.z_;

	return sMat;
}

Mat4 Mat4::createTranslationMatrix(float tx, float ty, float tz)
{
	return createTranslationMatrix ({tx, ty, tz});
}

Mat4 Mat4::createTranslationMatrix(const Vec3& tVec)
{
	Mat4 tMat;	
	tMat[0][3] = tVec.x_;
	tMat[1][3] = tVec.y_;
	tMat[2][3] = tVec.z_;

	return tMat;
}

Mat4 Mat4::createXRotationMatrix		(float rotRadx)
{
	Mat4 rMat;

	rMat[2][2] = rMat[1][1] = cosf(rotRadx);
	rMat[1][2] = sin(rotRadx);
	rMat[2][1] = -rMat[1][2];

	return rMat;
}

Mat4 Mat4::createYRotationMatrix		(float rotRady)
{
	Mat4 rMat;

	rMat[0][0] = rMat[2][2] = cosf(rotRady);
	rMat[0][2] = sin(rotRady);
	rMat[2][0] = -rMat[0][2];

	return rMat;
}

Mat4 Mat4::createZRotationMatrix		(float rotRadz)
{
	Mat4 rMat;

	rMat[0][0] = rMat[1][1] = cosf(rotRadz);
	rMat[0][1] = sin(rotRadz);
	rMat[1][0] = -rMat[0][1];

	return rMat;
}

Mat4 Mat4::createFixedAngleEulerRotationMatrix (float rx, float ry, float rz)
{
	return createFixedAngleEulerRotationMatrix ({rx, ry, rz});
}

Mat4 Mat4::createFixedAngleEulerRotationMatrix	(const Vec3& rVec)
{
	return 	createYRotationMatrix (rVec.y_) * 
			createXRotationMatrix (rVec.x_) * 
			createZRotationMatrix (rVec.z_);
}

Mat4 Mat4::createTRSMatrix(const Vec3& scaleVec, const Vec3& rotVec, const Vec3& translVec)
{
	return 	createTranslationMatrix (translVec) * 
			createFixedAngleEulerRotationMatrix (rotVec) *
			createScaleMatrix (scaleVec);
}
/*
Vec3 Mat4::operator*(Vec3 cVec)
{
	Matrix mVec (4, 1, 1);
	mVec[0][0] = cVec.x_;
	mVec[0][1] = cVec.y_;
	mVec[0][2] = cVec.z_;
	mVec.display();

	mVec = (*this) * mVec;

	cVec.x_ = mVec[0][0];
	cVec.y_ = mVec[0][1];
	cVec.z_ = mVec[0][2];

	return cVec;
}*/
