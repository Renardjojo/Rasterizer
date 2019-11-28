#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>

namespace math
{
	//Matrix is in convention column
	typedef class Matrix
	{
		public:

			Matrix () = default;

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
			Matrix 		(unsigned int line, unsigned int column, float value = 0.f);

			/**
			 * function : Matrix (constructor)
			 *
			 * parameter : 
			 * unsigned int size : height and width of squart matrix
			 *
			 * brief : construct identity matrix. This matrix is squart 
			 */
			Matrix		(unsigned int size);

			/**
			 * function : Matrix (copy constructor)
			 *
			 * parameter : 
			 * const Matrix& other : other matrix to copy
			 *
			 * brief : construct matrix in function of over matrix. The new matrix is a copy 
			 */
			Matrix (const Matrix& other);
		
			/**
			 * function : Matrix (destructor)
			 *
			 * brief : destroy matrix
			 */
			virtual ~Matrix ();

			 /*----------*/
			/* methode  */
		   /*----------*/

			/**
			 * function : transpose
			 *
			 * return (type Matrix&	): return ref of current matrice after transposition
			 *
			 * brief : transpose matrix. The line become columne
			 */
			Matrix&		transpose		();

			/**
			 * function : display
			 *
			 * return (type void):
			 *
			 * brief : display matrix in terminal. Display float this prescision of 3 number befor coma.
			 */
			void		display		() const;

			/**
			 * function : isSquare
			 *
			 * parameter : 
			 *
			 * return (type bool):
			 *
			 * brief : return true if matrix form is like X*X. Else return false
			 */
			bool		isSquare		() const;
		
			/**
			 * function : isEmpty

			 *
			 * parameter : 
			 *
			 * return (type bool):
			 *
			 * brief : return true if matrix is empty
			 */
			bool		isEmpty		() const;

			/**
			 * function : isOrtho
			 *
			 * parameter :
			 *
			 * return (type bool):
			 *
			 * brief : return true of false if matrix is orthogonal. If M*M.transpose() = I. Assert if matrix is not square
			 */
			bool		isOrtho		() const;
		

			/**
			 * function : foundDeterminant
			 *
			 * parameter : 
			 *
			 * return (type float): return the determinant usfull to found the reverse matrix. If determinant is egal to 0, matrix can be reseable
			 *
			 * brief :  Calcul the derteminant of square matrix X*X. Create assert if matrix is not square or if matrix is void. 
			 *			If determinant is geometrical area betwen eache vector in matrix. 
			 */
			float		getDeterminant		();

			/**
			 * function : getReverse
			 *
			 * parameter : 
			 *
			 * return (type Matrix): return empty matrix if reverse is not possible
			 *
			 * brief : reserse matrix if it's possible, else return false. 
			 * If function if orthogonal, this function return the transposate of matrix.
			 * Assert if is square or empty
			 */
			Matrix		getReverse		() const;

			/**
			 * function : reverse
			 *
			 * parameter : 
			 *
			 * return (type bool): return true if matrix war be reserse. Else it's imposible and return false
			 *
			 * brief : reserse matrix if it's possible, else return false.
			 * If function if orthogonal, matrix will be transpose.
			 * Assert if is square or empty
			 */
			bool		reverse		();

			/**
			 * function : getReverse
			 *
			 * parameter : 
			 *
			 * return (type Matrix): return an empty matrix if solvation is not possible
			 *
			 * brief : This function solve a system of n equation of n unknow. 
			 * For exemple :
			 * q1 * x1 + q2 * x2 + q3 * x3 = v1 
			 * q4 * x1 + q5 * x2 + q6 * x3 = v2
			 * etc...
			 * Enter in parameter each coef under the form of matrix and each result under the form of colmun vector (other matrix) 
			 *	Assert if matrix of equation colum is under 1 or if one of all matrix is empty.
			 */
			static Matrix		getSolvationNEquationOfNInknow		(const Matrix& eqCoef, const Matrix& eqRslt);


			 /*----------*/
			/* accessor */
		   /*----------*/

			unsigned int 	get_nbLine	()	const	{	return line_;	}
			unsigned int 	get_nbColumn()	const	{	return column_;	}
			unsigned int 	get_size	()	const	{	return column_*line_;	}

			 /*----------*/
			/* mutator  */
		   /*----------*/

			 /*----------*/
			/* operator */
		   /*----------*/

			/**
			 * function : operator[]
			 *
			 * parameter : 
			 * unsigned int indexLine : index of line in matrix
			 *
			 * return (type float*):return tab of float corresponding to line of matrix.
			 *
			 * brief : this function return tab of float corresponding to line of matrix.
			 * This form allow this call matrix[n][m]. Thirst element start to 0 : [0][0]. Max = [line-1][colomn-1]
			 */
			float*		operator[]		(unsigned int indexLine) const;

			/**
			 * function : operator[]
			 *
			 * parameter : 
			 * unsigned int indexLine : index of line in matrix
			 *
			 * return (type float*):return tab of float corresponding to line of matrix.
			 *
			 * brief : this function return tab of float corresponding to line of matrix.
			 * This form allow this call matrix[n][m]. Thirst element start to 0 : [0][0]. Max = [line-1][colomn-1]
			 */
			float*		operator[]		(unsigned int indexLine);


			/**
			 * function : operator==
			 *
			 * parameter : 
			 * const Matrix& other: 
			 *
			 * return (type bool):
			 *
			 * brief : return true check if matrix A egal other matrix.
			 */
			bool	operator==		(const Matrix& other) const;

			/**
			 * function : operator=
			 *
			 * parameter : 
			 * const Matrix& other: 
			 *
			 * return (type Matrix&):
			 *
			 * brief : copy content of other matrix in matrix.
			 */
			Matrix&		operator=		(const Matrix& other);
		

			/**
			 * function : operator+=
			 *
			 * parameter : 
			 * const Matrix& other
			 * 
			 * return (type Matrix&):
			 *
			 * brief : add matrix en return result.
	 	     * Assert is other matrix size is not egal to matrix
			 */
			Matrix&		operator+=		(const Matrix& other);

			/**
			 * function : operator-=
			 *
			 * parameter : 
			 * const Matrix& other
			 * 
			 * return (type Matrix&):
			 *
			 * brief : sub matrix en return result.
	 	     * Assert is other matrix size is not egal to matrix
			 */
			Matrix&		operator-=		(const Matrix& other);

			/**
			 * function : operator*=
			 *
			 * parameter : 
			 * const Matrix& other
			 * 
			 * return (type Matrix&):
			 *
			 * brief : multiplie matrix en return result.
	 	     * Assert if other matrix line is not egal to matrx's column.
			 */
			Matrix&		operator*=		(const Matrix& other);
		
			/**
			 * function : operator+
			 *
			 * parameter : 
			 * Matrix other : copy of other matrix. Will be return after operation
			 *
			 * return (type Matrix):
			 *
			 * brief : create Matrix of adition between *this and other.
	 	     * Assert is other matrix size is not egal to matrix
			 */
			Matrix		operator+		(Matrix other);

			/**
			 * function : operator-
			 *
			 * parameter : 
			 * Matrix other : copy of other matrix. Will be return after operation
			 *
			 * return (type Matrix):
			 *
			 * brief : create Matrix of substraction between *this and other.
	 	     * Assert is other matrix size is not egal to matrix
			 */
			Matrix		operator-		(Matrix other);
		

			/**
			 * function : operator*
			 *
			 * parameter : 
			 * const Matrix& other :
			 *
			 * return (type Matrix):
			 *
			 * brief : create Matrix of multiplication between *this and other according to matrix multiplication formul.
			 * New matrix (M) size with multiplication of A and B is egal to M[An][Am]
	 	     * Assert if other matrix line is not egal to matrx's column.
			 */
			Matrix		operator*		(const Matrix& other);
		
			 /*----------*/
			/* convertor*/ 
		   /*----------*/

		protected:
			unsigned int 	line_;
			unsigned int 	column_;
			float* 			matrix_;

			/**
			 * function : foundDeterminantMatX
			 *
			 * parameter : 
			 *
			 * return (type float): return the determinant usfull to found the reverse matrix. If determinant is egal to 0, matrix can be reseable
			 *
			 * brief : Few function to calcul the derteminant of square matrix X*X. Create assert if matrix too big.
			 */
			float		foundDeterminantMat1		() const;
			float		foundDeterminantMat2		() const;
			float		foundDeterminantMat3		() const;
			float		foundDeterminantMat4		() const;
			float 		foundDeterminantMatX		() const; //recursive function for X square matrix


			/**
			 * function : getMinor
			 *
			 * parameter : 
			 *  unsigned int i : start to 0 just to n - 1 
			 *	unsigned int j : start to 0 just to n - 1
			 * 
			 *
			 * return (type float):
			 *
			 * brief : this function return the determinant of minor element in function of M aij. Assert if matrix is not square.
			 */
			float		getMinor		(unsigned int i, unsigned int j) const;


			/**
			 * function : getCofactor
			 *
			 * parameter : 
			 *  unsigned int i : start to 0 just to n - 1 
			 *	unsigned int j : start to 0 just to n - 1
			 *
			 * return (type float):
			 *
			 * brief : return the result of coeficient multipliate by his cofactor multipliate by the signe : (-1)^(i+j) * minor(i, j)
			 */
			float		getCofactor		(unsigned int i, unsigned int j) const;
				

			/**
			 * function : getCoMatrix
			 *
			 * parameter : 
			 *
			 * return (type Matrix):
			 *
			 * brief : return the cofactor matrix of the current matrix. Assert if is square
			 */
			Matrix		getCoMatrix		() const;
		
			/**
			 * function : getCoMatrix
			 *
			 * parameter : 
			 *
			 * return (type Matrix):
			 *
			 * brief : transpose the cofactor matrix. Assert if is square
			 */
			void		tranformCoMatToAdjointMat		();

			/**
			 * function : getCoMatrix
			 *
			 * parameter : 
			 *
			 * return (type bool): return if matrx can be invert (if zero was found in matrix)
			 *
			 * brief : retrun if the adjoint matrix can be reverse. Assert if is square
			 */
			bool		adjointMatrixIsReversible		() const;
		
		

		private:
	} Mat;

	//like display function. Display float this prescision of 3 number befor coma.
	std::ostream& 	operator<<		(std::ostream& out, const Mat& mat);
};

#endif // _MATRIX_H
