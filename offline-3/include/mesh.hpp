#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>
#include <space.hpp>

class color
{
public:
    float r;
    float g;
    float b;
    float a;

    color();
    color(const float &_r, const float &_g, const float &_b, const float &_a);
    color operator * (const float &value) const;
};

class face
{
public:
    std::array<glm::vec3, 3> vertices; // keep the vertices anti-clockwise might help with shaders
    color face_color;

    face(const std::array<glm::vec3, 3> &_vertices, const color &_face_color);
    glm::vec3 get_normal() const;
    glm::vec3 get_center() const;
};

class mesh
{
protected:
    std::vector<face> m_faces;

public:
    mesh();
    mesh(const std::vector<face> faces);
    const std::vector<face> *get_faces_ptr() const;
    void draw(const transform &object_transform) const;
};

#endif