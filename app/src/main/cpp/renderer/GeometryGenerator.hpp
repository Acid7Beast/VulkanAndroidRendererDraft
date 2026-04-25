#pragma once

#include "Mesh.hpp"
#include <vector>

namespace engine {

class GeometryGenerator {
public:
    static void generateCube(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    static void generateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    static void generateCone(float radius, float height, uint32_t sliceCount, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
};

} // namespace engine
