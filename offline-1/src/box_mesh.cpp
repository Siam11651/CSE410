#include <box_mesh.hpp>

box_mesh::box_mesh(const float &size_x, const float &size_y, const float &size_z)
{
    m_size_x = size_x;
    m_size_y = size_y;
    m_size_z = size_z;
    vector3 top_left_front(-m_size_x / 2.0f, m_size_y / 2.0f, -m_size_z / 2.0f);
    vector3 top_right_front(m_size_x / 2.0f, m_size_y / 2.0f, -m_size_z / 2.0f);
    vector3 bot_left_front(-m_size_x / 2.0f, -m_size_y / 2.0f, -m_size_z / 2.0f);
    vector3 bot_right_front(m_size_x / 2.0f, -m_size_y / 2.0f, -m_size_z / 2.0f);
    vector3 top_left_back(-m_size_x / 2.0f, m_size_y / 2.0f, m_size_z / 2.0f);
    vector3 top_right_back(m_size_x / 2.0f, m_size_y / 2.0f, m_size_z / 2.0f);
    vector3 bot_left_back(-m_size_x / 2.0f, -m_size_y / 2.0f, m_size_z / 2.0f);
    vector3 bot_right_back(m_size_x / 2.0f, -m_size_y / 2.0f, m_size_z / 2.0f);
    m_faces = 
    {
        std::array<vector3, 3>{top_left_front, bot_left_front, top_right_front},  // front face
        std::array<vector3, 3>{top_right_front, bot_left_front, bot_right_front}, // front face
        std::array<vector3, 3>{top_right_front, bot_right_front, top_right_back}, // right face
        std::array<vector3, 3>{top_right_back, bot_right_front, bot_right_back},  // right face
        std::array<vector3, 3>{top_left_back, bot_left_back, top_left_front},     // left face
        std::array<vector3, 3>{top_left_front, bot_left_back, bot_left_front},    // left face
        std::array<vector3, 3>{top_right_back, bot_right_back, bot_left_back},    // rear face
        std::array<vector3, 3>{top_right_back, bot_left_back, top_left_back},     // rear face
        std::array<vector3, 3>{top_left_back, top_right_back, top_left_front},     // top face
        std::array<vector3, 3>{top_right_back, top_right_front, top_left_front},  // top face
        std::array<vector3, 3>{bot_left_front, bot_right_front, bot_left_back},   // bot face
        std::array<vector3, 3>{bot_right_front, bot_right_back, bot_left_back}    // bot face
    };
}

float box_mesh::get_size_x() const
{
    return m_size_x;
}

float box_mesh::get_size_y() const
{
    return m_size_y;
}

float box_mesh::get_size_z() const
{
    return m_size_z;
}