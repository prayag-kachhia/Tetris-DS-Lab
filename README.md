# Tetris Game in C++

## Description

This project is a simple Tetris game implemented in C++ using the Windows Console. It features tetromino shapes, game mechanics like rotation, movement, collision detection, line clearing, and a scoring system.

## Features

- **Seven Tetromino Shapes** (I, O, T, L, J, S, Z)
- **Keyboard Controls**
  - Left Arrow (`←`): Move left
  - Right Arrow (`→`): Move right
  - Up Arrow (`↑`): Rotate
  - Down Arrow (`↓`): Soft drop
  - Space (` `): Hard drop
  - Escape (`Esc`): Quit the game
- **Automatic Piece Drop** based on level speed
- **Line Clearing** and Scoring System
- **Dynamic Leveling System** (Level increases as lines are cleared)
- **Frame Optimization** using Console Cursor Positioning

## Installation

1. **Clone the repository** or download the source files.
2. **Compile the code** using a C++ compiler (such as MinGW g++ or MSVC).
   ```sh
   g++ -o tetris tetris.cpp -std=c++11
   ```
3. **Run the executable**:
   ```sh
   ./tetris
   ```

## Requirements

- Windows OS (due to `windows.h` usage)
- A C++ compiler supporting C++11 or later
- Console with keyboard input

## How It Works

1. The game initializes a 10x20 grid.
2. A random Tetromino spawns at the top.
3. Players move, rotate, or drop the Tetromino.
4. If the Tetromino lands, it merges with the board.
5. Full lines are cleared, and the score is updated.
6. The game continues until the pieces reach the top.

##

##

