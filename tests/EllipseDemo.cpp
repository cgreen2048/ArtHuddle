#include "ArtHuddle/elements/Ellipse.hpp"
#include "ArtHuddle/elements/Screen.hpp"
#include "ArtHuddle/elements/Factory.hpp"
#include "ArtHuddle/elements/Layout.hpp"
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"
#include "ArtHuddle/elements/Box.hpp"
#include "ArtHuddle/elements/Triangle.hpp"
#include "ArtHuddle/elements/GuiElement.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include <iostream>
#include <SDL3/SDL.h>

const int X = 960;
const int Y = 540;

int main() {
    std::cout << "Ellipse Class Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Ellipse Demo", X, Y, 0);
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

    ElementParameters ellipseParam;
    ellipseParam.center = ivec2(X/2, Y/2);
    ellipseParam.radiusX = 50;
    ellipseParam.radiusY = 25;
    ellipseParam.color = ivec3(255, 0, 0);
    
    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0, 0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;
    Layout *layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));
    Ellipse* e = dynamic_cast<Ellipse*>(factory(guiElement::ELLIPSE, ellipseParam));
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