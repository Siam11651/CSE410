#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
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
constexpr float camera_speed = 2.0f;
constexpr float m_camera_spin = 0.5f;
o3::camera camera;

void handle_inputs(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.transform.position += camera.transform.get_forward() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.transform.position -= camera.transform.get_right() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.transform.position -= camera.transform.get_forward() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.transform.position += camera.transform.get_right() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {
        camera.transform.position += camera.transform.get_up() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        camera.transform.position -= camera.transform.get_up() * camera_speed * time::delta_time_s();
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        const glm::vec3 &right = camera.transform.get_right();
        const float angle = -m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * right.x;
        const float qy = std::sin(angle / 2.0f) * right.y;
        const float qz = std::sin(angle / 2.0f) * right.z;
        camera.transform.rotation = glm::quat(qw, qx, qy, qz) * camera.transform.rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        const glm::vec3 &right = camera.transform.get_right();
        const float angle = m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * right.x;
        const float qy = std::sin(angle / 2.0f) * right.y;
        const float qz = std::sin(angle / 2.0f) * right.z;
        camera.transform.rotation = glm::quat(qw, qx, qy, qz) * camera.transform.rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        const glm::vec3 &up = camera.transform.get_up();
        const float angle = -m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * up.x;
        const float qy = std::sin(angle / 2.0f) * up.y;
        const float qz = std::sin(angle / 2.0f) * up.z;
        camera.transform.rotation = glm::quat(qw, qx, qy, qz) * camera.transform.rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        const glm::vec3 &up = camera.transform.get_up();
        const float angle = m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * up.x;
        const float qy = std::sin(angle / 2.0f) * up.y;
        const float qz = std::sin(angle / 2.0f) * up.z;
        camera.transform.rotation = glm::quat(qw, qx, qy, qz) * camera.transform.rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        const glm::vec3 &forward = camera.transform.get_forward();
        const float angle = -m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * forward.x;
        const float qy = std::sin(angle / 2.0f) * forward.y;
        const float qz = std::sin(angle / 2.0f) * forward.z;
        camera.transform.rotation = glm::quat(qw, qx, qy, qz) * camera.transform.rotation;
    }

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        const glm::vec3 &forward = camera.transform.get_forward();
        const float angle = m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * forward.x;
        const float qy = std::sin(angle / 2.0f) * forward.y;
        const float qz = std::sin(angle / 2.0f) * forward.z;
        camera.transform.rotation = glm::quat(qw, qx, qy, qz) * camera.transform.rotation;
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
    uint32_t camera_transform_loc = glGetUniformLocation(shader_program, "camera_transform");
    uint32_t bot_left_loc = glGetUniformLocation(shader_program, "bot_left");
    uint32_t dx_loc = glGetUniformLocation(shader_program, "dx");
    uint32_t dy_loc = glGetUniformLocation(shader_program, "dy");
    glm::vec3 point_light_positions[] = {glm::vec3(0.0f, 10.0f, -5.0f)};
    glm::vec3 point_light_colors[] = {glm::vec3(1.0f, 1.0f, 1.0f)};

    for(size_t i = 0; i < 1; ++i)
    {
        std::stringstream ss;

        ss << i;

        uint32_t point_light_position_uinform_loc = glGetUniformLocation(shader_program, ("point_light_positions[" + ss.str() + "]").c_str());
        uint32_t point_light_colors_uinform_loc = glGetUniformLocation(shader_program, ("point_light_colors[" + ss.str() + "]").c_str());

        glUniform3fv(point_light_position_uinform_loc, 1, glm::value_ptr(point_light_positions[i]));
        glUniform3fv(point_light_colors_uinform_loc, 1, glm::value_ptr(point_light_colors[i]));
    }

    glm::vec3 spot_light_positions[] = {glm::vec3(5.0f, 5.0f, 5.0f)};
    glm::vec3 spot_light_directions[] = {glm::vec3(0.0f, -1.0f, 0.0f)};
    glm::vec3 spot_light_colors[] = {glm::vec3(1.0f, 0.0f, 0.0f)};
    float spot_light_angles[] = {12.0f};

    for(size_t i = 0; i < 1; ++i)
    {
        std::stringstream ss;

        ss << i;

        uint32_t spot_light_positions_loc = glGetUniformLocation(shader_program, ("spot_light_positions[" + ss.str() + "]").c_str());
        uint32_t spot_light_directions_loc = glGetUniformLocation(shader_program, ("spot_light_directions[" + ss.str() + "]").c_str());
        uint32_t spot_light_colors_loc = glGetUniformLocation(shader_program, ("spot_light_colors[" + ss.str() + "]").c_str());
        uint32_t spot_light_angles_loc = glGetUniformLocation(shader_program, ("spot_light_angles[" + ss.str() + "]").c_str());

        glUniform3fv(spot_light_positions_loc, 1, glm::value_ptr(spot_light_positions[i]));
        glUniform3fv(spot_light_directions_loc, 1, glm::value_ptr(spot_light_directions[i]));
        glUniform3fv(spot_light_colors_loc, 1, glm::value_ptr(spot_light_colors[i]));
        glUniform1f(spot_light_angles_loc, spot_light_angles[i]);
    }

    glm::vec3 circle_colors[] = {glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)};
    float circle_ambients[] = {0.6f, 0.5f};
    float circle_diffuses[] = {0.2f, 0.3f};
    float circle_speculars[] = {0.3f, 0.2f};
    int32_t circle_shininesses[] = {5, 7};
    float circle_reflections[] = {0.1f, 0.9f};
    glm::vec3 circle_centers[] = {glm::vec3(-3.0f, 2.0f, 0.0f), glm::vec3(3.0f, 2.0f, 0.0f)};
    float circle_radius[] = {1.0f, 2.0f};

    for(size_t i = 0; i < 2; ++i)
    {
        std::stringstream ss;

        ss << i;

        uint32_t circle_color_uinform_loc = glGetUniformLocation(shader_program, ("circle_colors[" + ss.str() + "]").c_str());
        uint32_t circle_ambient_uinform_loc = glGetUniformLocation(shader_program, ("circle_ambients[" + ss.str() + "]").c_str());
        uint32_t circle_diffuses_uinform_loc = glGetUniformLocation(shader_program, ("circle_diffuses[" + ss.str() + "]").c_str());
        uint32_t circle_speculars_uinform_loc = glGetUniformLocation(shader_program, ("circle_speculars[" + ss.str() + "]").c_str());
        uint32_t circle_shininesses_uinform_loc = glGetUniformLocation(shader_program, ("circle_shininesses[" + ss.str() + "]").c_str());
        uint32_t circle_reflections_uinform_loc = glGetUniformLocation(shader_program, ("circle_reflections[" + ss.str() + "]").c_str());
        uint32_t circle_center_uinform_loc = glGetUniformLocation(shader_program, ("circle_centers[" + ss.str() + "]").c_str());
        uint32_t circle_radius_uinform_loc = glGetUniformLocation(shader_program, ("circle_radius[" + ss.str() + "]").c_str());

        glUniform3fv(circle_color_uinform_loc, 1, glm::value_ptr(circle_colors[i]));
        glUniform1f(circle_ambient_uinform_loc, circle_ambients[i]);
        glUniform1f(circle_diffuses_uinform_loc, circle_diffuses[i]);
        glUniform1f(circle_speculars_uinform_loc, circle_speculars[i]);
        glUniform1f(circle_shininesses_uinform_loc, circle_shininesses[i]);
        glUniform1f(circle_reflections_uinform_loc, circle_reflections[i]);
        glUniform3fv(circle_center_uinform_loc, 1, glm::value_ptr(circle_centers[i]));
        glUniform1f(circle_radius_uinform_loc, circle_radius[i]);
    }

    glm::vec3 triangle_colors[] = {glm::vec3(1.0f, 1.0f, 1.0f)};
    float triangle_ambients[] = {0.3f};
    float triangle_diffuses[] = {0.5f};
    float triangle_speculars[] = {0.9f};
    int32_t triangle_shininesses[] = {90};
    float triangle_reflections[] = {0.25f};
    glm::vec3 triangle_vertices0[] = {glm::vec3(-1.0f, 1.0f, 5.0f)};
    glm::vec3 triangle_vertices1[] = {glm::vec3(1.0f, 1.0f, 5.0f)};
    glm::vec3 triangle_vertices2[] = {glm::vec3(0.0f, 1.0f, 4.5f)};

    for(size_t i = 0; i < 1; ++i)
    {
        std::stringstream ss;

        ss << i;

        uint32_t triangle_color_uinform_loc = glGetUniformLocation(shader_program, ("triangle_colors[" + ss.str() + "]").c_str());
        uint32_t triangle_ambient_uinform_loc = glGetUniformLocation(shader_program, ("triangle_ambients[" + ss.str() + "]").c_str());
        uint32_t triangle_diffuses_uinform_loc = glGetUniformLocation(shader_program, ("triangle_diffuses[" + ss.str() + "]").c_str());
        uint32_t triangle_speculars_uinform_loc = glGetUniformLocation(shader_program, ("triangle_speculars[" + ss.str() + "]").c_str());
        uint32_t triangle_shininesses_uinform_loc = glGetUniformLocation(shader_program, ("triangle_shininesses[" + ss.str() + "]").c_str());
        uint32_t triangle_reflections_uinform_loc = glGetUniformLocation(shader_program, ("triangle_reflections[" + ss.str() + "]").c_str());
        uint32_t triangle_vertices0_uinform_loc = glGetUniformLocation(shader_program, ("triangle_vertices0[" + ss.str() + "]").c_str());
        uint32_t triangle_vertices1_uinform_loc = glGetUniformLocation(shader_program, ("triangle_vertices1[" + ss.str() + "]").c_str());
        uint32_t triangle_vertices2_uinform_loc = glGetUniformLocation(shader_program, ("triangle_vertices2[" + ss.str() + "]").c_str());

        glUniform3fv(triangle_color_uinform_loc, 1, glm::value_ptr(triangle_colors[i]));
        glUniform1f(triangle_ambient_uinform_loc, triangle_ambients[i]);
        glUniform1f(triangle_diffuses_uinform_loc, triangle_diffuses[i]);
        glUniform1f(triangle_speculars_uinform_loc, triangle_speculars[i]);
        glUniform1f(triangle_shininesses_uinform_loc, triangle_shininesses[i]);
        glUniform1f(triangle_reflections_uinform_loc, triangle_reflections[i]);
        glUniform3fv(triangle_vertices0_uinform_loc, 1, glm::value_ptr(triangle_vertices0[i]));
        glUniform3fv(triangle_vertices1_uinform_loc, 1, glm::value_ptr(triangle_vertices1[i]));
        glUniform3fv(triangle_vertices2_uinform_loc, 1, glm::value_ptr(triangle_vertices2[i]));
    }

    float shape_a[] = {1.0f};
    float shape_b[] = {0.0f};
    float shape_c[] = {1.0f};
    float shape_d[] = {0.0f};
    float shape_e[] = {0.0f};
    float shape_f[] = {0.0f};
    float shape_g[] = {0.0f};
    float shape_h[] = {0.0f};
    float shape_i[] = {0.0f};
    float shape_j[] = {-1.0f};
    glm::vec3 shape_colors[] = {glm::vec3(1.0f, 0.0f, 1.0f)};
    float shape_ambients[] = {0.4f};
    float shape_diffuses[] = {0.1f};
    float shape_speculars[] = {0.5f};
    int32_t shape_shininesses[] = {1};
    float shape_reflections[] = {0.35f};
    glm::vec3 shape_cube_positions[] = {glm::vec3(1.0f, 1.0f, 0.0f)};
    glm::vec3 shape_cube_dimensions[] = {glm::vec3(3.0f, 1.0f, 0.0f)};

    for(size_t i = 0; i < 1; ++i)
    {
        std::stringstream ss;

        ss << i;

        uint32_t shape_a_loc = glGetUniformLocation(shader_program, ("shape_a[" + ss.str() + "]").c_str());
        uint32_t shape_b_loc = glGetUniformLocation(shader_program, ("shape_b[" + ss.str() + "]").c_str());
        uint32_t shape_c_loc = glGetUniformLocation(shader_program, ("shape_c[" + ss.str() + "]").c_str());
        uint32_t shape_d_loc = glGetUniformLocation(shader_program, ("shape_d[" + ss.str() + "]").c_str());
        uint32_t shape_e_loc = glGetUniformLocation(shader_program, ("shape_e[" + ss.str() + "]").c_str());
        uint32_t shape_f_loc = glGetUniformLocation(shader_program, ("shape_f[" + ss.str() + "]").c_str());
        uint32_t shape_g_loc = glGetUniformLocation(shader_program, ("shape_g[" + ss.str() + "]").c_str());
        uint32_t shape_h_loc = glGetUniformLocation(shader_program, ("shape_h[" + ss.str() + "]").c_str());
        uint32_t shape_i_loc = glGetUniformLocation(shader_program, ("shape_i[" + ss.str() + "]").c_str());
        uint32_t shape_j_loc = glGetUniformLocation(shader_program, ("shape_j[" + ss.str() + "]").c_str());
        uint32_t shape_colors_loc = glGetUniformLocation(shader_program, ("shape_colors[" + ss.str() + "]").c_str());
        uint32_t shape_ambients_loc = glGetUniformLocation(shader_program, ("shape_ambients[" + ss.str() + "]").c_str());
        uint32_t shape_diffuses_loc = glGetUniformLocation(shader_program, ("shape_diffuses[" + ss.str() + "]").c_str());
        uint32_t shape_speculars_loc = glGetUniformLocation(shader_program, ("shape_speculars[" + ss.str() + "]").c_str());
        uint32_t shape_shininesses_loc = glGetUniformLocation(shader_program, ("shape_shininesses[" + ss.str() + "]").c_str());
        uint32_t shape_reflections_loc = glGetUniformLocation(shader_program, ("shape_reflections[" + ss.str() + "]").c_str());
        uint32_t shape_cube_positions_loc = glGetUniformLocation(shader_program, ("shape_cube_positions[" + ss.str() + "]").c_str());
        uint32_t shape_cube_dimensions_loc = glGetUniformLocation(shader_program, ("shape_cube_dimensions[" + ss.str() + "]").c_str());

        glUniform1f(shape_a_loc, shape_a[i]);
        glUniform1f(shape_b_loc, shape_b[i]);
        glUniform1f(shape_c_loc, shape_c[i]);
        glUniform1f(shape_d_loc, shape_d[i]);
        glUniform1f(shape_e_loc, shape_e[i]);
        glUniform1f(shape_f_loc, shape_f[i]);
        glUniform1f(shape_g_loc, shape_g[i]);
        glUniform1f(shape_h_loc, shape_h[i]);
        glUniform1f(shape_i_loc, shape_i[i]);
        glUniform1f(shape_j_loc, shape_j[i]);
        glUniform3fv(shape_colors_loc, 1, glm::value_ptr(shape_colors[i]));
        glUniform1f(shape_ambients_loc, shape_ambients[i]);
        glUniform1f(shape_diffuses_loc, shape_diffuses[i]);
        glUniform1f(shape_speculars_loc, shape_speculars[i]);
        glUniform1f(shape_shininesses_loc, shape_shininesses[i]);
        glUniform1f(shape_reflections_loc, shape_reflections[i]);
        glUniform3fv(shape_cube_positions_loc, 1, glm::value_ptr(shape_cube_positions[i]));
        glUniform3fv(shape_cube_dimensions_loc, 1, glm::value_ptr(shape_cube_dimensions[i]));
    }

    glUniform1i(screen_dimension_loc, (int32_t)screen::window_width());
    glUniform1f(dx_loc, 0.5f / screen::window_width());
    glUniform1f(dy_loc, 0.5f / screen::window_height());

    const float plane_distance = 1.0f / std::tan(fovy / 2.0f);

    glm::vec3 bot_left = glm::vec3(-0.5f, -0.5f, plane_distance);

    glUniform3fv(bot_left_loc, 1, glm::value_ptr(bot_left));

    // current_scene = new rtx_scene();
    double mouse_pos_x;
    double mouse_pos_y;

    camera.transform.position.y = 2.0f;
    camera.transform.position.z = -10.0f;

    while(!glfwWindowShouldClose(window))
    {
        time::start_frame();
        glfwPollEvents();
        handle_inputs(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float angle = glm::angle(camera.transform.rotation);
        const glm::vec3 axis = glm::axis(camera.transform.rotation);
        glm::mat4 camera_transform = glm::translate(glm::mat4(1.0f), camera.transform.position);
        camera_transform = glm::rotate(camera_transform, angle, axis);;

        glUniform3fv(camera_pos_loc, 1, glm::value_ptr(camera.transform.position));
        glUniformMatrix4fv(camera_transform_loc, 1, GL_FALSE, glm::value_ptr(camera_transform));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        time::end_frame();
    }

    // delete current_scene;

    glfwTerminate();

    return 0;
}