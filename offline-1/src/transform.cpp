#include <transform.hpp>
#include <cmath>

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