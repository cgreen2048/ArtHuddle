#include <iostream>
#include <typeinfo>
#include <chrono>
#include <thread>
#include "../SoundPlayer.hpp"


const int X = 960;
const int Y = 540;

bool soundTests(SoundPlayer*);

int main() {
    int failure = 0;
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);

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

bool soundTests(SoundPlayer* player) {
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
    std::this_thread::sleep_for(std::chrono::seconds(15));
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