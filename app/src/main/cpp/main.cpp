#include <android_native_app_glue.h>
#include <android/log.h>
#include "renderer/VulkanRenderer.hpp"
#include "renderer/GeometryGenerator.hpp"
#include "renderer/Math.hpp"
#include <chrono>

#define LOG_TAG "VulkanMain"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

struct AppState {
    engine::VulkanRenderer* renderer = nullptr;
    bool animating = false;
};

static void handle_cmd(struct android_app* app, int32_t cmd) {
    AppState* state = (AppState*)app->userData;
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            LOGI("APP_CMD_INIT_WINDOW received");
            if (app->window != nullptr) {
                LOGI("Window is valid, creating renderer...");
                state->renderer = new engine::VulkanRenderer(app);
                
                // Initialize scene
                std::vector<engine::Vertex> vertices;
                std::vector<uint32_t> indices;
                
                // Cube
                engine::GeometryGenerator::generateCube(vertices, indices);
                auto cubeMesh = std::make_shared<engine::Mesh>(
                    state->renderer->getDevice()->getLogicalDevice(),
                    state->renderer->getDevice()->getPhysicalDevice(),
                    vertices, indices);
                
                // Sphere
                engine::GeometryGenerator::generateSphere(0.5f, 32, 16, vertices, indices);
                auto sphereMesh = std::make_shared<engine::Mesh>(
                    state->renderer->getDevice()->getLogicalDevice(),
                    state->renderer->getDevice()->getPhysicalDevice(),
                    vertices, indices);

                // Cone
                engine::GeometryGenerator::generateCone(0.5f, 1.0f, 32, vertices, indices);
                auto coneMesh = std::make_shared<engine::Mesh>(
                    state->renderer->getDevice()->getLogicalDevice(),
                    state->renderer->getDevice()->getPhysicalDevice(),
                    vertices, indices);

                // Add to renderer (this would be done by the RenderingSystem in ECS)
                // Left-Back
                engine::Matrix4x4 t1 = engine::Matrix4x4::translation(-2.0f, 0.0f, 8.0f);
                state->renderer->addMesh(cubeMesh, t1.m);

                // Center-Front
                engine::Matrix4x4 t2 = engine::Matrix4x4::translation(0.0f, 0.0f, 5.0f);
                state->renderer->addMesh(sphereMesh, t2.m);

                // Right-Back
                engine::Matrix4x4 t3 = engine::Matrix4x4::translation(2.0f, 0.0f, 8.0f);
                state->renderer->addMesh(coneMesh, t3.m);

                // Enable Panini Projection (FOV 100, D=1.0)
                state->renderer->setPanini(100.0f, 1.0f);

                state->animating = true;
            }
            break;
        case APP_CMD_TERM_WINDOW:
            if (state->renderer) {
                delete state->renderer;
                state->renderer = nullptr;
            }
            state->animating = false;
            break;
    }
}

void android_main(struct android_app* app) {
    LOGI("------------------------------------------------");
    LOGI("Android Main Started");
    LOGI("------------------------------------------------");
    
    try {
        AppState state;
        app->userData = &state;
        app->onAppCmd = handle_cmd;

        auto lastTime = std::chrono::high_resolution_clock::now();
        int frameCount = 0;

        while (true) {
            int ident;
            int events;
            struct android_poll_source* source;

            while ((ident = ALooper_pollAll(state.animating ? 0 : -1, nullptr, &events, (void**)&source)) >= 0) {
                if (source != nullptr) {
                    source->process(app, source);
                }
                if (app->destroyRequested != 0) {
                    LOGI("Destroy requested, exiting...");
                    return;
                }
            }

            if (state.animating && state.renderer) {
                state.renderer->render();
                
                // FPS Counter
                frameCount++;
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
                if (duration >= 1000) {
                    LOGI("Benchmark: %d FPS", frameCount);
                    frameCount = 0;
                    lastTime = currentTime;
                }
            }
        }
    } catch (const std::exception& e) {
        LOGE("FATAL ERROR in android_main: %s", e.what());
    } catch (...) {
        LOGE("FATAL ERROR in android_main: Unknown exception");
    }
}
