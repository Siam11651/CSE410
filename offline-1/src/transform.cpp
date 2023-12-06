#include <transform.hpp>
#include <cmath>

const float transform::DEG2RAD = (float)M_PI / 180.0f;

void transform::rotate(float &x, float &y, float &z) const
{
    z = std::cos(m_euler_rotation.const_x()) * z + std::sin(m_euler_rotation.const_x()) * y;
    y = std::sin(m_euler_rotation.const_x()) * z + std::cos(m_euler_rotation.const_x()) * y;
    x = std::cos(m_euler_rotation.const_y()) * x - std::sin(m_euler_rotation.const_y()) * z;
    z = -std::sin(m_euler_rotation.const_y()) * x + std::cos(m_euler_rotation.const_y()) * z;
    x = std::cos(m_euler_rotation.const_z()) * x + std::sin(m_euler_rotation.const_z()) * y;
    y = std::sin(m_euler_rotation.const_z()) * x + std::cos(m_euler_rotation.const_z()) * y;
}

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
    
    rotate(x, y, z);

    return vector3(x, y, z);
}

vector3 transform::get_up() const
{
    float x = 0.0f;
    float y = 1.0f;
    float z = 0.0f;
    
    rotate(x, y, z);

    return vector3(x, y, z);
}

vector3 transform::get_right() const
{
    float x = 1.0f;
    float y = 0.0f;
    float z = 0.0f;

    rotate(x, y, z);

    return vector3(x, y, z);
}