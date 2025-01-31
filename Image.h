#pragma once
#include <vector>
#include "RGB.h"

class Image {
private:
    int width_;
    int height_;
    int x_pixels_per_m_;
    int y_pixels_per_m_;
    std::vector<std::vector<RGB>> pixels_;

public:
    Image();
    Image(int width, int height);

    RGB GetRgb(int x, int y) const;
    void ChangePixel(RGB rgb, int x, int y);

    int Width() const;
    int Height() const;
    int GetXPixels() const;
    int GetYPixels() const;

    friend void SaveFile(const char* path, Image& image);  // Мейби умбрать

    void Read(const char* path);
};
