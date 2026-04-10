#include "../Freehand.hpp"
#include "../Screen.hpp"
#include "../Factory.hpp"
#include "../Layout.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../GuiElement.hpp"
#include "../ElementParameters.hpp"
#include "../EventSystem.hpp"
#include "../MouseDownEvent.hpp"
#include "../MouseUpEvent.hpp"
#include "../MouseMotionEvent.hpp"
#include "../SoundPlayer.hpp"
#include <iostream>
#include <SDL3/SDL.h>

const int X = 960;
const int Y = 540;

int main() {
    std::cout << "Freehand Draw Demo\n";

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
    SDL_Event event;
    Screen *screen = new Screen(X, Y);
    
    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0, 0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;
    Layout *layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));

    ivec3 color{255,0,0};

    EventSystem& eventSystem = EventSystem::getInstance();

    // This marks that the user is in Freehand draw mode, which will allow for Freehand upon mouse down
    bool isFreehand = true;

    while (true) {
       while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    SDL_Quit();
                    return 0;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    if (isFreehand) {
                        Freehand* freehand = new Freehand(color);
                        layout->addElement(freehand);
                        eventSystem.setTargetedElement(freehand);
                        ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                        
                        eventSystem.push(std::make_unique<MouseDownEvent>(point));
                        
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    if (isFreehand && event.motion.state != 0) {
                        ivec2 point(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y));

                        eventSystem.push(std::make_unique<MouseMotionEvent>(point, true));
                        break;
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP: {
                    if (isFreehand) {
                        ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));

                        eventSystem.push(std::make_unique<MouseUpEvent>(point));
                    }
                    break;
                }
            }
        }

        screen->clear(ivec3(255, 255, 255));
        layout->draw(screen);
        screen->blitTo(SDL_GetWindowSurface(window));
        SDL_UpdateWindowSurface(window);
        eventSystem.processEvents(layout);
    }
}