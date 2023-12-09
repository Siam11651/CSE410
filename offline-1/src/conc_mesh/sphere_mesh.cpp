#include <conc_mesh/sphere_mesh.hpp>
#include <cmath>

sphere_mesh::sphere_mesh(const float &radius, const size_t &stack_count,
    const size_t &segment_count)
{
    std::array<color, 2> colors{color(1.0f, 0.0f, 0.0f, 1.0f), color(0.0f, 1.0f, 0.0f, 1.0f)};
    size_t color_idx = 0;
    float stack_gap = (float)M_PI / stack_count;
    float segment_gap = (float)(2.0f * M_PI) / segment_count;

    for(size_t i = 0; i < stack_count; ++i)
    {
        float stack_start_angle = i * stack_gap;
        float stack_end_angle = (i + 1) * stack_gap;
        float y_top = std::cos(stack_start_angle) * radius;
        float y_bot = std::cos(stack_end_angle) * radius;
        float stack_start_radius = std::sin(stack_start_angle) * radius;
        float stack_end_radius = std::sin(stack_end_angle) * radius;

        for(size_t j = 0; j < segment_count; ++j)
        {
            float segment_start_angle = j * segment_gap;
            float segment_end_angle = (j + 1) * segment_gap;
            float x_top_left = std::cos(segment_start_angle) * stack_start_radius;
            float z_top_left = -std::sin(segment_start_angle) * stack_start_radius;
            float x_top_right = std::cos(segment_end_angle) * stack_start_radius;
            float z_top_right = -std::sin(segment_end_angle) * stack_start_radius;
            float x_bot_left = std::cos(segment_start_angle) * stack_end_radius;
            float z_bot_left = -std::sin(segment_start_angle) * stack_end_radius;
            float x_bot_right = std::cos(segment_end_angle) * stack_end_radius;
            float z_bot_right = -std::sin(segment_end_angle) * stack_end_radius;
            vector3 top_left(x_top_left, y_top, z_top_left);
            vector3 bot_left(x_bot_left, y_bot, z_bot_left);
            vector3 top_right(x_top_right, y_top, z_top_right);
            vector3 bot_right(x_bot_right, y_bot, z_bot_right);

            m_faces.emplace_back(std::array<vector3, 3>{top_left, bot_left, top_right},
                colors[color_idx % 2]);
            m_faces.emplace_back(std::array<vector3, 3>{top_right, bot_left, bot_right},
                colors[color_idx % 2]);

            ++color_idx;
        }

        if(segment_count % 2 != 0)
        {
            ++color_idx;
        }

        if(i == stack_count / 2)
        {
            ++color_idx;
        }
    }
}