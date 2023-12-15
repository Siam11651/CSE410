#include <conc_mesh/cylinder_mesh.hpp>
#include <cmath>

void cylinder_mesh::constructor_helper(const float &radius, const float &height, const size_t &segments,
    const float &angle, const color &cylinder_color)
{
    const float half_angle = angle / 2.0f;
    const float half_height = height / 2.0f;
    const float segment_angle = angle / segments;

    for(size_t i = 0; i < segments; ++i)
    {
        const float left_angle = half_angle + segment_angle * i;
        const float right_angle = half_angle + segment_angle * (i + 1);
        const float left_x = std::cos(left_angle) * radius;
        const float left_y = std::sin(left_angle) * radius;
        const float right_x = std::cos(right_angle) * radius;
        const float right_y = std::sin(right_angle) * radius;
        const vector3 top_left(left_x, left_y, half_height);
        const vector3 top_right(right_x, right_y, half_height);
        const vector3 bot_left(left_x, left_y, -half_height);
        const vector3 bot_right(right_x, right_y, -half_height);

        m_faces.emplace_back(std::array<vector3, 3>{top_left, bot_left, top_right}, cylinder_color);
        m_faces.emplace_back(std::array<vector3, 3>{top_right, bot_left, bot_right}, cylinder_color);
    }
}

cylinder_mesh::cylinder_mesh()
{
    constructor_helper(1.0f, 1.0f, 20, 2.0 * M_PI, color(1.0f, 1.0f, 1.0f, 1.0f));
}

cylinder_mesh::cylinder_mesh(const float &radius, const float &height, const size_t &segments)
{
    constructor_helper(radius, height, segments, 2.0 * M_PI, color(1.0f, 1.0f, 1.0f, 1.0f));
}

cylinder_mesh::cylinder_mesh(const float &radius, const float &height, const size_t &segments,
    const float &angle)
{
    constructor_helper(radius, height, segments, angle, color(1.0f, 1.0f, 1.0f, 1.0f));
}

cylinder_mesh::cylinder_mesh(const float &radius, const float &height, const size_t &segments,
    const float &angle, const color &cylinder_color)
{
    constructor_helper(radius, height, segments, angle, cylinder_color);
}