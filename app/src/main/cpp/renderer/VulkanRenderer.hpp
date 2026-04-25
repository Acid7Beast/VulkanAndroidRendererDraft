#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <android_native_app_glue.h>

#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanDepthBuffer.hpp"
#include "Mesh.hpp"
#include "PaniniProjection.hpp"

namespace engine {

class VulkanRenderer {
public:
    VulkanRenderer(android_app* app);
    ~VulkanRenderer();

    void render();
    void addMesh(std::shared_ptr<Mesh> mesh, const float* transform);
    void setPanini(float fov, float d);
    
    VulkanDevice* getDevice() const { return m_device.get(); }

private:
    android_app* m_app;
    VkInstance m_instance;
    VkSurfaceKHR m_surface;
    
    std::unique_ptr<VulkanDevice> m_device;
    std::unique_ptr<VulkanSwapchain> m_swapchain;
    std::unique_ptr<VulkanPipeline> m_pipeline;
    std::unique_ptr<VulkanDepthBuffer> m_depthBuffer;
    
    std::vector<VkFramebuffer> m_framebuffers;
    VkCommandPool m_commandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;

    static const int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkSemaphore> m_imageAvailableSemaphores;
    std::vector<VkSemaphore> m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;
    uint32_t m_currentFrame = 0;

    struct RenderItem {
        std::shared_ptr<Mesh> mesh;
        float transform[16];
    };
    std::vector<RenderItem> m_renderItems;
    std::unique_ptr<PaniniProjection> m_panini;

    bool m_initialized = false;

    void initVulkan();
    void createSurface();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();
};

} // namespace engine
