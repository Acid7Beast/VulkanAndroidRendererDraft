cmake_minimum_required(VERSION 3.22.1)
project("vulkan_renderer")

set(CMAKE_CXX_STANDARD 17)

# Main library
add_library(vulkan_renderer SHARED
    main.cpp
    renderer/VulkanRenderer.cpp
    renderer/VulkanDevice.cpp
    renderer/Mesh.cpp
    renderer/GeometryGenerator.cpp
    renderer/PaniniProjection.cpp
    renderer/VulkanSwapchain.cpp
    renderer/VulkanPipeline.cpp
    renderer/VulkanDepthBuffer.cpp
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

target_include_directories(vulkan_renderer PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue
)

# Find Vulkan
find_package(Vulkan REQUIRED)

if (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan NDK package not found! Cannot build renderer.")
endif()

message(STATUS "Vulkan version found: ${Vulkan_VERSION}")

# Link libraries
target_link_libraries(vulkan_renderer
    Vulkan::Vulkan
    android
    log
)
