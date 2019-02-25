//
//  matrix.cpp
//  
//
//  Created by Мой Господин on 25/02/2019.
//

#include "matrix.hpp"
namespace matrix
{
	//constructors
	Matrix::Matrix(long int size)
	{
		this->size = size;
		this->matrix.assign(size, std::vector<long int>(size, 0));
	}
	Matrix::Matrix(const Matrix& matrix)
	{
		this->size = matrix.size;
		this->matrix = this->matrix;
	}

	//operators
	bool Matrix::operator==(const Matrix& _matrix) const
	{	
		return _matrix.matrix == matrix;
	}
	Matrix & Matrix::operator=(const Matrix& matrix)
	{
		if (matrix.size != this->size) 
		{
			std::cerr << "Invalid size in '=' operator";
		}
		if (&matrix == this)
		{
			return *this;
		}
		// this->size = matrix.size;

		for (int i = 0; i < this->size; ++i)
		{
			this->matrix[i] = matrix[i];
		}
		return *this;
	}
	std::vector<long int>& Matrix::operator[](const long int number) 
	{
		return matrix[number];
	}
	//need in = overload
	const std::vector<long int>& Matrix::operator[](const long int number) const
	{
		return matrix[number];
	}
	std::istream& operator >>(std::istream& input, Matrix& matrix)
	{
		for (int i = 0; i < matrix.size; ++i)
		{
			for (int j = 0; j < matrix.size; ++j)
			{
				input >> matrix[i][j];
			}
		}
		return input;
	}
	std::ostream& operator << (std::ostream& output, Matrix& matrix)
	{
		for (int i = 0; i < matrix.size; ++i)
		{
			for (int j = 0; j < matrix.size; ++j)
			{
				output <<  matrix[i][j] << " ";
			}
			output << std::endl;
		}
		return output;
	}

	//gets
	long int Matrix::getsize() const
	{
		return this->size;
	}

	long int Matrix::get_determinant()
	{
		return computing_determinant(*this);
	}

	Matrix Matrix::get_minor(long int row, long int column) const
	{
		Matrix newminor (this->size - 1);

		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				newminor[i][j] = this->matrix[i][j];
			}
		}

		for (int i = 0; i < row; ++i)
		{
			for (int j = column + 1; j < size; ++j)
			{
				newminor[i][j - 1] = this->matrix[i][j];
			}
		}

		for (int i = row + 1; i < size; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				newminor[i - 1][j] = this->matrix[i][j];
			}
		}

		for (int i = row + 1; i < size; ++i)
		{
			for (int j = column + 1; j < size; ++j)
			{
				newminor[i - 1][j - 1] = this->matrix[i][j];
			}
		}

		return newminor;
	}
	long int computing_determinant(const Matrix& _matrix)
	{
		long int determinant = 0;
		int sign = 1;
		for (int i = 0; i < _matrix.getsize(); ++i)
		{
			determinant+=computing_determinant(_matrix.get_minor(0,i)) * sign;
			sign*=(-1);
		}

		return determinant;
	}
}