#include "helperFunctions.hpp"
#include <random>

#define GUI_ELEMENT_NAME_LENGTH 8


std::string generateElementName() {
    static const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, chars.size() - 1);
    static int GUI_ELEMENT_NAME_COUNTER = 0;

    std::string name;
    name.reserve(GUI_ELEMENT_NAME_LENGTH);

    for (int i = 0; i < GUI_ELEMENT_NAME_LENGTH; i++) {
        name += chars[dist(rng)];
    }

    name += std::to_string(GUI_ELEMENT_NAME_COUNTER);

    GUI_ELEMENT_NAME_COUNTER++;

    return name;
}