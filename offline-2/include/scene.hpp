#ifndef SCENE_H
#define SCENE_H

#include <space.hpp>

class view
{
private:
    bool m_updated;
    vector4 m_eye;
    vector4 m_look;
    vector4 m_up;

public:
    view();
    void set_eye(const vector4 &_eye);
    const vector4 &get_eye() const;
    void set_look(const vector4 &_look);
    const vector4 &get_look() const;
    void set_up(const vector4 &_up);
    const vector4 &get_up() const;
};

class perspective
{
private:
    bool m_updated;
    double m_fov;
    double m_aspect_ratio;
    double m_far;
    double m_near;

public:
    perspective();
    void set_fov(const double &_fov);
    const double &get_fov() const;
    void set_aspect_ratio(const double &_aspect_ratio);
    const double &get_aspect_ratio() const;
    void set_far(const double &_far);
    const double &get_far() const;
    void set_near(const double &_near);
    const double &get_near() const;
};

#endif