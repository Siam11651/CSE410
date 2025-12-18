#ifdef _WIN32
    #include <windows.h>
#endif

#include <GL/gl.h>
#include <scene.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>

o3::camera::camera()
{
    
}

o3::camera::camera(const o3::transform &_cam_transform)
{
    transform = _cam_transform;
}

// scene::scene()
// {
//     main_camera = nullptr;
// }

// void scene::setup_frame()
// {
//     const camera &temp_camera = *main_camera;
//     const transform &main_camera_transform = temp_camera.cam_transform;
//     const glm::vec3 &main_camera_position = main_camera_transform.position;
//     const glm::vec3 &main_camera_forward = main_camera_transform.get_forward();
//     const glm::vec3 &main_camera_up = main_camera_transform.get_up();
//     const glm::mat4 perspective = glm::perspective((float)M_PI / 4.0f, screen::aspect_ratio(), 0.01f, 100.0f);
//     const glm::mat4 view = glm::lookAt(glm::vec3(main_camera_position.x, main_camera_position.y, main_camera_position.z), glm::vec3(main_camera_position.x + main_camera_forward.x, main_camera_position.y + main_camera_forward.y, main_camera_position.z + main_camera_forward.z), glm::vec3(main_camera_up.x, main_camera_up.y, main_camera_up.z));
//     const glm::mat4 product = perspective * view;

//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();
//     glLoadMatrixf(glm::value_ptr(product));
// }

// void scene::show()
// {
//     for(const object *object_item : objects)
//     {
//         object_item->draw();
//     }
// }

// scene::~scene()
// {
    
// }