#include "PaniniProjection.hpp"
#include <cmath>

namespace engine {

PaniniProjection::PaniniProjection(float fovDegrees, float aspect, float d)
    : m_fov(fovDegrees), m_aspect(aspect), m_d(d) {}

Matrix4x4 PaniniProjection::getMatrix(float near, float far) const {
    // For now, we return a wide-perspective matrix.
    // Real Panini is often implemented in shaders, 
    // so this class acts as a parameter container and matrix generator.
    return Matrix4x4::perspective(m_fov * (3.14159f / 180.0f), m_aspect, near, far);
}

} // namespace engine
