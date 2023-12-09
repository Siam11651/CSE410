#include <screen.hpp>

size_t screen::s_window_width;
size_t screen::s_window_height;

size_t &screen::window_width()
{
    return s_window_width;
}

size_t &screen::window_height()
{
    return s_window_height;
}

float screen::aspect_ratio()
{
    return (float)s_window_width / s_window_height;
}