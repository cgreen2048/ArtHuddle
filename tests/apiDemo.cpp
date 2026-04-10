#include "../API.hpp"

void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);

int main() {
    std::cout << "API Demo\n";
    initialize();
    loadSound("../SFX/song.wav");
    playSound("../SFX/song.wav", true);
    int type = 0;
    int point = 0;
    ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec3 color = ivec3(125, 125, 125);
    int numKeys;
    SDL_Event event;
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
                    switch (type) {
                        case 0: {
                            point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                            drawElement(type, point1, point2, point3, color);
                            resetPoints(point, point1, point2, point3);
                            break;
                        }
                        case 1: {
                            switch (point) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(point, point1, point2, point3);
                                    break;
                                }
                            }
                            break;
                        }
                        case 2: {
                            switch (point) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(point, point1, point2, point3);
                                    break;
                                }
                            }
                            break;
                        }
                        case 3: {
                            switch (point) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 2: {
                                    point3 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(point, point1, point2, point3);
                                    break;
                                }
                            }
                            break;
                        }
                        case 4: {
                            switch (point) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 2: {
                                    point3 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(point, point1, point2, point3);
                                    break;
                                }
                            }
                            break;
                        }
                        case 5: {
                            switch (point) {
                                case 0: {
                                    point1 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 1: {
                                    point2 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    ++point;
                                    break;
                                }
                                case 2: {
                                    point3 = ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                                    drawElement(type, point1, point2, point3, color);
                                    resetPoints(point, point1, point2, point3);
                                    break;
                                }
                            }
                            break;
                        }
                        default: {
                            clicked(ivec2(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                            break;
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
                if (point == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                }
                break;
            }
            case 2: {
                if (point == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                }
                break;
            }
            case 3: {
                if (point == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(1, point1, point2, point3, color);
                }
                else if (point == 2) {
                    point3 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                    break;
                }
                break;
            }
            case 4: {
                if (point == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(1, point1, point2, point3, color);
                }
                else if (point == 2) {
                    point3 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                    break;
                }
                break;
            }
            case 5: {
                if (point == 1) {
                    point2 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(2, point1, point2, point3, color);
                }
                else if (point == 2) {
                    point3 = ivec2(static_cast<int>(mouseX), static_cast<int>(mouseY));
                    drawTempElement(type, point1, point2, point3, color);
                    break;
                }
                break;
            }
            default: {
                break;
            }
        }

        const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
        if (keyboardState[SDL_SCANCODE_1]) {
            type = 0;
            resetPoints(point, point1, point2, point3);
        }
        if (keyboardState[SDL_SCANCODE_2]) {
            type = 1;
            resetPoints(point, point1, point2, point3);
        }
        if (keyboardState[SDL_SCANCODE_3]) {
            type = 2;
            resetPoints(point, point1, point2, point3);
        }
        if (keyboardState[SDL_SCANCODE_4]) {
            type = 3;
            resetPoints(point, point1, point2, point3);
        }
        if (keyboardState[SDL_SCANCODE_5]) {
            type = 4;
            resetPoints(point, point1, point2, point3);
        }
        if (keyboardState[SDL_SCANCODE_6]) {
            type = 5;
            resetPoints(point, point1, point2, point3);
        }
        if (keyboardState[SDL_SCANCODE_ESCAPE]) {
            type = -1;
            resetPoints(point, point1, point2, point3);
        }
        update();
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