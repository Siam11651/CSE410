#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <thread>
#include <cmath>
#include <arg_parser.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <scene.hpp>
#include <input.hpp>
#include <conc_scene/rtx_scene.hpp>

scene *current_scene = nullptr;

int main(int argc, char **argv)
{
    arg_parser parser(argv[0]);

    parser.add_value("scene", "roll");
    parser.parse(argc, argv);
    time::initialise();

    screen::window_title() = "offline-1";
    screen::window_width() = 1366;
    screen::window_height() = 768;

    if(!glfwInit())
    {
        std::cerr << "Failed to initialise GLFW" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow *window = glfwCreateWindow(screen::window_width(), screen::window_height(), screen::window_title().c_str(), nullptr, nullptr);

    if(!window)
    {
        std::cerr << "Failed to create window" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    current_scene = new rtx_scene();
    double mouse_pos_x;
    double mouse_pos_y;

    while(!glfwWindowShouldClose(window))
    {
        time::start_frame();
        glfwPollEvents();

        if(current_scene != nullptr)
        {
            glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
            
            input::mouse new_mouse;
            new_mouse.position = glm::vec2(mouse_pos_x, mouse_pos_y);
            
            input::set_key(input::key::mouse_left, (input::status)glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT));
            input::set_mouse(new_mouse);
            input::set_key(input::key::key_w, (input::status)glfwGetKey(window, GLFW_KEY_W));
            input::set_key(input::key::key_a, (input::status)glfwGetKey(window, GLFW_KEY_A));
            input::set_key(input::key::key_s, (input::status)glfwGetKey(window, GLFW_KEY_S));
            input::set_key(input::key::key_d, (input::status)glfwGetKey(window, GLFW_KEY_D));
            input::set_key(input::key::key_up, (input::status)glfwGetKey(window, GLFW_KEY_UP));
            input::set_key(input::key::key_down, (input::status)glfwGetKey(window, GLFW_KEY_DOWN));
            input::set_key(input::key::key_left, (input::status)glfwGetKey(window, GLFW_KEY_LEFT));
            input::set_key(input::key::key_right, (input::status)glfwGetKey(window, GLFW_KEY_RIGHT));
            input::set_key(input::key::key_q, (input::status)glfwGetKey(window, GLFW_KEY_Q));
            input::set_key(input::key::key_e, (input::status)glfwGetKey(window, GLFW_KEY_E));

            current_scene->setup_frame();
            current_scene->on_new_frame();
            current_scene->on_new_frame_late();
            current_scene->show();
        }

        glfwSwapBuffers(window);
        time::end_frame();
    }

    delete current_scene;

    glfwTerminate();

    return 0;
}