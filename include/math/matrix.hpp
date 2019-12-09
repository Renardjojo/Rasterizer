#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <cassert>
#include <cmath>

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
			inline Matrix 		(unsigned int line, unsigned int column, float value = 0.f)
				: 	line_	(line),
					column_	(column),
					matrix_	(new float[line_*column_])
			{
				for ( size_t i = 0; i < line_; i++)
				{
					for ( size_t j = 0; j < column_; j++)
					{
						(*this)[i][j] = value;
					}
				}
			}

			/**
			 * function : Matrix (constructor)
			 *
			 * parameter : 
			 * unsigned int size : height and width of squart matrix
			 *
			 * brief : construct identity matrix. This matrix is squart 
			 */
			inline Matrix		(unsigned int size)
					: 	line_	(size),
					column_	(size),
					matrix_	(new float[line_*column_])
			{
				for ( size_t i = 0; i < size; i++ )
				{
					for ( size_t j = 0; j < size; j++ )
					{
						(*this)[i][j] = i == j ? 1.f : 0.f;
					}
				}
			}


			/**
			 * function : Matrix (copy constructor)
			 *
			 * parameter : 
			 * const Matrix& other : other matrix to copy
			 *
			 * brief : construct matrix in function of over matrix. The new matrix is a copy 
			 */
			inline Matrix (const Matrix& other)
				: 	line_	(other.get_nbLine()),
					column_	(other.get_nbColumn()),
					matrix_	(new float[line_*column_])
			{
				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						(*this)[i][j] = other[i][j];
					}
				}
			}

		
			/**
			 * function : Matrix (destructor)
			 *
			 * brief : destroy matrix
			 */
			inline virtual ~Matrix ()
			{
				delete[] matrix_;
			}

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
			inline bool		isSquare		() const
			{
				return line_ == column_;
			}
					
			/**
			 * function : isEmpty

			 *
			 * parameter : 
			 *
			 * return (type bool):
			 *
			 * brief : return true if matrix is empty
			 */
			inline bool		isEmpty		() const
			{
				return line_ + column_ == 0 || matrix_ == nullptr;
			}

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

			inline unsigned int 	get_nbLine	()	const	{	return line_;	}
			inline unsigned int 	get_nbColumn()	const	{	return column_;	}
			inline unsigned int 	get_size	()	const	{	return column_*line_;	}

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
			inline float*		operator[]		(unsigned int indexLine) const
			{
				return &matrix_[indexLine*(column_)];
			}

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
			inline float*		operator[]		(unsigned int indexLine)
			{
				return &matrix_[indexLine*(column_)];
			}


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
			bool	operator==		(const Matrix& other) const
			{
				if (other.get_nbLine() != line_ && other.get_nbColumn() != column_)
					return false;

				for (unsigned int i = 0; i < line_; i++)
				{
					for (unsigned int j = 0; j < column_; j++)
					{
						if ((*this)[i][j] != other[i][j]) 
							return false;
					}
				}

				return true;
			}

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
			Matrix&		operator=		(const Matrix& other)
			{
				delete[] matrix_;
				
				line_	= other.get_nbLine();
				column_	= other.get_nbColumn();
				matrix_	= new float[line_*column_];

				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						(*this)[i][j] = other[i][j];
					}
				}

				return *this;
			}		

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
			inline Matrix&		operator+=		(const Matrix& other)
			{
				assert(line_ == other.get_nbLine() &&  column_ == other.get_nbColumn());

				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						(*this)[i][j] += other[i][j];
					}
				}
					
				return *this;
			}


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
			inline Matrix&		operator-=		(const Matrix& other)
			{
				assert(line_ == other.get_nbLine() &&  column_ == other.get_nbColumn());

				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						(*this)[i][j] -= other[i][j];
					}
				}
					
				return *this;
			}

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
			Matrix&		operator*=		(const Matrix& other)
			{
				assert(column_ == other.get_nbLine());

				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						float result = 0.f;

						for ( size_t index = 0; index < column_; index++)
						{
							result += ((*this)[i][index] * other[index][j]);
						}	
					}
				}
					
				return *this;
			}
					
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
			Matrix		operator+		(Matrix other)
			{
				assert(line_ == other.get_nbLine() &&  column_ == other.get_nbColumn());

				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						other[i][j] += (*this)[i][j];
					}
				}
					
				return other;
			}

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
			inline Matrix		operator-		(Matrix other)
			{
				assert(line_ == other.get_nbLine() &&  column_ == other.get_nbColumn());

				for ( size_t i = 0; i < line_; i++ )
				{
					for ( size_t j = 0; j < column_; j++ )
					{
						other[i][j] -= (*this)[i][j];
					}
				}
					
				return other;
			}
		

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
			inline Matrix		operator*		(const Matrix& other)
			{
				assert(column_ == other.get_nbLine());

				Matrix mResult (line_, other.get_nbColumn());
				
				for ( size_t i = 0; i < mResult.get_nbLine(); i++ )
				{
					for ( size_t j = 0; j < mResult.get_nbColumn(); j++ )
					{
						float result = 0.f;

						for ( size_t index = 0; index < column_; index++)
						{
							result += ((*this)[i][index] * other[index][j]);
						}
						mResult[i][j] = result;
					}
				}

				return mResult;
			}

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
			inline float		foundDeterminantMat1		() const
			{
				assert(line_ == 1);
				return *this[0][0];
			}

			inline float		foundDeterminantMat2		() const
			{
				assert(line_ == 2);

				return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
			}

			inline float		foundDeterminantMat3		() const
			{
				assert(line_ == 3);

				float determinantMat1 = (*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2];
				float determinantMat2 = (*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2];
				float determinantMat3 = (*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2];

				return 	  (*this)[0][0] * determinantMat1 
						- (*this)[1][0] * determinantMat2 
						+ (*this)[2][0] * determinantMat3;
			}


			float				foundDeterminantMat4		() const;
			float 				foundDeterminantMatX		() const; //recursive function for X square matrix


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
			inline float		getCofactor		(unsigned int i, unsigned int j) const
			{
				return pow(-1, i+j) * getMinor(i, j);
			}
				

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
			inline void		tranformCoMatToAdjointMat		()
			{
				assert (isSquare());
				transpose();
			}

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
	inline std::ostream& 	operator<<		(std::ostream& out, const Mat& mat)
	{
		std::cout.precision(3);
		for ( size_t i = 0; i < mat.get_nbLine(); i++ )
		{
			for ( size_t j = 0; j < mat.get_nbColumn(); j++ )
		{
			out << mat[i][j] << "	";
		}
		out << std::endl;
		}
		return out;
	}

};

#endif // _MATRIX_H
