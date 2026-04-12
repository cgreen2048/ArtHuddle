#include "../Arrow.hpp"
#include "../Screen.hpp"
#include "../Factory.hpp"
#include "../Layout.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../Box.hpp"
#include "../Triangle.hpp"
#include "../GuiElement.hpp"
#include "../ElementParameters.hpp"
#include <iostream>
#include <SDL3/SDL.h>

const int X = 960;
const int Y = 540;

int main() {
    std::cout << "Arrow Class Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Arrow Demo", X, Y, 0);
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

    SDL_Event event;
    Screen *screen = new Screen(X, Y, renderer);

    ElementParameters arrowParam;
    arrowParam.min = ivec2(250, 250);
    arrowParam.max = ivec2(500, 400);
    arrowParam.pointA = ivec2(500, 150);
    arrowParam.pointB = ivec2(500, 500);
    arrowParam.pointC = ivec2(650, 325);
    arrowParam.minType = TagType::IVec;
    arrowParam.maxType = TagType::IVec;
    arrowParam.pointAType = TagType::IVec;
    arrowParam.pointBType = TagType::IVec;
    arrowParam.pointCType = TagType::IVec;
    arrowParam.color = ivec3(125, 125, 125);
    arrowParam.colorType = TagType::IVec;
    
    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0, 0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;
    Layout *layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));
    Arrow* e = dynamic_cast<Arrow*>(factory(guiElement::ARROW, arrowParam));
    layout->addElement(e);

    while (true) {
       while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    SDL_Quit();
                    return 0;
                }
            }
        }

        screen->clear(ivec3(255, 255, 255));
        layout->draw(screen);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        screen->renderToRenderer();

        SDL_RenderPresent(renderer);
       
    }
}