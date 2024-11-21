#include <stdio.h>
#include <stdlib.h>

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define BLUE    "\033[44m"
#define YELLOW  "\033[43m"
#define RED     "\033[41m"
#define GREEN   "\033[42m"
#define WHITE   "\033[47m"
#define GRAY    "\033[100m"
#define BLACK   "\033[40m"

// Grid array
char grid[15][15];

void initializeGrid() {
    // Initialize all cells as white
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            grid[i][j] = '.'; 
        }
    }

    // Mark home yards
    for (int i = 0; i < 6; i++) {
        // A = Red
        for (int j = 0; j < 6; j++) grid[i][j] = 'A'; 
        // B = Yellow
        for (int j = 9; j < 15; j++) grid[i][j] = 'B'; 
    }
    
    for (int i = 9; i < 15; i++) {
        // C = Blue
        for (int j = 0; j < 6; j++) grid[i][j] = 'C'; 
        // D = Green
        for (int j = 9; j < 15; j++) grid[i][j] = 'D'; 
    }

    // Mark pathways
    // B = Yellow Pathway
    for (int i = 1; i < 6; i++) grid[i][7] = 'B'; 
    grid[1][8] = 'B';
    
    // D = Green Pathway
    for (int j = 13; j > 8; j--) grid[7][j] = 'D'; 
    grid[8][13] = 'D';
    
    // C = Blue Pathway
    for (int i = 13; i > 8; i--) grid[i][7] = 'C'; 
    grid[13][6] = 'C';
    
    // A = Red Pathway
    for (int j = 1; j < 6; j++) grid[7][j] = 'A'; 
    grid[6][1] = 'A';
    
    // Stops 
    grid[2][6] = 'S'; // Yellow Home stop
    grid[6][12] = 'S'; // Green Home stop
    grid[12][8] = 'S'; // Blue Home stop for C
    grid[8][2] = 'S'; // Safe zone for Player D

    //center
     for (int i = 6; i <= 8; i++) {       
        for (int j = 6; j <= 8; j++) {   
            grid[i][j] = 'X';            
        }
    }
}

void displayGrid() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (grid[i][j] == 'A') {
                printf(RED "   " RESET); // Player A's area
            } else if (grid[i][j] == 'B') {
                printf(YELLOW "   " RESET); // Player B's area
            } else if (grid[i][j] == 'C') {
                printf(BLUE "   " RESET); // Player C's area
            } else if (grid[i][j] == 'D') {
                printf(GREEN "   " RESET); // Player D's area
            } else if (grid[i][j] == 'S') {
                printf(GRAY "   " RESET); // Safe zones (gray)
            } else if (grid[i][j] == 'X') {
                printf(BLACK "   " RESET); // Black box (center)
            } else {
                printf(WHITE "   " RESET); // General pathway
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Initialize the grid
    initializeGrid();

    // Display the grid
    displayGrid();

    return 0;
}

