#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>
#include <space.hpp>

class color
{
private:
    float m_r;
    float m_g;
    float m_b;
    float m_a;

public:
    color();
    color(const float &r, const float &g, const float &b, const float &a);
    float &r();
    float &g();
    float &b();
    float &a();
    const float &const_r() const;
    const float &const_g() const;
    const float &const_b() const;
    const float &const_a() const;
};

class face
{
private:
    std::array<vector3, 3> m_vertices; // keep the vertices anti-clockwise might help with shaders
    color m_face_color;

public:
    face(const std::array<vector3, 3> &vertices, const color &face_color);
    color &face_color();
    const color &const_face_color() const;
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