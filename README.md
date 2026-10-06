# Multiplayer Generic Snake Game

A console-based multiplayer Snake Game developed in **C++** as part of the AI and CS Certification Program at **ITU and Seed Programming**.

The game supports up to **five players**, with each player controlling an independent snake using assigned keyboard controls.

## Features

* Supports 1–5 players
* Real-time keyboard controls
* Multiple snakes in the same game
* Food generation at random positions
* Snake growth after eating food
* Score tracking
* Collision detection between snakes
* Screen wrapping when a snake reaches the edge
* Colored console output
* Windows console-based gameplay

## Controls

| Player   | Left | Right | Up | Down |
| -------- | ---- | ----- | -- | ---- |
| Player 1 | A    | D     | W  | S    |
| Player 2 | V    | N     | G  | B    |
| Player 3 | J    | L     | I  | K    |

## Game Rules

1. Select the number of players when the game starts.
2. Each player controls a snake using their assigned keys.
3. Snakes move continuously around the game area.
4. Eating food increases the player's score by 10 points.
5. Eating food also increases the snake's length.
6. The game ends when snakes collide with each other.
7. The final score of each player is displayed when the game ends.

## Technical Concepts

This project demonstrates practical use of:

* C++ structures
* Enumerations
* Vectors
* Functions
* Pass-by-reference
* Dynamic data structures
* Keyboard input handling
* Collision detection
* Random number generation
* Console cursor positioning
* Console colors
* Game loops

## Project Structure

```text
Multiplayer-Snake-Game/
│
├── main.cpp
└── README.md
```

## Requirements

* Windows operating system
* C++ compiler
* Console/terminal

The project uses Windows-specific libraries such as:

```cpp
#include <windows.h>
#include <conio.h>
```

Therefore, it is intended to run in a Windows console environment.

## How to Run

Compile `main.cpp` using a C++ compiler that supports the required Windows libraries.

Then run the generated executable from the Windows console.

## Learning Outcomes

This project helped develop practical understanding of:

* C++ programming
* Data structures using vectors
* Game-state management
* Input handling
* Collision detection
* Modular function design
* Real-time console applications

## Author

**Abdul Haseeb**

AI and CS Certification Program
ITU and Seed Programming

**Date:** 26 August 2026
