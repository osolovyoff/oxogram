#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <cmath>

#define M_PI 3.14f

#include "bitmap.h"
#include "can_linux.h"

int main(int ac, char* av[])
{

    auto w = 255;
    auto h = 255;

    Bitmap bmp("graph.bmp",w,h);
    for (size_t i = 0; i < 50; ++i)
    {
        const float heading = (rand() % 90 * M_PI) / 180;
        const float attitude = (rand() % 90 * M_PI) / 180;
        const float bank = (rand() % 90 * M_PI) / 180;

        const float c1 = cos(heading / 2);
        const float c2 = cos(bank / 2);
        const float c3 = sin(heading / 2);

        const float s1 = sin(heading / 2);
        const float s2 = sin(attitude / 2);
        const float s3 = sin(bank / 2);

        const float w = sqrt(1.0f + c1 + c2 + c1*c3 - s1*s2*s3 + c2*c3) / 2;
        const float x = (c2 * s3 + c1 *s3 + s1*s2*c3) / (4.0*w);
        const float y = (s1 *c2 + s1*c3 + c1*s2*s3) / (4.0 *w);
        const float z = (-s1 *s3 + c1*s2*c3 + s2) / (4.0*w);
        
        std::cout
            << w << " "
            << x << " "
            << y << " "
            << z << " "
            << std::endl;


        int in_r = 0;
        int in_g = 0;
        int in_b = 0;

        const uint8_t x_pixel = rand() % 255;
        const uint8_t y_pixel = rand() % 255;

        bmp.get_pixel(x_pixel, y_pixel, in_r, in_g, in_b);
        in_r++;
        in_g++;
        in_b++;

        bmp.draw_pixel(x_pixel, y_pixel, in_r, in_g, in_b);
    }

    bmp.save();

    std::cin.get();
	return 0;	
}