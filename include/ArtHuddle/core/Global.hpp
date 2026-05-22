#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include "ArtHuddle/elements/Box.hpp"
#include "ArtHuddle/elements/InputTextBox.hpp"
#include "ArtHuddle/elements/Button.hpp"
#include "ArtHuddle/events/ClickEvent.hpp"
#include "ArtHuddle/core/DrawingMode.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include "ArtHuddle/core/ElementTypes.hpp"
#include "ArtHuddle/events/Event.hpp"
#include "ArtHuddle/events/EventSystem.hpp"
#include "ArtHuddle/utility/Selected.hpp"
#include "ArtHuddle/elements/Factory.hpp"
#include "ArtHuddle/utility/GUIFile.hpp"
#include "ArtHuddle/elements/GuiElement.hpp"
#include "ArtHuddle/elements/Layout.hpp"
#include "ArtHuddle/elements/Line.hpp"
#include "ArtHuddle/elements/Point.hpp"
#include "ArtHuddle/elements/Freehand.hpp"
#include "ArtHuddle/elements/Screen.hpp"
#include "ArtHuddle/events/ShowEvent.hpp"
#include "ArtHuddle/utility/Sound.hpp"
#include "ArtHuddle/events/SoundEvent.hpp"
#include "ArtHuddle/events/MouseEvent.hpp"
#include "ArtHuddle/events/MouseDownEvent.hpp"
#include "ArtHuddle/events/MouseMotionEvent.hpp"
#include "ArtHuddle/events/MouseUpEvent.hpp"
#include "ArtHuddle/utility/SoundPlayer.hpp"
#include "ArtHuddle/core/SoundState.hpp"
#include "ArtHuddle/utility/ThreadPool.hpp"
#include "ArtHuddle/elements/Triangle.hpp"
#include "ArtHuddle/core/XmlWriteHelpers.hpp"
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"
#include <fstream>
#include <filesystem>
#include <SDL3/SDL.h>
#include <SDL3/SDL_dialog.h>
#include "ArtHuddle/network/RelayServer.hpp"
#include "ArtHuddle/network/ClientNetwork.hpp"
#include "ArtHuddle/network/InitializeClientMessage.hpp"
#include "ArtHuddle/core/MessageTypes.hpp"
#include <string>
#include <chrono>



const int X = 960, Y = 540;
const int centerX = X/2, centerY = Y/2;
extern SDL_Window* window;
extern Screen* screen;
extern SoundPlayer* soundPlayer;
extern Layout* rootLayout;
extern Layout* toolBarLayout;
extern Layout* tempLayout;
extern Layout* canvasLayout;
extern Layout* serverLayout;
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
extern Button* colorIndicator;
extern Button* startDrawingButton;
extern Button* connectToHostButton;
extern Uint64 saveFlashUntil;
extern Uint64 loadFlashUntil;
extern GuiElement* draggingElement;
extern guiElement draggingType;
extern ElementParameters originalElementParameters;
extern ElementParameters draggingElementParameters;
extern ivec2 lastMousePos;
extern ElementParameters clipboard;
extern guiElement clipboardType;
extern std::filesystem::path currentFileLoadPath;
extern std::filesystem::path currentFileSavePath;
extern SDL_Cursor* arrowCursor;
extern SDL_Cursor* handCursor;
extern SDL_Cursor* currentCursor;

extern std::unique_ptr<RelayServer> server;
extern std::unique_ptr<ClientNetwork> client;
extern std::unique_ptr<ThreadPool> pool;
extern std::string connectedHost;
extern bool isHost;

const std::vector<const char*> hosts = {"10.24.102.212", "129.74.152.140", "129.74.152.141", "129.74.152.142", "129.74.152.143", "127.0.0.1"};

extern InputTextBox* hostIpTextBox;
extern Button* submitHostIpButton;

extern Button* pressedButton;

extern bool pendingStartHost;
extern bool pendingJoinHost;
extern std::atomic<bool> pendingDisconnect;
extern std::string pendingHostIp;
extern Button* disconnectButton;
extern Button* welcomeMessage;


void createWindow();
void createScreen();
Layout* createStartMenuLayout(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void createDrawingLayout(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void setEventSystem();
void initButtons(Layout *layout, DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void resetGlobalPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);
void saveCanvas(const std::string& filePath);
void loadCanvas(const std::string& filePath, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void updateToolbarButtonColors(DrawingMode mode);
void updateActionButtonColors();
static void SDLCALL loadFileCallback(void* userdata, const char* const* filelist, int filter);
static void SDLCALL saveFileCallback(void* userdata, const char* const* filelist, int filter);
void updateLoadSavePermissions();
void switchToDrawingLayout(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3);
void resetGlobalState();



#endif