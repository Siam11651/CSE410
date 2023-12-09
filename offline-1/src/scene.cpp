#include <scene.hpp>

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

std::vector<object> &scene::objects()
{
    return m_objects;
}

const camera &scene::const_main_camera() const
{
    return m_main_camera;
}

const std::vector<object> &scene::const_objects() const
{
    return m_objects;
}

void scene::show()
{
    for(object &object_item : m_objects)
    {
        rigidbody *object_rigidbody = object_item.get_rigidbody();

        if(object_rigidbody == nullptr)
        {
            continue;
        }

        const std::optional<collission_event> &opt_collission_event =
            object_rigidbody->const_opt_collission_event();

        if(opt_collission_event.has_value())
        {

        }
        else
        {
            vector3 &object_position = object_item.object_transform().position();
            const vector3 &object_velocity = object_rigidbody->const_velocity();
            object_position += object_velocity * 0.0166f;
        }
    }

    for(size_t i = 0; i < m_objects.size(); ++i)
    {
        rigidbody *object_rigidbody = m_objects[i].get_rigidbody();

        if(object_rigidbody == nullptr)
        {
            continue;
        }

        for(size_t j = 0; j < m_objects.size(); ++j)
        {
            if(i == j)
            {
                continue;
            }

            if(m_objects[j].get_collider() == nullptr)
            {
                continue;
            }

            object_rigidbody->predict_collission(m_objects[j].get_collider());
        }
    }

    for(object &object_item : m_objects)
    {
        object_item.draw();
    }
}