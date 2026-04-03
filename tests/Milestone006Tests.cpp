#include <iostream>
#include <typeinfo>
#include <chrono>
#include <thread>
#include "../SoundPlayer.hpp"
#include "../Factory.hpp"
#include "../GuiElement.hpp"
#include "../Layout.hpp"
#include "../Triangle.hpp"
#include "../Box.hpp"
#include "../Line.hpp"
#include "../Point.hpp"
#include "../Screen.hpp"
#include "../Event.hpp"
#include "../ClickEvent.hpp"
#include "../ShowEvent.hpp"
#include "../SoundEvent.hpp"
#include "../Button.hpp"


const int X = 960;
const int Y = 540;

bool factoryTests();
bool eventTests();
bool buttonTests();
bool soundTests(SoundPlayer*);

int main() {
    int failure = 0;
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);

    bool factorySuccess = factoryTests();
    if (!factorySuccess) {
        failure = 1;
    }
    std::cout << '\n';

    bool eventSuccess = eventTests();
    if (!eventSuccess) {
        failure = 1;
    }

    std::cout << '\n';

    bool buttonSuccess = buttonTests();
    if (!buttonSuccess) {
        failure = 1;
    }

    std::cout << '\n';

    SoundPlayer* player = new SoundPlayer();
    bool soundSuccess = soundTests(player);
    if (!soundSuccess) {
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

    delete player;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return failure;
}

bool factoryTests() {
    std::cout << "***Factory tests***\n";
    bool success = true;
    ElementParameters pointParam;
    pointParam.color = ivec3(244, 245, 103);
    pointParam.point1Type = TagType::IVec;
    pointParam.colorType = TagType::IVec;
    GuiElement* p = factory(guiElement::POINT, pointParam);
    if (p) {
        success = false;
        std::cout << "point missing coordinate test FAILED\n";
    }
    else {
        std::cout << "point missing coordinate test passed\n";
    }

    ElementParameters point2Param;
    point2Param.point1 = ivec2(100, 50);
    point2Param.point1Type = TagType::IVec;
    point2Param.colorType = TagType::IVec;
    GuiElement* p2 = factory(guiElement::POINT, point2Param);
    if (!p2) {
        success = false;
        std::cout << "point missing color test FAILED\n";
    }
    else {
        std::cout << "point missing color test passed\n";
    }

    ElementParameters lineParam;
    lineParam.point1 = ivec2(50, 75);
    lineParam.color = ivec3(244, 245, 103);
    lineParam.point1Type = TagType::IVec;
    lineParam.colorType = TagType::IVec;
    GuiElement* l = factory(guiElement::LINE, lineParam);
    if (l) {
        success = false;
        std::cout << "line missing coordinate test FAILED\n";
    }
    else {
        std::cout << "line missing coordinate test passed\n";
    }

    ElementParameters lineParam2;
    lineParam2.point1 = ivec2(100, 50);
    lineParam2.point2 = ivec2(150, 75);
    lineParam2.point1Type = TagType::IVec;
    lineParam2.colorType = TagType::IVec;
    GuiElement* l2 = factory(guiElement::LINE, lineParam2);
    if (!l2) {
        success = false;
        std::cout << "line missing color test FAILED\n";
    }
    else {
        std::cout << "line missing color test passed\n";
    }

    ElementParameters boxParam;
    boxParam.point1 = ivec2(50, 75);
    boxParam.color = ivec3(244, 245, 103);
    boxParam.point1Type = TagType::IVec;
    boxParam.colorType = TagType::IVec;
    GuiElement* b = factory(guiElement::BOX, boxParam);
    if (b) {
        success = false;
        std::cout << "box missing coordinate test FAILED\n";
    }
    else {
        std::cout << "box missing coordinate test passed\n";
    }

    ElementParameters boxParam2;
    boxParam2.point1 = ivec2(100, 50);
    boxParam2.point2 = ivec2(150, 75);
    boxParam2.point1Type = TagType::IVec;
    boxParam2.colorType = TagType::IVec;
    GuiElement* b2 = factory(guiElement::BOX, boxParam2);
    if (!b2) {
        success = false;
        std::cout << "box missing color test FAILED\n";
    }
    else {
        std::cout << "box missing color test passed\n";
    }

    ElementParameters triParam;
    triParam.point1 = ivec2(50, 75);
    triParam.color = ivec3(244, 245, 103);
    triParam.point1Type = TagType::IVec;
    triParam.colorType = TagType::IVec;
    GuiElement* t = factory(guiElement::TRIANGLE, triParam);
    if (t) {
        success = false;
        std::cout << "triangle missing coordinate test FAILED\n";
    }
    else {
        std::cout << "triangle missing coordinate test passed\n";
    }

    ElementParameters triParam2;
    triParam2.point1 = ivec2(100, 50);
    triParam2.point2 = ivec2(150, 75);
    triParam2.point3 = ivec2(125, 75);
    triParam2.point1Type = TagType::IVec;
    triParam2.colorType = TagType::IVec;
    GuiElement* t2 = factory(guiElement::TRIANGLE, triParam2);
    if (!t2) {
        success = false;
        std::cout << "triangle missing color test FAILED\n";
    }
    else {
        std::cout << "triangle missing color test passed\n";
    }    

    ElementParameters layoutParam;
    layoutParam.layoutStart = vec2(0.1, 0.5);
    GuiElement* layout = factory(guiElement::LAYOUT, layoutParam);
    if (layout) {
        success = false;
        std::cout << "layout missing end test FAILED\n";
    }
    else {
        std::cout << "layout missing end test passed\n";
    }

    ElementParameters layoutParam2;
    layoutParam2.layoutEnd = vec2(0.1, 0.5);
    GuiElement* layout2 = factory(guiElement::LAYOUT, layoutParam2);
    if (layout2) {
        success = false;
        std::cout << "layout missing start test FAILED\n";
    }
    else {
        std::cout << "layout missing start test passed\n";
    }

    if (!success) {
        std::cout << "IMPLEMENTATION FAILED: REVIEW TESTS\n";
    }
    else {
        std::cout << "factory working\n";
    }
    return success;
}

bool eventTests() {
    std::cout << "***Event tests***\n";

    int failure = 0;

    ClickEvent* click = new ClickEvent(X, Y);
    if (click->getType() != EventType::CLICK || click->getMouseX() != X || click->getMouseY() != Y) {
        failure = 1;
    }

    ShowEvent* show = new ShowEvent("testLayout", ShowActionType::HIDE);
    if (show->getType() != EventType::SHOW || show->getLayoutName() != "testLayout" || show->getAction() != ShowActionType::HIDE) {
        failure = 1;
    }
    ShowEvent* defaultShow = new ShowEvent("testLayout");
    if (defaultShow->getType() != EventType::SHOW || defaultShow->getLayoutName() != "testLayout" || defaultShow->getAction() != ShowActionType::SHOW) {
        failure = 1;
    }

    SoundEvent* sound = new SoundEvent("../SFX/song.wav", SoundActionType::PLAY, true);
    if (sound->getType() != EventType::SOUND || sound->getSoundName() != "../SFX/song.wav" || sound->getAction() != SoundActionType::PLAY || sound->shouldLoop() != true) {
        failure = 1;
    }
    SoundEvent* defaultSound = new SoundEvent("../SFX/song.wav");
    if (defaultSound->getType() != EventType::SOUND || defaultSound->getSoundName() != "../SFX/song.wav" || defaultSound->getAction() != SoundActionType::PLAY || defaultSound->shouldLoop() != false) {
        failure = 1;
    }

    delete click;
    delete show;
    delete defaultShow;
    delete sound;
    delete defaultSound;
    return failure;
}

bool buttonTests() {
    std::cout << "***Button tests***\n";

    int failure = 0;
    bool clicked = false;
    Button* button = new Button(ivec2(50, 50), ivec2(150, 100), ivec3(255, 0, 0), [&clicked](){ clicked = true; }, "testCallback", "Click me!");
    if (button->getName() != "testCallback") {
        failure = 1;
        std::cout << "button name test FAILED\n";
    }
    else {
        std::cout << "button name test passed\n";
    }

    if (button->getText() != "Click me!") {
        failure = 1;
        std::cout << "button text test FAILED\n";
    }
    else {
        std::cout << "button text test passed\n";
    }

    if (button->resolveEvent(Event(EventType::CLICK))) {
        if (!clicked) {
            failure = 1;
            std::cout << "button click callback test FAILED\n";
        }
        else {
            std::cout << "button click callback test passed\n";
        }
    }
    else {
        failure = 1;
        std::cout << "button click event resolution test FAILED\n";
    }

    if (!button->resolveEvent(Event(EventType::SHOW))) {
        std::cout << "button non-click event resolution test passed\n";
    }
    else {
        failure = 1;
        std::cout << "button non-click event resolution test FAILED\n";
    }

    if (!failure) {
        std::cout << "Button working\n";
    }
    else {
        std::cout << "IMPLEMENTATION FAILED: REVIEW TESTS\n";
    }

    delete button;
    return failure;
}


bool soundTests(SoundPlayer* player) {
    std::cout << "***SoundPlayer tests***\n";
    bool loaded = player->loadSound("../SFX/song.wav");
    if (!loaded) {
        std::cout << "loading valid wav file test FAILED\n";
    }
    else {
        std::cout << "loading valid wav file test succeeded\n";
    }

    bool loadedMP3 = player->loadSound("../SFX/toreador.mp3");
    if (loadedMP3) {
        std::cout << "loading mp3 file test FAILED\n";
    }
    else {
        std::cout << "loading mp3 file test succeeded\n";
    }

    bool playing = player->playSound("../SFX/song.wav", 1);
    if (!playing) {
        std::cout << "playing valid sound test FAILED\n";
    }
    else {
        std::cout << "playing valid sound test succeeded\n";
    }

    bool playingUnloaded = player->playSound("../SFX/chords.wav", 1);
    if (!playingUnloaded) {
        std::cout << "playing valid unloaded sound test FAILED\n";
    }
    else {
        std::cout << "playing valid unloaded sound test succeeded\n";
    }

    player->togglePlayback();
    bool badLoad = player->loadSound("bad");
    if (badLoad) {
        std::cout << "loading invalid file test FAILED\n";
    }
    else {
        std::cout << "loading invalid file test succeeded\n";
    }

    bool badPlay = player->playSound("bad", 0);
    if (badPlay) {
        std::cout << "playing bad file test FAILED\n";
    }
    else {
        std::cout << "playing bad file test succeeded\n";
    }

    player->togglePlayback();
    std::vector<Sound> soundBank = player->getSoundBank();
    for (auto itr = soundBank.begin(); itr != soundBank.end(); ++itr) {
        std::cout << itr->getName() << '\n';
    }
    // std::this_thread::sleep_for(std::chrono::seconds(15));
    bool stoppage = player->stopSound("../SFX/chords.wav");
    if (!stoppage) {
        std::cout << "stopping valid sound test FAILED\n";
    }
    else {
        std::cout << "stopping valid sound test succeeded\n";
    }

    bool badStoppage = player->stopSound("bad");
    if (badStoppage) {
        std::cout << "stopping invalid sound test FAILED\n";
    }
    else {
        std::cout << "stopping invalid sound test succeeded\n";
    }

    bool success = loaded && !loadedMP3 && playing && playingUnloaded && !badLoad && !badPlay && stoppage;
    if (!success) {
        std::cout << "IMPLEMENTATION FAILED: REVIEW TESTS\n";
    }
    else {
        std::cout << "SoundPlayer working\n";
    }
    return success;
}