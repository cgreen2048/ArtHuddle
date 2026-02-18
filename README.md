# SP26_Team02

# main.cpp

## Description

main.cpp is a demonstration program

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


# Screen

## Description
`Screen` is a class representing an SDL_Surface with methods to draw to and color pixels on the surface. THhe surface can then be displayed using an SDL_Window.
- `uint32_t width, height`: The width and height of the surface
- `SDL_Surface* surface`: Holds a pointer to the SDL_Surface object

## Methods

### `blitTo(SDL_Surface*) const`
Blits the current Screen object to the target surface
- Verifies target surface exists
- Uses SDL_BlitSurface to blit between surfaces

### `colorOnePixel(const Tvec2<T1>, const Tvec3<T2>)`


### `drawBox(Tvec2<T1>, Tvec2<T2>, Tvec3<T3>)`


### `drawBresenhamLine(ivec2, ivec2, ivec3)`


### `Screen()`


### `Screen(uint32_t, uint_32)`


### `Screen(const Screen&)`


### `Screen& operator=(const Screen&)`


### `~Screen()`



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