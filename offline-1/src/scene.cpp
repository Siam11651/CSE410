#include <scene.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <exceptions.hpp>
#include <GL/freeglut.h>
#include <functional>

camera::camera()
{

}

camera::camera(const transform &camera_transform)
{
    m_transform = camera_transform;
}

transform &camera::cam_transform()
{
    return m_transform;
}

const transform &camera::const_cam_transform() const
{
    return m_transform;
}

scene::scene()
{

}

camera &scene::main_camera()
{
    return m_main_camera;
}

const camera &scene::const_main_camera() const
{
    return m_main_camera;
}

std::vector<object *> &scene::object_ptrs()
{
    return m_objects;
}

const std::vector<object *> &scene::const_object_ptrs() const
{
    return m_objects;
}

void scene::setup_frame()
{
    const camera &main_camera = const_main_camera();
    const transform &main_camera_transform = main_camera.const_cam_transform();
    const vector3 &main_camera_position = main_camera_transform.const_position();
    const vector3 &main_camera_forward = main_camera_transform.get_forward();
    const vector3 &main_camera_up = main_camera_transform.get_up();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(45.0f, screen::aspect_ratio(), 0.01f, 100.0f);
    gluLookAt(
        main_camera_position.const_x(), main_camera_position.const_y(), main_camera_position.const_z(),
        main_camera_position.const_x() + main_camera_forward.const_x(),
        main_camera_position.const_y() + main_camera_forward.const_y(),
        main_camera_position.const_z() + main_camera_forward.const_z(),
        main_camera_up.const_x(), main_camera_up.const_y(), main_camera_up.const_z());
}

void scene::simulate_physics()
{
    bool collided = false;

    for(size_t i = 0; i < m_objects.size(); ++i)
    {
        rigidbody *object_rigidbody = m_objects[i]->get_rigidbody();

        if(object_rigidbody == nullptr)
        {
            continue;
        }

        if(!object_rigidbody->const_enabled())
        {
            continue;
        }

        collission_event *next_collission_event = object_rigidbody->get_collission_event();
        object &this_object = *m_objects[i];

        std::function<void(const float &)> translation_simulation(
        [&this_object, &object_rigidbody](const float &delta_time)
        {
            vector3 &object_position = this_object.object_transform().position();
            const vector3 &object_velocity = object_rigidbody->const_velocity();
            object_position += object_velocity * delta_time;
        });

        if(next_collission_event == nullptr)
        {
            translation_simulation(time::delta_time_s());
        }
        else
        {
            int64_t now_ns = time::now_ns();
            const int64_t &collide_time_ns = next_collission_event->const_trigger_time();

            if(now_ns >= collide_time_ns)
            {
                collided = true;
                object_rigidbody->velocity() = next_collission_event->const_new_velocity();
                quaternion new_rotation = quaternion::get_rotation(vector3(0.0f, 0.0f, 1.0f),
                    object_rigidbody->const_velocity().get_normalized());
                this_object.object_transform().rotation() = new_rotation;
                int64_t ahead_ns = now_ns - collide_time_ns;
                
                translation_simulation(ahead_ns / 1e9f);
                object_rigidbody->reset_collission_event();
            }
            else
            {
                translation_simulation(time::delta_time_s());
            }
        }
    }

    if(collided)
    {
        update_collissions();
    }
}

void scene::update_collissions()
{
    for(size_t i = 0; i < m_objects.size(); ++i)
    {
        rigidbody *this_rigidbody = m_objects[i]->get_rigidbody();

        if(this_rigidbody == nullptr)
        {
            continue;
        }

        collider *this_collider = m_objects[i]->get_collider();

        if(this_collider == nullptr)
        {
            throw null_collider_exception();
        }

        this_rigidbody->reset_collission_event();

        collission_event *nearest_collission_event = nullptr;

        for(size_t j = 0; j < m_objects.size(); ++j)
        {
            if(i == j)
            {
                continue;
            }

            collider *other_collider = m_objects[j]->get_collider();

            if(other_collider == nullptr)
            {
                continue;
            }

            collission_event *new_collission_event =
                this_collider->create_collission_event(other_collider);

            if(new_collission_event == nullptr)
            {
                continue;
            }

            if(nearest_collission_event)
            {
                if(*new_collission_event < *nearest_collission_event)
                {
                    delete nearest_collission_event;

                    nearest_collission_event = new_collission_event;
                }
                else
                {
                    delete new_collission_event;
                }
            }
            else
            {
                nearest_collission_event = new_collission_event;
            }
        }

        if(nearest_collission_event)
        {
            this_rigidbody->register_collission_event(nearest_collission_event);
        }
    }
}

void scene::show()
{
    for(const object *object_item : m_objects)
    {
        object_item->draw();
    }
}