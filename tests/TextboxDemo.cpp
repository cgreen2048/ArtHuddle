#include "../TextBox.hpp"
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

// ===================== RENDERING PIPELINE NOTE =====================
//
// We are using an SDL_Renderer-based pipeline, NOT a surface-based pipeline.
//
// That means:
//   - Screen draws everything onto an internal SDL_Surface
//   - Then we COPY that surface → renderer (texture)
//   - Then we PRESENT the renderer to the window
//
// IMPORTANT:
//   ❌ DO NOT use:
//        screen->blitTo(SDL_GetWindowSurface(window));
//        SDL_UpdateWindowSurface(window);
//
//   Those are ONLY for window surface rendering (no renderer involved).
//
//   ✅ INSTEAD use:
//        screen->renderToRenderer();
//        SDL_RenderPresent(renderer);
//
//   Because:
//     - SDL_Renderer manages the GPU pipeline
//     - Mixing surface blitting with renderer causes undefined behavior
//     - Only one system should control the final output (we use renderer)
//
// Rendering Flow:
//   1. screen->clear()
//   2. layout->draw()            → draw shapes to surface
//   3. screen->renderToRenderer() → copy surface → renderer
//   4. layout->drawTextOverlay()     → draw text/cursor (still uses screen abstraction)
//   5. SDL_RenderPresent()       → display final frame
//
// ================================================================


const int X = 960;
const int Y = 540;

int main() {
    std::cout << "TextBox Class Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("TextBox Demo", X, Y, 0);
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

    ElementParameters textBoxParam;
    textBoxParam.min = ivec2(200, 200);
    textBoxParam.max = ivec2(500, 260);
    textBoxParam.color = ivec3(220, 220, 220);
    textBoxParam.textColor = ivec3(0, 0, 0);
    textBoxParam.text = "";

    TextBox* textBox = dynamic_cast<TextBox*>(factory(guiElement::TEXTBOX, textBoxParam));
    layout->addElement(textBox);

    SDL_StartTextInput(window);

    while (true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    SDL_StopTextInput(window);
                    delete layout;
                    delete screen;
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                }

                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    int mx = event.button.x;
                    int my = event.button.y;

                    if (textBox->containsPoint(mx, my)) {
                        textBox->setActive(true);
                    } else {
                        textBox->setActive(false);
                    }
                    break;
                }

                case SDL_EVENT_TEXT_INPUT: {
                    if (textBox->isActive()) {
                        textBox->appendText(event.text.text);
                    }
                    break;
                }

                case SDL_EVENT_KEY_DOWN: {
                    if (textBox->isActive() && event.key.key == SDLK_BACKSPACE) {
                        textBox->backspace();
                    }
                    break;
                }
            }
        }

        screen->clear(ivec3(255, 255, 255));

        layout->draw(screen);


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        screen->renderToRenderer();
        layout->drawTextOverlay(screen);


        SDL_RenderPresent(renderer);
    }
}