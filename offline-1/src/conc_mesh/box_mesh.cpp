#include <conc_mesh/box_mesh.hpp>

void box_mesh::initialise_mesh(const vector3 &dimensions, const color &mesh_color)
{
    const float &size_x = dimensions.const_x();
    const float &size_y = dimensions.const_y();
    const float &size_z = dimensions.const_z();
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
        face({top_left_front, bot_left_front, top_right_front}, mesh_color),    // front face
        face({top_right_front, bot_left_front, bot_right_front}, mesh_color),   // front face
        face({top_right_front, bot_right_front, top_right_back}, mesh_color),   // right face
        face({top_right_back, bot_right_front, bot_right_back}, mesh_color),    // right face
        face({top_left_back, bot_left_back, top_left_front}, mesh_color),       // left face
        face({top_left_front, bot_left_back, bot_left_front}, mesh_color),      // left face
        face({top_right_back, bot_right_back, bot_left_back}, mesh_color),      // rear face
        face({top_right_back, bot_left_back, top_left_back}, mesh_color),       // rear face
        face({top_left_back, top_right_back, top_left_front}, mesh_color),      // top face
        face({top_right_back, top_right_front, top_left_front}, mesh_color),    // top face
        face({bot_left_front, bot_right_front, bot_left_back}, mesh_color),     // bot face
        face({bot_right_front, bot_right_back, bot_left_back}, mesh_color)      // bot face
    };
}

box_mesh::box_mesh()
{
    initialise_mesh(vector3(1.0f, 1.0f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f));
}

box_mesh::box_mesh(const vector3 &dimensions)
{
    initialise_mesh(dimensions, color(1.0f, 1.0f, 1.0f, 1.0f));
}

box_mesh::box_mesh(const vector3 &dimensions, const color &mesh_color)
{
    initialise_mesh(dimensions, mesh_color);
}