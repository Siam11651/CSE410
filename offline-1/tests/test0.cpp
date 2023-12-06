#include <transform.hpp>
#include <cstdint>
#include <iostream>

int main()
{
    for(int8_t x = -90; x <= 90; ++x)
    {
        for(int8_t y = -90; y <= 90; ++y)
        {
            for(int8_t z = -90; z <= 90; ++z)
            {
                transform instance(vector3(0.0f, 0.0f, 0.0f), vector3(x, y, z));
                vector3 direction = instance.get_forward();
                float magnitude = direction.get_magnitude();

                if(std::abs(magnitude - 1.0f) > 1e-6)
                {
                    std::cerr << "Forward fail on "
                        << "x = " << (int16_t)x << ' '
                        << "y = " << (int16_t)y << ' '
                        << "z = " << (int16_t)z << std::endl;

                    return -1;
                }

                direction = instance.get_right();
                magnitude = direction.get_magnitude();

                if(std::abs(magnitude - 1.0f) > 1e-6)
                {
                    std::cerr << "Right fail on "
                        << "x = " << (int16_t)x << ' '
                        << "y = " << (int16_t)y << ' '
                        << "z = " << (int16_t)z << std::endl;

                    return -1;
                }
            }
        }
    }

    return 0;
}