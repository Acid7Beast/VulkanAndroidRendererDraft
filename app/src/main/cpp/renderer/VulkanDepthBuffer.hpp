#pragma once

#include <vulkan/vulkan.h>
#include "VulkanDevice.hpp"

namespace engine {

class VulkanDepthBuffer {
public:
    VulkanDepthBuffer(VulkanDevice* device, uint32_t width, uint32_t height);
    ~VulkanDepthBuffer();

    VkImageView getView() const { return m_imageView; }
    VkFormat getFormat() const { return m_format; }

    static VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);

private:
    VulkanDevice* m_device;
    VkImage m_image;
    VkDeviceMemory m_memory;
    VkImageView m_imageView;
    VkFormat m_format;

    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

} // namespace engine
