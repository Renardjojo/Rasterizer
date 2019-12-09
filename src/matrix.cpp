#include <cassert>
#include <utility>
#include <cmath>

#include "matrix.hpp"

using namespace std;
using namespace math;

Matrix&		Matrix::transpose		()
{
	Matrix mTemp(column_, line_);	
	
	for ( size_t i = 0; i < line_; i++)
	{
		for ( size_t j = 0; j < column_; j++)
		{
			mTemp[j][i] = (*this)[i][j];
		}
	}

	(*this) = mTemp;

	return *this;
}

bool	Matrix::isOrtho		() const
{
	assert (isSquare());

	Matrix mT = (*this); 	mT.transpose();
	const Matrix mI (line_);

	return mT * (*this) == mI; 
}

float		Matrix::getDeterminant		()
{
	assert (isSquare() || isEmpty());

	switch (line_)
	{
		case 1 :
			return foundDeterminantMat1();
		break;

		case 2 :
			return foundDeterminantMat2();
		break;

		case 3 :
			return foundDeterminantMat3();
		break;

		case 4 :
			return foundDeterminantMat4();
		break;

		default :
			return foundDeterminantMatX();
		break;
	}
}

Matrix	Matrix::getReverse		() const
{
	assert (isSquare() || isEmpty());

	if (isOrtho() == true)
	{
		return Matrix((*this)).transpose();
	}

	float determinant = foundDeterminantMatX();
	
	if (determinant == 0.f) //in two step for more perform
		return Matrix(0);

	Matrix reversedMatrix = getCoMatrix();
	reversedMatrix.tranformCoMatToAdjointMat();

	if (!reversedMatrix.adjointMatrixIsReversible()) //in two step for more perform
		return Matrix(0);

    for ( size_t i = 0; i < line_; i++ )
	{
        for ( size_t j = 0; j < column_; j++ )
		{
			 reversedMatrix[i][j] =  reversedMatrix[i][j] / determinant;
		}
	}

	return reversedMatrix;
}

bool	Matrix::reverse		()
{
	assert (isSquare() || isEmpty());

	Matrix reversedMatrix = getReverse();

	if (reversedMatrix.isEmpty())
	{
		return false;
	}

	(*this) = reversedMatrix;
	return true;
}

Matrix		Matrix::getSolvationNEquationOfNInknow		(const Matrix& eqCoef, const Matrix& eqRslt)
{
	assert(!eqCoef.isEmpty() && !eqRslt.isEmpty() && eqCoef.isSquare() && eqRslt.get_nbColumn() == 1);

	return eqCoef.getReverse() * eqRslt;
}

float		Matrix::foundDeterminantMat4		() const
{
	assert(line_ == 4);

	float determinantMat1 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3]; 
	float determinantMat2 = (*this)[1][2] * (*this)[3][3] - (*this)[3][2] * (*this)[1][3]; 
	float determinantMat3 = (*this)[1][2] * (*this)[2][3] - (*this)[2][2] * (*this)[1][3];
	float determinantMat4 = (*this)[0][2] * (*this)[3][3] - (*this)[3][2] * (*this)[0][3];
	float determinantMat5 = (*this)[0][2] * (*this)[2][3] - (*this)[2][2] * (*this)[0][3];
	float determinantMat6 = (*this)[0][2] * (*this)[1][3] - (*this)[1][2] * (*this)[0][3];


	float determinantMat2_1 =  	  (*this)[1][1] * determinantMat1 
								- (*this)[2][1] * determinantMat2 
								+ (*this)[3][1] * determinantMat3; 

	float determinantMat2_2 =  	  (*this)[0][1] * determinantMat1 
								- (*this)[2][1] * determinantMat4 
								+ (*this)[3][1] * determinantMat5; 

	float determinantMat2_3 =  	  (*this)[0][1] * determinantMat2 
								- (*this)[1][1] * determinantMat4 
								+ (*this)[3][1] * determinantMat6;

	float determinantMat2_4 =  	  (*this)[0][1] * determinantMat3 
								- (*this)[1][1] * determinantMat5 
								+ (*this)[2][1] * determinantMat6;

	return 	  (*this)[0][0] * determinantMat2_1
			- (*this)[1][0] * determinantMat2_2
			+ (*this)[2][0] * determinantMat2_3
			- (*this)[3][0] * determinantMat2_4;
}

float		Matrix::foundDeterminantMatX		() const
{
	float result = 0.f;

	for (unsigned int i = 0; i < column_; i++)
	{
		//found signe
		signed int signe = pow(-1, 0 + i);

		//found coef
		float coef = signe * (*this)[i][0];
	
		//create submatrix
		Matrix subMatrix(get_nbLine() - 1, get_nbColumn() - 1);

		//fill submatrix
		bool coefLineFound = false;

		for (unsigned int iSubMatrix = 0; iSubMatrix < get_nbLine() - 1; iSubMatrix++)
		{
			if (iSubMatrix == i)
				coefLineFound = true;

			for (unsigned int jSubMatrix = 0; jSubMatrix < get_nbColumn() - 1; jSubMatrix++)
			{ 
				subMatrix[iSubMatrix][jSubMatrix] = (*this)[iSubMatrix + coefLineFound][jSubMatrix + 1];
			}
		}

		//found determinant
		float determinant = subMatrix.getDeterminant();

		//found result
		result += coef * determinant;
	}

	return result;
}

float		Matrix::getMinor		(unsigned int i, unsigned int j) const
{
	assert (isSquare());

	Matrix subMatrix (line_ - 1, column_ - 1);

	//fill submatrix
	bool coefLineFound = false;
	bool coefRowFound = false;

	for (unsigned int iSubMatrix = 0; iSubMatrix < line_ - 1; iSubMatrix++)
	{
		if (iSubMatrix == i)
			coefLineFound = true;

		for (unsigned int jSubMatrix = 0; jSubMatrix < column_ - 1; jSubMatrix++)
		{
			if (jSubMatrix == j)
				coefRowFound = true;

			subMatrix[iSubMatrix][jSubMatrix] = (*this)	[iSubMatrix + coefLineFound]
														[jSubMatrix + coefRowFound];
		}
		coefRowFound = false;
	}


	return subMatrix.getDeterminant();
}

Matrix		Matrix::getCoMatrix		() const
{
	assert (isSquare());

	Matrix coMatrix (line_, column_);

    for ( unsigned int i = 0; i < line_; i++ )
	{
        for ( unsigned int j = 0; j < column_; j++ )
		{
			coMatrix[i][j] = getCofactor(i, j);
		}
	}
	
	return coMatrix;
}

bool		Matrix::adjointMatrixIsReversible		() const
{
	assert (isSquare());
	
    for ( unsigned int i = 0; i < line_; i++ )
	{
        for ( unsigned int j = 0; j < column_; j++ )
		{
			if ((*this)[i][j] == 0.f)
				return false;
		}
	}

	return true;
}