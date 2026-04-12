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

int selectedDemo(Screen *screen, SDL_Window *window, SDL_Renderer *renderer);
void spawnEvents();

int main()
{
    std::cout << "Selected Singleton Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Selected Singleton Demo", X, Y, 0);
    if (!window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Screen *screen = new Screen(X, Y, renderer);

    int failure = selectedDemo(screen, window, renderer);

    if (failure == 1)
    {
        std::cout << "Demo did not execute successfully\n";
    }
    else
    {
        std::cout << "Demo succeeded and window closed\n";
    }

    SDL_Quit();
    return failure;
}

int selectedDemo(Screen *screen, SDL_Window *window, SDL_Renderer *renderer)
{
    bool end = false;
    int failure = 0;
    SDL_Event event;
    EventSystem &eventSystem = EventSystem::getInstance();
    Selected &selectedSingleton = Selected::getInstance();
    SoundPlayer player;
    eventSystem.setSoundPlayer(&player);

    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0, 0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;
    rootLayout.name = "rootLayout";
    Layout *layout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, rootLayout));

    ElementParameters pointParam;
    pointParam.coords = ivec2(500, 500);
    pointParam.color = ivec3(20, 255, 20);
    pointParam.coordsType = TagType::IVec;
    pointParam.name = "point1";
    Point *point = dynamic_cast<Point *>(factory(guiElement::POINT, pointParam));
    layout->addElement(point);

    ElementParameters lineParam;
    lineParam.start = ivec2(450, 450);
    lineParam.end = ivec2(450, 375);
    lineParam.color = ivec3(20, 255, 20);
    lineParam.startType = TagType::IVec;
    lineParam.endType = TagType::IVec;
    lineParam.name = "line1";
    Line *line = dynamic_cast<Line *>(factory(guiElement::LINE, lineParam));
    layout->addElement(line);

    ElementParameters boxParam;
    boxParam.min = ivec2(50, 200);
    boxParam.max = ivec2(100, 300);
    boxParam.color = ivec3(20, 255, 20);
    boxParam.minType = TagType::IVec;
    boxParam.maxType = TagType::IVec;
    boxParam.name = "box1";
    Box *box = dynamic_cast<Box *>(factory(guiElement::BOX, boxParam));
    layout->addElement(box);

    ElementParameters triangleParam;
    triangleParam.pointA = ivec2(450, 50);
    triangleParam.pointB = ivec2(450, 200);
    triangleParam.pointC = ivec2(300, 150);
    triangleParam.color = ivec3(20, 255, 20);
    triangleParam.pointAType = TagType::IVec;
    triangleParam.pointBType = TagType::IVec;
    triangleParam.pointCType = TagType::IVec;
    triangleParam.name = "triangle1";
    Triangle *triangle = dynamic_cast<Triangle *>(factory(guiElement::TRIANGLE, triangleParam));
    layout->addElement(triangle);

    ElementParameters ellipseParam;
    ellipseParam.center = ivec2(600, 300);
    ellipseParam.radiusX = 25;
    ellipseParam.radiusY = 50;
    ellipseParam.color = ivec3(20, 255, 20);
    ellipseParam.centerType = TagType::IVec;
    ellipseParam.name = "ellipse1";
    Ellipse *ellipse = dynamic_cast<Ellipse *>(factory(guiElement::ELLIPSE, ellipseParam));
    layout->addElement(ellipse);

    ElementParameters buttonParam;
    buttonParam.min = ivec2(X / 4, Y / 4);
    buttonParam.max = ivec2(X / 2, Y / 2);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.minType = TagType::IVec;
    buttonParam.maxType = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    buttonParam.name = "button1";
    buttonParam.callback = spawnEvents;
    buttonParam.callbackName = "spawnEvents";
    Button *button = dynamic_cast<Button *>(factory(guiElement::BUTTON, buttonParam));
    layout->addElement(button);

    ElementParameters arrowParam;
    arrowParam.min = ivec2(500, 50);
    arrowParam.max = ivec2(700, 150);
    arrowParam.pointA = ivec2(700, 25);
    arrowParam.pointB = ivec2(700, 175);
    arrowParam.pointC = ivec2(800, 100);
    arrowParam.minType = TagType::IVec;
    arrowParam.maxType = TagType::IVec;
    arrowParam.pointAType = TagType::IVec;
    arrowParam.pointBType = TagType::IVec;
    arrowParam.pointCType = TagType::IVec;
    arrowParam.color = ivec3(125, 125, 125);
    arrowParam.colorType = TagType::IVec;
    arrowParam.name = "arrow1";
    Arrow *arrow = dynamic_cast<Arrow *>(factory(guiElement::ARROW, arrowParam));
    layout->addElement(arrow);

    ElementParameters boundingLayoutParam;
    boundingLayoutParam.layoutStart = vec2(0.0, 0.0);
    boundingLayoutParam.layoutEnd = vec2(1.0, 1.0);
    boundingLayoutParam.parentStart = ivec2(0, 0);
    boundingLayoutParam.parentEnd = ivec2(X, Y);
    boundingLayoutParam.active = true;
    boundingLayoutParam.name = "boundingLayout";
    Layout *boundingLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, boundingLayoutParam));
    selectedSingleton.setSelectedLayout(boundingLayout);
    layout->addElement(boundingLayout);

    while (!end)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
            {
                end = true;
                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                eventSystem.push(std::make_unique<ClickEvent>(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                break;
            }
            }
        }
        screen->clear(ivec3(255, 255, 255));

        layout->draw(screen);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        screen->renderToRenderer();
        layout->drawOverlay(screen);

        SDL_RenderPresent(renderer);

        eventSystem.processEvents(layout);
    }

    return failure;
}

void spawnEvents()
{
    std::cout << "Button clicked, spawning events\n";
    EventSystem &eventSystem = EventSystem::getInstance();
    eventSystem.push(std::make_unique<ShowEvent>("nestedLayout", ShowActionType::SHOW));
    eventSystem.push(std::make_unique<SoundEvent>("../SFX/song.wav", SoundActionType::PLAY, false));
}