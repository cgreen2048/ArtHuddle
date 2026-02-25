SDL3_ROOT := $(HOME)/esc-courses/sp26-cse-40232.01/public/SDL
SDL3_INC  := $(SDL3_ROOT)/include
SDL3_LIB  := $(SDL3_ROOT)/build

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(SDL3_INC)
LDFLAGS  := -L$(SDL3_LIB) -Wl,-rpath,$(SDL3_LIB) -lSDL3

test:
	$(CXX) tests.cpp $(CXXFLAGS) $(LDFLAGS)
	$(CXX) ../Matrix.cpp Milestone001Tests.cpp -std=c++17 -Wall -o milestone001
	$(CXX) ../Screen.cpp Milestone002Tests.cpp $(CXXFLAGS) $(LDFLAGS) -o milestone002
	$(CXX) ../GUIFile.cpp Milestone003Tests.cpp -Wall -o milestone003
	$(CXX) ../Screen.cpp screenDemo.cpp $(CXXFLAGS) $(LDFLAGS) -o screenDemo

mac:
	g++ tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall
	g++ ../Matrix.cpp Milestone001Tests.cpp -Wall -o milestone001
	g++ ../Screen.cpp Milestone002Tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone002
	g++ ../Screen.cpp screenDemo.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o screenDemo
	g++ ../GUIFile.cpp Milestone003Tests.cpp -Wall -o milestone003

clean:
	rm a.out
	rm milestone001
	rm milestone002
	rm screenDemo
	rm milestone003