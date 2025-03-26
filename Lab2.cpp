#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const vector<vector<vector<int>>> SHAPES = {
    // I shape
    {
        {0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0},
        {0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0}
    },
    // O shape
    {
        {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0}
    },
    // T shape
    {
        {0,0,0,0, 1,1,1,0, 0,1,0,0, 0,0,0,0},
        {0,1,0,0, 1,1,0,0, 0,1,0,0, 0,0,0,0},
        {0,1,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,0},
        {0,1,0,0, 0,1,1,0, 0,1,0,0, 0,0,0,0}
    },
    // L shape
    {
        {0,0,0,0, 1,1,1,0, 1,0,0,0, 0,0,0,0},
        {1,1,0,0, 0,1,0,0, 0,1,0,0, 0,0,0,0},
        {0,0,1,0, 1,1,1,0, 0,0,0,0, 0,0,0,0},
        {0,1,0,0, 0,1,0,0, 0,1,1,0, 0,0,0,0}
    },
    // J shape
    {
        {1,0,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,0},
        {0,1,1,0, 0,1,0,0, 0,1,0,0, 0,0,0,0},
        {0,0,0,0, 1,1,1,0, 0,0,1,0, 0,0,0,0},
        {0,1,0,0, 0,1,0,0, 1,1,0,0, 0,0,0,0}
    },
    // S shape
    {
        {0,0,0,0, 0,1,1,0, 1,1,0,0, 0,0,0,0},
        {1,0,0,0, 1,1,0,0, 0,1,0,0, 0,0,0,0}
    },
    // Z shape
    {
        {0,0,0,0, 1,1,0,0, 0,1,1,0, 0,0,0,0},
        {0,1,0,0, 1,1,0,0, 1,0,0,0, 0,0,0,0}
    }
};
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; // Set the cursor visibility to false
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

class Tetromino {
public:
    int x, y, type, rotation;
    vector<vector<int>> shape;

    Tetromino(int type) : type(type), rotation(0), x(3), y(0) {
        updateShape();
    }

    void updateShape() {
        int rot = rotation % SHAPES[type].size();
        shape.clear();
        for (int i = 0; i < 4; ++i) {
            vector<int> row;
            for (int j = 0; j < 4; ++j) {
                row.push_back(SHAPES[type][rot][i * 4 + j]);
            }
            shape.push_back(row);
        }
    }

    void rotate() {
        rotation++;
        updateShape();
    }
};

class GameBoard {
    int width, height;
public:
    vector<vector<int>> grid;

    GameBoard(int w, int h) : width(w), height(h), grid(h, vector<int>(w, 0)) {}

    bool checkCollision(const Tetromino& t) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (t.shape[i][j]) {
                    int nx = t.x + j, ny = t.y + i;
                    if (nx < 0 || nx >= width || ny >= height) return true;
                    if (ny >= 0 && grid[ny][nx]) return true;
                }
            }
        }
        return false;
    }

    void merge(const Tetromino& t) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (t.shape[i][j]) {
                    int x = t.x + j, y = t.y + i;
                    if (y >= 0) grid[y][x] = 1;
                }
            }
        }
    }

    int clearLines() {
        int lines = 0;
        for (int y = height - 1; y >= 0; --y) {
            bool full = true;
            for (int x : grid[y]) if (!x) full = false;
            if (full) {
                grid.erase(grid.begin() + y);
                grid.insert(grid.begin(), vector<int>(width, 0));
                lines++;
                y++;
            }
        }
        return lines;
    }
};

class Game {
    GameBoard board;
    Tetromino* current;
    int score, level, lines;
    bool gameOver;
    DWORD lastDrop;

    // Store the previous frame for comparison
    vector<vector<int>> prevGrid;

public:
    Game() : board(10, 20), score(0), level(1), lines(0), gameOver(false) {
        spawnNew();
        lastDrop = GetTickCount();
        prevGrid = board.grid; // Initialize previous frame
    }

    void spawnNew() {
        current = new Tetromino(rand() % SHAPES.size());
        if (board.checkCollision(*current)) gameOver = true;
    }

    void handleInput() {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) {
                ch = _getch();
                Tetromino temp = *current;
                switch (ch) {
                    case 75: temp.x--; break;
                    case 77: temp.x++; break;
                    case 72: temp.rotate(); break;
                    case 80: temp.y++; break;
                }
                if (!board.checkCollision(temp)) *current = temp;
            }
            else if (ch == ' ') {
                while (!board.checkCollision(*current)) current->y++;
                current->y--;
                merge();
            }
            else if (ch == 27) gameOver = true;
        }
    }

    void merge() {
        board.merge(*current);
        int cleared = board.clearLines();
        score += cleared * 100;
        lines += cleared;
        if (lines >= level * 5) level++;
        spawnNew();
    }

    void update() {
        DWORD now = GetTickCount();
        if (now - lastDrop > 1000 / level) {
            current->y++;
            if (board.checkCollision(*current)) {
                current->y--;
                merge();
            }
            lastDrop = now;
        }
    }

    void draw() {
        // Move cursor to top-left corner instead of clearing the screen
        HideCursor();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

        // Draw the game board
        cout << "Score: " << score << " Level: " << level << endl;
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 10; ++x) {
                bool part = false;
                for (int i = 0; i < 4; ++i)
                    for (int j = 0; j < 4; ++j)
                        if (current->shape[i][j] && current->x + j == x && current->y + i == y)
                            part = true;
                cout << (part || board.grid[y][x] ? '#' : '.');
            }
            cout << endl;
        }
    }

    void run() {
        while (!gameOver) {
            handleInput();
            update();
            draw();
            Sleep(50); // Control frame rate
        }
        cout << "Game Over! Score: " << score << endl;
    }
};

int main() {
    srand(time(0));
    
    Game().run();
    return 0;
}