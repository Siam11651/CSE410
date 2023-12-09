#ifndef TIME_H
#define TIME_H

#include <chrono>

class time
{
private:
    static constexpr float s_FPS = 60.0f;
    static std::chrono::steady_clock::time_point s_frame_begin_time_point;
    static std::chrono::steady_clock::time_point s_frame_end_time_point;
    static float s_delta_time;

public:
    static const float &FPS();
    static inline int64_t frame_time_ns();
    static void start_frame();
    static void end_frame();
    static const float &delta_time();
};

#endif