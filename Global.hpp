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

const int X = 960, Y = 540;
extern SDL_Window* window;
extern Screen* screen;
extern SoundPlayer* soundPlayer;
extern Layout* rootLayout;
extern Layout* tempLayout;
extern Layout* boundingLayout;
extern SDL_Renderer* renderer;
extern GuiElement* draggingElement;
extern guiElement draggingType;
extern ElementParameters originalElementParameters;
extern ElementParameters draggingElementParameters;
extern ivec2 lastMousePos;
extern ElementParameters clipboard;
extern guiElement clipboardType;
void createWindow();
void createScreen();
Layout* createRootLayout();
void setEventSystem();

#endif