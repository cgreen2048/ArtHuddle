#ifndef __API_HPP__
#define __API_HPP__

#include <SDL3/SDL.h>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include "ArtHuddle/core/InteractionState.hpp"
#include "ArtHuddle/core/DrawingMode.hpp"
#include "ArtHuddle/core/MessageTypes.hpp"
#include "ArtHuddle/core/EventTypes.hpp"

void initialize(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
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
ElementParameters paste();
ElementParameters changeColor(ivec3 colorIncrement);
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
bool isElementSelected();
bool isClickInside(ivec2 mousePos);
bool isSelectedInputTextBox();
bool setSelectedElement(ivec2 mousePos);
bool hasCanvas();
bool hasColorIndicator();
bool isClientConnected();
void clientProcessMessages();
void serverProcessMessages();
bool isServer();
void sendToServer(ElementParameters ep, MessageType type);
void createEvent(ivec2 coordinate, EventType type);

#endif