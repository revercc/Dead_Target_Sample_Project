//
// Created by reverccqin on 2023-11-10.
//

#ifndef DEAD_TARGET_SAMPLE_PROJECT_VECTOR4_H
#define DEAD_TARGET_SAMPLE_PROJECT_VECTOR4_H

#endif //DEAD_TARGET_SAMPLE_PROJECT_VECTOR4_H
#include "Matrix4x4.h"
class Vector4 {
public:
    float x;
    float y;
    float z;
    float w;
    Vector4()
            : x(0)
            , y(0)
            , z(0)
            , w(0)
    {
    }
    Vector4(float x1, float y1, float z1, float w1)
            : x(x1)
            , y(y1)
            , z(z1)
            , w(w1)
    {
    }

    // 矩阵乘法
    Vector4 operator*(const Matrix4x4& matrix) const {
        Vector4 result;

        // 实现矩阵与向量相乘的逻辑
        result.x = x * matrix.elements[0][0] + y * matrix.elements[1][0] + z * matrix.elements[2][0] + w * matrix.elements[3][0];
        result.y = x * matrix.elements[0][1] + y * matrix.elements[1][1] + z * matrix.elements[2][1] + w * matrix.elements[3][1];
        result.z = x * matrix.elements[0][2] + y * matrix.elements[1][2] + z * matrix.elements[2][2] + w * matrix.elements[3][2];
        result.w = x * matrix.elements[0][3] + y * matrix.elements[1][3] + z * matrix.elements[2][3] + w * matrix.elements[3][3];

        return result;
    }



    Vector4(const Vector4& v);
    ~Vector4();
};
Vector4::Vector4(const Vector4& v)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(v.w)
{
}
Vector4::~Vector4() {}