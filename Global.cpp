#include "Global.hpp"

SDL_Window* window = nullptr;
Screen* screen = nullptr;
SoundPlayer* soundPlayer = nullptr;
Layout* rootLayout = nullptr;


void createWindow() {
    window = SDL_CreateWindow("ArtHuddle", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
    }
}

void createScreen() {
    screen = new Screen(X, Y);
}

void createRootLayout() {
    ElementParameters root;
    root.layoutStart = vec2(0.0,0.0);
    root.layoutEnd = vec2(1.0, 1.0);
    root.parentStart = ivec2(0,0);
    root.parentEnd = ivec2(X,Y);
    root.active = true;
    root.name = "rootLayout";
    rootLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, root));
}

void setEventSystem() {
    EventSystem& eventSystem = EventSystem::getInstance();
    soundPlayer = new SoundPlayer();
    eventSystem.setSoundPlayer(soundPlayer);
}