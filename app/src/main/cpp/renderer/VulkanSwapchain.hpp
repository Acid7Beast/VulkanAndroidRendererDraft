#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanDevice.hpp"

namespace engine {

class VulkanSwapchain {
public:
    VulkanSwapchain(VulkanDevice* device, VkSurfaceKHR surface, uint32_t width, uint32_t height);
    ~VulkanSwapchain();

    VkSwapchainKHR getHandle() const { return m_swapChain; }
    VkExtent2D getExtent() const { return m_extent; }
    VkFormat getImageFormat() const { return m_imageFormat; }
    const std::vector<VkImageView>& getImageViews() const { return m_imageViews; }

private:
    VulkanDevice* m_device;
    VkSwapchainKHR m_swapChain;
    VkFormat m_imageFormat;
    VkExtent2D m_extent;
    std::vector<VkImage> m_images;
    std::vector<VkImageView> m_imageViews;

    void createSwapChain(VkSurfaceKHR surface, uint32_t width, uint32_t height);
    void createImageViews();
};

} // namespace engine
