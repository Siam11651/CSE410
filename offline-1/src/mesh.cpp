#include <mesh.hpp>
#include <GL/gl.h>

color::color()
{
    m_r = 0.0f;
    m_g = 0.0f;
    m_b = 0.0f;
    m_a = 1.0f;
}

color::color(const float &r, const float &g, const float &b, const float &a)
{
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

float &color::r()
{
    return m_r;
}

float &color::g()
{
    return m_g;
}

float &color::b()
{
    return m_b;
}

float &color::a()
{
    return m_a;
}

const float &color::const_r() const
{
    return m_r;
}

const float &color::const_g() const
{
    return m_g;
}

const float &color::const_b() const
{
    return m_b;
}

const float &color::const_a() const
{
    return m_a;
}

mesh::mesh()
{

}

face::face(const std::array<vector3, 3> &vertices, const color &face_color)
{
    m_vertices = vertices;
    m_face_color = face_color;
}

color &face::face_color()
{
    return m_face_color;
}

const color &face::const_face_color() const
{
    return m_face_color;
}

const std::array<vector3, 3> *face::get_vertices_ptr() const
{
    return &m_vertices;
}

mesh::mesh(const std::vector<face> faces)
{
    m_faces = faces;
}

const std::vector<face> *mesh::get_faces_ptr() const
{
    return &m_faces;
}

void mesh::draw() const
{
    glBegin(GL_TRIANGLES);
    
    for(const face &face_item : m_faces)
    {
        const color &face_color = face_item.const_face_color();

        glColor4f(face_color.const_r(), face_color.const_g(),
            face_color.const_b(), face_color.const_a());

        for(const vector3 &vertex_item : *face_item.get_vertices_ptr())
        {
            glVertex3f(vertex_item.const_x(), vertex_item.const_y(), vertex_item.const_z());
        }
    }

    glEnd();
}