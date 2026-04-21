#include "Global.hpp"

SDL_Window* window = nullptr;
Screen* screen = nullptr;
SoundPlayer* soundPlayer = nullptr;
Layout* rootLayout = nullptr;
Layout* toolBarLayout = nullptr;
Layout* tempLayout = nullptr;
SDL_Renderer* renderer = nullptr;

int type = 9;
int point = 0;
ivec2 point1;
ivec2 point2;
ivec2 point3;

Button* selectButton = nullptr;
Button* pointButton = nullptr;
Button* lineButton = nullptr;
Button* boxButton = nullptr;
Button* triangleButton = nullptr;
Button* ellipseButton = nullptr;
Button* arrowButton = nullptr;
Button* textBoxButton = nullptr;
Button* freehandLineButton = nullptr;
Button* freehandShapeButton = nullptr;

void initButtons() {
    ElementParameters selectButtonParam;
    selectButtonParam.min = ivec2(0, 0);
    selectButtonParam.max = ivec2(bW, bH);
    selectButtonParam.color = ivec3(180, 220, 255);
    selectButtonParam.textColor = ivec3(0, 0, 0);
    selectButtonParam.text = "Select";
    selectButtonParam.name = "selectButton";
    selectButtonParam.callbackName = "setSelectMode";
    selectButtonParam.callback = []() {
        type = 9;
        resetPoints(point, point1, point2, point3);
    };
    selectButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, selectButtonParam));

    ElementParameters pointButtonParam;
    pointButtonParam.min = ivec2(bW + p, 0);
    pointButtonParam.max = ivec2(2 * bW + p, bH);
    pointButtonParam.color = ivec3(180, 220, 255);
    pointButtonParam.textColor = ivec3(0, 0, 0);
    pointButtonParam.text = "Point";
    pointButtonParam.name = "pointButton";
    pointButtonParam.callbackName = "setPointMode";
    pointButtonParam.callback = []() {
        type = 0;
        resetPoints(point, point1, point2, point3);
    };
    pointButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, pointButtonParam));

    ElementParameters lineButtonParam;
    lineButtonParam.min = ivec2(2 * bW + 2 * p, 0);
    lineButtonParam.max = ivec2(3 * bW + 2 * p, bH);
    lineButtonParam.color = ivec3(180, 220, 255);
    lineButtonParam.textColor = ivec3(0, 0, 0);
    lineButtonParam.text = "Line";
    lineButtonParam.name = "lineButton";
    lineButtonParam.callbackName = "setLineMode";
    lineButtonParam.callback = []() {
        type = 1;
        resetPoints(point, point1, point2, point3);
    };
    lineButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, lineButtonParam));

    ElementParameters boxButtonParam;
    boxButtonParam.min = ivec2(3 * bW + 3 * p, 0);
    boxButtonParam.max = ivec2(4 * bW + 3 * p, bH);
    boxButtonParam.color = ivec3(180, 220, 255);
    boxButtonParam.textColor = ivec3(0, 0, 0);
    boxButtonParam.text = "Box";
    boxButtonParam.name = "boxButton";
    boxButtonParam.callbackName = "setBoxMode";
    boxButtonParam.callback = []() {
        type = 2;
        resetPoints(point, point1, point2, point3);
    };
    boxButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, boxButtonParam));

    ElementParameters triangleButtonParam;
    triangleButtonParam.min = ivec2(4 * bW + 4 * p, 0);
    triangleButtonParam.max = ivec2(5 * bW + 4 * p, bH);
    triangleButtonParam.color = ivec3(180, 220, 255);
    triangleButtonParam.textColor = ivec3(0, 0, 0);
    triangleButtonParam.text = "Triangle";
    triangleButtonParam.name = "triangleButton";
    triangleButtonParam.callbackName = "setTriangleMode";
    triangleButtonParam.callback = []() {
        type = 3;
        resetPoints(point, point1, point2, point3);
    };
    triangleButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, triangleButtonParam));

    ElementParameters ellipseButtonParam;
    ellipseButtonParam.min = ivec2(5 * bW + 5 * p, 0);
    ellipseButtonParam.max = ivec2(6 * bW + 5 * p, bH);
    ellipseButtonParam.color = ivec3(180, 220, 255);
    ellipseButtonParam.textColor = ivec3(0, 0, 0);
    ellipseButtonParam.text = "Ellipse";
    ellipseButtonParam.name = "ellipseButton";
    ellipseButtonParam.callbackName = "setEllipseMode";
    ellipseButtonParam.callback = []() {
        type = 4;
        resetPoints(point, point1, point2, point3);
    };
    ellipseButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, ellipseButtonParam));

    ElementParameters arrowButtonParam;
    arrowButtonParam.min = ivec2(6 * bW + 6 * p, 0);
    arrowButtonParam.max = ivec2(7 * bW + 6 * p, bH);
    arrowButtonParam.color = ivec3(180, 220, 255);
    arrowButtonParam.textColor = ivec3(0, 0, 0);
    arrowButtonParam.text = "Arrow";
    arrowButtonParam.name = "arrowButton";
    arrowButtonParam.callbackName = "setArrowMode";
    arrowButtonParam.callback = []() {
        type = 5;
        resetPoints(point, point1, point2, point3);
    };
    arrowButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, arrowButtonParam));

    ElementParameters textBoxButtonParam;
    textBoxButtonParam.min = ivec2(7 * bW + 7 * p, 0);
    textBoxButtonParam.max = ivec2(8 * bW + 7 * p, bH);
    textBoxButtonParam.color = ivec3(180, 220, 255);
    textBoxButtonParam.textColor = ivec3(0, 0, 0);
    textBoxButtonParam.text = "Text Box";
    textBoxButtonParam.name = "textBoxButton";
    textBoxButtonParam.callbackName = "setTextBoxMode";
    textBoxButtonParam.callback = []() {
        type = 6;
        resetPoints(point, point1, point2, point3);
    };
    textBoxButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, textBoxButtonParam));

    ElementParameters freehandLineButtonParam;
    freehandLineButtonParam.min = ivec2(8 * bW + 8 * p, 0);
    freehandLineButtonParam.max = ivec2(8 * bW + 8 * p + bigBW, bH);
    freehandLineButtonParam.color = ivec3(180, 220, 255);
    freehandLineButtonParam.textColor = ivec3(0, 0, 0);
    freehandLineButtonParam.text = "Freehand Line";
    freehandLineButtonParam.name = "freehandLineButton";
    freehandLineButtonParam.callbackName = "setFreehandLineMode";
    freehandLineButtonParam.callback = []() {
        type = 7;
        resetPoints(point, point1, point2, point3);
    };
    freehandLineButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, freehandLineButtonParam));

    ElementParameters freehandShapeButtonParam;
    freehandShapeButtonParam.min = ivec2(8 * bW + 8 * p + bigBW + p, 0);
    freehandShapeButtonParam.max = ivec2(8 * bW + 8 * p + 2 * bigBW + p, bH);
    freehandShapeButtonParam.color = ivec3(180, 220, 255);
    freehandShapeButtonParam.textColor = ivec3(0, 0, 0);
    freehandShapeButtonParam.text = "Freehand Shape";
    freehandShapeButtonParam.name = "freehandShapeButton";
    freehandShapeButtonParam.callbackName = "setFreehandShapeMode";
    freehandShapeButtonParam.callback = []() {
        type = 8;
        resetPoints(point, point1, point2, point3);
    };
    freehandShapeButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, freehandShapeButtonParam));
}

void createWindow() {
    window = SDL_CreateWindow("ArtHuddle", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
    }
}

void createScreen() {
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    screen = new Screen(X, Y, renderer);
}

Layout* createRootLayout() {
    ElementParameters root;
    root.layoutStart = vec2(0.0,0.0);
    root.layoutEnd = vec2(1.0, 1.0);
    root.parentStart = ivec2(0,0);
    root.parentEnd = ivec2(X,Y);
    root.active = true;
    root.name = "rootLayout";
    rootLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, root));

    ElementParameters toolBar;
    toolBar.layoutStart = vec2(0.0,0.0);
    toolBar.layoutEnd = vec2(1.0, 1.0);
    toolBar.parentStart = ivec2(0,0);
    toolBar.parentEnd = ivec2(X,Y);
    toolBar.active = true;
    toolBar.name = "toolBarLayout";
    toolBarLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, toolBar));
    
    ElementParameters temp;
    temp.layoutStart = vec2(0.0,0.0);
    temp.layoutEnd = vec2(1.0, 1.0);
    temp.parentStart = ivec2(0,0);
    temp.parentEnd = ivec2(X,Y);
    temp.active = true;
    temp.name = "tempLayout";
    tempLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, temp));
    rootLayout->addElement(tempLayout);

    Selected& selectedSingleton = Selected::getInstance();
    ElementParameters boundingLayoutParam;
    boundingLayoutParam.layoutStart = vec2(0.0,0.0);
    boundingLayoutParam.layoutEnd = vec2(1.0, 1.0);
    boundingLayoutParam.parentStart = ivec2(0,0);
    boundingLayoutParam.parentEnd = ivec2(X,Y);
    boundingLayoutParam.active = true;
    boundingLayoutParam.name = "boundingLayout";
    Layout *boundingLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, boundingLayoutParam));
    selectedSingleton.setSelectedLayout(boundingLayout);
    rootLayout->addElement(boundingLayout);

    return rootLayout;
}

void setEventSystem() {
    EventSystem& eventSystem = EventSystem::getInstance();
    soundPlayer = new SoundPlayer();
    eventSystem.setSoundPlayer(soundPlayer);
}

