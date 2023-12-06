#include <transform.hpp>
#include <cmath>

const float transform::DEG2RAD = (float)M_PI / 180.0f;

transform::transform()
{

}

transform::transform(const vector3 &position, const vector3 &euler_rotation)
{
    m_position = position;
    const float &ex = euler_rotation.const_x();
    const float &ey = euler_rotation.const_y();
    const float &ez = euler_rotation.const_z();
    quaternion qx(std::cos(ex / 2.0f), std::sin(ex / 2.0f), 0.0f, 0.0f);
    quaternion qy(std::cos(ey / 2.0f), 0.0f, std::sin(ey / 2.0f), 0.0f);
    quaternion qz(std::cos(ez / 2.0f), 0.0f, 0.0f, std::sin(ez / 2.0f));
    m_quaternion = qz * qy * qx;
}

vector3 &transform::position()
{
    return m_position;
}

const vector3 &transform::const_position() const
{
    return m_position;
}

vector3 transform::get_forward() const
{
    return m_quaternion.rotate(vector3(0.0f, 0.0f, 1.0f));
}

vector3 transform::get_up() const
{
    return m_quaternion.rotate(vector3(0.0f, 1.0f, 0.0f));
}

vector3 transform::get_right() const
{
    return m_quaternion.rotate(vector3(1.0f, 0.0f, 0.0f));
}