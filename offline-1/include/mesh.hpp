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
    color operator * (const float &value) const;
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
    vector3 get_normal() const;
    vector3 get_center() const;
    std::array<vector3, 3> &vertices();
    const std::array<vector3, 3> &const_vertices() const;
};

class light
{
private:
    transform m_transform;
    color m_color;

public:
    light();
    light(const transform &light_transform, const color &light_color);
    transform &light_transform();
    const transform &const_light_transform() const;
    color &light_color();
    const color &const_light_color() const;
};

class mesh
{
protected:
    std::vector<face> m_faces;
    float m_ambiance_intensity;
    bool m_shade;

public:
    mesh();
    mesh(const std::vector<face> faces);
    const std::vector<face> *get_faces_ptr() const;
    float &ambience_intensity();
    const float &const_ambience_intensity() const;
    bool &shade();
    const bool &shade() const;
    void draw(const light &scene_light, const transform &object_transform) const;
};

#endif