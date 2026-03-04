# SP26_Team02

# main.cpp

## Description

main.cpp is a demonstration program

# Box

## Description
`Box` is a class used for storing and drawing a filled box to a `Screen` object. It inherits from the `GuiElement` class
- `vec2 min`: the coordinates of the minimum point of the box
- `vec2 max`: the coordinates of the maximum point of the box
- `vec3 color`: the color of the box

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


# Line

## Description
`Line` is a class used for storing and drawing a line to a `Screen` object. It inherits from the `GuiElement` class
- `vec2 start`: the coordinates of the starting point of the line
- `vec2 end`: the coordinates of the ending point of the line
- `vec3 color`: the color of the line

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


# Point

## Description
`Point` is a class used for storing and drawing a point to a `Screen` object. It inherits from the `GuiElement` class
- `vec2 coords`: the coordinates of the point
- `vec3 color`: the color of the box

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


# GUIFile

## Description

`GUIFile` is a class responsible for reading and writing a simple XML-like layout file that describes graphical primitives.

It stores three types of objects:

- `std::vector<Line> lines`
- `std::vector<Box> boxes`
- `std::vector<Point> points`

Each object stores position data (`vec2` / `ivec2`) and color data (`vec3` / `ivec3`).  

The class supports both floating-point vectors (`<vec2>`, `<vec3>`) and integer vectors (`<ivec2>`, `<ivec3>`), tracking which type was used through the `TagType` enum.

---

## Internal Data Structures

### `enum class TagType`
Indicates whether a vector was parsed/written as:
- `TagType::Vec` → `<vec2>` or `<vec3>`
- `TagType::IVec` → `<ivec2>` or `<ivec3>`

---

### `Line`

A nested struct inside GUIFile that represents a line segment

- `vec2 start`
- `vec2 end`
- `vec3 color`
- `TagType startType`
- `TagType endType`
- `TagType colorType`

Used to store both geometric and color information for a line.

---

### `Box`

A nested struct inside GUIFile that represents an axis-aligned rectangle.

- `vec2 min`
- `vec2 max`
- `vec3 color`
- `TagType minType`
- `TagType maxType`
- `TagType colorType`

---

### `Point`

A nested struct inside GUIFile that represents a single point in space.

- `vec2 position`
- `vec3 color`
- `TagType posType`
- `TagType colorType`

---

## Supported XML Layout Format

The layout file must follow this structure:

```xml
<layout>
    <line>
        <vec2>
            <x>...</x>
            <y>...</y>
        </vec2>
        <vec2>
            <x>...</x>
            <y>...</y>
        </vec2>
        <vec3>
            <x>...</x>
            <y>...</y>
            <z>...</z>
        </vec3>
    </line>

    <box> ... </box>

    <point> ... </point>
</layout>
```

Both `<vec*>` and `<ivec*>` variants are supported.

---

## Public Methods

### `GUIFile()`

Default constructor.  
Initializes empty vectors of lines, boxes, and points.

---

### `const std::vector<Line>& getLines() const`
Returns all stored `Line` objects.

---

### `const std::vector<Box>& getBoxes() const`
Returns all stored `Box` objects.

---

### `const std::vector<Point>& getPoints() const`
Returns all stored `Point` objects.

---

### `void addLine(const Line& l)`
Appends a `Line` to the internal list.

---

### `void addBox(const Box& b)`
Appends a `Box` to the internal list.

---

### `void addPoint(const Point& p)`
Appends a `Point` to the internal list.

---

### `void clear()`
Clears all stored layout data:
- `lines`
- `boxes`
- `points`

Used before loading a new file.

---

## File Parsing

### `void readFile(std::string fileName)`

Reads a layout file and parses its contents.

### Behavior:

- Opens the file using `std::ifstream`
- Uses a stack to match opening and closing tags
- Detects malformed XML structures
- Builds:
  - `Line`
  - `Box`
  - `Point`
- Validates:
  - Proper tag nesting
  - Required `<x>`, `<y>`, `<z>` values
  - Matching open/close tag pairs
- Converts `<ivec*>` values into floating-point equivalents when stored

If malformed input is detected:
- Prints `"Malformed XML"`
- Immediately exits parsing

---

## File Writing

### `void writeFile(const std::string& fileName) const`

Writes the current layout data to file in proper XML format.

### Behavior:

- Opens output file
- Writes root `<layout>` tag
- Iterates through:
  - Lines
  - Boxes
  - Points
- Writes each object using the correct tag type:
  - `<vec2>` vs `<ivec2>`
  - `<vec3>` vs `<ivec3>`
- Closes layout properly

Integer vectors are written using rounded float values.

---

These are static helper utilities used during parsing and writing:

- `trim()` → Removes leading/trailing whitespace
- `toInt()` → Rounds float and converts to int
- `writeVec2()`
- `writeIVec2()`
- `writeVec3()`
- `writeIVec3()`

These functions ensure consistent formatting of XML output.

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

### `colorOnePixel(const Tvec2<T1> coords, const Tvec3<T2> colors)`
Colors target pixel in object's SDL_Surface
- Uses a 2D mathematical vector object to hold target pixel's X and Y components
- Uses a 3D mathematical vector object to hold target pixel's color value in RGB format (clamped between 0 and 255)
- Uses `SDL_MapRGBA` to convert the color to the pixel

### `drawBox(Tvec2<T1> min, Tvec2<T2> max, Tvec3<T3> colors`
Draws a box on the target Screen object's SDL_Surface
- Uses 2D mathematical vectors to store the minimum and maximum coordinates for the box
- Clamps minimum and maximum X and Y values between 0 and the Screen object's height/width values
- Uses 3D mathematical vector to store the target color for the box
- Calls `colorOnePixel` for each coordinate in the bounds of the box in a double nested for loop

### `drawBresenhamLine(ivec2 start, ivec2 end, ivec3 color)`
Draws a line to the Target Screen object's SDL_Surface using the Bresenham algorithm
- Uses 2D mathematical vectors to store the start and end points of the line
- Will only draw on pixels that exist in the surface
- Calls colorOnePixel for each pixel that exists on the line

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