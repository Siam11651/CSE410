#include <conc_collider/box_collider.hpp>

box_collider::box_collider(const vector3 &dimensions)
{
    m_dimensions = dimensions;
}

vector3 &box_collider::dimensions()
{
    return m_dimensions;
}

const vector3 &box_collider::const_dimensions() const
{
    return m_dimensions;
}

collission_event *box_collider::create_collission_event(collider *other_collider)
{

}