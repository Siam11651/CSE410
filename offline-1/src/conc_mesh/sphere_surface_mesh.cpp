#include <conc_mesh/sphere_surface_mesh.hpp>
#include <cmath>

void sphere_surface_mesh::constructor_helper(const float &radius, const size_t &segments,
    const color &surface_color)
{
    // const float half_total_angle = (M_PI - std::acos(-1.0f / 3.0f)) / 2.0f;
    const float half_total_angle = M_PI / 4.0f;
    const float total_angle = 2.0f * half_total_angle;
    const float angle_gap = total_angle / segments;

    for(size_t i = 0; i < segments; ++i)    // rotate along z axis
    {
        const float left_x = std::cos(-half_total_angle + angle_gap * i);
        const float right_x = std::cos(-half_total_angle + angle_gap * (i + 1));
        const float left_y = std::sin(-half_total_angle + angle_gap * i);
        const float right_y = std::sin(-half_total_angle + angle_gap * (i + 1));

        for(size_t j = 0; j < segments; ++j)    // rotate along x axis
        {
            const float rear_z = std::cos(-half_total_angle + angle_gap * j);
            const float front_z = std::cos(-half_total_angle + angle_gap * (j + 1));
            const float rear_y = std::sin(-half_total_angle + angle_gap * j);
            const float front_y = std::sin(-half_total_angle + angle_gap * (j + 1));
            const vector3 left_rear = vector3::cross(vector3(0.0f, rear_y, rear_z),
                vector3(left_x, left_y, 0.0f));
            const vector3 right_rear = vector3::cross(vector3(0.0f, rear_y, rear_z),
                vector3(right_x, right_y, 0.0f));
            const vector3 left_front = vector3::cross(vector3(0.0f, front_y, front_z),
                vector3(left_x, left_y, 0.0f));
            const vector3 right_front = vector3::cross(vector3(0.0f, front_y, front_z),
                vector3(right_x, right_y, 0.0f));

            m_faces.emplace_back(std::array<vector3, 3>{left_rear, left_front, right_rear},
                surface_color);
            m_faces.emplace_back(std::array<vector3, 3>{right_rear, left_front, right_front},
                surface_color);
        }
    }
}

sphere_surface_mesh::sphere_surface_mesh(const float &radius, const size_t &segments)
{
    constructor_helper(radius, segments, color(1.0f, 1.0f, 1.0f, 1.0f));
}

sphere_surface_mesh::sphere_surface_mesh(const float &radius, const size_t &segments,
    const color &surface_color)
{
    constructor_helper(radius, segments, surface_color);
}