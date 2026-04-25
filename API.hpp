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
#include "InteractionState.hpp"
#include "DrawingMode.hpp"


Layout* initialize(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void loadSound(std::string filePath);
void playSound(std::string filePath, int loop);
void drawTempElement(guiElement ge, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color);
void drawElement(guiElement ge, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color);
void startFreehandDraw(const ivec2& point, const ivec3& color, bool isFreehandShape);
void continueFreehandDraw(const ivec2& point);
void endFreehandDraw(const ivec2& point);
void setClickAndDrag(ivec2);
void endClickAndDrag();
void drawClickAndDrag(ivec2);
void cancelMove();
void unselect();
void clicked(ivec2 coords);
bool isSelectedTextBox();
void appendToTextBox(const std::string& s);
void deleteText();
void deleteTempShape();
void deleteShape();
void updateScreen(DrawingMode mode);
void closeAll();
void copy();
void paste();
bool changeColor(ivec3 colorIncrement);
void updateCursorIcon(const ivec2& point, bool currentlyDragging);
int requiredPointsForType(guiElement type);
guiElement tempElementType(DrawingMode mode);
guiElement modeToType(DrawingMode mode);
void storePoint(int points, ivec2 mousePos, ivec2& point1, ivec2& point2, ivec2& point3);
void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);


#endif