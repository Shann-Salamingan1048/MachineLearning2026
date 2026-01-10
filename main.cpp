#include "Starting.h"
#include "Matrices.h"
#include "Vectors.h"
int main()
{
    //Start::Run();
    LinAlg::V2d v1{1,2};
    LinAlg::V2d v2{1,2};
    v1 += v2;
    v1 -= v2;
    v1 *= v2;
    printVector(v1);
    v1 += 1;
    v1 -= 1;
    v1 *= 1;
    printVector(v1);
    LinAlg::Mat2d mat1{{1,2},{3,4}};
    LinAlg::Mat2d mat2{{5,6},{7,8}};
    mat1 += mat2;
    mat1 -= mat2;
    mat1 -= mat2;
    printMatrix(mat1);
    LinAlg::Mat5d mat3{2};
    LinAlg::Mat5d mat4{3};
    mat3 += mat4;
    mat3 += mat4;
    mat3 += mat4;
    mat3 *= 5;
    printMatrix(mat3);
    LinAlg::V10d v3{5.2, 10.2};
    printVector(v3);
}