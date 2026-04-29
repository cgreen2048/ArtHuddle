STUDENT_MACHINE_SDL3_ROOT := $(HOME)/esc-courses/sp26-cse-40232.01/public/SDL
SDL3_INC := $(STUDENT_MACHINE_SDL3_ROOT)/include
SDL3_LIB := $(STUDENT_MACHINE_SDL3_ROOT)/build

CXX := g++
CXXFLAGS := -std=c++17 -I$(SDL3_INC) -I.. -I../external

# Test flags
TEST_CXXFLAGS := -std=c++17 -I.. -I../external -I$(SDL3_ROOT)/include
TEST_LDFLAGS := -L$(SDL3_ROOT)/lib -Wl,-rpath,$(SDL3_ROOT)/lib

# Link flags: where to find it at link time + where to find it at run time
LDFLAGS := -L$(SDL3_LIB) -Wl,-rpath,$(SDL3_LIB)
LDLIBS := -lSDL3 -lstdc++fs -pthread

# Mac flags
MAC_CXXFLAGS := -std=c++17 -I.. -I../external
MAC_LDFLAGS := -Wl,-rpath,"/Library/Frameworks" -F/Library/Frameworks
MAC_LDLIBS := -framework sdl3

FACTORY_ELEMENTS := ../Factory.cpp ../GuiElement.cpp ../helperFunctions.cpp ../Layout.cpp ../Triangle.cpp ../Box.cpp ../Line.cpp ../Point.cpp ../Screen.cpp ../Button.cpp  ../Ellipse.cpp ../TextBox.cpp ../Arrow.cpp ../Freehand.cpp ../InputTextBox.cpp
EVENT_ELEMENTS := ../Event.cpp ../EventSystem.cpp ../ClickEvent.cpp ../ShowEvent.cpp ../SoundEvent.cpp ../MouseEvent.cpp ../MouseUpEvent.cpp ../MouseDownEvent.cpp ../MouseMotionEvent.cpp
UTILITY_ELEMENTS := ../Selected.cpp ../Sound.cpp ../SoundPlayer.cpp ../GUIFile.cpp ../ThreadPool.cpp
MESSAGE_ELEMENTS := ../DrawElementMessage.cpp ../DeleteElementMessage.cpp ../UpdateElementMessage.cpp ../InitializeClientMessage.cpp ../MessageHandler.cpp

test:
	$(CXX) tests.cpp $(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS)

	$(CXX) ../Matrix.cpp Milestone001Tests.cpp $(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone001

	$(CXX) ../Screen.cpp ../ThreadPool.cpp Milestone002Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone002

	$(CXX) ../Screen.cpp ../ThreadPool.cpp screenDemo.cpp \
	 	$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o screenDemo

	$(CXX) Milestone003Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone003

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone004Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone004

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)  Milestone005LayoutTests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone005LayoutTests

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone005Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone005

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) layoutDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o layoutDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone006Tests.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone006

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone006EventSystem.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone006EventSystem

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone006Demo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o milestone006Demo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) TextboxDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o textBoxDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) TextInButtonDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o textInButtonDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) ArrowDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o arrowDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) EllipseDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o ellipseDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) SelectedDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o selectedDemo
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)   freehandDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o freehandDemo

	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)   LayoutDeleteTest.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o layoutDelete
	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) $(MESSAGE_ELEMENTS) ../ClientNetwork.cpp ../RelayServer.cpp ../Global.cpp ../API.cpp apiDemo.cpp \
		$(TEST_CXXFLAGS) $(TEST_LDFLAGS) $(LDLIBS) -o apiDemo


studentMachine: testsStudentMachine freehandDemoStudentMachine milestone001StudentMachine \
 	milestone002StudentMachine screenDemoStudentMachine milestone003StudentMachine \
	milestone004StudentMachine milestone005LayoutTestsStudentMachine milestone005StudentMachine \
	layoutDemoStudentMachine milestone006StudentMachine milestone006EventSystemStudentMachine \
	milestone006DemoStudentMachine ellipseDemoStudentMachine arrowDemoStudentMachine \
	textBoxDemoStudentMachine textInButtonDemoStudentMachine selectedDemoStudentMachine \
	layoutDeleteStudentMachine apiDemoStudentMachine 

testsStudentMachine:
	$(CXX) tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

milestone001StudentMachine:
	$(CXX) ../Matrix.cpp Milestone001Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone001

milestone002StudentMachine:
	$(CXX) ../Screen.cpp ../ThreadPool.cpp Milestone002Tests.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone002

screenDemoStudentMachine:
	$(CXX) ../Screen.cpp ../ThreadPool.cpp screenDemo.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o screenDemo

milestone003StudentMachine:
	$(CXX) Milestone003Tests.cpp $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone003

milestone004StudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone004Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone004

milestone005LayoutTestsStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone005LayoutTests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005LayoutTests

milestone005StudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone005Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone005

layoutDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) layoutDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDemo

milestone006StudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone006Tests.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006

milestone006EventSystemStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) ${FACTORY_ELEMENTS} $(UTILITY_ELEMENTS) Milestone006EventSystem.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006EventSystem

milestone006DemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone006Demo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o milestone006Demo

ellipseDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) EllipseDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o ellipseDemo

arrowDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) ArrowDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o arrowDemo

freehandDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) freehandDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o freehandDemo

textBoxDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)  TextboxDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textBoxDemo

textInButtonDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS)  TextInButtonDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o textInButtonDemo

selectedDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) SelectedDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o selectedDemo

layoutDeleteStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) LayoutDeleteTest.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o layoutDelete

apiDemoStudentMachine:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) $(MESSAGE_ELEMENTS) ../ClientNetwork.cpp ../RelayServer.cpp ../Global.cpp ../API.cpp apiDemo.cpp \
		$(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o apiDemo


# MAC IMPLEMENTATION

mac: testsMac freehandDemoMac milestone001Mac milestone002Mac screenDemoMac \
	milestone003Mac milestone004Mac milestone005LayoutTestsMac milestone005Mac \
	layoutDemoMac milestone006Mac milestone006EventSystemMac milestone006DemoMac \
	ellipseDemoMac arrowDemoMac textBoxDemoMac textInButtonDemoMac selectedDemoMac \
	apiDemoMac

testsMac:
	$(CXX) tests.cpp $(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS)

freehandDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) freehandDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o freehandDemo

milestone001Mac:
	$(CXX) ../Matrix.cpp Milestone001Tests.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone001

milestone002Mac:
	$(CXX) ../Screen.cpp ../ThreadPool.cpp Milestone002Tests.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone002

screenDemoMac:
	$(CXX) ../Screen.cpp ../ThreadPool.cpp screenDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o screenDemo

milestone003Mac:
	$(CXX) Milestone003Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone003

milestone004Mac:
	$(CXX) Milestone004Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone004

milestone005LayoutTestsMac:
	$(CXX) Milestone005LayoutTests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005LayoutTests

milestone005Mac:
	$(CXX) Milestone005Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone005

layoutDemoMac:
	$(CXX) layoutDemo.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS)  \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDemo

milestone006Mac:
	$(CXX) Milestone006Tests.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS)  \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006

milestone006EventSystemMac:
	$(CXX) Milestone006EventSystem.cpp $(FACTORY_ELEMENTS) $(EVENT_ELEMENTS) $(UTILITY_ELEMENTS) \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006EventSystem

milestone006DemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) Milestone006Demo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o milestone006Demo

ellipseDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) EllipseDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o ellipseDemo

arrowDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) ArrowDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o arrowDemo

textBoxDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) TextboxDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o textBoxDemo
		
textInButtonDemoMac:	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) TextInButtonDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o textInButtonDemo

selectedDemoMac:	
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) SelectedDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o selectedDemo

layoutDeleteMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) LayoutDeleteTest.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o layoutDelete
	
apiDemoMac:
	$(CXX) $(EVENT_ELEMENTS) $(FACTORY_ELEMENTS) $(UTILITY_ELEMENTS) $(MESSAGE_ELEMENTS) ../ClientNetwork.cpp ../RelayServer.cpp ../Global.cpp ../API.cpp apiDemo.cpp \
		$(MAC_CXXFLAGS) $(MAC_LDFLAGS) $(MAC_LDLIBS) -o apiDemo

clean:
	rm -f a.out server freehandDemo milestone001 milestone002 screenDemo \
		milestone003 milestone004 milestone005 milestone005LayoutTests \
		milestone006 milestone006EventSystem milestone006Demo \
		layoutDemo ellipseDemo arrowDemo textBoxDemo textInButtonDemo \
		selectedDemo layoutDelete apiDemo


