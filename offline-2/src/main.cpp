#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <algorithm>
#include <filesystem>
#include <cmath>
#include <iomanip>
#include <scene.hpp>

const std::string input_dir("inputs/1/");
const size_t ssaa = 1;

size_t get_index(const double &_position, const size_t &_dimension)
{
    return (size_t)std::round(((_position + 1.0) / 2.0) * (_dimension - 1));
}

double get_position(const size_t &_idx, const size_t &_dimension)
{
    return ((double)_idx / (_dimension - 1)) * 2.0 - 1.0;
}

int main()
{
    view scene_view;
    perspective scene_perspective;
    std::vector<std::array<vector<4>, 3>> faces;

    {
        std::ifstream scene_stream(input_dir + "scene.txt");

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

    std::filesystem::create_directories("output");

    {
        std::ofstream stage1_stream("output/stage1.txt");
        std::ofstream stage2_stream("output/stage2.txt");
        std::ofstream stage3_stream("output/stage3.txt");

        for(size_t i = 0; i < faces.size(); ++i)
        {
            for(size_t j = 0; j < 3; ++j)
            {
                stage1_stream << std::fixed << std::setprecision(7) << faces[i][j].x << '\t'
                    << faces[i][j].y << '\t' << faces[i][j].z << std::endl;

                faces[i][j] = view_matrix * faces[i][j];

                stage2_stream << std::fixed << std::setprecision(7) << faces[i][j].x << '\t'
                    << faces[i][j].y << '\t' << faces[i][j].z << std::endl;

                faces[i][j] = projection_matrix * faces[i][j];
                faces[i][j] /= faces[i][j].w;

                stage3_stream << std::fixed << std::setprecision(7) << faces[i][j].x << '\t'
                    << faces[i][j].y << '\t' << faces[i][j].z << std::endl;
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
                if(-1.0 <= faces[i][j].x && faces[i][j].x <= 1.0
                    && -1.0 <= faces[i][j].y && faces[i][j].y <= 1.0
                    && -1.0 <= faces[i][j].z && faces[i][j].z <= 1.0)
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
        std::ifstream config_stream(input_dir + "config.txt");

        config_stream >> screen_width >> screen_height;

        config_stream.close();
    }

    constexpr double Z_MAX = 1.0;
    std::vector<std::vector<double>> z_buffer(screen_height,
        std::vector<double>(screen_width, Z_MAX));
    std::vector<std::vector<color>> color_buffer(screen_height,
        std::vector<color>(screen_width));

    {
        const double ssaa_width = screen_width * ssaa;
        const double ssaa_height = screen_width * ssaa;
        std::vector<std::vector<double>> sz_buffer(ssaa_height,
            std::vector<double>(ssaa_width, Z_MAX));
        std::vector<std::vector<color>> scolor_buffer(ssaa_height,
            std::vector<color>(ssaa_width));

        for(size_t i = 0; i < faces.size(); ++i)
        {
            double top = -1.0;
            double bot = 1.0;

            for(size_t j = 0; j < 3; ++j)
            {
                top = std::max(top, faces[i][j].y);
                bot = std::min(bot, faces[i][j].y);
            }

            top = std::min(top, 1.0);
            bot = std::max(bot, -1.0);

            if(top < bot)
            {
                continue;;
            }

            const size_t top_idx = get_index(top, ssaa_height);
            const size_t bot_idx = get_index(bot, ssaa_height);

            for(size_t j = bot_idx; j <= top_idx; ++j)
            {
                const double ordinate = get_position(j, ssaa_width);
                double left = 1.0;
                double right = -1.0;

                for(size_t k = 0; k < 3; ++k)
                {
                    const size_t start_idx = k;
                    const size_t end_idx = (k + 1) % 3;
                    const double &x0 = faces[i][start_idx].x;
                    const double &x1 = faces[i][end_idx].x;
                    const double &y0 = faces[i][start_idx].y;
                    const double &y1 = faces[i][end_idx].y;

                    if(std::abs(y0 - y1) <= 0.000001)
                    {
                        if(std::abs(ordinate - y0) <= 0.000001)
                        {
                            left = std::min(left, std::min(x0, x1));
                            right = std::max(left, std::max(x0, x1));
                        }
                    }
                    else
                    {
                        const double m = (x0 - x1) / (y0 - y1);
                        const double abscissa = m * (ordinate - y0) + x0;
                        left = std::min(left, abscissa);
                        right = std::max(right, abscissa);
                    }
                }

                left = std::clamp(left, -1.0, 1.0);
                right = std::clamp(right, -1.0, 1.0);

                if(left > right)
                {
                    continue;
                }

                const size_t left_idx = get_index(left, ssaa_width);
                const size_t right_idx = get_index(right, ssaa_width);
                const vector<4> &s = faces[i][0];
                const vector<4> p0(faces[i][1] - faces[i][0]);
                const vector<4> p1(faces[i][2] - faces[i][1]);

                for(size_t l = left_idx; l <= right_idx; ++l)
                {
                    const double abscissa = get_position(l, ssaa_width);
                    const double k0 = (p1.y * (abscissa - s.x) - p1.x * (ordinate - s.y))
                        / (p0.x * p1.y - p0.y * p1.x);
                    const double k1 = (p0.y * (abscissa - s.x) - p0.x * (ordinate - s.y))
                        / (p0.y * p1.x - p0.x * p1.y);
                    const double depth = s.z + k0 * p0.z + k1 * p1.z;

                    if(-Z_MAX < depth && depth < Z_MAX && sz_buffer[j][l] >= depth)
                    {
                        sz_buffer[j][l] = depth;
                        scolor_buffer[j][l] = face_colors[i];
                    }
                }
            }
        }

        for(size_t i = 0; i < screen_height; ++i)
        {
            for(size_t j = 0; j < screen_width; ++j)
            {
                double r_sum = 0.0;
                double g_sum = 0.0;
                double b_sum = 0.0;
                double depth_sum = 0.0;

                for(size_t k = 0; k < ssaa; ++k)
                {
                    for(size_t l = 0; l < ssaa; ++l)
                    {
                        r_sum += scolor_buffer[ssaa * i + k][ssaa * j + l].r;
                        g_sum += scolor_buffer[ssaa * i + k][ssaa * j + l].g;
                        b_sum += scolor_buffer[ssaa * i + k][ssaa * j + l].b;
                        depth_sum += sz_buffer[ssaa * i + k][ssaa * j + l];
                    }
                }

                color_buffer[i][j].r = r_sum / (ssaa * ssaa);
                color_buffer[i][j].g = g_sum / (ssaa * ssaa);
                color_buffer[i][j].b = b_sum / (ssaa * ssaa);
                z_buffer[i][j] = depth_sum / (ssaa * ssaa);
            }
        }
    }

    {
        std::ofstream z_stream("output/z_buffer.txt");

        for(size_t i = screen_height - 1; i != SIZE_MAX; --i)
        {
            for(size_t j = 0; j < screen_width; ++j)
            {
                if(z_buffer[i][j] < Z_MAX)
                {
                    z_stream << std::fixed << std::setprecision(6) << z_buffer[i][j] << '\t';
                }
            }

            z_stream << std::endl;
        }

        z_stream.close();        
    }

    std::ofstream bmp_stream("output/out.bmp");
    const uint8_t zero8 = 0;
    const uint16_t zero16 = 0;
    const uint32_t zero32 = 0;

    bmp_stream << "BM";

    const uint32_t bmp_size = 54 + screen_width * screen_height * 4;

    bmp_stream.write((const char *)&bmp_size, sizeof(uint32_t));

    for(size_t i = 0; i < 2; ++i)
    {
        bmp_stream.write((const char *)&zero16, sizeof(uint16_t));
    }

    const uint32_t array_offset = 54;

    bmp_stream.write((const char *)&array_offset, sizeof(uint32_t));

    const uint32_t dib_size = 40;

    bmp_stream.write((const char *)&dib_size, sizeof(uint32_t));

    const uint32_t bitmap_width = screen_width;
    const uint32_t bitmap_height = screen_height;

    bmp_stream.write((const char *)&bitmap_width, sizeof(uint32_t));
    bmp_stream.write((const char *)&bitmap_height, sizeof(uint32_t));

    const uint16_t color_pane_count = 1;

    bmp_stream.write((const char *)&color_pane_count, sizeof(uint16_t));

    const uint16_t bit_per_pixel = 24;

    bmp_stream.write((const char *)&bit_per_pixel, sizeof(uint16_t));

    const uint32_t compression_method = 0;

    bmp_stream.write((const char *)&compression_method, sizeof(uint32_t));

    const uint32_t raw_size = screen_width * screen_height * 4;

    bmp_stream.write((const char *)&raw_size, sizeof(uint32_t));

    const uint32_t resolution = 2835;

    bmp_stream.write((const char *)&resolution, sizeof(uint32_t));
    bmp_stream.write((const char *)&resolution, sizeof(uint32_t));

    for(size_t i = 0; i < 2; ++i)
    {
        bmp_stream.write((const char *)&zero32, sizeof(uint32_t));
    }

    size_t pad_size = (3 * screen_width) % 4;

    for(size_t i = 0; i < screen_height; ++i)
    {
        for(size_t j = 0; j < screen_width; ++j)
        {
            const uint8_t r = (uint8_t)(color_buffer[i][j].r * 255.0);
            const uint8_t g = (uint8_t)(color_buffer[i][j].g * 255.0);
            const uint8_t b = (uint8_t)(color_buffer[i][j].b * 255.0);

            bmp_stream.write((const char *)&b, sizeof(uint8_t));
            bmp_stream.write((const char *)&g, sizeof(uint8_t));
            bmp_stream.write((const char *)&r, sizeof(uint8_t));
        }

        for(size_t i = 0; i < pad_size; ++i)
        {
            bmp_stream.write((const char *)&zero8, sizeof(uint8_t));
        }
    }

    bmp_stream.close();

    return 0;
}