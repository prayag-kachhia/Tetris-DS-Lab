Tetris Game in C++

Description

This project is a simple Tetris game implemented in C++ using the Windows Console. It features tetromino shapes, game mechanics like rotation, movement, collision detection, line clearing, and a scoring system.

Features

Seven Tetromino Shapes (I, O, T, L, J, S, Z)

Keyboard Controls

Left Arrow (←): Move left

Right Arrow (→): Move right

Up Arrow (↑): Rotate

Down Arrow (↓): Soft drop

Space ( ): Hard drop

Escape (Esc): Quit the game

Automatic Piece Drop based on level speed

Line Clearing and Scoring System

Dynamic Leveling System (Level increases as lines are cleared)

Frame Optimization using Console Cursor Positioning

Installation

Clone the repository or download the source files.

Compile the code using a C++ compiler (such as MinGW g++ or MSVC).

g++ -o tetris tetris.cpp -std=c++11

Run the executable:

./tetris

Requirements

Windows OS (due to windows.h usage)

A C++ compiler supporting C++11 or later

Console with keyboard input

How It Works

The game initializes a 10x20 grid.

A random Tetromino spawns at the top.

Players move, rotate, or drop the Tetromino.

If the Tetromino lands, it merges with the board.

Full lines are cleared, and the score is updated.

The game continues until the pieces reach the top.





