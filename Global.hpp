#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include "Box.hpp"
#include "Button.hpp"
#include "ClickEvent.hpp"
#include "ElementParameters.hpp"
#include "Event.hpp"
#include "EventSystem.hpp"
#include "Selected.hpp"
#include "Factory.hpp"
#include "GUIFile.hpp"
#include "GuiElement.hpp"
#include "Layout.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "Freehand.hpp"
#include "Screen.hpp"
#include "ShowEvent.hpp"
#include "Sound.hpp"
#include "SoundEvent.hpp"
#include "MouseEvent.hpp"
#include "MouseDownEvent.hpp"
#include "MouseMotionEvent.hpp"
#include "MouseUpEvent.hpp" 
#include "SoundPlayer.hpp"
#include "SoundState.hpp"
#include "Triangle.hpp"
#include "XmlWriteHelpers.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include <fstream>


const int X = 960, Y = 540;
extern SDL_Window* window;
extern Screen* screen;
extern SoundPlayer* soundPlayer;
extern Layout* rootLayout;
extern Layout* toolBarLayout;
extern Layout* tempLayout;
extern Layout* canvasLayout;
extern Layout* boundingLayout;
extern SDL_Renderer* renderer;


const int p = 10;
const int bW = 76;
const int bigBW = 131;
const int bH = Y / 10;

extern Button* selectButton;
extern Button* pointButton;
extern Button* lineButton;
extern Button* boxButton;
extern Button* triangleButton;
extern Button* ellipseButton;
extern Button* arrowButton;
extern Button* textBoxButton;
extern Button* freehandLineButton;
extern Button* freehandShapeButton;
extern Button* saveButton;
extern Button* loadButton;
extern Uint64 saveFlashUntil;
extern Uint64 loadFlashUntil;
extern GuiElement* draggingElement;
extern guiElement draggingType;
extern ElementParameters originalElementParameters;
extern ElementParameters draggingElementParameters;
extern ivec2 lastMousePos;
extern ElementParameters clipboard;
extern guiElement clipboardType;


void createWindow();
void createScreen();
Layout* createRootLayout(int& type, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void setEventSystem();
void initButtons(Layout *layout, int& type, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void resetGlobalPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);
void saveCanvas(const std::string& filePath);
void loadCanvas(const std::string& filePath, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void updateToolbarButtonColors(int& type);
void updateActionButtonColors();

#endif