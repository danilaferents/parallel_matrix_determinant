//
//  matrix.cpp
//  
//
//  Created by Мой Господин on 25/02/2019.
//
#include <future>
#include "matrix.hpp"
namespace matrix
{
	//constructors
	Matrix::Matrix(long int size)
	{
		this->size = size;
		this->matrix.assign(size, std::vector<long int>(size, 0));
	}
	Matrix::Matrix(const Matrix& _matrix)
	{
		this->size = _matrix.size;
		this->matrix = _matrix.matrix;
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
			return (*this);
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
	//gets
	long int Matrix::getsize() const
	{
		return this->size;
	}

	long int Matrix::get_determinant()
	{
		return computing_determinant(*this);
	}
	long int Matrix::getfirst() const
	{
		return (*this)[0][0];
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
		if (_matrix.getsize() == 0)
		{
			return 1;
		}
		long int determinant = 0;
		int sign = 1;
		for (int i = 0; i < _matrix.getsize(); ++i)
		{
			determinant+=_matrix[0][i] *  sign * computing_determinant(_matrix.get_minor(0,i));
			// std::cout<<deterdminant<<" -- ";
			sign*=(-1);
		}
		return determinant;
	}
	void computing(const Matrix& _matrix, int i, std::vector<int>& threaddets) //не важно что передается по ссылке, все равно произойдет копирование матрицы
	{
		threaddets[i] = computing_determinant(_matrix);
	}
	long int computing_paralel_determinant(const Matrix& _matrix)
	{
		std::vector<std::thread> threads;
		std::vector<int> threaddets(_matrix.getsize(), 0);
		long int determinant  = 0;
		int sign = 1;
		for (int i = 0; i < _matrix.getsize(); ++i)
		{
			threads.push_back(std::thread (computing,_matrix.get_minor(0,i), i, std::ref(threaddets)));
			// // determinant+=_matrix[0][i] * sign * det;
			// std::for_each(threads.begin(), threads.end(),
			// std::mem_fn(&std::thread::join));
			threads[i].join();

			// auto f1=std::async(std::launch::async,computing(),_matrix.get_minor(0,i));
			// determinant += f1.get()*_matrix[0][i] * sign;
		}
		for (int i = 0; i < _matrix.getsize(); ++i)
		{
			determinant+=_matrix[0][i] * threaddets[i] * sign;
			sign*=(-1);
		}
		return determinant;
	}
}