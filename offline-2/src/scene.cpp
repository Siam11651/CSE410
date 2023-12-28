#include <scene.hpp>
#include <cmath>

view::view() {}

matrix4x4 view::get_matrix() const
{
    const vector<3> forward(0.0, 0.0, -1.0);
    const vector<3> rotated_forward = (look - eye).get_normalized();
    const quaternion rotation(forward, rotated_forward);
    const matrix4x4 rotation_matrix = (-rotation).get_matrix();
    const matrix4x4 translation_matrix = matrix4x4::get_translation(-eye);

    return rotation_matrix * translation_matrix;
}

perspective::perspective() {}

matrix4x4 perspective::get_matrix() const
{
    constexpr double DEG2RAD = M_PI / 180.0;
    const double fovX = fovY * aspect_ratio;
    const double t = near * std::tan((fovY / 2.0) * DEG2RAD);
    const double r = near * std::tan((fovX / 2.0) * DEG2RAD);
    matrix4x4 projection;
    projection[0].x = near / r;
    projection[1].y = near / t;
    projection[2].z = -(far + near) / (far - near);
    projection[2].w = -1.0;
    projection[3].z = -(2.0 * far * near) / (far - near);

    return projection;
}