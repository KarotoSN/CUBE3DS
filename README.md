*This project has been created as part of the 42 curriculum by <login1>[, <login2>].*



---

<h2 id="description">
  📖 Description
</h2>

> The objective of this project is to create a realistic 3D graphical representation of the inside of a maze from a first-person perspective. 

Using the mathematical principles of **Ray-Casting**, this engine calculates distances from the player to walls on a 2D grid and renders them vertically to simulate a 3D environment. It handles custom textures, floor and ceiling colors, and smooth window management. 

<h2 id="instructions">
  🚀 Instructions
</h2>

### Compilation

The project is equipped with a `Makefile`. To compile the program, run the following command at the root of the repository:

</h3>

| KEY           | Action        |
| ------------- |:-------------:|
| `ESC`         | exit game     |
| `Q`           | move left     |
| `D`           | move right    |
| `Z`           | move forward  |
| `S`           | move backward |
| `→`           | turn right    |
| `←`           | turn left     |

<h3>
Map
</h3>

| Character      | Description   |
| -------------  |:-------------:|
| `1`            | wall          |
| `0`            | floor         |
| `2`            | sprite #1     |
| `N`/`E`/`W`/`S`| player initial position + orientation|
| `NO`            | north texture file         |
| `SO`            | south texture file|
| `WE`            | west  texture file|
| `EA`            | east  texture file|
| `F`            | floor rgb color |
| `C`            | celling rgb color|
```shell
make

Execution

The game requires a valid scene description file (.cub) as an argument to run.
Shell

./cub3D maps/your_map.cub

Repository Architecture
Plaintext

.
├── 📁 inc/             # Header files (.h)
├── 📁 libft/           # Custom standard C library implementation
├── 📁 maps/            # Scene description files (.cub)
├── 📁 minilibx-linux/  # X-Window programming API in C
├── 📁 src/             # Source files (.c)
├── 📁 textures/        # XPM image files for walls and sprites
└── 📄 Makefile         # Compilation rules (all, clean, fclean, re)

Player Controls
Key	Action
W	Move forward
S	Move backward
A	Strafe left
D	Strafe right
←	Rotate camera left
→	Rotate camera right
ESC	Quit the game cleanly

Note: You can also click the red cross on the window's frame to exit the game.
Map Elements (.cub file)

The scene file must contain specific identifiers for textures and colors before the map grid.
Identifier	Description	Example
NO	North wall texture path	NO ./textures/north.xpm
SO	South wall texture path	SO ./textures/south.xpm
WE	West wall texture path	WE ./textures/west.xpm
EA	East wall texture path	EA ./textures/east.xpm
F	Floor color (R,G,B)	F 40,32,30
C	Ceiling color (R,G,B)	C 15,15,15

The map grid itself is built using the following characters:
Char	Definition
1	Solid wall
0	Walkable empty space
N, S, E, W	Player's spawn point and initial facing direction

    Lode's Computer Graphics Tutorial: An incredible and comprehensive guide covering the deep math and logic behind raycasting.

    Wolfenstein 3D: The original 1992 game to understand the expected behavior, historical context, and technical limitations of early raycasters.

Artificial Intelligence Usage

    Tasks: AI was utilized to debug memory leaks (specifically tracking down unreachable blocks related to XPM image allocations in the MinilibX) and to break down complex linear algebra formulas regarding matrix inversion for sprite translations.

    Review Process: All generated explanations were independently verified using standard mathematics documentation. Code suggestions for debugging were manually reviewed, adapted to fit the project's strict architectural norms, and thoroughly tested with Valgrind before implementation to ensure complete comprehension and ownership of the final source code.
```

    
    

| KEY           | Action        |
| ------------- |:-------------:|
| `ESC`         | exit game     |
| `Q`           | move left     |
| `D`           | move right    |
| `Z`           | move forward  |
| `S`           | move backward |
| `→`           | turn right    |
| `←`           | turn left     |

<h3>
Map
</h3>

| Character      | Description   |
| -------------  |:-------------:|
| `1`            | wall          |
| `0`            | floor         |
| `2`            | sprite #1     |
| `N`/`E`/`W`/`S`| player initial position + orientation|
| `NO`            | north texture file         |
| `SO`            | south texture file|
| `WE`            | west  texture file|
| `EA`            | east  texture file|
| `F`            | floor rgb color |
| `C`            | celling rgb color|
```shell