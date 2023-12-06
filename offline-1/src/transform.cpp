#include <transform.hpp>
#include <cmath>

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

vector3 transform::get_forward() const
{
    float x =  std::cos(((float)M_PI / 180.0f) * m_euler_rotation.get_x()) * std::sin(((float)M_PI / 180.0f) * m_euler_rotation.get_y());
    float y = -std::sin(((float)M_PI / 180.0f) * m_euler_rotation.get_x());
    float z =  std::cos(((float)M_PI / 180.0f) * m_euler_rotation.get_x()) * std::cos(((float)M_PI / 180.0f) * m_euler_rotation.get_y());

    return vector3(x, y, z);
}