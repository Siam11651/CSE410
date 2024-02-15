#include <mesh.hpp>
#include <GL/gl.h>

color::color()
{
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
}

color::color(const float &_r, const float &_g, const float &_b, const float &_a)
{
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

color color::operator * (const float &value) const
{
    return color(r * value, g * value, b * value, a);
}

face::face(const std::array<vector3, 3> &_vertices, const color &_face_color)
{
    vertices = _vertices;
    face_color = _face_color;
}

vector3 face::get_normal() const
{
    vector3 edge0 = vector3(vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].z - vertices[0].z);
    vector3 edge1 = vector3(vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y, vertices[2].z - vertices[0].z);

    // return vector3::cross(edge0, edge1).get_normalized();
    return vector3::cross(edge1, edge0).get_normalized();
}

vector3 face::get_center() const
{
    float x_sum = 0.0f;
    float y_sum = 0.0f;
    float z_sum = 0.0f;

    for(size_t i = 0; i < 3; ++i)
    {
        x_sum += vertices[i].x;
        y_sum += vertices[i].y;
        z_sum += vertices[i].z;
    }

    return vector3(x_sum / 3.0f, y_sum / 3.0f, z_sum / 3.0f);
}

mesh::mesh()
{
    
}

mesh::mesh(const std::vector<face> faces)
{
    m_faces = faces;
}

const std::vector<face> *mesh::get_faces_ptr() const
{
    return &m_faces;
}

void mesh::draw(const transform &object_transform) const
{
    glBegin(GL_TRIANGLES);
    
    for(const face &face_item : m_faces)
    {
        const color &face_color = face_item.face_color;
        glColor4f(face_color.r, face_color.g, face_color.b, face_color.a);

        for(const vector3 &vertex_item : face_item.vertices)
        {
            glVertex3f(vertex_item.x, vertex_item.y, vertex_item.z);
        }
    }

    glEnd();
}