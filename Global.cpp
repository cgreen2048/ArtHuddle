#include "Global.hpp"

SDL_Window* window = nullptr;
Screen* screen = nullptr;
SoundPlayer* soundPlayer = nullptr;
Layout* rootLayout = nullptr;
Layout* tempLayout = nullptr;
SDL_Renderer* renderer = nullptr;

void createWindow() {
    window = SDL_CreateWindow("ArtHuddle", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
    }
}

void createScreen() {
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    screen = new Screen(X, Y, renderer);
}

Layout* createRootLayout() {
    ElementParameters root;
    root.layoutStart = vec2(0.0,0.0);
    root.layoutEnd = vec2(1.0, 1.0);
    root.parentStart = ivec2(0,0);
    root.parentEnd = ivec2(X,Y);
    root.active = true;
    root.name = "rootLayout";
    rootLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, root));
    
    ElementParameters temp;
    temp.layoutStart = vec2(0.0,0.0);
    temp.layoutEnd = vec2(1.0, 1.0);
    temp.parentStart = ivec2(0,0);
    temp.parentEnd = ivec2(X,Y);
    temp.active = true;
    temp.name = "tempLayout";
    tempLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, temp));
    rootLayout->addElement(tempLayout);

    Selected& selectedSingleton = Selected::getInstance();
    ElementParameters boundingLayoutParam;
    boundingLayoutParam.layoutStart = vec2(0.0,0.0);
    boundingLayoutParam.layoutEnd = vec2(1.0, 1.0);
    boundingLayoutParam.parentStart = ivec2(0,0);
    boundingLayoutParam.parentEnd = ivec2(X,Y);
    boundingLayoutParam.active = true;
    boundingLayoutParam.name = "boundingLayout";
    Layout *boundingLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, boundingLayoutParam));
    selectedSingleton.setSelectedLayout(boundingLayout);
    rootLayout->addElement(boundingLayout);

    return rootLayout;
}

void setEventSystem() {
    EventSystem& eventSystem = EventSystem::getInstance();
    soundPlayer = new SoundPlayer();
    eventSystem.setSoundPlayer(soundPlayer);
}