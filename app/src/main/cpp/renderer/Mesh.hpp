#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Vertex.hpp"

namespace engine {

class Mesh {
public:
    Mesh(VkDevice device, VkPhysicalDevice physicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    ~Mesh();

    void draw(VkCommandBuffer commandBuffer);

private:
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkDevice m_device;
    VkPhysicalDevice m_physicalDevice;
    
    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;
    VkBuffer m_indexBuffer;
    VkDeviceMemory m_indexBufferMemory;

    uint32_t m_indexCount;
};

} // namespace engine
