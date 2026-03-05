#include <iostream>

#include "../Factory.hpp"
#include "../GuiElement.hpp"
#include "../Point.hpp"
#include "../Line.hpp"
#include "../Box.hpp"
#include "../Triangle.hpp"

const int X = 960;
const int Y = 540;

int drawTriangleTests(Screen);

int main() {
    int failure = 0;

    GuiElement *point = new Point(vec2(40, 500), vec3(200, 200, 200));
    GuiElement *line = new Line(vec2(250, 300), vec2(450, 500), vec3(200, 200, 200));
    GuiElement *box = new Box(vec2(40, 50), vec2(240, 450), vec3(200, 200, 0));
    GuiElement *triangle = new Triangle(ivec2(50,50), ivec2(120,200), ivec2(100, 50), ivec3(100,100,100));
    Screen screen = Screen(X, Y);
    
    
    point->setScreen(&screen);
    line->setScreen(&screen);
    box->setScreen(&screen);
    triangle->setScreen(&screen);
	
    
    point->draw();
    line->draw();
    box->draw();
    triangle->draw();

    failure = drawTriangleTests(screen);

    if (failure) {
        std::cout << "FAILED TESTS\n";
    }
    
    SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);
    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);
    
    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
			}
		}
    }


    return failure;
}


int drawTriangleTests(Screen screen) {
    int failure = 0;

    ivec2 pointA{50,50};
    ivec2 pointB{120,200};
    ivec2 pointC{100, 50};

    ivec2 pointInside{90, 100};
    ivec2 pointOutside{50, 200};
    ivec2 pointOnBorder{75, 50};
    ivec2 pointOnCorner{50,50};

    if (
        !screen.pointInTriangle(pointA, pointB, pointC, pointInside)
        || screen.pointInTriangle(pointA, pointB, pointC, pointOutside)
        || !screen.pointInTriangle(pointA, pointB, pointC, pointOnBorder)
        || !screen.pointInTriangle(pointA, pointB, pointC, pointOnCorner)
    ) {
        failure = 1;
    }

    return failure;
}