#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <tuple>
#include <string>
#include<chrono>
#include "gtest/gtest.h"
#include "matrix.hpp"
using namespace matrix;

std::vector<std::string> minorfiles = {"/Users/danilafurenc/AllMyProjects/spaceforprojects/C++ Projects/parallel_matrix_determinant/minor_1.txt", "/Users/danilafurenc/AllMyProjects/spaceforprojects/C++ Projects/parallel_matrix_determinant/minor_2.txt"};
std::vector<std::string> determfiles = {"/Users/danilafurenc/AllMyProjects/spaceforprojects/C++ Projects/parallel_matrix_determinant/determinant_1.txt","/Users/danilafurenc/AllMyProjects/spaceforprojects/C++ Projects/parallel_matrix_determinant/determinant_2.txt"};
int testnumber = 0;
int not_paralel_time = 0;
std::tuple <Matrix, Matrix> read_info_from_file(std::string name_of_file)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    std::ifstream input(name_of_file);
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
    Matrix helpminor(matrixsize - 1);

    input >> matrix >> row >> columns >> minor;
    testnumber++;
    start = std::chrono::high_resolution_clock::now();
    helpminor = matrix.get_minor(row, columns);
    stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = (stop-start); 
    std::cout<<std::endl<<"Not parallel done!"<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
    return std::make_tuple(helpminor, minor);
    // return std::make_tuple(matrix, row, columns, minor);
}
std::tuple <int, int, int> read_info1_from_file(std::string name_of_file)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    std::ifstream input(name_of_file);
    if (!input) 
    {
        std::cerr << "File did not open!"<<std::endl;
    }
    int matrixsize;
    int det;
    input >> matrixsize >>det;
    // std::cout<<"_____________"<<std::endl;
    // std::cout<<matrixsize<<" "<<det;
    Matrix matrix(matrixsize);
    input >> matrix;
    testnumber++;
    int determ_not_paralel;
    start = std::chrono::high_resolution_clock::now();
    determ_not_paralel = matrix.get_determinant();
    stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = (stop-start); 
    std::cout<<std::endl<<"Not parallel done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;

    start = std::chrono::high_resolution_clock::now();
    long int determ_paralel = computing_paralel_determinant(matrix);
    stop = std::chrono::high_resolution_clock::now();
    diff = (stop-start); 
    std::cout<<std::endl<<"Parallel done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
    // std::cout<<"Paralel"<<determ_paralel;
    // std::cout<<matrix;
    return std::make_tuple(determ_not_paralel, det, determ_paralel);
}
TEST(TestsMatrix,TestMinor_1)
{
    auto firsttest = read_info_from_file(minorfiles[testnumber]);
    // std::cout<<std::get<0> (firsttest);
    // std::get<2> (firsttest);
    // std::get<3> (firsttest);
    // std::cout<<std::get<3> (firsttest);
    // std::cout<<(std::get<0> (firsttest)).get_minor(std::get<1> (firsttest), std::get<2> (firsttest));
     ASSERT_EQ(std::get<0> (firsttest) == std::get<1> (firsttest),true);
    // ASSERT_EQ((std::get<0> (firsttest)).get_minor(std::get<1> (firsttest), std::get<2> (firsttest)) == std::get<3> (firsttest),true);
}
TEST(TestsMatrix,TestMinor_2)
{
    auto secondtest = read_info_from_file(minorfiles[testnumber]);
    ASSERT_EQ(std::get<0> (secondtest) == std::get<1> (secondtest),true);
    // ASSERT_EQ((std::get<0> (secondtest)).get_minor(std::get<1> (secondtest), std::get<2> (secondtest)) == std::get<3> (secondtest),true);
    testnumber = 0;
}
TEST(TestsMatrix,TestDet_1)
{
    auto firsttest = read_info1_from_file(determfiles[testnumber]);
    ASSERT_EQ(std::get<0> (firsttest) == std::get<1> (firsttest),true);
    ASSERT_EQ(std::get<1> (firsttest) == std::get<2> (firsttest),true);
    // std::cout<<computing_determinant(std::get<0>(firsttest));
    // ASSERT_EQ(std::get<0>(firsttest).get_determinant(), std::get<1> (firsttest));

}

 //g++ --std=c++11 -stdlib=libc++ matrix_main.cpp matrix.cpp  -lgtest -lpthread -o MatrixTest
//valgrind   --leak-check=full --leak-resolution=high ./MatrixTest

