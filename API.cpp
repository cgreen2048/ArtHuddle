#include "API.hpp"
#include "Global.hpp"

void initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        exit(1);
    }
    createWindow();
    createScreen();
    createRootLayout();
    setEventSystem();
}

void loadSound(std::string filePath) {
    soundPlayer->loadSound(filePath);
}

void playSound(std::string filePath, int loop) {
    soundPlayer->playSound(filePath, loop);
}

void drawTempElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    tempLayout->clearElements();
    guiElement ge = static_cast<guiElement>(type);
    ElementParameters ep;
    ep.color = color;
    ep.colorType = TagType::IVec;
    
    switch (ge) {
		case guiElement::LINE: {
            ep.start = point1;
            ep.end = point2;
            ep.startType = TagType::IVec;
            ep.endType = TagType::IVec;
			Line* element = dynamic_cast<Line*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::BOX: {
            ep.min = point1;
            ep.max = point2;
            ep.minType = TagType::IVec;
            ep.maxType = TagType::IVec;
			Box* element = dynamic_cast<Box*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::TRIANGLE: {
            ep.pointA = point1;
            ep.pointB = point2;
            ep.pointC = point3;
            ep.pointAType = TagType::IVec;
            ep.pointBType = TagType::IVec;
            ep.pointCType = TagType::IVec;
			Triangle* element = dynamic_cast<Triangle*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
        case guiElement::ELLIPSE: {
            ep.center = point1;
            ep.radiusX = std::abs(point3.x - point1.x);
            ep.radiusY = std::abs(point2.y - point1.y);
            ep.centerType = TagType::IVec;
            Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
        }
        case guiElement::ARROW: {
            ep.min = point1;
            ep.max = point2;
            ep.pointA = ivec2(point2.x, point1.y - ((point2.y - point1.y)/5));
            ep.pointB = ivec2(point2.x, point2.y + ((point2.y - point1.y)/5));
            ep.pointC = point3;
            ep.centerType = TagType::IVec;
            Arrow* element = dynamic_cast<Arrow*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
        }
        case guiElement::LAYOUT: {
			Layout* element = dynamic_cast<Layout*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::BUTTON: {
			Button* element = dynamic_cast<Button*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
        default: {
            return;
        }
	}
}

void drawElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    guiElement ge = static_cast<guiElement>(type);
    ElementParameters ep;
    ep.color = color;
    ep.colorType = TagType::IVec;
    
    switch (ge) {
		case guiElement::POINT: {
			ep.coords = point1;
            ep.coordsType = TagType::IVec;
            Point* element = dynamic_cast<Point*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
        case guiElement::LINE: {
            ep.start = point1;
            ep.end = point2;
            ep.startType = TagType::IVec;
            ep.endType = TagType::IVec;
			Line* element = dynamic_cast<Line*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::BOX: {
            ep.min = point1;
            ep.max = point2;
            ep.minType = TagType::IVec;
            ep.maxType = TagType::IVec;
			Box* element = dynamic_cast<Box*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::TRIANGLE: {
            ep.pointA = point1;
            ep.pointB = point2;
            ep.pointC = point3;
            ep.pointAType = TagType::IVec;
            ep.pointBType = TagType::IVec;
            ep.pointCType = TagType::IVec;
			Triangle* element = dynamic_cast<Triangle*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
        case guiElement::ELLIPSE: {
            ep.center = point1;
            ep.radiusX = std::abs(point3.x - point1.x);
            ep.radiusY = std::abs(point2.y - point1.y);
            ep.centerType = TagType::IVec;
            Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
        }
        case guiElement::ARROW: {
            ep.min = point1;
            ep.max = point2;
            ep.pointA = ivec2(point2.x, point1.y - ((point2.y - point1.y)/5));
            ep.pointB = ivec2(point2.x, point2.y + ((point2.y - point1.y)/5));
            ep.pointC = point3;
            ep.centerType = TagType::IVec;
            Arrow* element = dynamic_cast<Arrow*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
        }
        case guiElement::LAYOUT: {
			Layout* element = dynamic_cast<Layout*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::BUTTON: {
			Button* element = dynamic_cast<Button*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
        default: {
            return;
        }
	}
    tempLayout->clearElements();
}

void update() {
    screen->clear(ivec3(255,255,255));
    rootLayout->draw(screen);
    screen->blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);
    // eventSystem.processEvents(layout);
}

void closeAll() {
    delete soundPlayer;
    delete screen;
    SDL_Quit();
}