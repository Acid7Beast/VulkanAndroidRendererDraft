#pragma once

#include "Math.hpp"

namespace engine {

/**
 * Panini Projection helper.
 * Designed to handle ultra-wide FOV without extreme edge distortion.
 */
class PaniniProjection {
public:
    PaniniProjection(float fovDegrees, float aspect, float d = 1.0f);

    Matrix4x4 getMatrix(float near, float far) const;
    
    void setFOV(float fovDegrees) { m_fov = fovDegrees; }
    void setD(float d) { m_d = d; }

private:
    float m_fov;
    float m_aspect;
    float m_d; // Panini parameter: 0 = perspective, 1 = panini
};

} // namespace engine
