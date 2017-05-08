#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>

#include "bitmap.h"
#include "can_linux.h"

int main(int ac, char* av[])
{
    auto w = 666;
    auto h = 666;
    Bitmap bmp("vika.bmp",w,h);

    const size_t max_quaternion_count = 10'000;
    for (size_t i = 0; i < max_quaternion_count; ++i)
    {
    }

    for (size_t i = 0; i < w; ++i)
    {
        for (size_t j = 0; j < h; ++j)
        {
            bmp.draw_black(i, j, j);
        }
    }
    
    bmp.save();

    std::cin.get();
	return 0;	
}