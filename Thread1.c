#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "grid.h"
#include "Pathways.h"

// Mutex for thread safety
pthread_mutex_t lock;

int currentPositionA = 0; // Player A's position

// Dice roll function
int rollDice() {
    return (rand() % 6) + 1; // Random number 1-6
}

// Move token along the pathway
void moveToken(int *currentPosition, char tokenChar, int steps) {
    pthread_mutex_lock(&lock);

    // Clear current position
    int currentRow = pathway[*currentPosition][0];
    int currentCol = pathway[*currentPosition][1];
    grid[currentRow][currentCol] = '.'; // Reset to white

    // Calculate new position
    *currentPosition = (*currentPosition + steps) % pathwayLength;

    // Place token at the new position
    int newRow = pathway[*currentPosition][0];
    int newCol = pathway[*currentPosition][1];
    grid[newRow][newCol] = tokenChar;

    pthread_mutex_unlock(&lock);
}

// Thread function for a player's game loop
void* gameThread(void* arg) {
    char tokenChar = *(char*)arg; // Token character
    
    while (1) {
        printf("Press Enter to roll the dice for Player %c...", tokenChar);
        getchar(); // Wait for input

        int diceRoll = rollDice();
        printf("\nPlayer %c rolled a %d!\n", tokenChar, diceRoll);

        moveToken(&currentPositionA, tokenChar, diceRoll);
        displayGrid();
    }
    return NULL;
}

int main() {
    pthread_t threadA;

    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);

    initializeGrid(); // Initialize grid

    // Place Player A's token
    grid[pathway[currentPositionA][0]][pathway[currentPositionA][1]] = 'A';
    displayGrid(); // Show the grid initially

    // Start Player A's thread
    char tokenA = 'A';
    pthread_create(&threadA, NULL, gameThread, &tokenA);

    pthread_join(threadA, NULL); // Wait for thread to finish
    pthread_mutex_destroy(&lock); // Clean up mutex

    return 0;
}

