#include <scene.hpp>

view::view() {}

vector4 &view::eye()
{
    return m_eye;
}

const vector4 &view::ceye() const
{
    return m_eye;
}

vector4 &view::look()
{
    return m_look;
}

const vector4 &view::clook() const
{
    return m_look;
}

vector4 &view::up()
{
    return m_up;
}

const vector4 &view::cup() const
{
    return m_up;
}

perspective::perspective() {}

double &perspective::fov()
{
    return m_fov;
}

const double &perspective::cfov() const
{
    return m_fov;
}

double &perspective::aspect_ratio()
{
    return m_aspect_ratio;
}

const double &perspective::caspect_ratio() const
{
    return m_aspect_ratio;
}

double &perspective::far()
{
    return m_far;
}

const double &perspective::cfar() const
{
    return m_far;
}

double &perspective::near()
{
    return m_far;
}

const double &perspective::cnear() const
{
    return m_far;
}