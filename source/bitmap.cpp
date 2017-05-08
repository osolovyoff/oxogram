#include "bitmap.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

Bitmap::Bitmap(std::string filename, size_t width, const size_t height)
    : _filename(filename)
    , _width(width)
    , _height(height)
{
    _image = (unsigned char *)malloc(3 * _width*_height);
    memset(_image, 0, sizeof(_image));
}

Bitmap::~Bitmap()
{
    if (_image)
        free(_image);
}

void Bitmap::save()
{
    const size_t filesize = 54 + 3 * _width*_height;

    FILE *file_handle;
    file_handle = fopen(_filename.c_str(), "wb");
    fill_header(file_handle, filesize, _width, _height);
    write_image(file_handle, filesize, _width, _height);

    fclose(file_handle);
}

void Bitmap::draw()
{
    //for (size_t i = 0; i<_width; i++)
    //{
    //    for (size_t j = 0; j<_height; j++)
    //    {
    //        const size_t x = i;
    //        const size_t y = (_height - 1) - j;
    //        draw_pixel(x, y, 125, 125, 125);
    //    }
    //}

}

void Bitmap::draw_pixel(const size_t x, const size_t y, int r, int g, int b)
{
    _image[(x + y*_width) * 3 + 2] = (byte)(r < 255) ? r : 255;
    _image[(x + y*_width) * 3 + 1] = (byte)(g < 255) ? g : 255;
    _image[(x + y*_width) * 3 + 0] = (byte)(b < 255) ? b : 255;
}

void Bitmap::draw_black(const size_t x, const size_t y, int value)
{
    _image[(x + y*_width) * 3 + 2] = (byte)(value < 255) ? value : 255;
    _image[(x + y*_width) * 3 + 1] = (byte)(value < 255) ? value : 255;
    _image[(x + y*_width) * 3 + 0] = (byte)(value < 255) ? value : 255;
}

void Bitmap::fill_header(FILE * file, const size_t filesize, const size_t w, const size_t h)
{
    unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
    unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
    
    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);

    fwrite(bmpfileheader, 1, 14, file);
    fwrite(bmpinfoheader, 1, 40, file);
}

void Bitmap::write_image(FILE * file, const size_t filesize, const size_t w, const size_t h)
{
    unsigned char bmppad[3] = { 0,0,0 };
    for (size_t i = 0; i<h; i++)
    {
        fwrite(_image + (w*(h - i - 1) * 3), 3, w, file);
        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, file);
    }
}