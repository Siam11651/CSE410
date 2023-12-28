#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <cmath>
#include <scene.hpp>

int main()
{
    view scene_view;
    perspective scene_perspective;
    std::vector<std::array<vector<4>, 3>> faces;

    {
        std::ifstream scene_stream("inputs/1/scene.txt");

        scene_stream >> scene_view.eye.x >> scene_view.eye.y >> scene_view.eye.z;
        scene_stream >> scene_view.look.x >> scene_view.look.y >> scene_view.look.z;
        scene_stream >> scene_view.up.x >> scene_view.up.y >> scene_view.up.z;
        scene_stream >> scene_perspective.fovY >> scene_perspective.aspect_ratio
                >> scene_perspective.near >> scene_perspective.far;

        matrix4x4 identity;
        identity[0].x = 1.0;
        identity[1].y = 1.0;
        identity[2].z = 1.0;
        identity[3].w = 1.0;
        std::stack<matrix4x4> matrix_stack;

        matrix_stack.push(identity);

        while(true)
        {
            std::string command;

            scene_stream >> command;

            if(command == "triangle")
            {
                std::array<vector<4>, 3> vertices;

                for(size_t i = 0; i < 3; ++i)
                {
                    scene_stream >> vertices[i].x >> vertices[i].y >> vertices[i].z;

                    vertices[i].w = 1.0;
                    vertices[i] = matrix_stack.top() * vertices[i];
                }

                faces.push_back(vertices);
            }
            else if(command == "translate")
            {
                matrix4x4 translate;
                translate[0].x = 1.0;
                translate[1].y = 1.0;
                translate[2].z = 1.0;
                translate[3].w = 1.0;

                scene_stream >> translate[3].x >> translate[3].y >> translate[3].z;

                matrix_stack.top() *= translate;
            }
            else if(command == "scale")
            {
                matrix4x4 scale;
                scale[3].w = 1.0;

                scene_stream >> scale[0].x >> scale[1].y >> scale[2].z;

                matrix_stack.top() *= scale;
            }
            else if(command == "rotate")
            {
                constexpr double DEG2RAD = M_PI / 180.0;
                double angle;
                double axis_x;
                double axis_y;
                double axis_z;

                scene_stream >> angle >> axis_x >> axis_y >> axis_z;

                const double qw = std::cos(angle * DEG2RAD / 2.0);
                const double qx = axis_x * std::sin(angle * DEG2RAD / 2.0);
                const double qy = axis_y * std::sin(angle * DEG2RAD / 2.0);
                const double qz = axis_z * std::sin(angle * DEG2RAD / 2.0);
                matrix_stack.top() *= quaternion(qw, qx, qy, qz).get_matrix();
            }
            else if(command == "push")
            {
                matrix_stack.push(matrix_stack.top());
            }
            else if(command == "pop")
            {
                if(matrix_stack.size() > 1)
                {
                    matrix_stack.pop();
                }
                else
                {
                    std::cerr << "Cannot pop last transformation matrix" << std::endl;

                    return -1;
                }
            }
            else if(command == "end")
            {
                std::clog << "Finished reading scene" << std::endl;

                break;
            }
            else
            {
                std::cerr << "Invalid scene command, try again" << std::endl;
            }
        }

        scene_stream.close();
    }

    const matrix4x4 view_matrix = scene_view.get_matrix();
    const matrix4x4 projection_matrix = scene_perspective.get_matrix();

    {
        std::ofstream stage1_stream("output/stage1.txt");
        std::ofstream stage2_stream("output/stage2.txt");
        std::ofstream stage3_stream("output/stage3.txt");

        for(size_t i = 0; i < faces.size(); ++i)
        {
            for(size_t j = 0; j < 3; ++j)
            {
                stage1_stream << faces[i][j].x << ' ' << faces[i][j].y << ' ' << faces[i][j].z
                    << std::endl;

                faces[i][j] = view_matrix * faces[i][j];

                stage2_stream << faces[i][j].x << ' ' << faces[i][j].y << ' '
                    << faces[i][j].z << std::endl;

                faces[i][j] = projection_matrix * faces[i][j];
                faces[i][j] /= faces[i][j].w;

                stage3_stream << faces[i][j].x << ' ' << faces[i][j].y << ' '
                    << faces[i][j].z << std::endl;
            }

            stage1_stream << std::endl;
            stage2_stream << std::endl;
            stage3_stream << std::endl;
        }

        stage1_stream.close();
        stage2_stream.close();
        stage2_stream.close();
    }

    std::vector<color> face_colors;

    {
        std::vector<std::array<vector<4>, 3>> temp_faces;

        for(size_t i = 0; i < faces.size(); ++i)
        {
            bool inside = false;

            for(size_t j = 0; j < 3; ++j)
            {
                faces[i][j] = projection_matrix * view_matrix * faces[i][j];
                faces[i][j] /= faces[i][j].w;

                if(-1.0 <= faces[i][j].x && faces[i][j].x <= 1.0
                    || -1.0 <= faces[i][j].y && faces[i][j].y <= 1.0
                    || -1.0 <= faces[i][j].z && faces[i][j].z <= 1.0)
                {
                    inside |= true;
                }
            }

            if(inside)
            {
                temp_faces.push_back(faces[i]);
                face_colors.push_back(color::get_random_color());
            }
        }

        faces = temp_faces;
    }

    size_t screen_width;
    size_t screen_height;

    {
        std::ifstream config_stream("inputs/1/config.txt");

        config_stream >> screen_width >> screen_height;

        config_stream.close();
    }

    double dx = 2.0 / screen_width;
    double dy = 2.0 / screen_height;
    constexpr double Z_MAX = 2.0;
    std::vector<std::vector<double>> z_buffer(screen_height,
        std::vector<double>(screen_width, Z_MAX));

    return 0;
}