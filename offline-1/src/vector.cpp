#include <vector.hpp>

vector3::vector3(const float &x, const float &y, const float &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

float vector3::get_x() const
{
    return m_x;
}

float vector3::get_y() const
{
    return m_y;
}

float vector3::get_z() const
{
    return m_z;
}