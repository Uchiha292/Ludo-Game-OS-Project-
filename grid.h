#ifndef GRID_H
#define GRID_H

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define BLUE    "\033[44m"
#define YELLOW "\033[48;2;255;255;0m"
#define RED     "\033[41m"
#define GREEN   "\033[42m"
#define WHITE   "\033[47m"
#define GRAY    "\033[100m"
#define BLACK   "\033[40m"
#define LIGHT_RED "\033[48;2;255;102;102m"
#define LIGHT_YELLOW  "\033[43m"
#define DARK_BLUE "\033[48;2;0;0;139m"
#define DARK_GREEN "\033[48;2;0;100;0m"

// Shared grid array
extern char grid[15][15];

// Function prototypes
void initializeGrid();
void displayGrid();

#endif

