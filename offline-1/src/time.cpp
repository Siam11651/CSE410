#include <time.hpp>
#include <thread>

std::chrono::steady_clock::time_point time::s_frame_begin_time_point;
std::chrono::steady_clock::time_point time::s_frame_end_time_point;
float time::s_delta_time = 0.0f;

const float &time::FPS()
{
    return s_FPS;
}

int64_t time::frame_time_ns()
{
    return (int64_t)(1000000000 / s_FPS);
}

void time::start_frame()
{
    s_frame_begin_time_point = std::chrono::steady_clock::now();
}

void time::end_frame()
{
    s_frame_end_time_point = std::chrono::steady_clock::now();
    std::chrono::nanoseconds nanoseconds = s_frame_end_time_point - s_frame_begin_time_point;

    if(nanoseconds.count() < frame_time_ns())
    {
        std::chrono::nanoseconds sleep_time(frame_time_ns() - nanoseconds.count());

        std::this_thread::sleep_for(sleep_time);

        s_frame_end_time_point = std::chrono::steady_clock::now();
        nanoseconds = s_frame_end_time_point - s_frame_begin_time_point;
    }

    s_delta_time = nanoseconds.count() / 1e9f;
}

const float &time::delta_time()
{
    return s_delta_time;
}