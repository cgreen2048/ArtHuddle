#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include "Box.hpp"
#include "Button.hpp"
#include "ClickEvent.hpp"
#include "ElementParameters.hpp"
#include "Event.hpp"
#include "EventSystem.hpp"
#include "Factory.hpp"
#include "GUIFile.hpp"
#include "GuiElement.hpp"
#include "Layout.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "Screen.hpp"
#include "ShowEvent.hpp"
#include "Sound.hpp"
#include "SoundEvent.hpp"
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

void createWindow();
void createScreen();
void createRootLayout();
void setEventSystem();

#endif