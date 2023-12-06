#include <quaternion.hpp>
#include <cmath>
#include <array>

quaternion::quaternion()
{
    m_w = 1.0f;
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
}

quaternion::quaternion(const float &w, const float &x, const float &y, const float &z)
{
    m_w = w;
    m_x = x;
    m_y = y;
    m_z = z;
}

float &quaternion::w()
{
    return m_w;
}

float &quaternion::x()
{
    return m_x;
}

float &quaternion::y()
{
    return m_y;
}

float &quaternion::z()
{
    return m_z;
}

const float &quaternion::const_w() const
{
    return m_w;
}

const float &quaternion::const_x() const
{
    return m_x;
}

const float &quaternion::const_y() const
{
    return m_y;
}

const float &quaternion::const_z() const
{
    return m_z;
}

vector3 quaternion::rotate(const vector3 &source) const
{
    std::array<std::array<float, 3>, 3> matrix
    {
        std::array<float, 3>
        {
            1.0f - 2.0f * (m_y * m_y + m_z * m_z),
            2.0f * (m_x * m_y - m_w * m_z),
            2.0f * (m_x * m_z + m_w * m_y)
        },
        std::array<float, 3>
        {
            2.0f * (m_x * m_y + m_w * m_z),
            1.0f - 2.0f * (m_x * m_x + m_z * m_z),
            2.0f * (m_y * m_z - m_w * m_x)
        },
        std::array<float, 3>
        {
            2.0f * (m_x * m_z - m_w * m_y),
            2.0f * (m_y * m_z + m_w * m_x),
            1.0f - 2.0f * (m_x * m_x + m_y * m_y)
        }
    };

    const float &sx = source.const_x();
    const float &sy = source.const_y();
    const float &sz = source.const_z();

    return vector3(sx * matrix[0][0] + sy * matrix[0][1] + sz * matrix[0][2],
        sx * matrix[1][0] + sy * matrix[1][1] + sz * matrix[1][2],
        sx * matrix[2][0] + sy * matrix[2][1] + sz * matrix[2][2]);
}

quaternion quaternion::operator * (const quaternion &other) const
{
    const quaternion &q1 = *this;
    const quaternion &q2 = other;
    float new_w = q1.const_w() * q2.const_w() - q1.const_x() * q2.const_x()
        - q1.const_y() * q2.const_y() - q1.const_z() * q2.const_z();
    float new_x = q1.const_w() * q2.const_x() + q1.const_x() * q2.const_w()
        + q1.const_y() * q2.const_z() - q1.const_z() * q2.const_y();
    float new_y = q1.const_w() * q2.const_y() - q1.const_x() * q2.const_z()
        + q1.const_y() * q2.const_w() + q1.const_z() * q2.const_x();
    float new_z = q1.const_w() * q2.const_z() + q1.const_x() * q2.const_y()
        - q1.const_y() * q2.const_x() + q1.const_z() * q2.const_w();

    return quaternion(new_w, new_x, new_y, new_z);
}