#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

// Grid array
char grid[15][15];

// Explicitly define the pathway with (row, col) coordinates
int pathway[255][2] = {
    //red path starting
    {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5},
    //yellow path upward
    {5, 6}, {4, 6}, {3, 6}, {2, 6}, 
    //middle area of yellow
    {1, 6}, {0, 7}, {0, 8},
    //yellow down
    {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8},
    //green home forward
    {6, 10}, {6, 11}, {6, 12}, {6, 13}, 
    //middle area of green
    {6, 14}, {7, 14}, {8, 14},
    //green down forward
    {8, 13}, {8, 12}, {8, 11}, {8, 10}, {8, 9},
    //blue downward
    {10, 8}, {11, 8}, {12, 8}, {13, 8}, 
    //middle area blue
    {14, 8}, {14, 7}, {14, 6},
    //blue upward
    {13, 6} , {12, 6}, {11, 6}, {10, 6}, {9, 6},
    //red down 
    {8, 5}, {8, 4}, {8, 3}, {8, 2}, {8, 1},
    //middle of red
    {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, 
    //red home
    {7, 1}
};

int pathwayLength = sizeof(pathway) / sizeof(pathway[0]); // Total number of steps
                                                 
void initializeGrid() {
    // Initialize all cells as white
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            grid[i][j] = '.';
        }
    }

    // Mark home yards
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) grid[i][j] = 'A'; // Red
        for (int j = 9; j < 15; j++) grid[i][j] = 'B'; // Yellow
    }

    for (int i = 9; i < 15; i++) {
        for (int j = 0; j < 6; j++) grid[i][j] = 'C'; // Blue
        for (int j = 9; j < 15; j++) grid[i][j] = 'D'; // Green
    }

    // Pathways
    for (int i = 1; i < 6; i++) grid[i][7] = 'B'; 
    grid[1][8] = 'B';
    
    for (int j = 13; j > 8; j--) grid[7][j] = 'D'; 
    grid[8][13] = 'D';
    
    for (int i = 13; i > 8; i--) grid[i][7] = 'C'; 
    grid[13][6] = 'C';
    
    for (int j = 1; j < 6; j++) grid[7][j] = 'A'; 
    grid[6][1] = 'A';

    //stop of yellow home
    grid[2][6] = 'S'; 
    //stop of green home
    grid[6][12] = 'S'; 
    //stop of blue home
    grid[12][8] = 'S'; 
    //stop of red home
    grid[8][2] = 'S';

    for (int i = 6; i <= 8; i++) {
        for (int j = 6; j <= 8; j++) {
            grid[i][j] = 'X'; // Center block
        }
    }

}

void displayGrid() {
    //system("clear"); // Clear the console for a fresh grid display

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
                printf(GRAY "   " RESET); // Safe zones
            } else if (grid[i][j] == 'X') {
                printf(BLACK "   " RESET); // Center block
            } else if (grid[i][j] == 'a') {
                printf(LIGHT_RED "   " RESET); // tokens of Player A
            } else {
                printf(WHITE " * " RESET); // Pathway cells
            }
        }
        printf("\n");
    }
    printf("\n");
}



