test:
	g++ tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3
	g++ ../Matrix.cpp Milestone001Tests.cpp -o milestone001
	g++ ../Screen.cpp Milestone001Tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone002

mac:
	g++ tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall
	g++ ../Matrix.cpp Milestone001Tests.cpp -Wall -o milestone001
	g++ ../Screen.cpp Milestone002Tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone002

clean:
	rm a.out
	rm milestone001
	rm milestone002