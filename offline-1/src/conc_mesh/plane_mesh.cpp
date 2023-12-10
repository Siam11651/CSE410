#include <conc_mesh/plane_mesh.hpp>

plane_mesh::plane_mesh(const float &size_x, const float &size_z,
    const size_t &count_x, const size_t &count_z)
{
    const float og_x = -size_x / 2.0f;
    const float og_z = -size_z / 2.0f;
    const float check_size_x = size_x / count_x;
    const float check_size_z = size_z / count_z;
    color colors[2] = {color(1.0f, 1.0f, 1.0f, 1.0f), color(0.0f, 0.0f, 0.0f, 1.0f)};
    size_t color_idx = 0;

    for(size_t i = 0; i < count_x; ++i)
    {
        const float left = og_x + (i + 1) * check_size_x;
        const float right = og_x + i * check_size_x;

        for(size_t j = 0; j < count_z; ++j)
        {
            const float top = og_z + j * check_size_z;
            const float bot = og_z + (j + 1) * check_size_z;
            const vector3 top_left(left, 0.0f, top);
            const vector3 top_right(right, 0.0f, top);
            const vector3 bot_left(left, 0.0f, bot);
            const vector3 bot_right(right, 0.0f, bot);

            m_faces.emplace_back(std::array<vector3, 3>
            {
                top_left, bot_left, top_right
            }, colors[color_idx % 2]);
            m_faces.emplace_back(std::array<vector3, 3>
            {
                top_right, bot_right, bot_left
            }, colors[color_idx % 2]);

            ++color_idx;
        }

        if(count_x % 2 == 0)
        {
            ++color_idx;
        }
    }
}