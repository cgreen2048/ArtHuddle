#include "../Button.hpp"
#include "../Screen.hpp"
#include "../Factory.hpp"
#include "../Layout.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../Box.hpp"
#include "../GuiElement.hpp"
#include "../ElementParameters.hpp"
#include <iostream>
#include <SDL3/SDL.h>

const int X = 960;
const int Y = 540;

int main() {
    std::cout << "Button Text Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Button Text Demo", X, Y, 0);
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
    Screen* screen = new Screen(X, Y, renderer);

    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0, 0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;

    Layout* layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));

    auto fakeCallback = [](){
        std::cout << "Fake button callback triggered\n";
    };

    ElementParameters buttonParam;
    buttonParam.min = ivec2(300, 200);
    buttonParam.max = ivec2(660, 300);
    buttonParam.color = ivec3(180, 220, 255);
    buttonParam.textColor = ivec3(0, 0, 0);
    buttonParam.text = "Click Me";
    buttonParam.name = "demoButton";
    buttonParam.callbackName = "fakeCallback";

    Button* button = dynamic_cast<Button*>(factory(guiElement::BUTTON, buttonParam));
    layout->addElement(button);

    while (true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    delete layout;
                    delete screen;
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                }
            }
        }

        screen->clear(ivec3(255, 255, 255));

        // First pass: shapes to surface
        layout->draw(screen);

        // Clear renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Copy surface to renderer
        screen->renderToRenderer();

        // Second pass: overlay text to renderer
        layout->drawOverlay(screen);

        // Present final frame
        SDL_RenderPresent(renderer);
    }
}