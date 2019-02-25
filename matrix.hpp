//
//  matrix.hpp
//  
//
//  Created by Мой Господин on 25/02/2019.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <time.h>

namespace matrix
{
	class Matrix
	{
		public:
			//constructors
			Matrix(long int);
			Matrix(const Matrix&);

			//operators
			bool operator==(const Matrix& _matrix) const;
			Matrix & operator=(const Matrix& matrix);
			std::vector<long int>& operator[](const long int number);
			//need in = overload
			const std::vector<long int>& operator[](const long int number) const;
			friend std::istream& operator >>(std::istream& input, Matrix& matrix);	
			friend std::ostream& operator << (std::ostream& output, Matrix& matrix);
			//gets
			long int getsize() const;

			long int get_determinant();
			Matrix get_minor(long int row, long int column) const;
		private:
			long int size;
			std::vector<std::vector<long int> > matrix;
	};
	long int computing_determinant(const Matrix& _matrix);
}
#endif /* matrix_hpp */
