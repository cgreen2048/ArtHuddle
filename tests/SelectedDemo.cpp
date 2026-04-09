#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
#include "../ClickEvent.hpp"
#include "../ShowEvent.hpp"
#include "../SoundEvent.hpp"
#include "../EventSystem.hpp"
#include "../Factory.hpp"
#include "../Layout.hpp"
#include "../Box.hpp"
#include "../Button.hpp"
#include "../Screen.hpp"
#include "../GuiElement.hpp"
#include "../Selected.hpp"


const int X = 960, Y = 540;

int selectedDemo(Screen *screen, SDL_Window *window);
void spawnEvents();

int main() {
    std::cout << "Milestone 006 Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Milestone 006 Demo", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    Screen *screen = new Screen(X, Y);

    int failure = selectedDemo(screen, window);

    if (failure == 1) {
        std::cout << "Demo did not execute successfully\n";
    }
    else {
        std::cout << "Demo succeeded and window closed\n";
    }

    SDL_Quit();
    return failure;

}

int selectedDemo(Screen *screen, SDL_Window *window) {
    bool end = false;
    int failure = 0;
    SDL_Event event;
    EventSystem& eventSystem = EventSystem::getInstance();
    Selected& selectedSingleton = Selected::getInstance();
    SoundPlayer player;
    eventSystem.setSoundPlayer(&player);

    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0,0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0,0);
    rootLayout.parentEnd = ivec2(X,Y);
    rootLayout.active = true;
    rootLayout.name = "rootLayout";
    Layout *layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));

    ElementParameters boundingLayoutParam;
    boundingLayoutParam.layoutStart = vec2(0.0,0.0);
    boundingLayoutParam.layoutEnd = vec2(1.0, 1.0);
    boundingLayoutParam.parentStart = ivec2(0,0);
    boundingLayoutParam.parentEnd = ivec2(X,Y);
    boundingLayoutParam.active = true;
    boundingLayoutParam.name = "boundingLayout";
    Layout *boundingLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, boundingLayoutParam));
    selectedSingleton.setSelectedLayout(boundingLayout);
    layout->addElement(boundingLayout);

    ElementParameters pointParam;
    pointParam.point1 = ivec2(500, 500);
    pointParam.color = ivec3(20, 255, 20);
    pointParam.point1Type = TagType::IVec;
    pointParam.name = "point1";
    Point* point = dynamic_cast<Point*>(factory(guiElement::POINT, pointParam));
    layout->addElement(point);

    ElementParameters lineParam;
    lineParam.point1 = ivec2(450, 450);
    lineParam.point2 = ivec2(450, 375);
    lineParam.color = ivec3(20, 255, 20);
    lineParam.point1Type = TagType::IVec;
    lineParam.point2Type = TagType::IVec;
    lineParam.name = "line1";
    Line* line = dynamic_cast<Line*>(factory(guiElement::LINE, lineParam));
    layout->addElement(line);

    ElementParameters boxParam;
    boxParam.point1 = ivec2(50, 200);
    boxParam.point2 = ivec2(100, 300);
    boxParam.color = ivec3(20, 255, 20);
    boxParam.point1Type = TagType::IVec;
    boxParam.point2Type = TagType::IVec;
    boxParam.name = "box1";
    Box* box = dynamic_cast<Box*>(factory(guiElement::BOX, boxParam));
    layout->addElement(box);

    ElementParameters triangleParam;
    triangleParam.point1 = ivec2(450, 50);
    triangleParam.point2 = ivec2(450, 200);
    triangleParam.point3 = ivec2(300, 150);
    triangleParam.color = ivec3(20, 255, 20);
    triangleParam.point1Type = TagType::IVec;
    triangleParam.point2Type = TagType::IVec;
    triangleParam.point3Type = TagType::IVec;
    triangleParam.name = "triangle1";
    Triangle* triangle = dynamic_cast<Triangle*>(factory(guiElement::TRIANGLE, triangleParam));
    layout->addElement(triangle);

    ElementParameters ellipseParam;
    ellipseParam.center = ivec2(600, 300);
    ellipseParam.radiusX = 25;
    ellipseParam.radiusY = 50;
    ellipseParam.color = ivec3(20, 255, 20);
    ellipseParam.centerType = TagType::IVec;
    ellipseParam.name = "ellipse1";
    Ellipse* ellipse = dynamic_cast<Ellipse*>(factory(guiElement::ELLIPSE, ellipseParam));
    layout->addElement(ellipse);
    
    ElementParameters buttonParam;
    buttonParam.point1 = ivec2(X/4, Y/4);
    buttonParam.point2 = ivec2(X/2, Y/2);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.point1Type = TagType::IVec;
    buttonParam.point2Type = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    buttonParam.name = "button1";
    buttonParam.callback = spawnEvents;
    buttonParam.callbackName = "spawnEvents";
    Button* button = dynamic_cast<Button*>(factory(guiElement::BUTTON, buttonParam));
    layout->addElement(button);

    while (!end) {
        if (selectedSingleton.getSelectedElement()) {
            std::cout << selectedSingleton.getSelectedElement()->getName() << '\n';
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    end = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    eventSystem.push(std::make_unique<ClickEvent>(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                    break;
                }
            }
        }
        screen->clear(ivec3(255,255,255));

        layout->draw(screen);
        screen->blitTo(SDL_GetWindowSurface(window));
		SDL_UpdateWindowSurface(window);

        eventSystem.processEvents(layout);

    }

    return failure;
}

void spawnEvents() {
    std::cout << "Button clicked, spawning events\n";
    EventSystem& eventSystem = EventSystem::getInstance();
    eventSystem.push(std::make_unique<ShowEvent>("nestedLayout", ShowActionType::SHOW));
    eventSystem.push(std::make_unique<SoundEvent>("../SFX/song.wav", SoundActionType::PLAY, false));
}