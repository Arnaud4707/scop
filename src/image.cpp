#include "../include/header.hpp"

ImagePPM loadPPM(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Impossible open file : " + filename);
		glfwDestroyWindow(pointer_object.window);
		glfwTerminate();
    }

    std::string format;
    int width, height, maxColor;

    file >> format;
    if (format != "P6") {
        throw std::runtime_error("Only PPM P6 format is supported : " + format);
    }

    // skip comment
    char ch;
    file >> ch;
    while (ch == '#') {
        std::string dummy;
        std::getline(file, dummy);
        file >> ch;
    }
    file.unget();

    file >> width >> height >> maxColor;

    if (maxColor != 255) {
        throw std::runtime_error("Only 255 max value is supported.");
    }

    while (isspace(file.peek())) {
        file.get();
    }

    ImagePPM img;
    img.width = width;
    img.height = height;
    img.pixels.resize(width * height * 3);

    int rowSize = width * 3;
    for (int y = 0; y < height; ++y) {
        int targetY = height - 1 - y; 
        file.read(reinterpret_cast<char*>(img.pixels.data() + (targetY * rowSize)), rowSize);
    }
    return img;
}