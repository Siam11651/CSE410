#include <conc_scene/rolling_ball_scene.hpp>
#include <time.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_collider/sphere_collider.hpp>
#include <GL/freeglut.h>

rolling_ball_scene::rolling_ball_scene()
{
    m_camera_speed = 5.0f;
    m_camera_rotation_speed = 3.0f;
    m_ball_speed = 0.0f;
    m_ball_rotation_speed = 3.0f;
    sphere_mesh sphere_mesh0(0.2f, 25, 8);
    transform sphere_transform0(vector3(0.0f, 0.2f, 0.0f));
    object sphere_object(sphere_mesh0, sphere_transform0);
    sphere_collider rb_sphere_collider(0.2f);
    rigidbody *sphere_rigidbody = new rigidbody();
    sphere_object.set_rigidbody(sphere_rigidbody);
    sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
        * m_ball_speed;
    plane_mesh plane_mesh0(100.0f, 100.0f, 100, 100);
    object plane_object(plane_mesh0);
    transform main_camera_transform(vector3(0.0f, 3.0f, -3.0f), vector3(45.0f, 0.0f, 0.0f));
    camera main_camera(main_camera_transform);
    this->main_camera() = main_camera;
    std::vector<object> &scene_objects = this->objects();
    
    scene_objects.insert(scene_objects.end(),
    {
        sphere_object,
        plane_object
    });
}

void rolling_ball_scene::on_new_frame()
{

}

void rolling_ball_scene::on_ascii_key(uint8_t key, int32_t x, int32_t y)
{
    camera &main_camera = this->main_camera();
    transform &main_camera_transform = main_camera.cam_transform();
    object &sphere_object = this->objects().front();
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
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_right(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '4')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_right(),
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
    else if(key == 'j')
    {
        sphere_rotation = quaternion(sphere_transform.get_up(),
            m_ball_rotation_speed * time::delta_time_s()) * sphere_rotation;
        sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
            * m_ball_speed;
    }
    else if(key == 'k')
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
        main_camera_transform.position() += main_camera_transform.get_right()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        main_camera_transform.position() -= main_camera_transform.get_right()
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