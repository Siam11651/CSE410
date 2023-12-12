#include <conc_scene/rolling_ball_scene.hpp>
#include <time.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_mesh/box_mesh.hpp>
#include <GL/freeglut.h>
#include <cmath>

rolling_ball_scene::rolling_ball_scene()
{
    m_camera_speed = 5.0f;
    m_camera_rotation_speed = 3.0f;
    m_ball_speed = 3.0f;
    m_effective_ball_speed = 0.0f;
    m_ball_rotation_speed = 3.0f;
    // sphere
    sphere_mesh sphere_mesh0(0.2f, 25, 8);
    transform sphere_transform0(vector3(0.0f, 0.2f, 0.0f));
    m_sphere_object = new object(sphere_mesh0, sphere_transform0);
    m_sphere_rigidbody = new rigidbody();
    m_sphere_collider = new sphere_collider(0.2f);
    m_sphere_object->set_rigidbody(m_sphere_rigidbody);
    m_sphere_object->set_collider(m_sphere_collider);
    m_sphere_rigidbody->enabled() = false;
    m_sphere_rigidbody->velocity() = m_sphere_object->const_object_transform().get_forward()
        * m_ball_speed;
    // ground
    plane_mesh plane_mesh0(100.0f, 100.0f, 100, 100);
    m_plane_object = new object(plane_mesh0);
    // walls
    box_mesh vertical_wall_mesh(vector3(0.2f, 0.5f, 10.0f),
        color(1.0f, 0.0f, 0.0f, 1.0f));
    box_mesh horizontal_wall_mesh(vector3(0.2f, 0.5f, 9.8f),
        color(1.0f, 0.0f, 0.0f, 1.0f));
    transform left_wall_transform(vector3(5.0f, 0.25f, 0.0f));
    transform right_wall_transform(vector3(-5.0f, 0.25f, 0.0f));
    transform top_wall_transform(vector3(0.0f, 0.25f, 4.9f),
        vector3(0.0f, (float)M_PI / 2.0f, 0.0f));
    transform bot_wall_transform(vector3(0.0f, 0.25f, -4.9f),
        vector3(0.0f, (float)M_PI / 2.0f, 0.0f));
    m_left_wall_collider = new box_collider(vector3(0.2f, 0.5f, 10.0f));
    m_right_wall_collider = new box_collider(vector3(0.2f, 0.5f, 10.0f));
    m_top_wall_collider = new box_collider(vector3(0.2f, 0.5f, 9.8f));
    m_bot_wall_collider = new box_collider(vector3(0.2f, 0.5f, 9.8f));
    object *m_left_wall_object = new object(vertical_wall_mesh, left_wall_transform);
    object *m_right_wall_object = new object(vertical_wall_mesh, right_wall_transform);
    object *m_top_wall_object = new object(horizontal_wall_mesh, top_wall_transform);
    object *m_bot_wall_object = new object(horizontal_wall_mesh, bot_wall_transform);
    m_left_wall_object->name() = "left_wall";
    m_right_wall_object->name() = "right_wall";
    m_top_wall_object->name() = "top_wall";
    m_bot_wall_object->name() = "bot_wall";

    m_left_wall_object->set_collider(m_left_wall_collider);
    m_right_wall_object->set_collider(m_right_wall_collider);
    m_top_wall_object->set_collider(m_top_wall_collider);
    m_bot_wall_object->set_collider(m_bot_wall_collider);
    // direction box
    box_mesh direction_mesh(vector3(0.05f, 0.05f, 0.5f), color(0.0f, 1.0f, 1.0f, 1.0f));
    m_direction_box = new object(direction_mesh);
    // camera
    transform main_camera_transform(vector3(0.0f, 3.0f, -3.0f), vector3(M_PI / 4.0f, 0.0f, 0.0f));
    camera main_camera(main_camera_transform);
    this->main_camera() = main_camera;
    std::vector<object *> &scene_objects = this->object_ptrs();
    
    scene_objects.insert(scene_objects.end(),
    {
        m_sphere_object,
        m_plane_object,
        m_left_wall_object,
        m_right_wall_object,
        m_top_wall_object,
        m_bot_wall_object,
        m_direction_box
    });
}

void rolling_ball_scene::on_new_frame()
{
    const vector3 &sphere_velocity = m_sphere_rigidbody->const_velocity();
    const vector3 forward = sphere_velocity.get_normalized();
    const vector3 &position = m_sphere_object->const_object_transform().const_position();
    quaternion &rotation = m_sphere_object->object_transform().rotation();
    vector3 &new_position = m_direction_box->object_transform().position();
    new_position.x() = position.const_x() + forward.const_x() * 0.5f;
    new_position.y() = position.const_y() + forward.const_y() * 0.5f;
    new_position.z() = position.const_z() + forward.const_z() * 0.5f;
    quaternion &new_rotation = m_direction_box->object_transform().rotation();
    new_rotation = quaternion::get_rotation(vector3(0.0f, 0.0f, 1.0f), forward);
    const vector3 left = new_rotation.get_rotated_vector(vector3(1.0f, 0.0f, 0.0f));
    const float angle = m_effective_ball_speed * time::delta_time_s() / 0.2f;
    rotation = quaternion(left, angle) * rotation;
}

void rolling_ball_scene::on_ascii_key(uint8_t key, int32_t x, int32_t y)
{
    camera &main_camera = this->main_camera();
    transform &main_camera_transform = main_camera.cam_transform();
    object &sphere_object = *this->object_ptrs().front();
    transform &sphere_transform = sphere_object.object_transform();
    quaternion &sphere_rotation = sphere_transform.rotation();
    rigidbody *sphere_rigidbody = sphere_object.get_rigidbody();

    if(key == '1')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '2')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '3')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_left(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '4')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_left(),
            m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '5')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '6')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == ' ')
    {
        m_effective_ball_speed = std::abs(m_effective_ball_speed - m_ball_speed);
        // sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
        //     * m_effective_ball_speed;
        sphere_rigidbody->enabled() = !sphere_rigidbody->enabled();

        update_collissions();
    }
    else if(key == 'i')
    {
        sphere_transform.position() += sphere_transform.get_forward()
            * m_ball_speed * time::delta_time_s();
    }
    else if(key == 'k')
    {
        sphere_transform.position() -= sphere_transform.get_forward()
            * m_ball_speed * time::delta_time_s();

        update_collissions();
    }
    else if(key == 'j')
    {
        sphere_rotation = quaternion(sphere_transform.get_up(),
            m_ball_rotation_speed * time::delta_time_s()) * sphere_rotation;
        sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
            * m_ball_speed;

        update_collissions();
    }
    else if(key == 'l')
    {
        sphere_rotation = quaternion(sphere_transform.get_up(),
            -m_ball_rotation_speed * time::delta_time_s()) * sphere_rotation;
        sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
            * m_ball_speed;
    }
}

void rolling_ball_scene::on_special_key(int32_t key, int32_t x, int32_t y)
{
    camera &main_camera = this->main_camera();
    transform &main_camera_transform = main_camera.cam_transform();

    if(key == GLUT_KEY_LEFT)
    {
        main_camera_transform.position() += main_camera_transform.get_left()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        main_camera_transform.position() -= main_camera_transform.get_left()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_forward()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_forward()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_PAGE_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_up()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_PAGE_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_up()
            * m_camera_speed * time::delta_time_s();
    }
}