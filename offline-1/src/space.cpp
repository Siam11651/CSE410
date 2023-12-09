#include <space.hpp>
#include <cmath>
#include <array>

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

quaternion::quaternion()
{
    m_w = 1.0f;
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
}

quaternion::quaternion(const vector3 &euler_rotation)
{
    const float &ex = euler_rotation.const_x();
    const float &ey = euler_rotation.const_y();
    const float &ez = euler_rotation.const_z();
    quaternion qx(std::cos(ex / 2.0f), std::sin(ex / 2.0f), 0.0f, 0.0f);
    quaternion qy(std::cos(ey / 2.0f), 0.0f, std::sin(ey / 2.0f), 0.0f);
    quaternion qz(std::cos(ez / 2.0f), 0.0f, 0.0f, std::sin(ez / 2.0f));
    quaternion new_q = qz * qy * qx;
    m_w = new_q.m_w;
    m_x = new_q.m_x;
    m_y = new_q.m_y;
    m_z = new_q.m_z;
}

quaternion::quaternion(const vector3 &axis, const float &angle)
{
    m_w = std::cos(angle / 2.0f);
    m_x = axis.const_x() * std::sin(angle / 2.0f);
    m_y = axis.const_y() * std::sin(angle / 2.0f);
    m_z = axis.const_z() * std::sin(angle / 2.0f);
}

quaternion::quaternion(const float &w, const float &x, const float &y, const float &z)
{
    m_w = w;
    m_x = x;
    m_y = y;
    m_z = z;
}

vector3 quaternion::get_axis() const
{
    const float angle = std::acos(m_w);

    if(angle == 0.0f)
    {
        return vector3(0.0f, 0.0f, 0.0f);
    }

    const float new_x = m_x / std::sin(angle);
    const float new_y = m_y / std::sin(angle);
    const float new_z = m_z / std::sin(angle);

    return vector3(new_x, new_y, new_z);
}

float quaternion::get_angle() const
{
    return std::acos(m_w) * 2.0f;
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

vector3 quaternion::get_post_rotation(const vector3 &source) const
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

transform::transform()
{
    m_scale = vector3(1.0f, 1.0f, 1.0f);
}

transform::transform(const vector3 &position)
{
    m_position = position;
    m_scale = vector3(1.0f, 1.0f, 1.0f);
}

transform::transform(const vector3 &position, const vector3 &euler_rotation)
{
    m_position = position;
    m_rotation = quaternion(euler_rotation);
    m_scale = vector3(1.0f, 1.0f, 1.0f);
}

transform::transform(const vector3 &position, const vector3 &euler_rotation, const vector3 &scale)
{
    m_position = position;
    m_rotation = quaternion(euler_rotation);
    m_scale = scale;
}

vector3 &transform::position()
{
    return m_position;
}

quaternion &transform::rotation()
{
    return m_rotation;
}

vector3 &transform::scale()
{
    return m_scale;
}

const vector3 &transform::const_position() const
{
    return m_position;
}

const quaternion &transform::const_rotation() const
{
    return m_rotation;
}

const vector3 &transform::const_scale() const
{
    return m_scale;
}

vector3 transform::get_forward() const
{
    return m_rotation.get_post_rotation(vector3(0.0f, 0.0f, 1.0f));
}

vector3 transform::get_up() const
{
    return m_rotation.get_post_rotation(vector3(0.0f, 1.0f, 0.0f));
}

vector3 transform::get_right() const
{
    return m_rotation.get_post_rotation(vector3(1.0f, 0.0f, 0.0f));
}