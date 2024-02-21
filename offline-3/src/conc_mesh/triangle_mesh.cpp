#include <conc_mesh/triangle_mesh.hpp>

triangle_mesh::triangle_mesh(const face &_face)
{
    m_faces.push_back(_face);
}