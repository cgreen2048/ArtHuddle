#include "../Freehand.hpp"
#include "../Screen.hpp"
#include "../Factory.hpp"
#include "../Layout.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../Box.hpp"
#include "../GuiElement.hpp"
#include "../ElementParameters.hpp"
#include "../EventSystem.hpp"
#include "../MouseDownEvent.hpp"
#include "../MouseUpEvent.hpp"
#include "../MouseMotionEvent.hpp"
#include "../SoundPlayer.hpp"
#include "../Selected.hpp"
#include <iostream>
#include <SDL3/SDL.h>

const int X = 960;
const int Y = 540;

int main() {
    std::cout << "Freehand Draw Demo\n";
    std::cout << "Starting in Freehand Shape Mode\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Freehand Demo", X, Y, 0);
    if (!window) {
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

    SDL_Event event;
    EventSystem& eventSystem = EventSystem::getInstance();
    Selected& selectedSingleton = Selected::getInstance();
    
    ElementParameters rootLayout;
    rootLayout.layoutStart = vec2(0.0, 0.0);
    rootLayout.layoutEnd = vec2(1.0, 1.0);
    rootLayout.parentStart = ivec2(0, 0);
    rootLayout.parentEnd = ivec2(X, Y);
    rootLayout.active = true;
    Layout *layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, rootLayout));

    ElementParameters boxParam;
    boxParam.min = ivec2(50, 200);
    boxParam.max = ivec2(100, 300);
    boxParam.color = ivec3(20, 255, 20);
    boxParam.minType = TagType::IVec;
    boxParam.maxType = TagType::IVec;
    boxParam.name = "box1";
    Box* box = dynamic_cast<Box*>(factory(guiElement::BOX, boxParam));
    layout->addElement(box);

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

    ivec3 color{255,0,0};

    // This marks that the user is in Freehand draw mode, which will allow for Freehand upon mouse down
    bool isFreehandMode = false;

    // This marks whether or not we're in Freehand shape vs. Freehand line mode. Press the B ky on the keyboard to switch between modes
    bool isFreehandShape = true;

    while (true) {
       while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    SDL_Quit();
                    return 0;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    if (isFreehandMode) {
                        Freehand* freehand = new Freehand(color, isFreehandShape);
                        layout->addElement(freehand);
                        eventSystem.setTargetedElement(freehand);
                        ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                        
                        eventSystem.push(std::make_unique<MouseDownEvent>(point));
                        
                    }
                    else {
                        eventSystem.push(std::make_unique<ClickEvent>(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    if (isFreehandMode && event.motion.state != 0) {
                        ivec2 point(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y));

                        eventSystem.push(std::make_unique<MouseMotionEvent>(point, true));
                        break;
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP: {
                    if (isFreehandMode) {
                        ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));

                        eventSystem.push(std::make_unique<MouseUpEvent>(point));
                    }
                    break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    if (event.key.key == SDLK_B) {
                        std::cout << "Switching freehand drawing mode to ";
                        if (isFreehandShape) {
                            std::cout << "line mode\n";
                        } else {
                            std::cout << "shape mode\n";
                        }

                        isFreehandShape = !isFreehandShape;
                    }
                    if (event.key.key == SDLK_F) {
                        std::cout << "Toggling freehand drawing mode ";
                        if (isFreehandMode) {
                            std::cout << "off\n";
                        } else {
                            std::cout << "on\n";
                        }

                        isFreehandMode = !isFreehandMode;
                    }
                    if (event.key.key == SDLK_BACKSPACE) {
                        GuiElement *selected = selectedSingleton.getSelectedElement();
                        if (selected != nullptr) {
                            layout->deleteElement(selected->getName());
                        }
                    }
                    break;
                }
            }
        }

        eventSystem.processEvents(layout);

        screen->clear(ivec3(255, 255, 255));

        layout->draw(screen);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        screen->renderToRenderer();
        layout->drawOverlay(screen);

        SDL_RenderPresent(renderer);
    }
}