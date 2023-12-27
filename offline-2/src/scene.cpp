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