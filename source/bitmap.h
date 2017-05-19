#pragma once
#include <string>
#include <memory>

using byte = uint8_t;

class Color
{
public:

private:
    union
    {
        byte rgb[3];
        struct rgb
        {
            byte r, g, b;
        };
    };
};

class Bitmap
{
    using byte = uint8_t;
public:
    Bitmap(std::string filename, size_t width = 800, const size_t height = 800);
    ~Bitmap();

    void save();

    void get_pixel(const size_t x, const size_t y, int& r, int& g, int& b);

    void draw_pixel(const size_t x, const size_t y, int r, int g, int b);
    void draw_black(const size_t x, const size_t y, int value);

private:
    void fill_header(FILE* file, const size_t filesize, const size_t w, const size_t h);
    void write_image(FILE* file, const size_t filesize, const size_t w, const size_t h);

private:
    std::string _filename;
    size_t      _width;
    size_t      _height;
    byte*       _image = nullptr;
};