#include <conc_scene/rolling_ball_scene.hpp>
#include <time.hpp>
#include <conc_mesh/box_mesh.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/stl_mesh.hpp>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

rolling_ball_scene::rolling_ball_scene()
{
    m_camera_speed = 5.0f;
    m_camera_rotation_speed = 3.0f;
    m_ball_speed = 3.0f;
    m_ball_rotation_speed = 3.0f;
    m_forward_direction = 1.0f;
    m_forward_keypressed = false;
    m_simulate = false;
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
        vector3(0.0f, M_PI / 2.0f, 0.0f));
    transform bot_wall_transform(vector3(0.0f, 0.25f, -4.9f),
        vector3(0.0f, M_PI / 2.0f, 0.0f));
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
    // direction arrow
    stl_mesh forward_mesh("assets/arrow.stl", color(0.0f, 0.0f, 1.0f, 1.0f));
    stl_mesh up_mesh("assets/arrow.stl", color(0.0f, 1.0f, 1.0f, 1.0f));

    transform arrow_transform;
    arrow_transform.scale() *= 0.05f;
    m_forward_arrow = new object(forward_mesh, arrow_transform);
    arrow_transform.scale() = vector3(0.025f, 0.025f, 0.05f);
    arrow_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), -M_PI / 2.0f);
    m_up_arrow = new object(up_mesh, arrow_transform);
    // camera
    transform main_camera_transform(vector3(0.0f, 7.0f, -7.0f), vector3(M_PI / 4.0f, 0.0f, 0.0f));
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
        m_forward_arrow, 
        m_up_arrow
    });
}

void rolling_ball_scene::on_new_frame()
{
    m_sphere_rigidbody->enabled() = m_forward_keypressed || m_simulate;
    m_sphere_rigidbody->velocity() = m_sphere_rigidbody->velocity()* m_forward_direction;

    if(m_forward_keypressed)
    {
        update_collissions();
    }
}

void rolling_ball_scene::on_new_frame_late()
{
    vector3 &sphere_velocity = m_sphere_rigidbody->velocity();
    const vector3 forward = sphere_velocity.get_normalized() * m_forward_direction;
    const vector3 &position = m_sphere_object->const_object_transform().const_position();
    quaternion &rotation = m_sphere_object->object_transform().rotation();
    vector3 &new_forward_position = m_forward_arrow->object_transform().position();
    vector3 &new_up_position = m_up_arrow->object_transform().position();
    new_forward_position.x() = position.const_x() + forward.const_x() * 0.5f;
    new_forward_position.y() = position.const_y() + forward.const_y() * 0.5f;
    new_forward_position.z() = position.const_z() + forward.const_z() * 0.5f;
    new_up_position = position + vector3(0.0f, 0.6f, 0.0f);
    quaternion &new_forward_rotation = m_forward_arrow->object_transform().rotation();
    new_forward_rotation = quaternion::get_rotation(vector3(0.0f, 0.0f, 1.0f), forward);
    const vector3 left = new_forward_rotation.get_rotated_vector(vector3(1.0f, 0.0f, 0.0f));
    float angle = 0.0f;

    if(m_sphere_rigidbody->const_enabled())
    {
        angle = m_ball_speed * time::delta_time_s() * m_forward_direction / 0.2f;
    }

    rotation = quaternion(left, angle) * rotation;
    sphere_velocity = sphere_velocity * m_forward_direction;
    m_forward_keypressed = false;
    m_forward_direction = 1.0f;
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
        m_simulate = !m_simulate;

        update_collissions();
    }
    else if(key == 'i')
    {
        m_forward_keypressed = true;
        m_forward_direction = 1.0f;
    }
    else if(key == 'k')
    {
        m_forward_keypressed = true;
        m_forward_direction = -1.0f;
    }
    else if(key == 'j')
    {
        const quaternion old_velocity_rotation = quaternion::get_rotation(vector3(0.0f, 0.0f, 1.0f),
            sphere_rigidbody->velocity().get_normalized());
        const quaternion new_velocity_rotation = quaternion(vector3(0.0f, 1.0f, 0.0f),
            m_ball_rotation_speed * time::delta_time_s()) * old_velocity_rotation;
        sphere_rigidbody->velocity() = new_velocity_rotation.get_rotated_vector(
            vector3(0.0f, 0.0f, 1.0f)) * m_ball_speed;

        update_collissions();
    }
    else if(key == 'l')
    {
        const quaternion old_velocity_rotation = quaternion::get_rotation(vector3(0.0f, 0.0f, 1.0f),
            sphere_rigidbody->velocity().get_normalized());
        const quaternion new_velocity_rotation = quaternion(vector3(0.0f, 1.0f, 0.0f),
            -m_ball_rotation_speed * time::delta_time_s()) * old_velocity_rotation;
        sphere_rigidbody->velocity() = new_velocity_rotation.get_rotated_vector(
            vector3(0.0f, 0.0f, 1.0f)) * m_ball_speed;

        update_collissions();
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