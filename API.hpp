#ifndef __API_HPP__
#define __API_HPP__

#include <SDL3/SDL.h>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include "vec2.hpp"
#include "vec3.hpp"
#include "Layout.hpp"

Layout* initialize();
void loadSound(std::string filePath);
void playSound(std::string filePath, int loop);
void drawTempElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color);
void drawElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color);
void clicked(ivec2 coords);
bool isSelectedTextBox();
void appendToTextBox(const std::string& s);
void deleteText();
void deleteShape();
void update();
void closeAll();

#endif