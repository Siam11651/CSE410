#include <conc_collider/sphere_collider.hpp>
#include <conc_collider/box_collider.hpp>
#include <conc_mesh/box_mesh.hpp>
#include <object.hpp>
#include <time.hpp>
#include <functional>
#include <cmath>
#include <iostream>

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
    const object *this_object = get_parent_object();
    rigidbody *this_rigidbody = this_object->get_rigidbody();
    vector3 &this_velocity = this_rigidbody->velocity();
    const vector3 &center = this_object->const_object_transform().
        const_position();

    auto inverse_transform = [](const transform &_transform, const vector3 &_point) -> vector3
    {
        vector3 to_return = _point;
        to_return.x() -= _transform.const_position().const_x();
        to_return.y() -= _transform.const_position().const_y();
        to_return.z() -= _transform.const_position().const_z();
        to_return = (-_transform.const_rotation()).get_rotated_vector(to_return);
        to_return.x() /= _transform.const_scale().const_x();
        to_return.y() /= _transform.const_scale().const_y();
        to_return.z() /= _transform.const_scale().const_z();

        return to_return;
    };

    if(dynamic_cast<box_collider *>(other_collider))
    {
        box_collider *other_box_collider = (box_collider *)other_collider;
        object* box_object = other_box_collider->get_parent_object();
        transform box_transform = box_object->const_object_transform();
        const vector3 inv_og = inverse_transform(box_transform, vector3());
        const vector3 inv_center = inverse_transform(box_transform, center);
        const vector3 inv_velocity = inverse_transform(box_transform, this_velocity) - inv_og;
        const float x_limit = other_box_collider->const_dimensions().const_x() / 2.0f;
        const float y_limit = other_box_collider->const_dimensions().const_y() / 2.0f;
        const float z_limit = other_box_collider->const_dimensions().const_z() / 2.0f;
        float p = (z_limit - inv_center.const_z()) / inv_velocity.const_z();
    }

    return nullptr;
}