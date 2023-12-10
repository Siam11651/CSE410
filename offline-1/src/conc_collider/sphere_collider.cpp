#include <conc_collider/sphere_collider.hpp>
#include <conc_collider/box_collider.hpp>
#include <object.hpp>

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

collission_event *sphere_collider::create_collission_event(collider *other_collider)
{
    if(dynamic_cast<box_collider *>(other_collider))
    {
        box_collider *conc_collider = dynamic_cast<box_collider *>(other_collider);
        const transform &parent_object_transform =
            conc_collider->get_parent_object()->const_object_transform();
        const float &size_x = conc_collider->const_dimensions().const_x();
        const float &size_y = conc_collider->const_dimensions().const_y();
        const float &size_z = conc_collider->const_dimensions().const_z();
        // vector3 top_left_front()
    }
}