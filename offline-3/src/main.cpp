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
#include <time.hpp>
#include <screen.hpp>
#include <shader.hpp>
#include <scene.hpp>
#include <iostream>
#include <fstream>
#include <regex>

constexpr float fovy = M_PI / 4.0f;
constexpr float camera_speed = 50.0f;
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
    // other data
    size_t level;
    size_t window_dimension;

    // point light objects
    std::vector<glm::vec3> point_light_positions;
    std::vector<glm::vec3> point_light_colors;

    // spot light objects
    std::vector<glm::vec3> spot_light_positions;
    std::vector<glm::vec3> spot_light_directions;
    std::vector<glm::vec3> spot_light_colors;
    std::vector<float> spot_light_angles;

    // sphere objects
    std::vector<glm::vec3> circle_colors;
    std::vector<float> circle_ambients;
    std::vector<float> circle_diffuses;
    std::vector<float> circle_speculars;
    std::vector<int32_t> circle_shininesses;
    std::vector<float> circle_reflections;
    std::vector<glm::vec3> circle_centers;
    std::vector<float> circle_radius;

    // triangle objects
    std::vector<glm::vec3> triangle_colors;
    std::vector<float> triangle_ambients;
    std::vector<float> triangle_diffuses;
    std::vector<float> triangle_speculars;
    std::vector<int32_t> triangle_shininesses;
    std::vector<float> triangle_reflections;
    std::vector<glm::vec3> triangle_vertices0;
    std::vector<glm::vec3> triangle_vertices1;
    std::vector<glm::vec3> triangle_vertices2;

    // shape objects
    std::vector<float> shape_a;
    std::vector<float> shape_b;
    std::vector<float> shape_c;
    std::vector<float> shape_d;
    std::vector<float> shape_e;
    std::vector<float> shape_f;
    std::vector<float> shape_g;
    std::vector<float> shape_h;
    std::vector<float> shape_i;
    std::vector<float> shape_j;
    std::vector<glm::vec3> shape_colors;
    std::vector<float> shape_ambients;
    std::vector<float> shape_diffuses;
    std::vector<float> shape_speculars;
    std::vector<int32_t> shape_shininesses;
    std::vector<float> shape_reflections;
    std::vector<glm::vec3> shape_cube_positions;
    std::vector<glm::vec3> shape_cube_dimensions;

    // take input
    {
        std::ifstream ifstrm("inputs/input.txt");

        ifstrm >> level;
        ifstrm >> window_dimension;

        screen::window_width() = window_dimension;
        screen::window_height() = window_dimension;
        size_t object_count;

        ifstrm >> object_count;

        for(size_t i = 0; i < object_count; ++i)
        {
            std::string object_type;

            ifstrm >> object_type;

            if(object_type == "sphere")
            {
                glm::vec3 center;
                float radius;
                glm::vec3 color;
                float ambient;
                float diffuse;
                float specular;
                float reflection;
                uint32_t shininess;

                ifstrm >> center.x >> center.y >> center.z;
                ifstrm >> radius;
                ifstrm >> color.x >> color.y >> color.z;
                ifstrm >> ambient >> diffuse >> specular >> reflection;
                ifstrm >> shininess;

                std::swap(center.y, center.z);
                circle_centers.push_back(center);
                circle_radius.push_back(radius);
                circle_colors.push_back(color);
                circle_ambients.push_back(ambient);
                circle_diffuses.push_back(diffuse);
                circle_speculars.push_back(specular);
                circle_reflections.push_back(reflection);
                circle_shininesses.push_back(shininess);
            }
            else if(object_type == "triangle")
            {
                glm::vec3 v0;
                glm::vec3 v1;
                glm::vec3 v2;
                glm::vec3 color;
                float ambient;
                float diffuse;
                float specular;
                float reflection;
                uint32_t shininess;

                ifstrm >> v0.x >> v0.y >> v0.z;
                ifstrm >> v1.x >> v1.y >> v1.z;
                ifstrm >> v2.x >> v2.y >> v2.z;
                ifstrm >> color.x >> color.y >> color.z;
                ifstrm >> ambient >> diffuse >> specular >> reflection;
                ifstrm >> shininess;

                std::swap(v0.y, v0.z);
                std::swap(v1.y, v1.z);
                std::swap(v2.y, v2.z);
                triangle_vertices0.push_back(v0);
                triangle_vertices1.push_back(v1);
                triangle_vertices2.push_back(v2);
                triangle_colors.push_back(color);
                triangle_ambients.push_back(ambient);
                triangle_diffuses.push_back(diffuse);
                triangle_speculars.push_back(specular);
                triangle_reflections.push_back(reflection);
                triangle_shininesses.push_back(shininess);
            }
            else if(object_type == "general")
            {
                float a;
                float b;
                float c;
                float d;
                float e;
                float f;
                float g;
                float h;
                float i;
                float j;
                glm::vec3 cube_position;
                glm::vec3 cube_dimension;
                glm::vec3 color;
                float ambient;
                float diffuse;
                float specular;
                float reflection;
                uint32_t shininess;

                ifstrm >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
                ifstrm >> cube_position.x >> cube_position.y >> cube_position.z >> cube_dimension.x >> cube_dimension.y >> cube_dimension.z;
                ifstrm >> color.x >> color.y >> color.z;
                ifstrm >> ambient >> diffuse >> specular >> reflection;
                ifstrm >> shininess;

                std::swap(cube_position.y, cube_position.z);
                std::swap(cube_dimension.y, cube_dimension.z);
                std::swap(b, c);
                std::swap(d, e);
                std::swap(h, i);
                shape_a.push_back(a);
                shape_b.push_back(b);
                shape_c.push_back(c);
                shape_d.push_back(d);
                shape_e.push_back(e);
                shape_f.push_back(f);
                shape_g.push_back(g);
                shape_h.push_back(h);
                shape_i.push_back(i);
                shape_j.push_back(j);
                shape_cube_positions.push_back(cube_position);
                shape_cube_dimensions.push_back(cube_dimension);
                shape_colors.push_back(color);
                shape_ambients.push_back(ambient);
                shape_diffuses.push_back(diffuse);
                shape_speculars.push_back(specular);
                shape_reflections.push_back(reflection);
                shape_shininesses.push_back(shininess);
            }
        }

        size_t point_light_count;

        ifstrm >> point_light_count;

        for(size_t i = 0; i < point_light_count; ++i)
        {
            glm::vec3 position;
            glm::vec3 color;

            ifstrm >> position.x >> position.y >> position.z;
            ifstrm >> color.x >> color.y >> color.z;

            std::swap(position.y, position.z);
            point_light_positions.push_back(position);
            point_light_colors.push_back(color);
        }

        size_t spot_light_count;

        ifstrm >> spot_light_count;

        for(size_t i = 0; i < spot_light_count; ++i)
        {
            glm::vec3 position;
            glm::vec3 color;
            glm::vec3 direction;
            float angle;

            ifstrm >> position.x >> position.y >> position.z;
            ifstrm >> color.x >> color.y >> color.z;
            ifstrm >> direction.x >> direction.y >> direction.z;
            ifstrm >> angle;

            std::swap(position.y, position.z);
            std::swap(direction.y, direction.z);
            spot_light_positions.push_back(position);
            spot_light_colors.push_back(color);
            spot_light_directions.push_back(direction);
            spot_light_angles.push_back(angle);
        }

        ifstrm.close();
    }

    time::initialise();

    screen::window_title() = "offline-3";

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

    // modify shader source
    std::string frag_shader_src_str(fragment_shader_source);

    {
        std::stringstream ss;

        if(point_light_positions.size() > 0)
        {
            ss << point_light_positions.size();
        }
        else
        {
            ss << "1";
        }

        frag_shader_src_str = std::regex_replace(frag_shader_src_str, std::regex("__1__"), ss.str());

        ss.str("");

        if(spot_light_positions.size() > 0)
        {
            ss << spot_light_positions.size();
        }
        else
        {
            ss << "1";
        }

        frag_shader_src_str = std::regex_replace(frag_shader_src_str, std::regex("__2__"), ss.str());

        ss.str("");

        if(circle_centers.size() > 0)
        {
            ss << circle_centers.size();
        }
        else
        {
            ss << "1";
        }

        frag_shader_src_str = std::regex_replace(frag_shader_src_str, std::regex("__3__"), ss.str());

        ss.str("");

        if(triangle_colors.size() > 0)
        {
            ss << triangle_colors.size();
        }
        else
        {
            ss << "1";
        }

        frag_shader_src_str = std::regex_replace(frag_shader_src_str, std::regex("__4__"), ss.str());

        ss.str("");

        if(shape_colors.size() > 0)
        {
            ss << shape_colors.size();
        }
        else
        {
            ss << "1";
        }

        frag_shader_src_str = std::regex_replace(frag_shader_src_str, std::regex("__5__"), ss.str());
    }

    const char *frag_shader_src_parameterised = frag_shader_src_str.c_str();

    // compile shaders
    uint32_t shader_program;

    {
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

        glShaderSource(fragment_shader, 1, &frag_shader_src_parameterised, NULL);
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

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    glUseProgram(shader_program);

    {
        uint32_t screen_dimension_loc = glGetUniformLocation(shader_program, "screen_dimension");
        uint32_t dx_loc = glGetUniformLocation(shader_program, "dx");
        uint32_t dy_loc = glGetUniformLocation(shader_program, "dy");

        glUniform1i(screen_dimension_loc, (int32_t)screen::window_width());
        glUniform1f(dx_loc, 0.5f / screen::window_width());
        glUniform1f(dy_loc, 0.5f / screen::window_height());
    }

    {
        uint32_t point_light_count_loc = glGetUniformLocation(shader_program, ("point_light_count"));
        
        glUniform1ui(point_light_count_loc, (uint32_t)point_light_positions.size());
    }

    for(size_t i = 0; i < point_light_positions.size(); ++i)
    {
        std::stringstream ss;

        ss << i;

        uint32_t point_light_position_uinform_loc = glGetUniformLocation(shader_program, ("point_light_positions[" + ss.str() + "]").c_str());
        uint32_t point_light_colors_uinform_loc = glGetUniformLocation(shader_program, ("point_light_colors[" + ss.str() + "]").c_str());

        glUniform3fv(point_light_position_uinform_loc, 1, glm::value_ptr(point_light_positions[i]));
        glUniform3fv(point_light_colors_uinform_loc, 1, glm::value_ptr(point_light_colors[i]));
    }

    {
        uint32_t spot_light_count_loc = glGetUniformLocation(shader_program, ("spot_light_count"));
        
        glUniform1ui(spot_light_count_loc, (uint32_t)spot_light_positions.size());
    }

    for(size_t i = 0; i < spot_light_positions.size(); ++i)
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

    {
        uint32_t circle_count_loc = glGetUniformLocation(shader_program, ("circle_count"));
        
        glUniform1ui(circle_count_loc, (uint32_t)circle_colors.size());
    }

    for(size_t i = 0; i < circle_colors.size(); ++i)
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
        glUniform1ui(circle_shininesses_uinform_loc, circle_shininesses[i]);
        glUniform1f(circle_reflections_uinform_loc, circle_reflections[i]);
        glUniform3fv(circle_center_uinform_loc, 1, glm::value_ptr(circle_centers[i]));
        glUniform1f(circle_radius_uinform_loc, circle_radius[i]);
    }

    {
        uint32_t triangle_count_loc = glGetUniformLocation(shader_program, ("triangle_count"));
        
        glUniform1ui(triangle_count_loc, (uint32_t)triangle_colors.size());
    }

    for(size_t i = 0; i < triangle_colors.size(); ++i)
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
        glUniform1ui(triangle_shininesses_uinform_loc, triangle_shininesses[i]);
        glUniform1f(triangle_reflections_uinform_loc, triangle_reflections[i]);
        glUniform3fv(triangle_vertices0_uinform_loc, 1, glm::value_ptr(triangle_vertices0[i]));
        glUniform3fv(triangle_vertices1_uinform_loc, 1, glm::value_ptr(triangle_vertices1[i]));
        glUniform3fv(triangle_vertices2_uinform_loc, 1, glm::value_ptr(triangle_vertices2[i]));
    }

    {
        uint32_t shape_count_loc = glGetUniformLocation(shader_program, ("shape_count"));
        
        glUniform1ui(shape_count_loc, (uint32_t)shape_a.size());
    }

    for(size_t i = 0; i < shape_a.size(); ++i)
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
        glUniform1ui(shape_shininesses_loc, shape_shininesses[i]);
        glUniform1f(shape_reflections_loc, shape_reflections[i]);
        glUniform3fv(shape_cube_positions_loc, 1, glm::value_ptr(shape_cube_positions[i]));
        glUniform3fv(shape_cube_dimensions_loc, 1, glm::value_ptr(shape_cube_dimensions[i]));
    }

    const float plane_distance = 1.0f / std::tan(fovy / 2.0f);
    uint32_t camera_pos_loc = glGetUniformLocation(shader_program, "camera_pos");
    uint32_t camera_transform_loc = glGetUniformLocation(shader_program, "camera_transform");

    {
        uint32_t bot_left_loc = glGetUniformLocation(shader_program, "bot_left");
        glm::vec3 bot_left = glm::vec3(-0.5f, -0.5f, plane_distance);

        glUniform3fv(bot_left_loc, 1, glm::value_ptr(bot_left));
    }

    double mouse_pos_x;
    double mouse_pos_y;
    camera.transform.position.y = 120.0f;
    camera.transform.position.z = -120.0f;
    camera.transform.rotation = glm::quat(glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));

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

    glfwTerminate();

    return 0;
}