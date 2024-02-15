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

face::face(const std::array<glm::vec3, 3> &_vertices, const color &_face_color)
{
    vertices = _vertices;
    face_color = _face_color;
}

glm::vec3 face::get_normal() const
{
    glm::vec3 edge0(vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].z - vertices[0].z);
    glm::vec3 edge1(vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y, vertices[2].z - vertices[0].z);

    // return glm::vec3::cross(edge0, edge1).get_normalized();
    return glm::normalize(glm::cross(edge1, edge0));
}

glm::vec3 face::get_center() const
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

    return glm::vec3(x_sum / 3.0f, y_sum / 3.0f, z_sum / 3.0f);
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

        for(const glm::vec3 &vertex_item : face_item.vertices)
        {
            glVertex3f(vertex_item.x, vertex_item.y, vertex_item.z);
        }
    }

    glEnd();
}