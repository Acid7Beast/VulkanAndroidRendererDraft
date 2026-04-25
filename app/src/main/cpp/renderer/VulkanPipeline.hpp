#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <android/asset_manager.h>
#include "VulkanDevice.hpp"

namespace engine {

class VulkanPipeline {
public:
    VulkanPipeline(VulkanDevice* device, VkFormat colorFormat, VkFormat depthFormat, AAssetManager* assetManager);
    ~VulkanPipeline();

    VkPipeline getHandle() const { return m_graphicsPipeline; }
    VkPipelineLayout getLayout() const { return m_pipelineLayout; }
    VkRenderPass getRenderPass() const { return m_renderPass; }

private:
    VulkanDevice* m_device;
    VkRenderPass m_renderPass;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;

    void createRenderPass(VkFormat colorFormat, VkFormat depthFormat);
    void createGraphicsPipeline(AAssetManager* assetManager);
    VkShaderModule createShaderModule(const std::vector<uint8_t>& code);
    std::vector<uint8_t> readAsset(AAssetManager* assetManager, const std::string& filename);
};

} // namespace engine
