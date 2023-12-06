#include <mesh.hpp>
#include <GL/gl.h>

face::face(const std::array<vector3, 3> &vertices)
{
    m_vertices = vertices;
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
    float colors[12][3] =
    {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f}
    };

    glBegin(GL_TRIANGLES);

    size_t index = 0;
    size_t color_index = 0;
    
    for(const face &face_item : m_faces)
    {
        glColor4f(colors[color_index][0], colors[color_index][1], colors[color_index][2], 1.0f);

        for(const vector3 &vertex_item : *face_item.get_vertices_ptr())
        {
            glVertex3f(vertex_item.const_x(), vertex_item.const_y(), vertex_item.const_z());
        }

        ++index;

        if(index % 2 == 0)
        {
            ++color_index;
        }
    }

    glEnd();
}