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

    if(dynamic_cast<box_collider *>(other_collider))
    {
        box_collider *other_box_collider = (box_collider *)other_collider;
        object* box_object = other_box_collider->get_parent_object();
        transform box_transform = box_object->const_object_transform();
        vector3 closest_position = center;
        closest_position.x() -= box_transform.const_position().const_x();
        closest_position.y() -= box_transform.const_position().const_y();
        closest_position.z() -= box_transform.const_position().const_z();
        closest_position = (-box_transform.const_rotation()).get_rotated_vector(closest_position);
        closest_position.x() /= box_transform.const_scale().const_x();
        closest_position.y() /= box_transform.const_scale().const_y();
        closest_position.z() /= box_transform.const_scale().const_z();
        const float x_bound = other_box_collider->dimensions().const_x() / 2.0f;
        const float y_bound = other_box_collider->dimensions().const_y() / 2.0f;
        const float z_bound = other_box_collider->dimensions().const_z() / 2.0f;
        closest_position.x() = std::clamp(closest_position.x(), -x_bound, x_bound);
        closest_position.y() = std::clamp(closest_position.y(), -y_bound, y_bound);
        closest_position.z() = std::clamp(closest_position.z(), -z_bound, z_bound);
        closest_position.x() *= box_transform.const_scale().const_x();
        closest_position.y() *= box_transform.const_scale().const_y();
        closest_position.z() *= box_transform.const_scale().const_z();
        closest_position = box_transform.const_rotation().get_rotated_vector(closest_position);
        closest_position.x() += box_transform.const_position().const_x();
        closest_position.y() += box_transform.const_position().const_y();
        closest_position.z() += box_transform.const_position().const_z();
        const vector3 displacement = (closest_position - center);
        const vector3 normal = (-displacement).get_normalized();
        const quaternion reflector(normal, M_PI);
        const vector3 new_velocity = reflector.get_rotated_vector(-this_velocity);
        const float distance = displacement.get_magnitude() - radius();

        const float velocity_component = vector3::dot(displacement.get_normalized(), this_velocity);

        if(std::abs(velocity_component) <= 0.0000001f)
        {
            return nullptr; // will never collide
        }

        int64_t time = (distance * 1000000000) / velocity_component;

        if(time < 0 && distance >= 0.0f)
        {
            return nullptr; // will never collide
        }

        time += time::now_ns();

        return new collission_event(time, new_velocity);
    }

    return nullptr;
}