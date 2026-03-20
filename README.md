# SP26_Team02

# main.cpp

## Description

main.cpp is a demonstration program

# GuiElement

## Description

`GuiElement` is the **base class for all drawable GUI primitives** in the system.

It defines a common interface used by all graphical objects such as:

- `Layout`
- `Point`
- `Line`
- `Box`
- `Triangle`

The class allows these derived types to be handled **polymorphically**, meaning they can be stored and manipulated using a `GuiElement*`.

Each element maintains a pointer to the `Screen` object where it will be rendered.

---

## Internal Data Structures

### `enum class guiElement`

This enumeration identifies the type of GUI element being created.  
It is primarily used by the **Factory** to determine which object to instantiate.

```cpp
enum class guiElement { LAYOUOT, POINT, LINE, BOX, TRIANGLE };
```

## Data Members

- `Screen* screen`  
  Pointer to the `Screen` object where the element will be drawn.

- `ivec2 parentStart`
  `ivec2` that stores the starting coordinates of the parent `GuiElement` (usually `Layout`)

- `ivec2 parentEnd`
  `ivec2` that stores the ending coordinates of the parent `GuiElement` (usually `Layout`)

---

## Methods

### `GuiElement()`

Default constructor.  
Initializes the base GUI element.

---

### `~GuiElement()`

Destructor for the base GUI element class.

Derived classes inherit this destructor behavior.

---

### `void draw()`

Virtual draw method intended to be **overridden by derived classes**.

Each derived class implements its own drawing behavior:

| Class | Screen Function Used |
|------|------|
| `Point` | `colorOnePixel()` |
| `Line` | `drawBresenhamLine()` |
| `Box` | `drawBox()` |
| `Triangle` | `drawTriangle()` |

In addition, calling `draw()` in a parent-type GUI Element (ex. `Layout`) will call `draw()` on all children of that parent

---

### `void writeXml(std::ostream& out) const`

Virtual method used for writing the GUI element to an XML layout file.

Derived classes override this method to write their specific geometry and color information.

---

### `void setScreen(Screen* target)`

Associates the GUI element with a target `Screen`.

Parameters:

- `target` — pointer to the `Screen` where the element should draw itself.

---

### `Screen* getScreen()`

Returns the pointer to the `Screen` associated with the GUI element.

Returns:

- `Screen*` pointing to the target screen.

---

### `void GuiElement::setParentStart(const ivec2& start)`

Sets the `parentStart` data for the current `GuiElement` object

---

### `void GuiElement::setParentEnd(const ivec2& end)`

Sets the `parentEnd` data for the current `GuiElement` object

---

### `ivec2 GuiElement::getParentStart()`

Returns the `parentStart` data for the current `GuiElement` object in `ivec2` format

---

### `ivec2 GuiElement::getParentEnd()`

Returns the `parentEnd` data for the current `GuiElement` object in `ivec2` format

---

# Factory

## Description

The `factory()` function implements a **Factory Design Pattern** used to dynamically create GUI elements.

Instead of directly constructing objects like `new Line` or `new Box`, the program calls the factory and specifies which type of element is needed.

This provides:

- centralized object creation
- simplified parsing logic
- polymorphic object handling via `GuiElement*`

The factory returns a pointer to a `GuiElement`, allowing the caller to treat all shapes uniformly.

---

## Function

### `GuiElement* factory(guiElement e)`

Creates a new GUI element based on the `guiElement` enum value.

Parameters:

- `e` — enum specifying which GUI element type to construct.

Returns:

- Pointer to a newly allocated `GuiElement` object.
- Returns `nullptr` if the enum value does not match any supported element.

---

## Supported Element Types

| Enum Value | Object Created |
|------|------|
| `guiElement::LAYOUT` | `Layout` |
| `guiElement::POINT` | `Point` |
| `guiElement::LINE` | `Line` |
| `guiElement::BOX` | `Box` |
| `guiElement::TRIANGLE` | `Triangle` |

---

## Example Usage

```cpp
GuiElement* element = factory(guiElement::LINE);

element->setScreen(screen);
element->draw();
```
# Layout

## Description
`Layout` is the primary "parent-type" `GuiElement` that functions to nest elements within certain bounds. It inherits from the `GuiElement` class to not only align itself according to its parent's bounds, but also align its children according to its own bounds.
- `vec2 start`: The percentage of the `Layout`'s parent bounds to start this `Layout` at for `x` and `y` respectively
- `vec2 end`: The percentage of the `Layout`'s parent bounds to end this `Layout` at for `x` and `y` respectively
- `bool hasParentStart`: Boolean to check if the parent bounds have been set yet so that the `Layout` cannot draw otherwise
- `bool hasParentEnd`: Similar to `hasParentStart` but for ending coordinates too to ensure that all bounds are satisfied
- `std::vector<GuiElement*> elements`: Contains all elements nested within this `Layout`
- `bool active`: Display the `Layout` or not based on the boolean parameter


## Methods

### `Layout()`
The default constructor, which only initializes `active` to false for other data to be set at a later time

### `~Layout`
The default destructor. Destroys not only the `Layout` but also all of the children that the `Layout` owns in `elements`

### `void setStart(const vec2& start)`
Sets the `start` to the starting percentage values for this `Layout`

### `void setStart(const vec2& start)`
Sets the `end` to the ending percentage values for this `Layout`

### `void setParentStart(const ivec2& start)`
Sets the parent starting coordinates as in `GuiElement` but overloaded to also set `hasParentStart` to `true` to signal that a starting bound has been added

### `void setParentEnd(const ivec2& end)`
Sets the parent ending coordinates as in `GuiElement` but overloaded to also set `hasParentEnd` to `true` to signal that an ending bound has been added

### `void setActive(bool value)`
Sets `active` to `value`, toggling the `Layout` active (able to be drawn) or not

### `void isActive()`
Getter method for `active` to check if the `Layout` can be drawn

### `void addElement(GuiElement *element)`
Adds `element` to `elements` as a child of this `Layout` and sets `element->parentStart` to the absolute starting position of this `Layout`, `element->parentEnd` to the absolute ending position of this `Layout`,
and `element->screen` to this `Layout`'s screen

### `void draw()`
If the `Layout` is active and contains both starting and ending parent bounds, iterates through every `GuiElement*` in `elements` to call their individual `draw()` functions, drawing every child element

### `void writeXml(std::ostream& out)`
Similar to `draw()` except first printing the proper `<layout>` tag with parameters and then writing to an XML by calling each child `GuiElement*`'s `writeXml()` function. I

### `vec2 getStart()`
Returns starting coordinate percentages from `this->start`

### `vec2 getEnd()`
Returns ending coordinate percentages from `this->end`

### `const std::vector<GuiElement*>& getElements() const`
Returns a reference to `Layout`'s `elements` vector

### `int getAbsoluteStartX`
Returns the absolute starting x position of this Layout

### `int getAbsoluteStartY`
Returns the absolute starting y position of this Layout

### `int getAbsoluteEndX`
Returns the absolute ending x position of this Layout

### `int getAbsoluteEndY`
Returns the absolute ending y position of this Layout

# Triangle

## Description
`Triangle` is a class used for storing and drawing a filled triangle to a `Screen` object. It inherits from the `GuiElement` class
- `ivec2 a`: the coordinates of the first point of the triangle
- `ivec2 b`: the coordinates of the second point of the triangle
- `ivec2 c`: the coordinates of the third point of the triangle
- `ivec3 color`: the color of the triangle
- `TagType aType`: the type of tag for the `a` attribute
- `TagType bType`: the type of tag for the `b` attribute
- `TagType cType`: the type of tag for the `c` attribute
- `TagType colorType`: the type of tag for the `color` attribute

## Methods

### `Triangle()`
The default constructor. Initializes `a`, `b`, `c`, and `color` to zeros

### `Triangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec3 color)`
The parameterized constructor. Assigns `pointA` to `a`, `pointB` to `b`, `pointC` to `c`, and `color` to `color

### `~Triangle()`
The default destructor

### `void draw()`
Method to draw the stored triangle to a `Screen` object
- Accesses `screen` attribute (inherited from the `GuiElement` class) storing a pointer to a `Screen` object
- Calls the `drawTriangle` within the `Screen` class to draw the box to to the screen's `SDL_Surface`

### `void Triangle::setA(const ivec2& v, TagType t)`
Method to set the `a` and `aType` attributes of a triangle object

### `void Triangle::setB(const ivec2& v, TagType t)`
Method to set the `b` and `bType` attributes of a triangle object

### `void Triangle::setC(const ivec2& v, TagType t)`
Method to set the `c` and `cType` attributes of a triangle object

### `void Triangle::setColor(const ivec3& v, TagType t)`
Method to set the `color` and `colorType` attributes of a triangle object

### `getA()`
Returns the `a` attribute of the triangle

---

### `getB()`
Returns the `b` attribute of the triangle

---

### `getC()`
Returns the `c` attribute of the triangle

---

### `void writeXml(std::ostream& out) const`

Writes the triangle to an XML layout file.

Behavior:

- Writes a `<triangle>` tag to the output stream
- Writes the three triangle vertices (`a`, `b`, `c`)
- Each vertex is written as either:
  - `<vec2>` if the stored `TagType` is `TagType::Vec`
  - `<ivec2>` if the stored `TagType` is `TagType::IVec`
- Writes the triangle color (`color`)
  - `<vec3>` if `TagType::Vec`
  - `<ivec3>` if `TagType::IVec`
- Closes the `<triangle>` tag

This allows the triangle to preserve whether the original data used floating-point (`vec`) or integer (`ivec`) values when writing the layout file.

# Box

## Description
`Box` is a class used for storing and drawing a filled box to a `Screen` object. It inherits from the `GuiElement` class
- `vec2 min`: the coordinates of the minimum point of the box
- `vec2 max`: the coordinates of the maximum point of the box
- `vec3 color`: the color of the box
- `TagType minType`: the type of tag for the `min` attribute
- `TagType maxType`: the type of tag for the `max` attribute
- `TagType colorType`: the type of tag for the `color` attribute

## Methods

### `Box()`
The default constructor. Initializes `min`, `max`, and `color` to zeros

### `Box(vec2 min, vec2 max, vec3 color)`
The parameterized constructor. Assigns `min`, `max`, and `color` to appropriate attributes in the `Box` class

### `~Box()`
The default destructor

### `void draw()`
Method to draw the stored box to a `Screen` object
- Accesses `screen` attribute (inherited from the `GuiElement` class) storing a pointer to a `Screen` object
- Calls the `drawBox` within the `Screen` class to draw the box to to the screen's `SDL_Surface`

### `void Box::setMin(const ivec2& v, TagType t)`
Method to set the `min` and `minType` attributes of a box object

### `void Box::setB(const ivec2& v, TagType t)`
Method to set the `max` and `maxType` attributes of a box object

### `void Box::setColor(const ivec3& v, TagType t)`
Method to set the `color` and `colorType` attributes of a box object

### `void writeXml(std::ostream& out) const`

Writes the box to an XML layout file.

Behavior:

- Writes a `<box>` tag to the output stream
- Writes the minimum corner (`min`)
  - `<vec2>` if the stored `TagType` is `TagType::Vec`
  - `<ivec2>` if the stored `TagType` is `TagType::IVec`
- Writes the maximum corner (`max`)
  - `<vec2>` if the stored `TagType` is `TagType::Vec`
  - `<ivec2>` if the stored `TagType` is `TagType::IVec`
- Writes the box color (`color`)
  - `<vec3>` if `TagType::Vec`
  - `<ivec3>` if `TagType::IVec`
- Closes the `<box>` tag

This ensures the XML output preserves whether integer or floating-point vector tags were used.

# Line

## Description
`Line` is a class used for storing and drawing a line to a `Screen` object. It inherits from the `GuiElement` class
- `vec2 start`: the coordinates of the starting point of the line
- `vec2 end`: the coordinates of the ending point of the line
- `vec3 color`: the color of the line
- `TagType startType`: the type of tag for the `start` attribute
- `TagType endType`: the type of tag for the `end` attribute
- `TagType colorType`: the type of tag for the `color` attribute

## Methods

### `Line()`
The default constructor. Initializes `start`, `end`, and `color` to zeros

### `Line(vec2 start, vec2 end, vec3 color)`
The parameterized constructor. Assigns `start`, `end`, and `color` to appropriate attributes in the `Line` class

### `~Line()`
The default destructor

### `void draw()`
Method to draw the stored line to a `Screen` object
- Accesses `screen` attribute (inherited from the `GuiElement` class) storing a pointer to a `Screen` object
- Calls the `drawBresenhamLine` within the `Screen` class to draw the line to to the screen's `SDL_Surface`

### `void Line::setStart(const ivec2& v, TagType t)`
Method to set the `start` and `startType` attributes of a line object

### `void Box::setEnd(const ivec2& v, TagType t)`
Method to set the `end` and `endType` attributes of a line object

### `void Line::setColor(const ivec3& v, TagType t)`
Method to set the `color` and `colorType` attributes of a line object

### `void writeXml(std::ostream& out) const`

Writes the line to an XML layout file.

Behavior:

- Writes a `<line>` tag to the output stream
- Writes the starting point (`start`)
  - `<vec2>` if the stored `TagType` is `TagType::Vec`
  - `<ivec2>` if the stored `TagType` is `TagType::IVec`
- Writes the ending point (`end`)
  - `<vec2>` if the stored `TagType` is `TagType::Vec`
  - `<ivec2>` if the stored `TagType` is `TagType::IVec`
- Writes the line color (`color`)
  - `<vec3>` if `TagType::Vec`
  - `<ivec3>` if `TagType::IVec`
- Closes the `<line>` tag

This allows the line to maintain the same vector type used in the original layout file.

# Point

## Description
`Point` is a class used for storing and drawing a point to a `Screen` object. It inherits from the `GuiElement` class
- `vec2 coords`: the coordinates of the point
- `vec3 color`: the color of the box
- `TagType coordsType`: the type of tag for the `coords` attribute
- `TagType colorType`: the type of tag for the `color` attribute

## Methods

### `Point()`
The default constructor. Initializes `coords` and `color` to zeros

### `Point(vec2 coords, vec3 color)`
The parameterized constructor. Assigns `coords` and `color` to appropriate attributes in the `Point` class

### `~Point()`
The default destructor

### `void draw()`
Method to draw the stored point to a `Screen` object
- Accesses `screen` attribute (inherited from the `GuiElement` class) storing a pointer to a `Screen` object
- Calls the `colorOnePixel` within the `Screen` class to draw the point to to the screen's `SDL_Surface`

### `void Point::setCoords(const ivec2& v, TagType t)`
Method to set the `coords` and `coordsType` attributes of a point object

### `void Point::setColor(const ivec3& v, TagType t)`
Method to set the `color` and `colorType` attributes of a point object

### `void writeXml(std::ostream& out) const`

Writes the point to an XML layout file.

Behavior:

- Writes a `<point>` tag to the output stream
- Writes the point position (`coords`)
  - `<vec2>` if the stored `TagType` is `TagType::Vec`
  - `<ivec2>` if the stored `TagType` is `TagType::IVec`
- Writes the point color (`color`)
  - `<vec3>` if `TagType::Vec`
  - `<ivec3>` if `TagType::IVec`
- Closes the `<point>` tag

This ensures the XML output preserves whether integer or floating-point vector tags were used in the layout file.

# GUIFile

## Description

`GUIFile` is responsible for **reading and writing an XML-based layout file** that describes a hierarchy of GUI elements.

---

## Key Update

Instead of storing elements in a flat container:

```cpp
std::vector<GuiElement*> elements;
```
the system now uses a hierarchical structure:
```cpp
Layout* rootLayout;
```

## Core Concept

### Layout Tree Structure

The GUI is represented as a tree:
```
Layout (root)
├── Layout
│   ├── Line
│   └── Box
├── Triangle
└── Point
```

- Every node is a `GuiElement`
- `Layout` nodes can contain children
- Leaf nodes are drawable primitives (`Line`, `Box`, `Point`, `Triangle`)

---

## Data Members

### `Layout* rootLayout`

- Pointer to the root layout of the GUI
- Owns the entire hierarchy
- All elements are stored within this layout tree
- `GUIFile` is responsible for deleting it

---

## Memory Management

### Key Idea

Ownership is hierarchical:

- `GUIFile` owns `rootLayout`
- `Layout` owns all of its child elements

Deleting the root layout recursively deletes the entire GUI structure.


The class supports both floating-point vector tags (`<vec2>`, `<vec3>`) and integer vector tags (`<ivec2>`, `<ivec3>`).  
When reading, the parser records which tag type was used and stores that information in the element using a `TagType`.  
When writing, each element's `writeXml()` method outputs the correct tag type.


## XML Token Constants

The header defines constant strings representing all valid XML tokens:

### Layout Tags
- `<layout>`
- `</layout>`

### Element Tags
- `<line>`
- `</line>`
- `<box>`
- `</box>`
- `<point>`
- `</point>`

### Vector Tags
- `<vec2>`
- `<vec3>`
- `<ivec2>`
- `<ivec3>`

### Coordinate Tags
- `<x>`
- `<y>`
- `<z>`

Two arrays are used to validate XML structure:

- `OPENERS` → list of all opening tags
- `CLOSERS` → list of all closing tags

These are used by the parser to verify correct nesting.

---

# Supported XML Layout Format

### Layout Tag

Layouts include bounds as attributes:


```xml
<layout sX="0" sY="0" eX="1" eY="1">
    <layout sX="0.1" sY="0.1" eX="0.5" eY="0.5">
        <line>
            <vec2>
                <x>10</x>
                <y>20</y>
            </vec2>
            <vec2>
                <x>40</x>
                <y>60</y>
            </vec2>
            <vec3>
                <x>255</x>
                <y>0</y>
                <z>0</z>
            </vec3>
        </line>
    </layout>

    <triangle>
        ...
    </triangle>
</layout>
```

Both `<vec*>` and `<ivec*>` variants are supported.

---

## Public Methods

### `GUIFile()`

Default constructor.

- Initializes `rootLayout` to `nullptr`

---

### `~GUIFile()`

Destructor.

- Calls `clear()` to free all owned memory

---

### `void clear()`

Deletes the entire layout tree.

```cpp
if (rootLayout != nullptr) {
    delete rootLayout;
    rootLayout = nullptr;
}
```

### `Layout* getRootLayout() const`

Returns the pointer to the root layout.

---

### `void setRootLayout(Layout* root)`

Sets a new root layout.

- Deletes the existing layout if one exists  
- Transfers ownership of `root` to `GUIFile`  

---

# File Parsing

### `void readFile(const std::string& fileName)`

Reads an XML file and constructs the layout tree.

#### Behavior

- Clears existing data  
- Opens the file  
- Reads the first tag  
- Verifies it is a valid `<layout ...>` tag  
- Calls the internal recursive parser  
- Stores the result in `rootLayout`  

---

### `void writeFile(const std::string& fileName) const`

Writes the layout tree to an XML file.

#### Behavior

- Opens the output file  
- Verifies `rootLayout` exists  
- Calls:

```cpp
rootLayout->writeXml(out);
```
The layout recursively writes all children

---
## Internal Helper Functions

These functions are internal to `GUIFile.cpp` and are not part of the public interface.

They implement the parsing logic used by `readFile()`.

---

### `Layout* parseLayout(std::ifstream& inFile, const std::string& layoutOpenTag)`

Parses a `<layout ...>` tag and its contents.

#### Purpose

- Creates a `Layout`  
- Reads layout attributes:
  - `sX`, `sY`  
  - `eX`, `eY`  
- Recursively parses:
  - child layouts  
  - child elements  
- Returns the completed layout subtree

#### Additional Parsing Details

- Uses helper functions (`parseVec2`, `parseIVec2`, `parseVec3`, `parseIVec3`) to read vector data  
- These helpers ensure all required components (`x`, `y`, `z`) are present  
- If any component is missing or malformed, parsing fails immediately  

#### Why recursion is used

Layouts can contain other layouts, forming a tree structure.  
A recursive function naturally mirrors this structure.

---

### `GuiElement* parseElement(std::ifstream& inFile, const std::string& elementOpenTag)`

Parses a drawable GUI element.

#### Supported types

- `Point`  
- `Line`  
- `Box`  
- `Triangle`  

#### Behavior
- Determines type from opening tag
- Uses the Factory to create the object
- Parses coordinate and color data
- Stores tag type (vec vs ivec)
- Uses vector parsing helpers
- Preserves original tag types for XML output
- Returns a GuiElement*
---

## Error Handling

If malformed XML is detected:

- `"Malformed XML"` is printed  
- Partially created objects are deleted  
- Parsing stops immediately  

### Examples of malformed XML

- Missing layout attributes  
- Mismatched tags  
- Missing coordinates  
- Invalid nesting  
- Missing vector components  
- Unexpected tags  

---

## Internal Parsing Utilities

Used during parsing:

- `trim()` → removes whitespace  
- `getNextTag()` → reads next XML tag  
- `getNextPayload()` → reads text between tags  
- `getFloatAttribute()` → extracts layout attributes  
- `isLayoutOpen()` / `isLayoutClose()` → layout tag checks  
- `isElementOpen()` → element detection  
- `isMatchingElementClose()` → validates closing tags
- `determineGuiElementOpenerType()` → maps XML tags to `guiElement` enum  
- `parseVec2()` → parses `<vec2>` data and validates structure  
- `parseIVec2()` → parses `<ivec2>` integer vector data  
- `parseVec3()` → parses `<vec3>` data with x, y, z components  
- `parseIVec3()` → parses `<ivec3>` integer vector data    

---

## Type Conversion Helpers

Used to convert between float and integer vector types:

- `toIVec2(const vec2&)`  
- `toIVec3(const vec3&)`  
- `toVec2(const ivec2&)`  
- `toVec3(const ivec3&)`  
- `toInt(float)`  

These ensure the correct internal representation while preserving original XML tag types.

---


## UML Diagram
![UML Diagram](images/Milestone003_UML.png)

---

# Screen

## Description
`Screen` is a class representing an SDL_Surface with methods to draw to and color pixels on the surface. THhe surface can then be displayed using an SDL_Window.
- `uint32_t width, height`: The width and height of the surface
- `SDL_Surface* surface`: Holds a pointer to the SDL_Surface object

## Methods

### `blitTo(SDL_Surface* target) const`
Blits the current Screen object to the target surface
- Takes in pointer to an SDL_Surface as the target to blit to
- Verifies target surface exists
- Uses `SDL_BlitSurface` to blit between surfaces

### `colorOnePixel(const Tvec2<T1> coords, const Tvec3<T2> colors, ivec2 parentStart, ivec2 parentEnd)`
Colors target pixel in object's SDL_Surface
- Uses a 2D mathematical vector object to hold target pixel's X and Y components
- Uses a 3D mathematical vector object to hold target pixel's color value in RGB format (clamped between 0 and 255)
- Uses `SDL_MapRGBA` to convert the color to the pixel
- Will only draw if the pixel falls within the bounds of the Screen as well as the `parentStart` and `parentEnd` coordinates passed from a drawable object's `Layout` object

### `drawBox(Tvec2<T1> min, Tvec2<T2> max, Tvec3<T3> colors, ivec2 parentStart, ivec2 parentEnd)`
Draws a box on the target Screen object's SDL_Surface
- Uses 2D mathematical vectors to store the minimum and maximum coordinates for the box
- Clamps minimum and maximum X and Y values between 0 and the Screen object's height/width values
- Uses 3D mathematical vector to store the target color for the box
- Calls `colorOnePixel` for each coordinate in the bounds of the box in a double nested for loop as long as the coordinate falls within the `parentStart` and `parentEnd` coordinates passed from the Box's `Layout` object

### `pointInTriangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec2 pointP)`
Determines if `pointP` is within the bounds of the triangle established by `pointA`, `pointB`, and `pointC`
- Calculates the cross products AP x AB, BP x BC, & CP x CA
- If no conflicting signs exist between these three cross products, `point` is inside the triangle, else it is not

### `drawTriangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec3 color, ivec2 parentStart, ivec2 parentEnd)`
Draws a triangle on the target Screen object's SDL_Surface
- Computes a bounding box around the triangle using the min and max of the corners' x & y values
- Iterates over all points in the box & uses pointInTriangle to determine if the current point is in the triangle
- Calls `colorOnePixel` for each coordinate in the bounds of the triangle 

### `drawBresenhamLine(ivec2 start, ivec2 end, ivec3 color, ivec2 parentStart, ivec2 parentEnd)`
Draws a line to the Target Screen object's SDL_Surface using the Bresenham algorithm
- Uses 2D mathematical vectors to store the start and end points of the line
- Will only draw on pixels that exist in the surface
- Calls `colorOnePixel` for each pixel that exists on the line

### `clear(ivec3 color)`
Clears the Target Screen object's `SDL_Surface` by filling the entire surface with the given color
- Uses `drawBox` to draw a filled rectangle from `(0, 0)` to `(width, height)`
- Overwrites all previously drawn pixels in the surface
- Intended to be called at the start of each frame before drawing new elements

### `SDL_Surface* getSurface()`
Returns the surface for comparisons

### `uint32_t getHeight()`
Returns the height stored in the Screen object

### `uint32_t getWidth()`
Returns the width stored in the Screen object

### `bool surfaceEqual(const SDL_Surface* rhs)`
Compares the current Screen's SDL_Surface with the target SDL_Surface
- Uses `memcmp` to compare the memory of the two surfaces
- Returns false if either surface does not exist or is not equal, true otherwise

### `Screen()`
Default constructor. Initializes `width` and `height` to 0

### `Screen(uint32_t w, uint_32 h)`
Constructor that takes in values for width and height. Calls SDL_CreateSurface to create an SDL_Surface for the object
- Calls drawBox() to fill the entire screen with a black box as a way of clearing garbage values

### `Screen(const Screen& cp)`
Copy constructor. Creates a new Screen with the same values as `cp`
- Calls `cp.blitTo(this->surface)` to blit existing surface to the new surface

### `Screen& operator=(const Screen& cp)`
Copy assignment operator. Replaces Screen object's values with values from `cp`.
- Calls `cp.blitTo(this->surface)` to blit existing surface to the new surface

### `bool operator==(const Screen rhs)`
Compares two Screen objects
- Compares Screen widths and heights
- Calls surfaceEqual to check surface equality
- Returns false if any checks fail, true otherwise

### `~Screen()`
Destructor method. Checks if Screen object has a valid SDL_Surface before calling `SDL_DestroySurface`


# Matrix

## Description

`Matrix` is a 2D array of floats:
- `MATRIX_MAX` defined to be 3, used for both dimensions
- `float matrix[MATRIX_MAX][MATRIX_MAX]`
- `x[a][c]` is defined to be a float
    - *Note: Bracket access is not a public method

## Methods

### `Matrix()`
Matrix constructor. Initializes all elements to 0 using list initialization

### `Matrix(float _data[MATRIX_MAX][MATRIX_MAX])`
Creates a new Matrix object with floats stored in 2D _data array
- Uses a nested for loop to assign corresponding elements from `_data` to `components` array

### `Matrix(const Matrix& cp)`
Copy constructor. Places values in `components` with values from Matrix `cp`
- Uses a nested for loop to assign corresponding elements from `cp.components` to `components`

### `Matrix& operator=(const Matrix& cp)`
Replaces values in target Matrix's `components` with values from `cp.components`
- If target Matrix and Matrix cp are equal, this function immediately returns
- Uses a nested for loop to assign corresponding elements from `cp.components` to `components`

### `bool operator==(Matrix rhs)`
Checks Matrices for equality
- Uses a nested for loop to check target Matrix's values against corresponding values in Matrix rhs
- Returns false immediately if any values do not match between Matrices
- Returns true if nested for loops cycle through entire Matrix

### `bool operator!=(Matrix rhs)`
Returns the inverse of operator==
- Negates operator== in implementation
- Refer to operator== documentation for description of funtionality

### `Matrix operator*(Matrix rhs)`
Performs matrix multiplication with the target matrix on the left hand side and Matrix rhs on the right hand side, returning a Matrix
- Creates a vec3 for each row and column to utilize existing dot() functionality defined in vec3.hpp
- Performs dot product between each row and column according to the steps of matrix multiplication
- Creates a temporary 2D array of floats before returning a Matrix

### `Matrix transpose()`
Returns the transpose of target Matrix as a Matrix
- Creates a temporary 2D array of floats before returning a Matrix

# vec2

## Description

`vec2` is a 2D mathematical vector storing:

- `x` component (`float`)
- `y` component (`float`)

`ivec2` is the integer specialization of `vec2`, storing:

- `x` component (`int`)
- `y` component (`int`)

## Methods

### Constructors

### `Tvec2()`

Default constructor. Initializes both components to zero and binds `x` and `y` as references to the underlying `components` array.

- Initializes `components` to `{0, 0}`
- Sets `x` to alias `components[0]`
- Sets `y` to alias `components[1]`

---

### `Tvec2(const Tvec2& cp)`

Copy constructor. Creates a new vector with the same component values as `cp`.

- Uses constructor delegation to run the default constructor first
- Copies `cp.x` and `cp.y` into this vector

Parameters:
- `cp` — the vector to copy from

---

### `Tvec2(T _x, T _y)`

Value constructor. Creates a new vector with the given `x` and `y` component values.

- Uses constructor delegation to run the default constructor first
- Assigns `_x` to `x` and `_y` to `y`

Parameters:
- `_x` — initial x-component value  
- `_y` — initial y-component value  

---

### Assignment

### `Tvec2& operator=(const Tvec2& cp)`

Copy assignment operator. Replaces this vector’s component values with `cp`’s component values.

- Self-assignment safe (checks `this == &cp`)
- Copies `cp.x` and `cp.y`
- Returns `*this` to allow chaining

Parameters:
- `cp` — the vector to copy from

Returns:
- A reference to the modified vector (`*this`)

---

### Vector Math

### `T dot(Tvec2 rhs)`

Computes the dot product between this vector and `rhs`.

Parameters:
- `rhs` — the other vector

Returns:
- The dot product as type `T`

---

### `T mag()`

Computes the Euclidean magnitude (length) of the vector.


Returns:
- The magnitude as type `T`

---

### `Tvec2 unit()`

Returns the unit (normalized) vector pointing in the same direction as this vector.


Returns:
- A new `Tvec2` with components `(x / mag(), y / mag())`

Notes:
- If the magnitude is zero, this will divide by zero (undefined behavior).

---

### `T cross(Tvec2 rhs)`

Computes the cross product between the current vector & the `rhs` vector

Parameters:
- `rhs` — the other vector

Returns:
- The scalar cross product as type `T`

### Comparison Operators

### `bool operator==(Tvec2 rhs)`

Checks component-wise equality with `rhs`.

Returns:
- `true` if `x == rhs.x` and `y == rhs.y`, otherwise `false`

---

### `bool operator!=(Tvec2 rhs)`

Checks component-wise inequality with `rhs`.

Returns:
- `true` if at least one component differs, otherwise `false`

---

### Element Access

### `T& operator[](int index)`

Provides mutable access to a vector component using array-style indexing.

- `index == 0` accesses `x`
- `index == 1` accesses `y`

Parameters:
- `index` — the component position to access

Returns:
- A reference to the component at the specified index

Notes:
- Because this function returns a reference (`T&`), the returned component can be modified (e.g., `v[0] = 5;`).
- If `index` is out of range, this implementation prints an error message and terminates the program.

---

### Arithmetic Operators

### `Tvec2& operator+=(Tvec2 rhs)`

Adds `rhs` to this vector (component-wise) and returns the modified vector.

Parameters:
- `rhs` — vector to add

Returns:
- A reference to the modified vector (`*this`)

---

### `Tvec2 operator+(Tvec2 rhs)`

Returns the component-wise sum of this vector and `rhs`.

Parameters:
- `rhs` — vector to add

Returns:
- A new `Tvec2` equal to `(*this + rhs)`

---

### `Tvec2& operator*=(T scalar)`

Multiplies this vector by a scalar and returns the modified vector.

Parameters:
- `scalar` — the scalar multiplier

Returns:
- A reference to the modified vector (`*this`)

---

### `Tvec2 operator*(T scalar)`

Returns the result of scalar multiplication.

Parameters:
- `scalar` — the scalar multiplier

Returns:
- A new `Tvec2` equal to `(*this * scalar)`

---

### `Tvec2& operator-=(Tvec2 rhs)`

Subtracts `rhs` from this vector (component-wise) and returns the modified vector.

Parameters:
- `rhs` — vector to subtract

Returns:
- A reference to the modified vector (`*this`)

---

### `Tvec2 operator-(Tvec2 rhs)`

Returns the component-wise difference of this vector and `rhs`.

Parameters:
- `rhs` — vector to subtract

Returns:
- A new `Tvec2` equal to `(*this - rhs)`

---

### Template Specializations (`T = int`)

The following member functions are explicitly specialized for `Tvec2<int>` (i.e., `ivec2`) to preserve integer return types while performing floating-point calculations internally.

---

### `int mag()`  *(specialization for `ivec2`)*

Computes the Euclidean magnitude of the integer vector and returns the result rounded to the nearest integer.


Implementation details:

- Computes the magnitude using `std::sqrt`
- Rounds the result using `std::round`
- Casts the result to `int` using `static_cast<int>`

Returns:
- The rounded magnitude as an `int`

Notes:
- Uses `inline` to prevent multiple definition errors when included in header files.

---

### `ivec2 unit()`  *(specialization for `ivec2`)*

Returns the unit vector of an integer vector with each component rounded to the nearest integer.

Implementation details:

- Computes the integer magnitude using the specialized `mag()`
- Divides each component by the magnitude
- Rounds each result using `std::round`
- Casts each component to `int`

Returns:
- A new `ivec2` with rounded integer components

Notes:
- If the magnitude is zero, this results in division by zero (undefined behavior).
- Because integer vectors cannot exactly represent most normalized vectors, rounding is required.



# vec3

## Description
`vec3` is a 3D mathematical vector storing:
- `float components[3]`
with
- `x`: `components[0]` (`float&`)
- `y`: `components[1]` (`float&`)
- `z`: `components[2]` (`float&`)

`ivec3` is a 3D mathematical vector storing:
- `int components[3]`
with
- `x`: `components[0]` (`int&`)
- `y`: `components[1]` (`int&`)
- `z`: `components[2]` (`int&`)

## Methods

### return identifier(parameter list)

### `Tvec3()`
Initializes components to [0,0,0] & binds `x`, `y`, & `z` as references to the underlying `components` array.

### `Tvec3(const Tvec3& cp)`
Creates a new Tvec3 with the same component values as `cp` via copying `cp.x` to `x` & `cp.y` to `y`

### `Tvec3(T _x, T _y, T_z)`
Creates a new Tvec3 with component values [`_x`, `_y`, `_z`]

### `Tvec3& operator=(const Tvec3& cp)`
Replaces the current vector's components with `cp`'s components

### `T dot(Tvec3 rhs)`
Computes the dot product of the current vector with `rhs`

### `T mag()`
Computes the magnitude of the current vector

### `Tvec3 unit()`
Constructs a unit vector from the current vector, returning this unit vector

### `Tvec3 cross(Tvec3 rhs)`
Computes the cross product between the current vector and `rhs`, returning a new `Tvec3` 
whose components correspond to the cross product's output

### `bool operator==(Tvec3 rhs)`
Checks if each component of the current vector is equal to each component of `rhs` respectively, returning true if so or false if not

### `bool operator!=(Tvec3 rhs)`
Checks if any component of the current vector is equal to the respective component of `rhs`, returning true if so or false if not

### `T& operator[](int index)`
Allows for random indexing of `components` by returning a reference to the value in `components` at `index`

### `Tvec3& operator+=(const Tvec3& rhs)` 
Adds `rhs.x`, `rhs.y`, & `rhs.z` to current vector's `x`, `y`, & `z` respectively, returning a reference to the current vector

### `Tvec3 operator+(const Tvec3& rhs)` 
Completes the same computation as the `+=` overload but returns a copy of
the current vector after addition without changing the current vector's values

### `Tvec3& operator*=(T scalar)` 
Multiplies the current vector's `x`, `y`, & `z`, each by `scalar`, returning a reference to the current vector

### `Tvec3 operator*(const Tvec3& rhs)` 
Completes the same computation as the `*=` overload but returns a copy of
the current vector after scalar multiplication without changing the current vector's values

### `Tvec3& operator-=(const Tvec3& rhs)` 
Subtracts `rhs.x`, `rhs.y`, & `rhs.z` from current vector's `x`, `y`, & `z` respectively, returning a reference to the current vector

### `Tvec3 operator-(const Tvec3& rhs)` 
Completes the same computation as the `-=` overload but returns a copy of
the current vector after subtraction without changing the current vector's values

### `int ivec3::mag()`
Specialized version of the `mag()` function for the `ivec3` class that rounds the magnitude to the nearest integer then casts it as an integer

### `ivec3 ivec3::unit()`
Specialized version of the `unit()` function for the `ivec3` class that rounds each component of the computed unit vector to the nearest integer and then casts each as an `int`