#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
#include "../SoundPlayer.hpp"
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


const int X = 960, Y = 540;

int eventDemo(Screen *screen, SDL_Window *window);
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
    std::cout << "surface = " << screen->getSurface() << '\n';

    int failure = eventDemo(screen, window);

    if (failure == 1) {
        std::cout << "Demo did not execute successfully\n";
    }
    else {
        std::cout << "Demo succeeded and window closed\n";
    }

    SDL_Quit();
    return failure;

}

int eventDemo(Screen *screen, SDL_Window *window) {
    bool end = false;
    int failure = 0;
    SDL_Event event;
    EventSystem& eventSystem = EventSystem::getInstance();
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

    ElementParameters buttonParam;
    buttonParam.min = ivec2(X/4, Y/4);
    buttonParam.max = ivec2(X/2, Y/2);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.minType = TagType::IVec;
    buttonParam.maxType = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    buttonParam.name = "button1";
    buttonParam.callback = spawnEvents;
    buttonParam.callbackName = "spawnEvents";
    Button* button = dynamic_cast<Button*>(factory(guiElement::BUTTON, buttonParam));
    layout->addElement(button);

    ElementParameters nestedLayoutParam;
    nestedLayoutParam.layoutStart = vec2(0.2, 0.2);
    nestedLayoutParam.layoutEnd = vec2(1.0, 1.0);
    nestedLayoutParam.active = false;
    nestedLayoutParam.name = "nestedLayout";
    Layout* nestedLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, nestedLayoutParam));
    layout->addElement(nestedLayout);



    ElementParameters nestedBoxParam;
    nestedBoxParam.min = ivec2(3 * X / 4, 3 * Y / 4);
    nestedBoxParam.max = ivec2(X, Y);
    nestedBoxParam.color = ivec3(0, 255, 0);
    nestedBoxParam.minType = TagType::IVec;
    nestedBoxParam.maxType = TagType::IVec;
    nestedBoxParam.colorType = TagType::IVec;
    nestedBoxParam.name = "nestedBox";
    Box* nestedBox = dynamic_cast<Box*>(factory(guiElement::BOX, nestedBoxParam));
    nestedLayout->addElement(nestedBox);



    while (!end) {
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