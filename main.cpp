#include "Starting.h"
#include "Matrices.h"
#include "Vectors.h"
int main()
{
    //Start::Run();
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
    mat5 *= -3.0;
    printMatrix(mat5);
    roundOff(mat5, 3);
    printMatrix(mat5);


    LinAlg::Mat2f m2f{};
    printMatrix(m2f);


    LinAlg::V2f vf2{3,5};
    printVector(vf2);
    LinAlg::V2f vf3{6,7};
    vf3 -= vf2;
    printVector(vf3);
    LinAlg::V2f vf4 = vf3 + vf2;
    printVector(vf4);
    LinAlg::V3d v1{1.99999,3.199999,1.999222};
    roundOff(v1, 3);
    printVector(v1);
    v1 *= 2;
    printVector(v1);

}