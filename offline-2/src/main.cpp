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
    std::ifstream scene_stream("inputs/1/scene.txt");
    view scene_view;
    perspective scene_perspective;

    scene_stream >> scene_view.eye.x >> scene_view.eye.y >> scene_view.eye.z;
    scene_stream >> scene_view.look.x >> scene_view.look.y >> scene_view.look.z;
    scene_stream >> scene_view.up.x >> scene_view.up.y >> scene_view.up.z;
    scene_stream >> scene_perspective.fov >> scene_perspective.aspect_ratio
            >> scene_perspective.far >> scene_perspective.near;

    std::vector<std::array<vector<4>, 3>> models;

    {
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

                models.push_back(vertices);
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
                double angle;
                double axis_x;
                double axis_y;
                double axis_z;

                scene_stream >> angle >> axis_x >> axis_y >> axis_z;

                const double qw = std::cos(angle / 2.0);
                const double qx = axis_x * std::sin(angle / 2.0);
                const double qy = axis_y * std::sin(angle / 2.0);
                const double qz = axis_z * std::sin(angle / 2.0);
                matrix4x4 rotation;
                rotation[0].x = 1.0 - 2.0 * (qy * qy + qz * qz);
                rotation[1].x = 2.0 * (qx * qy - qz * qw);
                rotation[2].x = 2.0 * (qx * qz + qy * qw);
                rotation[0].y = 2.0 * (qx * qy + qz * qw);
                rotation[1].y = 1.0 - 2.0 * (qx * qx + qz * qz);
                rotation[2].y = 2.0 * (qy * qz - qx * qw);
                rotation[0].z = 2.0 * (qx * qz - qy * qw);
                rotation[1].z = 2.0 * (qy * qz + qx * qw);
                rotation[2].z = 1.0 - 2.0 * (qx * qx + qy * qy);
                rotation[3].w = 1.0;
                matrix_stack.top() *= rotation;
            }
            else if(command == "push")
            {
                matrix_stack.push(matrix_stack.top());
            }
            else if(command == "pop")
            {
                if(!matrix_stack.empty())
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
    }

    scene_stream.close();

    return 0;
}