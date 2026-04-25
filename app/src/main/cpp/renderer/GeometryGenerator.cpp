#include "GeometryGenerator.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

namespace engine {

void GeometryGenerator::generateCube(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    vertices = {
        // Front face
        {{-0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0, 0, 1}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 1, 0}, {0, 0, 1}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {0, 0, 1}},
        {{-0.5f,  0.5f,  0.5f}, {1, 1, 0}, {0, 0, 1}},
        // Back face
        {{-0.5f, -0.5f, -0.5f}, {1, 0, 1}, {0, 0, -1}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 1}, {0, 0, -1}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0, 0, -1}},
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, 0}, {0, 0, -1}}
    };

    indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 0, 3, 3, 5, 4,
        1, 7, 6, 6, 2, 1,
        3, 2, 6, 6, 5, 3,
        4, 7, 1, 1, 0, 4
    };
}

void GeometryGenerator::generateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    vertices.clear();
    indices.clear();

    vertices.push_back({{0.0f, radius, 0.0f}, {0, 1, 0}, {0, 1, 0}});

    float phiStep = M_PI / stackCount;
    float thetaStep = 2.0f * M_PI / sliceCount;

    for (uint32_t i = 1; i <= stackCount - 1; ++i) {
        float phi = i * phiStep;
        for (uint32_t j = 0; j <= sliceCount; ++j) {
            float theta = j * thetaStep;

            Vertex v;
            v.pos[0] = radius * sinf(phi) * cosf(theta);
            v.pos[1] = radius * cosf(phi);
            v.pos[2] = radius * sinf(phi) * sinf(theta);

            v.color[0] = v.pos[0] / radius * 0.5f + 0.5f;
            v.color[1] = v.pos[1] / radius * 0.5f + 0.5f;
            v.color[2] = v.pos[2] / radius * 0.5f + 0.5f;

            float len = sqrtf(v.pos[0] * v.pos[0] + v.pos[1] * v.pos[1] + v.pos[2] * v.pos[2]);
            v.normal[0] = v.pos[0] / len;
            v.normal[1] = v.pos[1] / len;
            v.normal[2] = v.pos[2] / len;

            vertices.push_back(v);
        }
    }

    vertices.push_back({{0.0f, -radius, 0.0f}, {0, 0, 1}, {0, -1, 0}});

    for (uint32_t i = 1; i <= sliceCount; ++i) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    uint32_t baseIndex = 1;
    uint32_t ringVertexCount = sliceCount + 1;
    for (uint32_t i = 0; i < stackCount - 2; ++i) {
        for (uint32_t j = 0; j < sliceCount; ++j) {
            indices.push_back(baseIndex + i * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }

    uint32_t southPoleIndex = (uint32_t)vertices.size() - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (uint32_t i = 0; i < sliceCount; ++i) {
        indices.push_back(southPoleIndex);
        indices.push_back(baseIndex + i);
        indices.push_back(baseIndex + i + 1);
    }
}

void GeometryGenerator::generateCone(float radius, float height, uint32_t sliceCount, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    vertices.clear();
    indices.clear();

    float halfHeight = height * 0.5f;

    // Tip
    vertices.push_back({{0.0f, halfHeight, 0.0f}, {1, 1, 0}, {0, 1, 0}});

    float thetaStep = 2.0f * M_PI / sliceCount;
    for (uint32_t i = 0; i <= sliceCount; ++i) {
        float theta = i * thetaStep;

        Vertex v;
        v.pos[0] = radius * cosf(theta);
        v.pos[1] = -halfHeight;
        v.pos[2] = radius * sinf(theta);

        v.color[0] = 0.5f;
        v.color[1] = 0.5f;
        v.color[2] = 0.5f;

        v.normal[0] = v.pos[0] / radius;
        v.normal[1] = 0.0f;
        v.normal[2] = v.pos[2] / radius;

        vertices.push_back(v);
    }

    // Base center
    vertices.push_back({{0.0f, -halfHeight, 0.0f}, {0, 1, 1}, {0, -1, 0}});

    // Indices for sides
    for (uint32_t i = 1; i <= sliceCount; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    // Indices for base
    uint32_t centerIndex = (uint32_t)vertices.size() - 1;
    for (uint32_t i = 1; i <= sliceCount; ++i) {
        indices.push_back(centerIndex);
        indices.push_back(i + 1);
        indices.push_back(i);
    }
}

} // namespace engine
