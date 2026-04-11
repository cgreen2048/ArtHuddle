STUDENT_MACHINE_SDL3_ROOT := $(HOME)/esc-courses/sp26-cse-40232.01/public/SDL
SDL3_INC := $(STUDENT_MACHINE_SDL3_ROOT)/include
SDL3_LIB := $(STUDENT_MACHINE_SDL3_ROOT)/build

CXX := g++
CXXFLAGS := -std=c++17 -I$(SDL3_INC)

# Link flags: where to find it at link time + where to find it at run time
LDFLAGS := -L$(SDL3_LIB) -Wl,-rpath,$(SDL3_LIB)
LDLIBS := -lSDL3

MAC_CXXFLAGS := -std=c++17 -Wall
MAC_LDFLAGS := -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks
MAC_LDLIBS := -framework sdl3

FACTORY_ELEMENTS := ../Factory.cpp ../GuiElement.cpp ../Layout.cpp ../Triangle.cpp ../Box.cpp ../Line.cpp ../Point.cpp ../Screen.cpp ../Button.cpp ../TextBox.cpp  ../Ellipse.cpp ../Arrow.cpp
EVENT_ELEMENTS := ../Event.cpp ../ClickEvent.cpp ../ShowEvent.cpp ../SoundEvent.cpp

test:
	g++ tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3

	g++ ../Matrix.cpp Milestone001Tests.cpp -o milestone001

	g++ ../Screen.cpp Milestone002Tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone002

	g++ ../Screen.cpp screenDemo.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o screenDemo

	g++ Milestone003Tests.cpp ../GUIFile.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../Selected.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone003

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp Milestone004Tests.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone004

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../GUIFile.cpp Milestone005LayoutTests.cpp ../Selected.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone005LayoutTests

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) Milestone005Tests.cpp ../Selected.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone005

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) layoutDemo.cpp ../Selected.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o layoutDemo

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../SoundPlayer.cpp ../Sound.cpp Milestone006Tests.cpp ../Selected.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone006

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp Milestone006EventSystem.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone006EventSystem

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp Milestone006Demo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone006Demo
	
	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) TextboxDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o textboxdemo
	
	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) TextInButtonDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o textinbuttondemo
	
	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp ArrowDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o arrowDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp EllipseDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o ellipseDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp SelectedDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o selectedDemo


studentMachine:
	$(CXX) tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

	$(CXX) ../Matrix.cpp Milestone001Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone001

	$(CXX) ../Screen.cpp Milestone002Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone002

	$(CXX) ../Screen.cpp screenDemo.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o screenDemo

	$(CXX) Milestone003Tests.cpp $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../GUIFile.cpp ../Selected.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone003

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp Milestone004Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone004

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../GUIFile.cpp ../Selected.cpp Milestone005LayoutTests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005LayoutTests

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp Milestone005Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp layoutDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../SoundPlayer.cpp ../Sound.cpp ../Selected.cpp Milestone006Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006

	$(CXX) $(EVENT_ELEMENTS) ${FACTORY_ELEMENTS}  ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp Milestone006EventSystem.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006EventSystem

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp Milestone006Demo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006Demo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp EllipseDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o ellipseDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp ArrowDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o arrowDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp  TextboxDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textboxdemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp  TextInButtonDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textinbuttondemo
		
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp SelectedDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o selectedDemo
	

mac:
	$(CXX) tests.cpp $(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS)

	$(CXX) ../Matrix.cpp Milestone001Tests.cpp -Wall -o milestone001

	$(CXX) ../Screen.cpp Milestone002Tests.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone002

	$(CXX) ../Screen.cpp screenDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o screenDemo

	$(CXX) Milestone003Tests.cpp ../GUIFile.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone003

	$(CXX) Milestone004Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone004

	$(CXX) Milestone005LayoutTests.cpp ../GUIFile.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005LayoutTests

	$(CXX) Milestone005Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005

	$(CXX) layoutDemo.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDemo

	$(CXX) Milestone006Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) ../SoundPlayer.cpp ../Sound.cpp ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006

	$(CXX) Milestone006EventSystem.cpp $(FACTORY_ELEMENTS) ../EventSystem.cpp ../Sound.cpp ../SoundPlayer.cpp $(EVENT_ELEMENTS) ../Selected.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006EventSystem

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp Milestone006Demo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006Demo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp EllipseDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o ellipseDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp ArrowDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o arrowDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp TextboxDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textboxdemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Selected.cpp TextInButtonDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textinbuttondemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../Sound.cpp ../SoundPlayer.cpp ../EventSystem.cpp ../Selected.cpp SelectedDemo.cpp \
			$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o selectedDemo

clean:
	rm a.out
	rm milestone001
	rm milestone002
	rm screenDemo
	rm milestone003
	rm milestone004
	rm milestone005
	rm milestone005LayoutTests
	rm milestone006EventSystem
	rm layoutDemo
	rm milestone006
	rm milestone006Demo
	rm ellipseDemo
	rm arrowDemo
	rm textboxdemo
	rm textinbuttondemo
	rm selectedDemo
