#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "grid.h"
#include "Pathways.h"

// Mutex for thread safety
pthread_mutex_t lock;

// Player A's position
//Token in base when game starts
int currentPositionA = -1; 

// Dice roll function
int rollDice() {
    return (rand() % 6) + 1; // Random number 1-6
}

// Move token for Player A along the pathway
void moveToken(int *currentPosition, char tokenChar, int steps) {
    pthread_mutex_lock(&lock);
    initializeGrid();// re-intilization of grind when the token moves through stops 
    
    // Clear the current position
    int currentRow = pathway[*currentPosition][0];
    int currentCol = pathway[*currentPosition][1];
    grid[currentRow][currentCol] = '.'; // Reset to pathway

    // Calculate new position (circular movement along pathway)
    *currentPosition = (*currentPosition + steps) % pathwayLength;

    // Place token at the new position
    int newRow = pathway[*currentPosition][0];
    int newCol = pathway[*currentPosition][1];
    grid[newRow][newCol] = tokenChar;
    
    printf("Player %c moved to position (%d, %d)\n", tokenChar, newRow, newCol);

    pthread_mutex_unlock(&lock);
}

// Thread function for Player A's game loop
void* gameThread(void* arg) {
    char tokenChar = *(char*)arg; // Token character

    while (1) {
        printf("Press Enter to roll the dice for Player %c...", tokenChar);
        getchar(); // Wait for input

        int diceRoll = rollDice();
        printf("\nPlayer %c rolled a %d!\n", tokenChar, diceRoll);

        // If token is in base and
        // If dicerolls a 6
        //token will be placed at starting point 
        //of their respective pathway's starting point
        if (currentPositionA == -1) { //-1 means token is in base
            if (diceRoll == 6) {
                // Place the token at the starting position of the pathway
                currentPositionA = 0; // Starting index in pathway
                int startRow = pathway[currentPositionA][0];
                int startCol = pathway[currentPositionA][1];
                grid[startRow][startCol] = tokenChar; // Place token on grid
            } 
            else {
                printf("Player %c cannot move.\n", tokenChar);
            }
        } 
        else {
            // Move Token if already in pathway
            moveToken(&currentPositionA, tokenChar, diceRoll);
        }
        displayGrid();
    }
    return NULL;
}

int main() {
    pthread_t threadA;

    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);

    initializeGrid(); // Initialize grid

    // Place Player A's token in its respective base
    grid[1][1] = 'a';
    displayGrid(); // Show the grid initially

    // Start Player A's thread
    char tokenA = 'a';
    pthread_create(&threadA, NULL, gameThread, &tokenA);

    pthread_join(threadA, NULL); // Wait for thread to finish
    pthread_mutex_destroy(&lock); // Clean up mutex

    return 0;
}

