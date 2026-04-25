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
    
    int type = 9;
    int points = 0;
    ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());

    Layout* layout = initialize(type, points, point1, point2, point3);

    loadSound("../SFX/song.wav");
    playSound("../SFX/song.wav", true);
    ivec3 color = ivec3(125, 125, 125);
    std::cout << "1 to draw a point\n2 to draw a line\n3 to draw a box\n4 to draw a triangle\n5 to draw an ellipse\n6 to draw an arrow\n7 to draw a text box\n8 to draw a freehand line\n9 to draw a freehand shape\n0 to select elements\nEscape to exit drawing mode\nBackspace after selecting an element to delete it\nR/E to increment/decrement red amount\nG/F to increment/decrement green amount\nB/V to increment/decrement blue amount\n";

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

                    if (mouseY <= 2 * bH - p) {
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
                            startFreehandDraw(ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y)), color, false);
                            justFinishedDrawing = true;
                            break;
                        }
                        case 8: {
                            startFreehandDraw(ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y)), color, true);
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
                        continueFreehandDraw(ivec2(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y)));
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
                        endFreehandDraw(ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                        break;
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
                                deleteShape();
                                break;
                            }
                            case SDL_SCANCODE_R: {
                                if (!changeColor(ivec3(1, 0, 0))) {
                                    color.x += 1;
                                    if (color.x > 255) {
                                        color.x = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_G: {
                                if (!changeColor(ivec3(0, 1, 0))) {
                                    color.y += 1;
                                    if (color.y > 255) {
                                        color.y = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_B: {
                                if (!changeColor(ivec3(0, 0, 1))) {
                                    color.z += 1;
                                    if (color.z > 255) {
                                        color.z = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_E: {
                                if (!changeColor(ivec3(-1, 0, 0))) {
                                    color.x -= 1;
                                    if (color.x < 0) {
                                        color.x = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_F: {
                                if (!changeColor(ivec3(0, -1, 0))) {
                                    color.y -= 1;
                                    if (color.y < 0) {
                                        color.y = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_V: {
                                if (!changeColor(ivec3(0, 0, -1))) {
                                    color.z -= 1;
                                    if (color.z < 0) {
                                        color.z = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_C: {
                                copy();
                                break;
                            }
                            case SDL_SCANCODE_P: {
                                paste();
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

        update(type);
    }
    closeAll();
    return 0;
}

void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3) {
    point = 0;
    point1.x = std::numeric_limits<int>::lowest();
    point1.y = std::numeric_limits<int>::lowest();
    point2.x = std::numeric_limits<int>::lowest();
    point2.y = std::numeric_limits<int>::lowest();
    point3.x = std::numeric_limits<int>::lowest();
    point3.y = std::numeric_limits<int>::lowest();
}
