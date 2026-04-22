#include "../API.hpp"
#include "../Global.hpp"
#include <memory>
#include "../Layout.hpp"
#include "../Button.hpp"
#include "../EventSystem.hpp"
#include "../Freehand.hpp"
#include "../MouseDownEvent.hpp"
#include "../MouseMotionEvent.hpp"
#include "../MouseUpEvent.hpp"

void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);

int main() {
    std::cout << "API Demo\n";
    Layout* layout = initialize();

    loadSound("../SFX/song.wav");
    playSound("../SFX/song.wav", true);
    int type = 0;
    int points = 0;
    ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec3 color = ivec3(125, 125, 125);
    std::cout << "1 to draw a point\n2 to draw a line\n3 to draw a box\n4 to draw a triangle\n5 to draw an ellipse\n6 to draw an arrow\n7 to draw a text box\n8 to draw a freehand line\n9to draw a freehand shape\n0 to select elements\nEscape to exit drawing mode\nBackspace after selecting an element to delete it\nR/E to increment/decrement red amount\nG/F to increment/decrement green amount\nB/V to increment/decrement blue amount\n";
    

    int p = 10;
    int bW = 76;
    int bigBW = 131;
    int bH = Y / 10;

    ElementParameters selectButtonParam;
    selectButtonParam.min = ivec2(0, 0);
    selectButtonParam.max = ivec2(bW, bH);
    selectButtonParam.color = ivec3(180, 220, 255);
    selectButtonParam.textColor = ivec3(0, 0, 0);
    selectButtonParam.text = "Select";
    selectButtonParam.name = "selectButton";
    selectButtonParam.callbackName = "setSelectMode";
    selectButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 9;
        resetPoints(points, point1, point2, point3);
    };
    Button* selectButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, selectButtonParam));
    layout->addElement(selectButton);

    ElementParameters pointButtonParam;
    pointButtonParam.min = ivec2(bW + p, 0);
    pointButtonParam.max = ivec2(2 * bW + p, bH);
    pointButtonParam.color = ivec3(180, 220, 255);
    pointButtonParam.textColor = ivec3(0, 0, 0);
    pointButtonParam.text = "Point";
    pointButtonParam.name = "pointButton";
    pointButtonParam.callbackName = "setPointMode";
    pointButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 0;
        resetPoints(points, point1, point2, point3);
    };
    Button* pointButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, pointButtonParam));
    layout->addElement(pointButton);

    ElementParameters lineButtonParam;
    lineButtonParam.min = ivec2(2 * bW + 2 * p, 0);
    lineButtonParam.max = ivec2(3 * bW + 2 * p, bH);
    lineButtonParam.color = ivec3(180, 220, 255);
    lineButtonParam.textColor = ivec3(0, 0, 0);
    lineButtonParam.text = "Line";
    lineButtonParam.name = "lineButton";
    lineButtonParam.callbackName = "setLineMode";
    lineButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 1;
        resetPoints(points, point1, point2, point3);
    };
    Button* lineButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, lineButtonParam));
    layout->addElement(lineButton);

    ElementParameters boxButtonParam;
    boxButtonParam.min = ivec2(3 * bW + 3 * p, 0);
    boxButtonParam.max = ivec2(4 * bW + 3 * p, bH);
    boxButtonParam.color = ivec3(180, 220, 255);
    boxButtonParam.textColor = ivec3(0, 0, 0);
    boxButtonParam.text = "Box";
    boxButtonParam.name = "boxButton";
    boxButtonParam.callbackName = "setBoxMode";
    boxButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 2;
        resetPoints(points, point1, point2, point3);
    };
    Button* boxButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, boxButtonParam));
    layout->addElement(boxButton);

    ElementParameters triangleButtonParam;
    triangleButtonParam.min = ivec2(4 * bW + 4 * p, 0);
    triangleButtonParam.max = ivec2(5 * bW + 4 * p, bH);
    triangleButtonParam.color = ivec3(180, 220, 255);
    triangleButtonParam.textColor = ivec3(0, 0, 0);
    triangleButtonParam.text = "Triangle";
    triangleButtonParam.name = "triangleButton";
    triangleButtonParam.callbackName = "setTriangleMode";
    triangleButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 3;
        resetPoints(points, point1, point2, point3);
    };
    Button* triangleButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, triangleButtonParam));
    layout->addElement(triangleButton);

    ElementParameters ellipseButtonParam;
    ellipseButtonParam.min = ivec2(5 * bW + 5 * p, 0);
    ellipseButtonParam.max = ivec2(6 * bW + 5 * p, bH);
    ellipseButtonParam.color = ivec3(180, 220, 255);
    ellipseButtonParam.textColor = ivec3(0, 0, 0);
    ellipseButtonParam.text = "Ellipse";
    ellipseButtonParam.name = "ellipseButton";
    ellipseButtonParam.callbackName = "setEllipseMode";
    ellipseButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 4;
        resetPoints(points, point1, point2, point3);
    };
    Button* ellipseButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, ellipseButtonParam));
    layout->addElement(ellipseButton);

    ElementParameters arrowButtonParam;
    arrowButtonParam.min = ivec2(6 * bW + 6 * p, 0);
    arrowButtonParam.max = ivec2(7 * bW + 6 * p, bH);
    arrowButtonParam.color = ivec3(180, 220, 255);
    arrowButtonParam.textColor = ivec3(0, 0, 0);
    arrowButtonParam.text = "Arrow";
    arrowButtonParam.name = "arrowButton";
    arrowButtonParam.callbackName = "setArrowMode";
    arrowButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 5;
        resetPoints(points, point1, point2, point3);
    };
    Button* arrowButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, arrowButtonParam));
    layout->addElement(arrowButton);

    ElementParameters textBoxButtonParam;
    textBoxButtonParam.min = ivec2(7 * bW + 7 * p, 0);
    textBoxButtonParam.max = ivec2(8 * bW + 7 * p, bH);
    textBoxButtonParam.color = ivec3(180, 220, 255);
    textBoxButtonParam.textColor = ivec3(0, 0, 0);
    textBoxButtonParam.text = "Text Box";
    textBoxButtonParam.name = "textBoxButton";
    textBoxButtonParam.callbackName = "setTextBoxMode";
    textBoxButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 6;
        resetPoints(points, point1, point2, point3);
    };
    Button* textBoxButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, textBoxButtonParam));
    layout->addElement(textBoxButton);

    ElementParameters freehandLineButtonParam;
    freehandLineButtonParam.min = ivec2(8 * bW + 8 * p, 0);
    freehandLineButtonParam.max = ivec2(8 * bW + 8 * p + bigBW, bH);
    freehandLineButtonParam.color = ivec3(180, 220, 255);
    freehandLineButtonParam.textColor = ivec3(0, 0, 0);
    freehandLineButtonParam.text = "Freehand Line";
    freehandLineButtonParam.name = "freehandLineButton";
    freehandLineButtonParam.callbackName = "setFreehandLineMode";
    freehandLineButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 7;
        resetPoints(points, point1, point2, point3);
    };
    Button* freehandLineButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, freehandLineButtonParam));
    layout->addElement(freehandLineButton);

    ElementParameters freehandShapeButtonParam;
    freehandShapeButtonParam.min = ivec2(8 * bW + 8 * p + bigBW + p, 0);
    freehandShapeButtonParam.max = ivec2(8 * bW + 8 * p + 2 * bigBW + p, bH);
    freehandShapeButtonParam.color = ivec3(180, 220, 255);
    freehandShapeButtonParam.textColor = ivec3(0, 0, 0);
    freehandShapeButtonParam.text = "Freehand Shape";
    freehandShapeButtonParam.name = "freehandShapeButton";
    freehandShapeButtonParam.callbackName = "setFreehandShapeMode";
    freehandShapeButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 8;
        resetPoints(points, point1, point2, point3);
    };
    Button* freehandShapeButton = dynamic_cast<Button*>(factory(guiElement::BUTTON, freehandShapeButtonParam));
    layout->addElement(freehandShapeButton);

    bool clickAndHold = false;
    bool justFinishedDrawing = false;
    ivec2 lastMousePos;
    SDL_Event event;
    EventSystem& eventSystem = EventSystem::getInstance();
    bool end = false;
    while (!end) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    end = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    // eventSystem.push(std::make_unique<ClickEvent>(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                    // playSound("../SFX/chords.wav", true);
                    int mouseX = static_cast<int>(event.button.x);
                    int mouseY = static_cast<int>(event.button.y);

                    if (mouseY <= bH) {
                        eventSystem.push(std::make_unique<ClickEvent>(mouseX, mouseY));
                        eventSystem.processEvents(layout);
                        break;
                    }

                    switch (type) {
                        case 0: {
                            point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                            drawElement(type, point1, point2, point3, color);
                            resetPoints(points, point1, point2, point3);
                            justFinishedDrawing = true;
                            type = 9;
                            break;
                        }
                        case 1: {
                            switch (points) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(points, point1, point2, point3);
                                    justFinishedDrawing = true;
                                    type = 9;
                                    break;
                                }
                            }
                            break;
                        }
                        case 2: {
                            switch (points) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(points, point1, point2, point3);
                                    justFinishedDrawing = true;
                                    type = 9;
                                    break;
                                }
                            }
                            break;
                        }
                        case 3: {
                            switch (points) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 2: {
                                    point3 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(points, point1, point2, point3);
                                    justFinishedDrawing = true;
                                    type = 9;
                                    break;
                                }
                            }
                            break;
                        }
                        case 4: {
                            switch (points) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 2: {
                                    point3 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(points, point1, point2, point3);
                                    justFinishedDrawing = true;
                                    type = 9;
                                    break;
                                }
                            }
                            break;
                        }
                        case 5: {
                            switch (points) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 2: {
                                    point3 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(points, point1, point2, point3);
                                    justFinishedDrawing = true;
                                    type = 9;
                                    break;
                                }
                            }
                            break;
                        }
                        case 6: {
                            switch (points) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++points;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(points, point1, point2, point3);
                                    justFinishedDrawing = true;
                                    type = 9;
                                    break;
                                }
                            }
                            break;
                        }
                        case 7: {
                            Freehand* freehand = new Freehand(color, false);
                            layout->addElement(freehand);
                            eventSystem.setTargetedElement(freehand);
                            ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                            
                            eventSystem.push(std::make_unique<MouseDownEvent>(point));
                            justFinishedDrawing = true;
                            break;
                        }
                        case 8: {
                            Freehand* freehand = new Freehand(color, true);
                            layout->addElement(freehand);
                            eventSystem.setTargetedElement(freehand);
                            ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                            eventSystem.push(std::make_unique<MouseDownEvent>(point));
                            justFinishedDrawing = true;
                            break;
                        }
                        case 9: {
                            if (justFinishedDrawing) {
                                break;
                            }
                            lastMousePos = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                            eventSystem.push(std::make_unique<MouseDownEvent>(lastMousePos));
                            // eventSystem.push(std::make_unique<ClickEvent>(lastMousePos.x, lastMousePos.y));
                            clickAndHold = true;
                            setClickAndDrag(lastMousePos);
                        }
                        default: {
                            clicked(ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                            break;
                        }
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    if ((type == 7 || type == 8) && event.motion.state != 0) {
                        ivec2 point(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y));

                        eventSystem.push(std::make_unique<MouseMotionEvent>(point, true));
                        break;
                    }
                    if (type == 9) {
                        if (clickAndHold && !justFinishedDrawing) {
                            drawClickAndDrag(ivec2(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y)));
                        }
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP: {
                    if (type == 7 || type == 8) {
                        ivec2 point(static_cast<int>(event.button.x), static_cast<int>(event.button.y));

                        eventSystem.push(std::make_unique<MouseUpEvent>(point));
                    }
                    if (justFinishedDrawing) {
                        justFinishedDrawing = false;
                        clickAndHold = false;
                        break;
                    }
                    if (type == 9) {
                        if (clickAndHold) {
                            clickAndHold = false;
                            endClickAndDrag();
                        }
                    }
                    break;
                }
                case SDL_EVENT_TEXT_INPUT: {
                    if (isSelectedTextBox()) {
                        appendToTextBox(event.text.text);
                    }
                    break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    if (!isSelectedTextBox()) {
                        switch (event.key.scancode) {
                            case SDL_SCANCODE_1: {
                                type = 0;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_2: {
                                type = 1;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_3: {
                                type = 2;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_4: {
                                type = 3;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_5: {
                                type = 4;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_6: {
                                type = 5;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_7: {
                                type = 6;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_8: {
                                type = 7;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_9: {
                                type = 8;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_0: {
                                type = 9;
                                resetPoints(points, point1, point2, point3);
                                break;
                            }
                            case SDL_SCANCODE_ESCAPE: {
                                type = 9;
                                resetPoints(points, point1, point2, point3);
                                cancelMove();
                                unselect();
                                clickAndHold = false;
                                justFinishedDrawing = false;
                                break;
                            }
                            case SDL_SCANCODE_BACKSPACE: {
                                type = -1;
                                deleteShape();
                                break;
                            }
                            case SDL_SCANCODE_R: {
                                color.x += 1;
                                if (color.x > 255) {
                                    color.x = 255;
                                }
                                break;
                            }
                            case SDL_SCANCODE_G: {
                                color.y += 1;
                                if (color.y > 255) {
                                    color.y = 255;
                                }
                                break;
                            }
                            case SDL_SCANCODE_B: {
                                color.z += 1;
                                if (color.z > 255) {
                                    color.z = 255;
                                }
                                break;
                            }
                            case SDL_SCANCODE_E: {
                                color.x -= 1;
                                if (color.x < 0) {
                                    color.x = 0;
                                }
                                break;
                            }
                            case SDL_SCANCODE_F: {
                                color.y -= 1;
                                if (color.y < 0) {
                                    color.y = 0;
                                }
                                break;
                            }
                            case SDL_SCANCODE_V: {
                                color.z -= 1;
                                if (color.z < 0) {
                                    color.z = 0;
                                }
                                break;
                            }
                            case SDL_SCANCODE_C: {
                                copy();
                                break;
                            }
                            case SDL_SCANCODE_P: {
                                float x, y;
                                SDL_GetMouseState(&x, &y);
                                paste(ivec2(static_cast<int>(x), static_cast<int>(y)));
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    else {
                        switch (event.key.scancode) {
                            case SDL_SCANCODE_BACKSPACE: {
                                deleteText();
                                break;
                            }
                            case SDL_SCANCODE_ESCAPE: {
                                unselect();
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
        float mouseX = 0;
        float mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        switch (type) {
            case 1: {
                if (points == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                }
                break;
            }
            case 2: {
                if (points == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                }
                break;
            }
            case 3: {
                if (points == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(1, point1, point2, point3, color);
                }
                else if (points == 2) {
                    point3 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                    break;
                }
                break;
            }
            case 4: {
                if (points == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(1, point1, point2, point3, color);
                }
                else if (points == 2) {
                    point3 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                    break;
                }
                break;
            }
            case 5: {
                if (points == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(2, point1, point2, point3, color);
                }
                else if (points == 2) {
                    point3 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                    break;
                }
                break;
            }
            case 6: {
                if (points == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(2, point1, point2, point3, color);
                }
                break;
            }
            default: {
                break;
            }
        }

        update();
    }
    closeAll();
    return 0;
}

void resetPoints(int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    points = 0;
    point1.x = std::numeric_limits<int>::lowest();
    point1.y = std::numeric_limits<int>::lowest();
    point2.x = std::numeric_limits<int>::lowest();
    point2.y = std::numeric_limits<int>::lowest();
    point3.x = std::numeric_limits<int>::lowest();
    point3.y = std::numeric_limits<int>::lowest();
}