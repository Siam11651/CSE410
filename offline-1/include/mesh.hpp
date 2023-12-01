#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <array>
#include <vector.hpp>

class face
{
private:
    std::array<vector3, 3> m_vertices; // keep the vertices anti-clockwise might help with shaders

public:
    face(const std::array<vector3, 3> &vertices = std::array<vector3, 3>());
    const std::array<vector3, 3> *get_vertices_ptr() const;
};

class mesh
{
protected:
    std::vector<face> m_faces;

public:
    mesh(const std::vector<face> faces = std::vector<face>());
    const std::vector<face> *get_faces_ptr() const;
    void draw() const;
};

#endif