#pragma once

#include <cmath>
#include <cstring>

namespace engine {

struct Matrix4x4 {
    float m[16];

    Matrix4x4() {
        memset(m, 0, sizeof(m));
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }

    static Matrix4x4 identity() {
        return Matrix4x4();
    }

    static Matrix4x4 translation(float x, float y, float z) {
        Matrix4x4 res;
        res.m[12] = x;
        res.m[13] = y;
        res.m[14] = z;
        return res;
    }

    static Matrix4x4 rotationY(float angle) {
        Matrix4x4 res;
        float s = sinf(angle);
        float c = cosf(angle);
        res.m[0] = c;
        res.m[2] = -s;
        res.m[8] = s;
        res.m[10] = c;
        return res;
    }

    static Matrix4x4 rotationX(float angle) {
        Matrix4x4 res;
        float s = sinf(angle);
        float c = cosf(angle);
        res.m[5] = c;
        res.m[6] = s;
        res.m[9] = -s;
        res.m[10] = c;
        return res;
    }

    static Matrix4x4 perspective(float fov, float aspect, float near, float far) {
        Matrix4x4 res;
        memset(res.m, 0, sizeof(res.m));
        float tanHalfFov = tanf(fov / 2.0f);
        res.m[0] = 1.0f / (aspect * tanHalfFov);
        res.m[5] = 1.0f / (tanHalfFov);
        res.m[10] = far / (far - near);
        res.m[11] = 1.0f;
        res.m[14] = -(far * near) / (far - near);
        return res;
    }

    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 res;
        for (int i = 0; i < 4; ++i) { // column
            for (int j = 0; j < 4; ++j) { // row
                res.m[i * 4 + j] = 0;
                for (int k = 0; k < 4; ++k) {
                    res.m[i * 4 + j] += m[k * 4 + j] * other.m[i * 4 + k];
                }
            }
        }
        return res;
    }
};

} // namespace engine
