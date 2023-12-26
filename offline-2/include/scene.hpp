#ifndef SCENE_H
#define SCENE_H

#include <space.hpp>

class view
{
private:
    vector4 m_eye;
    vector4 m_look;
    vector4 m_up;

public:
    view();
    vector4 &eye();
    const vector4 &ceye() const;
    vector4 &look();
    const vector4 &clook() const;
    vector4 &up();
    const vector4 &cup() const;
};

class perspective
{
private:
    double m_fov;
    double m_aspect_ratio;
    double m_far;
    double m_near;

public:
    perspective();
    double &fov();
    const double &cfov() const;
    double &aspect_ratio();
    const double &caspect_ratio() const;
    double &far();
    const double &cfar() const;
    double &near();
    const double &cnear() const;
};

#endif