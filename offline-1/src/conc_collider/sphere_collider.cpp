#include <conc_collider/sphere_collider.hpp>
#include <conc_collider/box_collider.hpp>
#include <conc_mesh/box_mesh.hpp>
#include <object.hpp>
#include <time.hpp>
#include <functional>

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
    const vector3 &this_position = this_object->const_object_transform().
        const_position();

    if(dynamic_cast<box_collider *>(other_collider))
    {
        box_collider *conc_collider = (box_collider *)(other_collider);
        const float wall_gap = conc_collider->const_dimensions().const_x() / 2.0f;
        const object *other_object = other_collider->get_parent_object();
        const vector3 &other_position = other_object->const_object_transform().
            const_position();

        if(other_object->const_name() == "left_wall")
        {
            if(this_velocity.const_x() <= 0.0f)
            {
                return nullptr;
            }

            float distance_x = other_position.const_x() - this_position.const_x()
                - radius() - wall_gap;

            vector3 new_velocity = this_velocity;
            new_velocity.x() = -this_velocity.const_x();
            int64_t time = (int64_t)((distance_x * 1e9f) / this_velocity.const_x()) + time::now_ns();

            return new collission_event(time, new_velocity);
        }
        else if(other_object->const_name() == "right_wall")
        {
            if(this_velocity.const_x() >= 0.0f)
            {
                return nullptr;
            }

            float distance_x = this_position.const_x() - other_position.const_x()
                - radius() - wall_gap;

            vector3 new_velocity = this_velocity;
            new_velocity.x() = -this_velocity.const_x();
            int64_t time = (int64_t)((distance_x * 1e9f) / -this_velocity.const_x()) + time::now_ns();

            return new collission_event(time, new_velocity);
        }
        else if(other_object->const_name() == "top_wall")
        {
            if(this_velocity.const_z() <= 0.0f)
            {
                return nullptr;
            }

            float distance_z = other_position.const_z() - this_position.const_z()
                - radius() - wall_gap;

            vector3 new_velocity = this_velocity;
            new_velocity.z() = -this_velocity.const_z();
            int64_t time = (int64_t)((distance_z * 1e9f) / this_velocity.const_z()) + time::now_ns();

            return new collission_event(time, new_velocity);
        }
        else if(other_object->const_name() == "bot_wall")
        {
            if(this_velocity.const_z() >= 0.0f)
            {
                return nullptr;
            }

            float distance_z = this_position.const_z() - other_position.const_z()
                - radius() - wall_gap;

            vector3 new_velocity = this_velocity;
            new_velocity.z() = -this_velocity.const_z();
            int64_t time = (int64_t)((distance_z * 1e9f) / -this_velocity.const_z()) + time::now_ns();

            return new collission_event(time, new_velocity);
        }

        // else is not going to happen
    }

    return nullptr;
}