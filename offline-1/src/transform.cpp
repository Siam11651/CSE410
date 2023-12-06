#include <transform.hpp>
#include <cmath>

const float transform::DEG2RAD = (float)M_PI / 180.0f;

transform::transform()
{

}

transform::transform(const vector3 &position, const vector3 &euler_rotation)
{
    m_position = position;
    m_euler_rotation = euler_rotation;
}

vector3 &transform::position()
{
    return m_position;
}

vector3 &transform::euler_rotation()
{
    return m_euler_rotation;
}

const vector3 &transform::const_position() const
{
    return m_position;
}

const vector3 &transform::const_euler_rotation() const
{
    return m_euler_rotation;
}

vector3 transform::get_forward() const
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 1.0f;
    float plane_magnitude = 1.0f;
    z = std::cos(m_euler_rotation.const_x()) * plane_magnitude;
    y = std::sin(m_euler_rotation.const_x()) * plane_magnitude;
    plane_magnitude = z;
    z = std::cos(m_euler_rotation.const_y()) * plane_magnitude;
    x = -std::sin(m_euler_rotation.const_y()) * plane_magnitude;
    plane_magnitude = std::sqrt(x * x + y * y);
    x = std::cos(m_euler_rotation.const_z()) * plane_magnitude;
    y = std::sin(m_euler_rotation.const_z()) * plane_magnitude;

    return vector3(x, y, z);
}

vector3 transform::get_right() const
{
    float x = 1.0f;
    float y = 0.0f;
    float z = 0.0f;
    float plane_magnitude = 1.0f;
    z = std::sin(m_euler_rotation.const_y()) * plane_magnitude;
    x = std::cos(m_euler_rotation.const_y()) * plane_magnitude;
    plane_magnitude = std::sqrt(x * x + y * y);
    x = std::cos(m_euler_rotation.const_z()) * plane_magnitude;
    y = std::sin(m_euler_rotation.const_z()) * plane_magnitude;

    return vector3(x, y, z);
}