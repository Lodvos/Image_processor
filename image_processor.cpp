#include "Image.h"
#include "Filter.cpp"
#include "map"
#include "open_save.cpp"
#include "RGB.cpp"
#include "Image.cpp"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    std::map<std::string, Filter*> filters;
    std::map<std::string, int> filters_count;
    filters_count["-neg"] = 0;
    filters_count["-gs"] = 0;
    filters_count["-edge"] = 1;
    filters_count["-sharp"] = 0;
    filters_count["-blur"] = 1;
    filters_count["-crop"] = 2;

    filters["-gs"] = new Grayscale();
    filters["-neg"] = new Negative();
    filters["-sharp"] = new Sharpening();
    filters["-edge"] = 0;
    filters["-blur"] = 0;
    filters["-crop"] = 0;

    std::queue<char*> args;
    for (int i = 1; i < argc; ++i) {
        args.push(argv[i]);
    }
    if (argc == 1) {
        std::cout << "Неправильный ввод" << std::endl;
    }
    if (argc == 2) {
        throw std::runtime_error("No output file");
    }

    char* input_file = args.front();
    args.pop();
    char* output_file = args.front();
    args.pop();

    Image image;
    image.Read(input_file);

    while (!args.empty()) {
        std::string filter_name = args.front();
        args.pop();
        if (filters.find(filter_name) == filters.end()) {
            throw std::runtime_error("filter not found");
        }
        std::vector<std::string> pars;
        for (int i = 0; i < filters_count.find(filter_name)->second; ++i) {
            if (args.empty()) {
                throw std::runtime_error("");
            }
            pars.push_back(args.front());
            args.pop();
        }

        filters.find(filter_name)->second->Change(image, pars);
    }

    SaveFile(output_file, image);
    for (auto& item : filters) {
        delete item.second;
    }
    return 0;
}