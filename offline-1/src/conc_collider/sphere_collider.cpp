#include <conc_collider/sphere_collider.hpp>

sphere_collider::sphere_collider(const float &radius)
{
    m_radius = radius;
}

float &sphere_collider::radius()
{
    return m_radius;
}

const float &sphere_collider::const_radius() const
{
    return m_radius;
}