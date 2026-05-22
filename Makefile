STUDENT_MACHINE_SDL3_ROOT := $(HOME)/esc-courses/sp26-cse-40232.01/public/SDL
SDL3_INC := $(STUDENT_MACHINE_SDL3_ROOT)/include
SDL3_LIB := $(STUDENT_MACHINE_SDL3_ROOT)/build

CXX := g++
CXXFLAGS := -std=c++17 -I$(SDL3_INC) -Iinclude -Iexternal

# Test flags
TEST_CXXFLAGS := -std=c++17 -I. -I./external -I$(SDL3_ROOT)/include
TEST_LDFLAGS := -L$(SDL3_ROOT)/lib -Wl,-rpath,$(SDL3_ROOT)/lib

# Link flags: where to find it at link time + where to find it at run time
LDFLAGS := -L$(SDL3_LIB) -Wl,-rpath,$(SDL3_LIB)
LDLIBS := -lSDL3 -lstdc++fs -pthread

# Mac flags
MAC_CXXFLAGS := -std=c++17 -Iinclude -Iexternal
MAC_LDFLAGS := -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks
MAC_LDLIBS := -framework sdl3

FACTORY_ELEMENTS := src/core/helperFunctions.cpp src/elements/Arrow.cpp src/elements/Box.cpp src/elements/Button.cpp src/elements/Ellipse.cpp src/elements/Factory.cpp src/elements/Freehand.cpp src/elements/GuiElement.cpp src/elements/InputTextBox.cpp src/elements/Layout.cpp src/elements/Line.cpp src/elements/Point.cpp src/elements/Screen.cpp src/elements/TextBox.cpp src/elements/Triangle.cpp
EVENT_ELEMENTS := src/events/ClickEvent.cpp src/events/Event.cpp src/events/EventSystem.cpp src/events/MouseDownEvent.cpp src/events/MouseEvent.cpp src/events/MouseMotionEvent.cpp src/events/MouseUpEvent.cpp src/events/ShowEvent.cpp src/events/SoundEvent.cpp
UTILITY_ELEMENTS := src/utility/GUIFile.cpp src/utility/Selected.cpp src/utility/Sound.cpp src/utility/SoundPlayer.cpp src/utility/ThreadPool.cpp
MESSAGE_ELEMENTS := src/network/ClientNetwork.cpp src/network/DeleteElementMessage.cpp src/network/DrawElementMessage.cpp src/network/InitializeClientMessage.cpp src/network/MessageHandler.cpp src/network/RelayServer.cpp src/network/UpdateElementMessage.cpp

test:
	$(CXX) tests/tests.cpp $(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS)

	$(CXX) src/core/Matrix.cpp tests/Milestone001Tests.cpp $(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone001

	$(CXX) src/elements/Screen.cpp src/utility/ThreadPool.cpp tests/Milestone002Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone002

	$(CXX) src/elements/Screen.cpp src/utility/ThreadPool.cpp tests/screenDemo.cpp \
	 	$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o screenDemo

	$(CXX) tests/Milestone003Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone003

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone004Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone004

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)  tests/Milestone005LayoutTests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone005LayoutTests

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone005Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone005

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/layoutDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o layoutDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone006Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone006

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone006EventSystem.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone006EventSystem

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone006Demo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone006Demo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/TextboxDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o textBoxDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/TextInButtonDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o textInButtonDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/ArrowDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o arrowDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/EllipseDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o ellipseDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/SelectedDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o selectedDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)   tests/freehandDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o freehandDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)   tests/LayoutDeleteTest.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o layoutDelete
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) $(MESSAGE_ELEMENTS) src/core/Global.cpp src/core/API.cpp main.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o main


studentMachine: testsStudentMachine freehandDemoStudentMachine milestone001StudentMachine \
 	milestone002StudentMachine screenDemoStudentMachine milestone003StudentMachine \
	milestone004StudentMachine milestone005LayoutTestsStudentMachine milestone005StudentMachine \
	layoutDemoStudentMachine milestone006StudentMachine milestone006EventSystemStudentMachine \
	milestone006DemoStudentMachine ellipseDemoStudentMachine arrowDemoStudentMachine \
	textBoxDemoStudentMachine textInButtonDemoStudentMachine selectedDemoStudentMachine \
	layoutDeleteStudentMachine mainStudentMachine

testsStudentMachine:
	$(CXX) tests/tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

milestone001StudentMachine:
	$(CXX) src/core/Matrix.cpp tests/Milestone001Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone001

milestone002StudentMachine:
	$(CXX) src/elements/Screen.cpp src/utility/ThreadPool.cpp tests/Milestone002Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone002

screenDemoStudentMachine:
	$(CXX) src/elements/Screen.cpp src/utility/ThreadPool.cpp tests/screenDemo.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o screenDemo

milestone003StudentMachine:
	$(CXX) tests/Milestone003Tests.cpp $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone003

milestone004StudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone004Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone004

milestone005LayoutTestsStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone005LayoutTests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005LayoutTests

milestone005StudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone005Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005

layoutDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/layoutDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDemo

milestone006StudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone006Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006

milestone006EventSystemStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) ${FACTORY_ELEMENTS} $(UTILITY_ELEMENTS) tests/Milestone006EventSystem.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006EventSystem

milestone006DemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone006Demo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006Demo

ellipseDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/EllipseDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o ellipseDemo

arrowDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/ArrowDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o arrowDemo

freehandDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/freehandDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o freehandDemo

textBoxDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)  tests/TextboxDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textBoxDemo

textInButtonDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)  tests/TextInButtonDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textInButtonDemo

selectedDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/SelectedDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o selectedDemo

layoutDeleteStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/LayoutDeleteTest.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDelete

mainStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) $(MESSAGE_ELEMENTS) src/core/Global.cpp src/core/API.cpp main.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o main


# MAC IMPLEMENTATION

mac: testsMac freehandDemoMac milestone001Mac milestone002Mac screenDemoMac \
	milestone003Mac milestone004Mac milestone005LayoutTestsMac milestone005Mac \
	layoutDemoMac milestone006Mac milestone006EventSystemMac milestone006DemoMac \
	ellipseDemoMac arrowDemoMac textBoxDemoMac textInButtonDemoMac selectedDemoMac \
	mainMac

testsMac:
	$(CXX) tests/tests.cpp $(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS)

freehandDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/freehandDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o freehandDemo

milestone001Mac:
	$(CXX) src/core/Matrix.cpp tests/Milestone001Tests.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone001

milestone002Mac:
	$(CXX) src/elements/Screen.cpp src/utility/ThreadPool.cpp tests/Milestone002Tests.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone002

screenDemoMac:
	$(CXX) src/elements/Screen.cpp src/utility/ThreadPool.cpp tests/screenDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o screenDemo

milestone003Mac:
	$(CXX) tests/Milestone003Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone003

milestone004Mac:
	$(CXX) tests/Milestone004Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone004

milestone005LayoutTestsMac:
	$(CXX) tests/Milestone005LayoutTests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005LayoutTests

milestone005Mac:
	$(CXX) tests/Milestone005Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005

layoutDemoMac:
	$(CXX) tests/layoutDemo.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS)  \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDemo

milestone006Mac:
	$(CXX) tests/Milestone006Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS)  \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006

milestone006EventSystemMac:
	$(CXX) tests/Milestone006EventSystem.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006EventSystem

milestone006DemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/Milestone006Demo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006Demo

ellipseDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/EllipseDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o ellipseDemo

arrowDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/ArrowDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o arrowDemo

textBoxDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/TextboxDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o textBoxDemo
		
textInButtonDemoMac:	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/TextInButtonDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o textInButtonDemo

selectedDemoMac:	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/SelectedDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o selectedDemo

layoutDeleteMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) tests/LayoutDeleteTest.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDelete
	
mainMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) $(MESSAGE_ELEMENTS) src/core/Global.cpp src/core/API.cpp main.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o main

clean:
	rm -f a.out server freehandDemo milestone001 milestone002 screenDemo \
		milestone003 milestone004 milestone005 milestone005LayoutTests \
		milestone006 milestone006EventSystem milestone006Demo \
		layoutDemo ellipseDemo arrowDemo textBoxDemo textInButtonDemo \
		selectedDemo layoutDelete main


