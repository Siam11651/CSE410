#include <conc_mesh/box_mesh.hpp>

box_mesh::box_mesh(const float &size_x, const float &size_y, const float &size_z)
{
    vector3 top_left_front(-size_x / 2.0f, size_y / 2.0f, -size_z / 2.0f);
    vector3 top_right_front(size_x / 2.0f, size_y / 2.0f, -size_z / 2.0f);
    vector3 bot_left_front(-size_x / 2.0f, -size_y / 2.0f, -size_z / 2.0f);
    vector3 bot_right_front(size_x / 2.0f, -size_y / 2.0f, -size_z / 2.0f);
    vector3 top_left_back(-size_x / 2.0f, size_y / 2.0f, size_z / 2.0f);
    vector3 top_right_back(size_x / 2.0f, size_y / 2.0f, size_z / 2.0f);
    vector3 bot_left_back(-size_x / 2.0f, -size_y / 2.0f, size_z / 2.0f);
    vector3 bot_right_back(size_x / 2.0f, -size_y / 2.0f, size_z / 2.0f);
    m_faces = 
    {
        face({top_left_front, bot_left_front, top_right_front}, color(1.0f, 1.0f, 1.0f, 1.0f)),  // front face
        face({top_right_front, bot_left_front, bot_right_front}, color(1.0f, 1.0f, 1.0f, 1.0f)), // front face
        face({top_right_front, bot_right_front, top_right_back}, color(1.0f, 0.0f, 0.0f, 1.0f)), // right face
        face({top_right_back, bot_right_front, bot_right_back}, color(1.0f, 0.0f, 0.0f, 1.0f)),  // right face
        face({top_left_back, bot_left_back, top_left_front}, color(0.0f, 1.0f, 0.0f, 1.0f)),     // left face
        face({top_left_front, bot_left_back, bot_left_front}, color(0.0f, 1.0f, 0.0f, 1.0f)),    // left face
        face({top_right_back, bot_right_back, bot_left_back}, color(0.0f, 0.0f, 1.0f, 1.0f)),    // rear face
        face({top_right_back, bot_left_back, top_left_back}, color(0.0f, 0.0f, 1.0f, 1.0f)),     // rear face
        face({top_left_back, top_right_back, top_left_front}, color(1.0f, 1.0f, 0.0f, 1.0f)),     // top face
        face({top_right_back, top_right_front, top_left_front}, color(1.0f, 1.0f, 0.0f, 1.0f)),  // top face
        face({bot_left_front, bot_right_front, bot_left_back}, color(1.0f, 0.0f, 1.0f, 1.0f)),   // bot face
        face({bot_right_front, bot_right_back, bot_left_back}, color(1.0f, 0.0f, 1.0f, 1.0f))    // bot face
    };
}