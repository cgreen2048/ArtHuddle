#include <iostream>
#include <SDL3/SDL.h>
#include "ArtHuddle/elements/Factory.hpp"
#include "ArtHuddle/elements/Layout.hpp"
#include "ArtHuddle/elements/Screen.hpp"
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"
#include "ArtHuddle/elements/Box.hpp"
#include "ArtHuddle/elements/Triangle.hpp"
#include "ArtHuddle/elements/GuiElement.hpp"

const int X = 960;
const int Y = 540;

int layoutDemo(Screen*, SDL_Window*, SDL_Renderer*);

int main() {
    std::cout << "Layout Class Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Layout Demo", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Screen* screen = new Screen(X, Y, renderer);

    int failure = layoutDemo(screen, window, renderer);

    SDL_Quit();

    if (failure == 1) {
        std::cout << "Demo did not execute successfully\n";
    }
    else {
        std::cout << "Demo succeeded and window closed\n";
    }

    return failure;
}

int layoutDemo(Screen* screen, SDL_Window *window, SDL_Renderer* renderer) {
    bool end = false;
    int failure = 0;
    SDL_Event event;
    float mouseX, mouseY;
    int x, y;

    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.1, 0.1);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;
    Layout* layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));

    
    ElementParameters triangleParam;
    triangleParam.pointA = ivec2(100, 100);
    triangleParam.pointB = ivec2(150, 100);
    triangleParam.pointC = ivec2(125, 150);
    triangleParam.color = ivec3(255, 0, 0);
    triangleParam.pointAType = TagType::IVec;
    triangleParam.pointBType = TagType::IVec;
    triangleParam.pointCType = TagType::IVec;
    triangleParam.colorType = TagType::IVec;
    
    ivec2 triangleA = triangleParam.pointA;
    ivec2 triangleB = triangleParam.pointB;
    ivec2 triangleC = triangleParam.pointC;

    Triangle* tri = dynamic_cast<Triangle*>(factory(guiElement::TRIANGLE, triangleParam));
    layout->addElement(tri);


    ElementParameters boxParam;
    boxParam.min = ivec2(200, 200);
    boxParam.max = ivec2(400, 400);
    boxParam.color = ivec3(0, 255, 255);
    boxParam.minType = TagType::IVec;
    boxParam.maxType = TagType::IVec;
    boxParam.colorType = TagType::IVec;
    Box* b = dynamic_cast<Box*>(factory(guiElement::BOX, boxParam));

    layout->addElement(b);


    ElementParameters nestedLayoutParam;
    nestedLayoutParam.layoutStart = vec2(0.5, 0.5);
    nestedLayoutParam.layoutEnd = vec2(1.0, 1.0);
    Layout* nestedLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, nestedLayoutParam));
    layout->addElement(nestedLayout);

    ElementParameters nestedVerticalParam;
    nestedVerticalParam.start = ivec2(X/2, Y/2);
    nestedVerticalParam.end = ivec2(X/2, Y);
    nestedVerticalParam.color = ivec3(0, 0, 0);
    nestedVerticalParam.startType = TagType::IVec;
    nestedVerticalParam.endType = TagType::IVec;
    nestedVerticalParam.colorType = TagType::IVec;
    Line* nestedLayoutVerticalBorder = dynamic_cast<Line*>(factory(guiElement::LINE, nestedVerticalParam));
    nestedLayout->addElement(nestedLayoutVerticalBorder);

    
    ElementParameters nestedHorizontalParam;
    nestedHorizontalParam.start = ivec2(X/2, Y/2);
    nestedHorizontalParam.end = ivec2(X, Y/2);
    nestedHorizontalParam.color = ivec3(0, 0, 0);
    nestedHorizontalParam.startType = TagType::IVec;
    nestedHorizontalParam.endType = TagType::IVec;
    nestedHorizontalParam.colorType = TagType::IVec;
    Line* nestedLayoutHorizontalBorder = dynamic_cast<Line*>(factory(guiElement::LINE, nestedHorizontalParam));
    nestedLayout->addElement(nestedLayoutHorizontalBorder);


    ElementParameters nestedBoxParam;
    nestedBoxParam.min = ivec2(800, 200);
    nestedBoxParam.max = ivec2(900, 500);
    nestedBoxParam.color = ivec3(255, 0, 0);
    nestedBoxParam.minType = TagType::IVec;
    nestedBoxParam.maxType = TagType::IVec;
    nestedBoxParam.colorType = TagType::IVec;
    Box* nestedBox = dynamic_cast<Box*>(factory(guiElement::BOX, nestedBoxParam));
    nestedLayout->addElement(nestedBox);



    ElementParameters nestedTriangleParam;
    nestedTriangleParam.pointA = ivec2(500, 530);
    nestedTriangleParam.pointB = ivec2(750, 510);
    nestedTriangleParam.pointC = ivec2(600, 460);
    nestedTriangleParam.color = ivec3(255, 0, 255);
    nestedTriangleParam.pointAType = TagType::IVec;
    nestedTriangleParam.pointBType = TagType::IVec;
    nestedTriangleParam.pointCType = TagType::IVec;
    nestedTriangleParam.colorType = TagType::IVec;
    Triangle* nestedTri = dynamic_cast<Triangle*>(factory(guiElement::TRIANGLE, nestedTriangleParam));
    nestedLayout->addElement(nestedTri);



    ElementParameters nestedLineParam;
    nestedLineParam.start = ivec2(480, 280);
    nestedLineParam.end = ivec2(940, 530);
    nestedLineParam.color = ivec3(132, 231, 52);
    nestedLineParam.minType = TagType::IVec;
    nestedLineParam.maxType = TagType::IVec;
    nestedLineParam.colorType = TagType::IVec;
    Line* nestedLine = dynamic_cast<Line*>(factory(guiElement::LINE, nestedLineParam));
    nestedLayout->addElement(nestedLine);
    
    

    while (!end) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    end = true;
                    break;
                }
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        x = static_cast<int>(mouseX);
        y = static_cast<int>(mouseY);
        bool inside = screen->pointInTriangle(triangleA, triangleB, triangleC, ivec2(x, y));
        if (inside) {
            nestedLayout->setActive(true);
        }
        else {
            nestedLayout->setActive(false);
        }

        screen->clear(ivec3(255,255,255));

        layout->draw(screen);
       

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        screen->renderToRenderer();

        
        SDL_RenderPresent(renderer);
    }
    delete layout;

    return failure;
}