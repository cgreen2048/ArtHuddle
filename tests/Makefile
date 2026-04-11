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

FACTORY_ELEMENTS := ../Factory.cpp ../GuiElement.cpp ../Layout.cpp ../Triangle.cpp ../Box.cpp ../Line.cpp ../Point.cpp ../Screen.cpp ../Button.cpp ../Ellipse.cpp ../Arrow.cpp ../Freehand.cpp ../Selected.cpp
EVENT_ELEMENTS := ../Event.cpp ../EventSystem.cpp ../Sound.cpp ../SoundPlayer.cpp ../ClickEvent.cpp ../ShowEvent.cpp ../SoundEvent.cpp ../MouseEvent.cpp ../MouseUpEvent.cpp ../MouseDownEvent.cpp ../MouseMotionEvent.cpp

test:
	g++ tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3

	g++ ../Matrix.cpp Milestone001Tests.cpp -o milestone001

	g++ ../Screen.cpp Milestone002Tests.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone002

	g++ ../Screen.cpp screenDemo.cpp -I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o screenDemo

	g++ Milestone003Tests.cpp ../GUIFile.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS)  \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone003

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)  Milestone004Tests.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone004

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../GUIFile.cpp Milestone005LayoutTests.cpp  \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone005LayoutTests

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) Milestone005Tests.cpp  \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone005

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) layoutDemo.cpp  \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o layoutDemo

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)   Milestone006Tests.cpp  \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone006

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)     Milestone006EventSystem.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone006EventSystem

	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)     Milestone006Demo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o milestone006Demo
	
	g++ $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)  ArrowDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o arrowDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)  EllipseDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o ellipseDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)     SelectedDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o selectedDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)    freehandDemo.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o freehandDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) LayoutDeleteTest.cpp \
		-I${SDL3_ROOT}/include -L${SDL3_ROOT}/lib -lSDL3 -o layoutDelete



studentMachine: testsSM freehandDemoSM milestone001SM milestone002SM screenDemoSM milestone003SM milestone004SM milestone005LayoutTestsSM milestone005SM layoutDemoSM milestone006SM milestone006EventSystemSM milestone006DemoSM ellipseDemoSM arrowDemoSM selectedDemoSM layoutDeleteSM

testsSM:
	$(CXX) tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

milestone001SM:
	$(CXX) ../Matrix.cpp Milestone001Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone001

milestone002SM:
	$(CXX) ../Screen.cpp Milestone002Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone002

screenDemoSM:
	$(CXX) ../Screen.cpp screenDemo.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o screenDemo

milestone003SM:
	$(CXX) Milestone003Tests.cpp $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../GUIFile.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone003

milestone004SM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) Milestone004Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone004

milestone005LayoutTestsSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ../GUIFile.cpp Milestone005LayoutTests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005LayoutTests

milestone005SM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) Milestone005Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005

layoutDemoSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) layoutDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDemo

milestone006SM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)   Milestone006Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006

milestone006EventSystemSM:
	$(CXX) $(EVENT_ELEMENTS) ${FACTORY_ELEMENTS}     Milestone006EventSystem.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006EventSystem

milestone006DemoSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)    Milestone006Demo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006Demo

ellipseDemoSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) EllipseDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o ellipseDemo

arrowDemoSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ArrowDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o arrowDemo

freehandDemoSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)    freehandDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o freehandDemo

selectedDemoSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)    SelectedDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o selectedDemo

layoutDeleteSM:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) LayoutDeleteTest.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDelete
	


# MAC IMPLEMENTATION

mac: testsMac freehandDemoMac milestone001Mac milestone002Mac screenDemoMac \
	milestone003Mac milestone004Mac milestone005LayoutTestsMac milestone005Mac \
	layoutDemoMac milestone006Mac milestone006EventSystemMac milestone006DemoMac \
	ellipseDemoMac arrowDemoMac selectedDemoMac

testsMac:
	$(CXX) tests.cpp $(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS)

freehandDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)    freehandDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o freehandDemo

milestone001Mac:
	$(CXX) ../Matrix.cpp Milestone001Tests.cpp -Wall -o milestone001

milestone002Mac:
	$(CXX) ../Screen.cpp Milestone002Tests.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone002

screenDemoMac:
	$(CXX) ../Screen.cpp screenDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o screenDemo

milestone003Mac:
	$(CXX) Milestone003Tests.cpp ../GUIFile.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone003

milestone004Mac:
	$(CXX) Milestone004Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone004

milestone005LayoutTestsMac:
	$(CXX) Milestone005LayoutTests.cpp ../GUIFile.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005LayoutTests

milestone005Mac:
	$(CXX) Milestone005Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005

layoutDemoMac:
	$(CXX) layoutDemo.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDemo

milestone006Mac:
	$(CXX) Milestone006Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS)   \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006

milestone006EventSystemMac:
	$(CXX) Milestone006EventSystem.cpp    ../GuiElement.cpp ../Layout.cpp $(EVENT_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006EventSystem

milestone006DemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)    Milestone006Demo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006Demo

ellipseDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) EllipseDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o ellipseDemo

arrowDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) ArrowDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o arrowDemo

selectedDemoMac:	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS)     SelectedDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o selectedDemo

layoutDeleteMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) LayoutDeleteTest.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDelete


clean:
	rm -f a.out freehandDemo milestone001 milestone002 screenDemo \
	      milestone003 milestone004 milestone005 milestone005LayoutTests \
	      milestone006 milestone006EventSystem milestone006Demo \
	      layoutDemo ellipseDemo arrowDemo selectedDemo layoutDelete


