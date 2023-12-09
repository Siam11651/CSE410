#ifndef SCREEN_H
#define SCREEN_H

#include <cstddef>

class screen
{
private:
    static size_t s_window_width;
    static size_t s_window_height;

public:
    static size_t &window_width();
    static size_t &window_height();
    static float aspect_ratio();
};

#endif