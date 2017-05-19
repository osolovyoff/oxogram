#pragma once
#include <cstdint>

class Color
{
public:
    Color(uint8_t r, uint8_t g, uint8_t b);

private:
    union
    {
        uint8_t rgb
    };
    uint8_t rgb/
        .
};