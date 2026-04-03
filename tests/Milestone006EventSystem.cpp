#include <iostream>
#include <memory>
#include "../EventSystem.hpp"
#include "../Event.hpp"
#include "../ClickEvent.hpp"
#include "../ShowEvent.hpp"
#include "../SoundEvent.hpp"




class TestLayout : public Layout {
public:
    int resolveCount = 0;

    bool resolveEvent(Event* e) {
        resolveCount++;
        return false;
    }
};

// --------------------------------------------------
// Function Declarations
// --------------------------------------------------

int singletonTest();
int pollEmptyTest();
int pushPollTest();
int fifoOrderTest();
int processEventsDispatchTest();
int processEventsSoundTest();
int processEventsClearsQueueTest();
int processEventsMixedDispatchTest();
void clearEventSystem();

// --------------------------------------------------
// Main
// --------------------------------------------------

int main() {
    int failure = 0;
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    if (singletonTest()) {
        failure = 1;
    }
    if (pollEmptyTest()) {
        failure = 1;
    }
    if (pushPollTest()) {
        failure = 1;
    }
    if (fifoOrderTest()) {
        failure = 1;
    }
    if (processEventsDispatchTest()) {
        failure = 1;
    }
    if (processEventsSoundTest()) {
        failure = 1;
    }
    if (processEventsClearsQueueTest()) {
        failure = 1;
    }
    if(processEventsMixedDispatchTest()){
        failure = 1;
    }

    if (failure) {
        std::cout << "IMPLEMENTATION(S) FAILED, REVIEW TESTS\n";
    } else {
        std::cout << "ALL TESTS PASSED\n";
    }

    return failure;
}

// --------------------------------------------------
// Function Definitions
// --------------------------------------------------

void clearEventSystem() {
    EventSystem& system = EventSystem::getInstance();
    while (system.poll() != nullptr) {

    }
}

int singletonTest() {
    int failure = 0;
    std::cout << "Testing singleton behavior\n";

    EventSystem& a = EventSystem::getInstance();
    EventSystem& b = EventSystem::getInstance();

    if (&a != &b) {
        std::cout << "singleton FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "singleton test FAILED\n" : "singleton test passed\n");
    return failure;
}

int pollEmptyTest() {
    int failure = 0;
    std::cout << "Testing poll on empty queue\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();

    if (system.poll() != nullptr) {
        std::cout << "poll empty FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "poll empty test FAILED\n" : "poll empty test passed\n");
    return failure;
}

int pushPollTest() {
    int failure = 0;
    std::cout << "Testing push and poll\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();

    system.push(std::make_unique<Event>(EventType::CLICK));

    std::unique_ptr<Event> e = system.poll();

    if (!e || e->getType() != EventType::CLICK) {
        std::cout << "push/poll FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "push/poll test FAILED\n" : "push/poll test passed\n");
    return failure;
}

int fifoOrderTest() {
    int failure = 0;
    std::cout << "Testing FIFO order\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();

    system.push(std::make_unique<Event>(EventType::CLICK));
    system.push(std::make_unique<Event>(EventType::SHOW));

    std::unique_ptr<Event> first = system.poll();
    std::unique_ptr<Event> second = system.poll();

    if (!first || !second ||
        first->getType() != EventType::CLICK ||
        second->getType() != EventType::SHOW) {

        std::cout << "FIFO FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "FIFO test FAILED\n" : "FIFO test passed\n");
    return failure;
}

int processEventsDispatchTest() {
    int failure = 0;
    std::cout << "Testing processEvents dispatch\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();
    TestLayout root;

    system.push(std::make_unique<Event>(EventType::CLICK));
    system.push(std::make_unique<Event>(EventType::SHOW));

    system.processEvents(&root);

    if (root.resolveCount != 2) {
        std::cout << "dispatch FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "dispatch test FAILED\n" : "dispatch test passed\n");
    return failure;
}

int processEventsSoundTest() {
    int failure = 0;
    std::cout << "Testing SOUND event handling\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();
    TestLayout root;

    system.push(std::make_unique<SoundEvent>("../SFX/song.wav", SoundActionType::PLAY, false));

    system.processEvents(&root);
    SDL_Delay(5000);

    if (root.resolveCount != 0) {
        std::cout << "sound handling FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "sound test FAILED\n" : "sound test passed\n");
    return failure;
}

int processEventsMixedDispatchTest() {
    int failure = 0;
    std::cout << "Testing mixed event dispatch\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();
    TestLayout root;

    system.push(std::make_unique<Event>(EventType::CLICK));
    system.push(std::make_unique<SoundEvent>("../SFX/song.wav", SoundActionType::PLAY, true));
    system.push(std::make_unique<Event>(EventType::SHOW));

    system.processEvents(&root);
    SDL_Delay(5000);

    if (root.resolveCount != 2) {
        std::cout << "mixed dispatch FAILED\n";
        failure = 1;
    }

    if (system.poll() != nullptr) {
        std::cout << "mixed dispatch queue clear FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "mixed dispatch test FAILED\n" : "mixed dispatch test passed\n");
    return failure;
}

int processEventsClearsQueueTest() {
    int failure = 0;
    std::cout << "Testing queue cleared after processing\n";

    clearEventSystem();
    EventSystem& system = EventSystem::getInstance();
    TestLayout root;

    system.push(std::make_unique<Event>(EventType::CLICK));

    system.processEvents(&root);

    if (system.poll() != nullptr) {
        std::cout << "queue not cleared FAILED\n";
        failure = 1;
    }

    std::cout << (failure ? "clear queue test FAILED\n" : "clear queue test passed\n");
    return failure;
}