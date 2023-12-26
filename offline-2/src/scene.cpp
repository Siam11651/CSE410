#include <scene.hpp>
#include <cmath>

view::view() {}

const matrix4x4 &view::get_matrix() const
{
    vector<3> forward = (look - eye).get_normalized();
}

perspective::perspective() {}