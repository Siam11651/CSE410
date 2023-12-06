#include <vector.hpp>
#include <cmath>

vector3::vector3(const float &x, const float &y, const float &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

const float &vector3::const_x() const
{
    return m_x;
}

const float &vector3::const_y() const
{
    return m_y;
}

const float &vector3::const_z() const
{
    return m_z;
}

float vector3::get_magnitude() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

vector3 vector3::get_normalized() const
{
    float magnitude = get_magnitude();

    return vector3(m_x / magnitude, m_y / magnitude, m_z / magnitude);
}

bool vector3::operator == (const vector3 &other) const
{
    return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

bool vector3::operator != (const vector3 &other) const
{
    return !(m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
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

vector3 vector3::operator - (const vector3 &other) const
{
    return vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

vector3 &vector3::operator -= (const vector3 &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;

    return *this;
}

vector3 vector3::operator * (const float &value) const
{
    return vector3(m_x * value, m_y * value, m_z * value);
}