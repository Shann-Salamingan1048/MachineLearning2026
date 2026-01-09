#include "Starting.h"
#include "Matrices.h"
#include "Vectors.h"
int main()
{
    //Start::Run();
    LinAlg::V1u32 s1{2};
    LinAlg::V1u32 s2{3};
    LinAlg::V1u32 s3 = s1 + s2;
    LinAlg::V1u32 s4{4};
    s4 += s3;
    printVec1(s3);
    printVec1(s4);
    LinAlg::Mat2u8 mat1{2};
    printMatrix(mat1);
    LinAlg::Mat3f mat2{1.0222};
    LinAlg::Mat3f mat3{1.333};
    LinAlg::Mat3f mat4 = mat2 + mat3;
    LinAlg::Mat3f mat5 = mat2 - mat3;
    printMatrix(mat2);
    printMatrix(mat4);
    printMatrix(mat5);
    mat5 -= mat2;
    printMatrix(mat5);
    mat5 *= -1.0;
    printMatrix(mat5);

}