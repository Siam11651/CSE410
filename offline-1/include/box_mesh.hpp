#ifndef BOX_MESH_H
#define BOX_MESH_H

#include <mesh.hpp>

class box_mesh : public mesh
{
private:
    float m_size_x;
    float m_size_y;
    float m_size_z;

public:
    box_mesh(const float &size_x = 1.0f, const float &size_y = 1.0f, const float &size_z = 1.0f);
    float get_size_x() const;
    float get_size_y() const;
    float get_size_z() const;
};

#endif