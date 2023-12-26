#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <scene.hpp>

int main()
{
    std::ifstream scene_stream("inputs/1/scene.txt");
    view scene_view;
    perspective scene_perspective;

    {
        vector4 eye;
        vector4 look;
        vector4 up;
        double fov;
        double aspect_ratio;
        double far;
        double near;

        scene_stream >> eye.x >> eye.y >> eye.z;
        scene_stream >> look.x >> look.y >> look.z;
        scene_stream >> up.x >> up.y >> up.z;
        scene_stream >> fov >> aspect_ratio >> far >> near;

        scene_view.set_eye(eye);
        scene_view.set_look(look);
        scene_view.set_up(up);
        scene_perspective.set_fov(fov);
        scene_perspective.set_aspect_ratio(aspect_ratio);
        scene_perspective.set_far(far);
        scene_perspective.set_near(near);
    }

    std::vector<vector4[3]> models;

    {
        std::stack<matrix4x4> matrix_stack;

        while(true)
        {
            std::string command;

            scene_stream >> command;

            if(command == "triangle")
            {
                vector4 vertices[3];

                for(size_t i = 0; i < 3; ++i)
                {
                    scene_stream >> vertices[i].x >> vertices[i].y >> vertices[i].z;

                    vertices[i].w = 1.0;
                    vertices[i] = matrix_stack.top() * vertices[i];
                }
            }
            else if(command == "translate")
            {
                matrix4x4 translate;
                translate[0].x = 1.0;
                translate[1].x = 0.0;
                translate[2].x = 0.0;
                translate[0].y = 0.0;
                translate[1].y = 1.0;
                translate[2].y = 0.0;
                translate[0].z = 0.0;
                translate[1].z = 0.0;
                translate[2].z = 1.0;
                translate[0].w = 0.0;
                translate[1].w = 0.0;
                translate[2].w = 0.0;
                translate[3].w = 1.0;

                scene_stream >> translate[3].x >> translate[3].y >> translate[3].z;

                matrix_stack.top() *= translate;
            }
            else if(command == "scale")
            {
                matrix4x4 scale;
                scale[1].x = 0.0;
                scale[2].x = 0.0;
                scale[3].x = 0.0;
                scale[0].y = 0.0;
                scale[2].y = 0.0;
                scale[3].y = 0.0;
                scale[0].z = 0.0;
                scale[1].z = 0.0;
                scale[3].z = 0.0;
                scale[0].w = 0.0;
                scale[1].w = 0.0;
                scale[2].w = 0.0;
                scale[3].w = 1.0;

                scene_stream >> scale[0].x >> scale[1].y >> scale[2].z;

                matrix_stack.top() *= scale;
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