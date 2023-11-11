//
// Created by reverccqin on 2023-11-10.
//

#ifndef DEAD_TARGET_SAMPLE_PROJECT_MATRIX4X4_H
#define DEAD_TARGET_SAMPLE_PROJECT_MATRIX4X4_H

#endif //DEAD_TARGET_SAMPLE_PROJECT_MATRIX4X4_H

class Matrix4x4 {
public:
    float elements[4][4];

    // 构造函数
    Matrix4x4() {
        // 初始化为单位矩阵
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                elements[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    // 矩阵乘法
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.elements[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    result.elements[i][j] += elements[i][k] * other.elements[k][j];
                }
            }
        }

        return result;
    }
};
