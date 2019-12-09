#ifndef _MAT4_H
#define _MAT4_H

#include "matrix.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace math
{
	//Matrix is in convention column
	class Mat4
		: public Matrix
	{
		public:

			/**
			 * function : Matrix (constructor)
			 *
			 * parameter : 
			 * unsigned int size : height and width of squart matrix
			 *
			 * brief : construct identity matrix. This matrix is squart 
			 */
			Mat4		();

			/**
			 * function : Matrix (constructor)
			 *
			 * parameter : 
			 * unsigned int line : number of line
			 * unsigned int column : number of column
			 * float value : value to set in matrix 
			 *
			 * brief : create null matrix with x line en y column 
			 */
			Mat4 		(float value);

			/**
			 * function : Matrix (copy constructor)
			 *
			 * parameter : 
			 * const Matrix& other : other matrix to copy
			 *
			 * brief : construct matrix in function of over matrix. The new matrix is a copy 
			 */
			Mat4 (const Mat4& other);
			Mat4 (const Matrix& other); //assertion if matrix is not 4*4

			/**
			 * function : Matrix (destructor)
			 *
			 * brief : destroy matrix
			 */

			virtual ~Mat4 ();


			//static function that return scale matrix with scale in parameter
			static Mat4 createScaleMatrix		(float tx, float ty, float tz);
			static Mat4 createScaleMatrix		(const Vec3& tVec);

			//static function that return translation matrix with translation in parameter
			static Mat4 createTranslationMatrix		(float tx, float ty, float tz);
			static Mat4 createTranslationMatrix		(const Vec3& tVec);

			//few static function that return rotation in x, y or z axis arround origin. Rotation is in degres
			static Mat4 createXRotationMatrix		(float rotRadx); //rot of axis Y to axis Z arround X
			static Mat4 createYRotationMatrix		(float rotRady); //rot of axis Z to axis X arround Y
			static Mat4 createZRotationMatrix		(float rotRadz); //rot of axis X to axis Y arround Z

			//static function that return euler rotation arround axis x, y and z give in parameter
			static Mat4 createFixedAngleEulerRotationMatrix (float rx, float ry, float rz);
			static Mat4 createFixedAngleEulerRotationMatrix	(const Vec3& rVec);

			//static function that return TRS matrix (matrix to passing to local to global wit scale, rotation and translation). 
			//Same as creat transform Matrix
			static Mat4 createTRSMatrix(const Vec3& scaleVec, const Vec3& rotVec, const Vec3& translVec);

			//static function that create projection in orthographinc matrix
			static Mat4 createOrthoMatrix	(float left, float right, float bottom, float top, float nearVal, float farVal);

			//static function that create projection in perspective matrix
			static Mat4 createPerspectiveMatrix  (float aspect, float near, float far, float fov);

			//static function that return projection matrix to pass from 3D to 2D.
			//Distance in parameter is the distance between pin hole and user.
			static Mat4 createProjectionMatrix (float distance);

			//this function transforme culumn vect to matrix 4*1 and multipli it by current matrix
			//Vec3 operator*(Vec3 culumnVec);

		protected:
 

		private:


	};

	typedef Mat4 Matix4D; //complet name

	// Multiply all the components of the matrix by a vector
	Vec4 operator*(const Mat4&, const Vec4&); 
};

#endif // _MAT4_H
