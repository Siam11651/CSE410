#ifndef CAMERA_H
#define CAMERA_H

#include <vector.hpp>

class transform
{
private:
    vector3 m_position;
    vector3 m_euler_rotation;

public:
    transform();
    transform(const vector3 &position, const vector3 &euler_rotation);
    vector3 &position();        // setter and getter
    vector3 &euler_rotation();  // setter and getter
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_right() const;
};

#endif