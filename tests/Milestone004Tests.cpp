#include <iostream>
#include <typeinfo>
#include "../Factory.hpp"
#include "../GuiElement.hpp"
#include "../Point.hpp"
#include "../Line.hpp"
#include "../Box.hpp"
#include "../Triangle.hpp"

const int X = 960;
const int Y = 540;

int pointTests(Screen, SDL_Window*);
int lineTests(Screen, SDL_Window*);
int boxTests(Screen, SDL_Window*);
int triangleTests(Screen, SDL_Window*);
void getPixelColor(SDL_Surface*, ivec2, uint8_t&, uint8_t&, uint8_t&);

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    int failure = 0;
    Screen screen = Screen(X, Y);
    SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);
    
    if (pointTests(screen, window)) {
        failure = 1;
    }
    if (lineTests(screen, window)) {
        failure = 1;
    }
    if (boxTests(screen, window)) {
        failure = 1;
    }
    if (triangleTests(screen, window)) {
        failure = 1;
    }

    if (failure) {
        std::cout << "IMPLEMENTATION(S) FAILED, REVIEW TESTS\n";
    }
    else {
        std::cout << "all tests passed\n";
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return failure;
}

int pointTests(Screen screen, SDL_Window* window) {
    int failure = 0;
    std::cout << "Testing Point class\n";
    GuiElement* point = new Point(ivec2(40, 500), ivec3(200, 200, 200));

    Point *test = new Point(ivec2(40, 500), ivec3(200, 200, 200));
    Point *dup = new Point(ivec2(40, 500), ivec3(200, 200, 200));
    Point *copy{test};

    if (*test != *dup) {
        std::cout << "point inequality FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "point inequality working\n";
    }
    
    if (*test != *copy) {
        std::cout << "point copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "point copy constructor working\n";
    }

    point->setParentStart(ivec2(0, 0));
    point->setParentEnd(ivec2(screen.getWidth(), screen.getHeight()));
    point->setScreen(&screen);
    point->draw();

    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    uint8_t r, g, b;
    getPixelColor(screen.getSurface(), ivec2(40, 500), r, g, b);
    if (r != 200 || g != 200 || b != 200) {
        failure = 1;
    }

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
    if (failure) {
        std::cout << "point tests FAILED\n";
    }
    else {
        std::cout << "point tests passed\n";
    }
    return failure;
}

int lineTests(Screen screen, SDL_Window* window) {
    int failure = 0;
    std::cout << "Testing Line class\n";
    GuiElement *line = new Line(ivec2(250, 300), ivec2(450, 500), ivec3(200, 200, 200));

    Line *test = new Line(ivec2(250, 300), ivec2(450, 500), ivec3(200, 200, 200));
    Line *dup = new Line(ivec2(250, 300), ivec2(450, 500), ivec3(200, 200, 200));
    Line *copy{test};

    if (*test != *dup) {
        std::cout << "line inequality FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "line inequality working\n";
    }
    
    if (*test != *copy) {
        std::cout << "line copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "line copy constructor working\n";
    }

    line->setParentStart(ivec2(0, 0));
    line->setParentEnd(ivec2(screen.getWidth(), screen.getHeight()));
    line->setScreen(&screen);
    line->draw();

    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    uint8_t r, g, b;
    getPixelColor(screen.getSurface(), ivec2(250, 300), r, g, b);
    if (r != 200 || g != 200 || b != 200) {
        failure = 1;
    }
    getPixelColor(screen.getSurface(), ivec2(450, 500), r, g, b);
    if (r != 200 || g != 200 || b != 200) {
        failure = 1;
    }

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
			}
		}
    }
    if (failure) {
        std::cout << "line tests FAILED\n";
    }
    else {
        std::cout << "line tests passed\n";
    }
    return failure;
}

int boxTests(Screen screen, SDL_Window* window) {
    int failure = 0;
    std::cout << "Testing Box class\n";
    GuiElement *box = new Box(ivec2(40, 50), ivec2(240, 450), ivec3(200, 200, 0));
    
    Box *test = new Box(ivec2(40, 50), ivec2(240, 450), ivec3(200, 200, 0));
    Box *dup = new Box(ivec2(40, 50), ivec2(240, 450), ivec3(200, 200, 0));
    Box *copy{test};

    if (*test != *dup) {
        std::cout << "box inequality FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "box inequality working\n";
    }

    if (*test != *copy) {
        std::cout << "box copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "box copy constructor working\n";
    }
    
    box->setParentStart(ivec2(0, 0));
    box->setParentEnd(ivec2(screen.getWidth(), screen.getHeight()));
    box->setScreen(&screen);
    box->draw();

    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    int boxXMin = 40;
    int boxXMax = 240;
    int boxYMin = 50;
    int boxYMax = 450;
    uint8_t r, g, b;
    for (int i = 0; i < screen.getWidth(); ++i) {
        for (int j = 0; j < screen.getHeight(); ++j) {
            getPixelColor(screen.getSurface(), ivec2(i, j), r, g, b);
            if ((i >= boxXMin) && (i <= boxXMax) && (j >= boxYMin) && (j <= boxYMax)) {
                if (r != 200 || g != 200 || b != 0) {
                    std::cout << r << ' ' << g << ' ' << b << '\n';
                    failure = 1;
                    break;
                }
            }
            else {
                if (r != 0 || g != 0 || b != 0) {
                    failure = 1;
                    break;
                }
            }
        }
        if (failure) {
            break;
        } 
    }

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
			}
		}
    }
    if (failure) {
        std::cout << "box tests FAILED\n";
    }
    else {
        std::cout << "box tests passed\n";
    }
    return failure;
}

int triangleTests(Screen screen, SDL_Window* window) {
    int failure = 0;
    GuiElement *triangle = new Triangle(ivec2(50,50), ivec2(120,200), ivec2(100, 50), ivec3(100,100,100));

    Triangle *test = new Triangle(ivec2(50,50), ivec2(120,200), ivec2(100, 50), ivec3(100,100,100));
    Triangle *copy{test};
    Triangle *equal = new Triangle();
    equal = copy;

    if (*test == *copy) {
        std::cout << "triangle copy constructor passed\n";
    }
    else {
        std::cout << "triangle copy constructor failed\n";
        failure = 1;
    }

    if (*test == *equal) {
        std::cout << "triangle equality operator passed\n";
    }
    else {
        std::cout << "triangle equality operator failed\n";
        failure = 1;
    }

    if (*test != *equal) {
        std::cout << "triangle inequality FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "triangle inequality working\n";
    }

    triangle->setParentStart(ivec2(0, 0));
    triangle->setParentEnd(ivec2(screen.getWidth(), screen.getHeight()));
    triangle->setScreen(&screen);
    triangle->draw();
    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

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
    
    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
			}
		}
    }

    if (failure) {
        std::cout << "triangle tests FAILED\n";
    }
    else {
        std::cout << "triangle tests passed\n";
    }
    return failure;
}

void getPixelColor(SDL_Surface* surface, ivec2 coords, uint8_t& r, uint8_t& g, uint8_t& b) {
    uint8_t* pixelPtr = static_cast<uint8_t*>(surface->pixels);
    uint8_t* pixel = pixelPtr 
        + static_cast<int>(coords.x) * sizeof(uint32_t) 
        + static_cast<int>(coords.y) * surface->pitch;
    uint32_t pixel32 = *reinterpret_cast<uint32_t*>(pixel);
    const SDL_PixelFormatDetails *details =  SDL_GetPixelFormatDetails(surface->format);

    uint8_t a;
    SDL_GetRGBA(pixel32, details, NULL, &r, &g, &b, &a);
}