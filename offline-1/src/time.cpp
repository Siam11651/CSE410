#include <time.hpp>
#include <thread>

std::chrono::steady_clock::time_point time::s_start_time_point;
std::chrono::steady_clock::time_point time::s_frame_begin_time_point;
std::chrono::steady_clock::time_point time::s_frame_end_time_point;
float time::s_delta_time_s = 0.0f;

const float &time::FPS()
{
    return s_FPS;
}

int64_t time::frame_time_ns()
{
    return (int64_t)(1000000000 / s_FPS);
}

void time::initialise()
{
    s_start_time_point = std::chrono::steady_clock::now();
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

    s_delta_time_s = nanoseconds.count() / 1e9f;
}

const float &time::delta_time_s()
{
    return s_delta_time_s;
}

int64_t time::now_ns()
{
    std::chrono::steady_clock::time_point now_time_point(std::chrono::steady_clock::now());
    std::chrono::nanoseconds time_point_ns(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
        now_time_point - s_start_time_point).count());

    return time_point_ns.count();
}

float time::now_s()
{
    return now_ns() / 1e9f;
}