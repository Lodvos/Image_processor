#include "Filter.h"
#include "Image.h"
#include <iostream>

Grayscale::Grayscale(){};

void Grayscale::Change(Image& image, std::vector<std::string> pars) {
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB rgb = image.GetRgb(i, j);
            float r = rgb.r_;
            float g = rgb.g_;
            float b = rgb.b_;
            rgb.r_ = 0.299 * r + 0.587 * g + 0.114 * b;  // NOLINT
            rgb.g_ = 0.299 * r + 0.587 * g + 0.114 * b;  // NOLINT
            rgb.b_ = 0.299 * r + 0.587 * g + 0.114 * b;  // NOLINT
            image.ChangePixel(rgb, i, j);
        }
    }
}

Negative::Negative(){};

void Negative::Change(Image& image, std::vector<std::string> pars) {
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB rgb = image.GetRgb(i, j);
            rgb.r_ = 1 - rgb.r_;  // NOLINT
            rgb.g_ = 1 - rgb.g_;  // NOLINT
            rgb.b_ = 1 - rgb.b_;  // NOLINT
            image.ChangePixel(rgb, i, j);
        }
    }
}

Sharpening::Sharpening(){};

void Sharpening::Change(Image& image, std::vector<std::string> pars) {
    Image image_base = image;
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB rgb = image_base.GetRgb(i, j);
            RGB rgb_c = image_base.GetRgb(i, j);
            rgb.r_ *= 5;  // NOLINT
            rgb.g_ *= 5;  // NOLINT
            rgb.b_ *= 5;  // NOLINT
            if (j > 0) {
                RGB rgb_new = image_base.GetRgb(i, j - 1);
                rgb.r_ -= rgb_new.r_;
                rgb.g_ -= rgb_new.g_;
                rgb.b_ -= rgb_new.b_;
            } else {
                rgb.r_ -= rgb_c.r_;
                rgb.g_ -= rgb_c.g_;
                rgb.b_ -= rgb_c.b_;
            }
            if (i > 0) {
                RGB rgb_new = image_base.GetRgb(i - 1, j);
                rgb.r_ -= rgb_new.r_;
                rgb.g_ -= rgb_new.g_;
                rgb.b_ -= rgb_new.b_;
            } else {
                rgb.r_ -= rgb_c.r_;
                rgb.g_ -= rgb_c.g_;
                rgb.b_ -= rgb_c.b_;
            }
            if (i < image.Width() - 1) {
                RGB rgb_new = image_base.GetRgb(i + 1, j);
                rgb.r_ -= rgb_new.r_;
                rgb.g_ -= rgb_new.g_;
                rgb.b_ -= rgb_new.b_;
            } else {
                rgb.r_ -= rgb_c.r_;
                rgb.g_ -= rgb_c.g_;
                rgb.b_ -= rgb_c.b_;
            }
            if (j < image.Height() - 1) {
                RGB rgb_new = image_base.GetRgb(i, j + 1);
                rgb.r_ -= rgb_new.r_;
                rgb.g_ -= rgb_new.g_;
                rgb.b_ -= rgb_new.b_;
            } else {
                rgb.r_ -= rgb_c.r_;
                rgb.g_ -= rgb_c.g_;
                rgb.b_ -= rgb_c.b_;
            }
            if (rgb.r_ < 0) {
                rgb.r_ = 0;
            } else if (rgb.r_ > 1) {
                rgb.r_ = 1;
            }
            if (rgb.g_ < 0) {
                rgb.g_ = 0;
            } else if (rgb.g_ > 1) {
                rgb.g_ = 1;
            }
            if (rgb.b_ < 0) {
                rgb.b_ = 0;
            } else if (rgb.b_ > 1) {
                rgb.b_ = 1;
            }
            image.ChangePixel(rgb, i, j);
        }
    }
}