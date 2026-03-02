#include <iostream>

#include "../Factory.hpp"
#include "../GuiElement.hpp"
#include "../Point.hpp"
#include "../Line.hpp"
#include "../Box.hpp"

const int X = 960;
const int Y = 540;


int main() {
    GuiElement *point = new Point(vec2(40, 500), vec3(200, 200, 200));
    // GuiElement *line = new Line(vec2(100, 300), vec2(150, 500), vec3(200, 200, 200));
    GuiElement *box = new Box(vec2(40, 50), vec2(240, 450), vec3(200, 200, 0));
    Screen screen = Screen(X, Y);
    
    
    point->setScreen(&screen);
    // line->setScreen(&screen);
    box->setScreen(&screen);
	
    
    point->draw();
    // line->draw();
    box->draw();
    
    SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);
    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);
    
    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
			}
		}
    }


    return 0;
}