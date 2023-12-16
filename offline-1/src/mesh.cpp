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

color color::operator * (const float &value) const
{
    return color(m_r * value, m_g * value, m_b * value, m_a);
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

vector3 face::get_normal() const
{
    vector3 edge0 = vector3(m_vertices[1].const_x() - m_vertices[0].const_x(),
        m_vertices[1].const_y() - m_vertices[0].const_y(),
        m_vertices[1].const_z() - m_vertices[0].const_z());
    vector3 edge1 = vector3(m_vertices[2].const_x() - m_vertices[0].const_x(),
        m_vertices[2].const_y() - m_vertices[0].const_y(),
        m_vertices[2].const_z() - m_vertices[0].const_z());

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
        x_sum += m_vertices[i].const_x();
        y_sum += m_vertices[i].const_y();
        z_sum += m_vertices[i].const_z();
    }

    return vector3(x_sum / 3.0f, y_sum / 3.0f, z_sum / 3.0f);
}

std::array<vector3, 3> &face::vertices()
{
    return m_vertices;
}

const std::array<vector3, 3> &face::const_vertices() const
{
    return m_vertices;
}

light::light()
{
    m_color = color(1.0f, 1.0f, 1.0f, 1.0f);
}

light::light(const transform &light_transform, const color &light_color)
{
    m_transform = light_transform;
    m_color = light_color;
}

transform &light::light_transform()
{
    return m_transform;
}

const transform &light::const_light_transform() const
{
    return m_transform;
}

color &light::light_color()
{
    return m_color;
}

const color &light::const_light_color() const
{
    return m_color;
}

mesh::mesh()
{
    m_ambiance_intensity = 0.1f;
    m_shade = false;
}

mesh::mesh(const std::vector<face> faces)
{
    m_ambiance_intensity = 0.1f;
    m_shade = false;
    m_faces = faces;
}

const std::vector<face> *mesh::get_faces_ptr() const
{
    return &m_faces;
}

float &mesh::ambience_intensity()
{
    return m_ambiance_intensity;
}

const float &mesh::const_ambience_intensity() const
{
    return m_ambiance_intensity;
}

bool &mesh::shade()
{
    return m_shade;
}

const bool &mesh::shade() const
{
    return m_shade;
}

void mesh::draw(const light &scene_light, const transform &object_transform) const
{
    const transform &light_transform = scene_light.const_light_transform();
    const vector3 &light_position = light_transform.const_position();
    const quaternion &light_rotation = light_transform.const_rotation();

    glBegin(GL_TRIANGLES);
    
    for(const face &face_item : m_faces)
    {
        const color &face_color = face_item.const_face_color();

        if(m_shade)
        {
            vector3 normal = face_item.get_normal();
            normal = object_transform.const_rotation().get_rotated_vector(normal);
            normal.x() *= object_transform.const_scale().const_x();
            normal.y() *= object_transform.const_scale().const_y();
            normal.z() *= object_transform.const_scale().const_z();
            normal = normal.get_normalized();
            const vector3 light_forward = light_transform.get_forward();
            const float diffuse = std::max(vector3::dot(normal, light_forward), 0.0f);
            const color shaded_color = face_item.const_face_color() * (m_ambiance_intensity + diffuse);
            
            glColor4f(shaded_color.const_r(), shaded_color.const_g(),
                shaded_color.const_b(), shaded_color.const_a());
        }
        else
        {
            glColor4f(face_color.const_r(), face_color.const_g(),
                face_color.const_b(), face_color.const_a());
        }

        for(const vector3 &vertex_item : face_item.const_vertices())
        {
            glVertex3f(vertex_item.const_x(), vertex_item.const_y(), vertex_item.const_z());
        }
    }

    glEnd();
}