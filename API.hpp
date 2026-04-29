#ifndef __API_HPP__
#define __API_HPP__

#include <SDL3/SDL.h>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include "vec2.hpp"
#include "vec3.hpp"
#include "Layout.hpp"
#include "ElementParameters.hpp"
#include "InteractionState.hpp"
#include "DrawingMode.hpp"

// const std::vector<const char*> hosts = {"10.24.102.212", "129.74.152.140", "129.74.152.141", "129.74.152.142", "129.74.152.143", "127.0.0.1"};

Layout* initialize(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void loadSound(std::string filePath);
void playSound(std::string filePath, int loop);
void drawTempElement(guiElement ge, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color);
ElementParameters drawElement(guiElement ge, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color);
void startFreehandDraw(const ivec2& point, const ivec3& color, bool isFreehandShape);
void continueFreehandDraw(const ivec2& point);
ElementParameters endFreehandDraw(const ivec2& point);
void setClickAndDrag(ivec2);
ElementParameters endClickAndDrag();
void drawClickAndDrag(ivec2);
void cancelMove();
void unselect();
void clicked(ivec2 coords);
bool isSelectedTextBox();
ElementParameters appendToTextBox(const std::string& s);
ElementParameters deleteText();
void deleteTempShape();
std::string deleteShape();
void updateScreen(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void handlePendingActions(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void closeAll();
void copy();
void paste();
bool changeColor(ivec3 colorIncrement);
void updateCursorIcon(const ivec2& point, bool currentlyDragging);
bool pressedStartLayoutButton(const ivec2& point);
bool pressedToolbarButton(const ivec2& point);
bool isInsideSameButton(const ivec2& point);
void resetPressedButton();
int requiredPointsForType(guiElement type);
guiElement tempElementType(DrawingMode mode);
guiElement modeToType(DrawingMode mode);
void storeCommittedPoint(int points, ivec2 mousePos, ivec2& point1, ivec2& point2, ivec2& point3);
void storeTemporaryPoint(int points, ivec2 mousePos, ivec2& point1, ivec2& point2, ivec2& point3);
void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);
void playDrawClickSound();
void playButtonClickSound();
void playFreehandDrawSound();
void playDeleteSound();


#endif