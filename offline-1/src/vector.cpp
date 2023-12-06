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

vector3 vector3::operator + (const vector3 &other) const
{
    return vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

vector3 &vector3::operator += (const vector3 &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;

    return *this;
}