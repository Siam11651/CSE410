#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <thread>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <arg_parser.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <shader.hpp>
#include <scene.hpp>
// #include <input.hpp>
// #include <conc_scene/rtx_scene.hpp>
#include <iostream>

// scene *current_scene = nullptr;

constexpr float fovy = M_PI / 4.0f;
constexpr float camera_speed = 1.0f;
o3::camera camera;

void handle_inputs(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.transform.position += camera.transform.get_forward() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.transform.position += camera.transform.get_right() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.transform.position -= camera.transform.get_forward() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.transform.position -= camera.transform.get_right() * camera_speed * time::delta_time_s();
    }
}

int main(int argc, char **argv)
{
    time::initialise();

    screen::window_title() = "offline-3";
    screen::window_width() = 768;
    screen::window_height() = 768;

    if(!glfwInit())
    {
        std::cerr << "Failed to initialise GLFW" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow *window = glfwCreateWindow(screen::window_width(), screen::window_height(), screen::window_title().c_str(), nullptr, nullptr);

    if(!window)
    {
        std::cerr << "Failed to create window" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialise GLAD" << std::endl;

        glfwTerminate();

        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    float render_surface[] =
    {
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };
    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(render_surface), render_surface, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    uint32_t vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    {
        int32_t success;
        char info_log[512];

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);

            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;

            glfwTerminate();

            return -1;
        }
    }

    uint32_t fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    {
        int32_t success;
        char info_log[512];

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);

            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;

            glfwTerminate();

            return -1;
        }
    }

    uint32_t shader_program;
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    {
        int32_t success;
        char info_log[512];

        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

        if(!success)
        {
            glGetProgramInfoLog(shader_program, 512, NULL, info_log);

            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;

            glfwTerminate();

            return -1;
        }
    }

    glUseProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader); 

    uint32_t screen_dimension_loc = glGetUniformLocation(shader_program, "screen_dimension");
    uint32_t camera_pos_loc = glGetUniformLocation(shader_program, "camera_pos");
    uint32_t bot_left_loc = glGetUniformLocation(shader_program, "bot_left");
    uint32_t dx_loc = glGetUniformLocation(shader_program, "dx");
    uint32_t dy_loc = glGetUniformLocation(shader_program, "dy");

    glUniform1i(screen_dimension_loc, (int32_t)screen::window_width());
    glUniform1f(dx_loc, 0.5f / screen::window_width());
    glUniform1f(dy_loc, 0.5f / screen::window_height());

    const float plane_distance = 1.0f / std::tan(fovy / 2.0f);
    // current_scene = new rtx_scene();
    double mouse_pos_x;
    double mouse_pos_y;

    while(!glfwWindowShouldClose(window))
    {
        time::start_frame();
        glfwPollEvents();
        handle_inputs(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 bot_left = camera.transform.position - camera.transform.get_right() * 0.5f - camera.transform.get_up() * 0.5f + camera.transform.get_forward() * plane_distance;

        glUniform3fv(bot_left_loc, 1, glm::value_ptr(bot_left));
        glUniform3fv(camera_pos_loc, 1, glm::value_ptr(camera.transform.position));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        time::end_frame();
    }

    // delete current_scene;

    glfwTerminate();

    return 0;
}