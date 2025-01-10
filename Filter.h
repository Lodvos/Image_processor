#pragma once

#include <iostream>
#include "Image.h"

class Filter {
public:
    Filter(){};
    virtual void Change(Image& image, std::vector<std::string> pars){};
    virtual ~Filter(){};
};

class Negative : public Filter {
public:
    Negative();
    ~Negative() override{};
    void Change(Image& image, std::vector<std::string> pars) override;
};

class Grayscale : public Filter {
public:
    Grayscale();
    ~Grayscale() override{};
    void Change(Image& image, std::vector<std::string> pars) override;
};

class Sharpening : public Filter {
public:
    Sharpening();
    ~Sharpening() override{};
    void Change(Image& image, std::vector<std::string> pars) override;
};