STUDENT_MACHINE_SDL3_ROOT := $(HOME)/esc-courses/sp26-cse-40232.01/public/SDL
SDL3_INC := $(STUDENT_MACHINE_SDL3_ROOT)/include
SDL3_LIB := $(STUDENT_MACHINE_SDL3_ROOT)/build

CXX := g++
CXXFLAGS := -std=c++17 -Wall -I$(SDL3_INC)

# Link flags: where to find it at link time + where to find it at run time
LDFLAGS := -L$(SDL3_LIB) -Wl,-rpath,$(SDL3_LIB)
LDLIBS := -lSDL3

test:
	g++ tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3
	g++ ../Matrix.cpp Milestone001Tests.cpp -o milestone001
	g++ ../Screen.cpp Milestone002Tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone002
	g++ ../Screen.cpp screenDemo.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o screenDemo
	g++ ../GUIFile.cpp ../Factory.cpp ../GuiElement.cpp ../Line.cpp ../Box.cpp ../Point.cpp ../Screen.cpp Milestone003Tests.cpp ../Triangle.cpp ../Layout.cpp  \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone003
	g++ ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Triangle.cpp ../Layout.cpp ../Screen.cpp Milestone004Tests.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone004
	g++ ../GUIFile.cpp ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Triangle.cpp ../Layout.cpp ../Screen.cpp Milestone005LayoutTests.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone005LayoutTests
	g++ ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Triangle.cpp ../Layout.cpp ../Screen.cpp Milestone005Tests.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone005
	g++ ../Factory.cpp ../GuiElement.cpp ../Layout.cpp ../Triangle.cpp ../Box.cpp ../Line.cpp ../Point.cpp ../Screen.cpp layoutDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o layoutDemo

studentMachine:
	$(CXX) tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)
	$(CXX) ../Matrix.cpp Milestone001Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone001
	$(CXX) ../Screen.cpp Milestone002Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone002
	$(CXX) ../Screen.cpp screenDemo.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o screenDemo
	$(CXX) Milestone003Tests.cpp ../GUIFile.cpp ../Factory.cpp ../GuiElement.cpp ../Line.cpp ../Box.cpp ../Point.cpp ../Screen.cpp ../Triangle.cpp ../Layout.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone003
	$(CXX) ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Triangle.cpp ../Layout.cpp ../Screen.cpp Milestone004Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone004
	$(CXX) ../GUIFile.cpp ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Triangle.cpp ../Layout.cpp ../Screen.cpp Milestone005LayoutTests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005LayoutTests
	$(CXX) ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Triangle.cpp ../Layout.cpp ../Screen.cpp Milestone005Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005
	$(CXX) ../Factory.cpp ../GuiElement.cpp ../Layout.cpp ../Triangle.cpp ../Box.cpp ../Line.cpp ../Point.cpp ../Screen.cpp layoutDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDemo
	

mac:
	g++ tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall
	g++ ../Matrix.cpp Milestone001Tests.cpp -Wall -o milestone001
	g++ ../Screen.cpp Milestone002Tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone002
	g++ ../Screen.cpp screenDemo.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o screenDemo
	g++ ../GUIFile.cpp ../Factory.cpp ../GuiElement.cpp ../Line.cpp ../Box.cpp ../Point.cpp ../Screen.cpp ../Triangle.cpp Milestone003Tests.cpp ../Layout.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone003
	g++ ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Screen.cpp ../Triangle.cpp ../Layout.cpp Milestone004Tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone004
	g++ ../GUIFile.cpp ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Screen.cpp ../Triangle.cpp ../Layout.cpp Milestone005LayoutTests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone005LayoutTests
	g++ ../Factory.cpp ../GuiElement.cpp ../Point.cpp ../Line.cpp ../Box.cpp ../Screen.cpp ../Triangle.cpp ../Layout.cpp Milestone005Tests.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o milestone005
	g++ ../Factory.cpp ../GuiElement.cpp ../Layout.cpp ../Triangle.cpp ../Box.cpp ../Line.cpp ../Point.cpp ../Screen.cpp layoutDemo.cpp -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks -framework sdl3 -std=c++17 -Wall -o layoutDemo



clean:
	rm a.out
	rm milestone001
	rm milestone002
	rm screenDemo
	rm milestone003
	rm milestone004
	rm milestone005
	rm milestone005LayoutTests
	rm layoutDemo


