#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <tuple>
#include "gtest/gtest.h"
#include "matrix.hpp"
using namespace matrix;

// std::tuple <Matrix, int, int, Matrix> read_info_from_file()
// {
//     std::ifstream input("/Users/danilafurenc/AllMyProjects/spaceforprojects/C++ Projects/parallel_matrix_determinant/minor_1.txt");
//     if (!input) 
//     {
//         std::cerr << "File did not open!"<<std::endl;
//     }
//     int matrixsize;
//     int row;
//     int columns;

//     input >> matrixsize;
//     Matrix matrix(matrixsize);
//     Matrix minor(matrixsize - 1);

//     input >> matrix >> row >> columns >> minor;
//     return std::make_tuple(matrix, row, columns, minor);
// }
TEST(TestsMatrix,TestMinor1)
{
    std::ifstream input("/Users/danilafurenc/AllMyProjects/spaceforprojects/C++ Projects/parallel_matrix_determinant/minor_1.txt");
    if (!input) 
    {
        std::cerr << "File did not open!"<<std::endl;
    }
    int matrixsize;
    int row;
    int columns;

    input >> matrixsize;
    Matrix matrix(matrixsize);
    Matrix minor(matrixsize - 1);

    input >> matrix >> row >> columns >> minor;
    ASSERT_TRUE(matrix.get_minor(row, columns) == minor);
    // auto firsttest = read_info_from_file();
    // ASSERT_TRUE((std::get<0> (firsttest)).get_minor(std::get<1> (firsttest), std::get<2> (firsttest)) == std::get<3> (firsttest));
}
// TEST(TestsMatrix,TestDeterminant2)
// {

// }

 //g++ --std=c++11 -stdlib=libc++ matrix_main.cpp matrix.cpp  -lgtest -lpthread -o MatrixTest
//valgrind   --leak-check=full --leak-resolution=high ./MatrixTest

