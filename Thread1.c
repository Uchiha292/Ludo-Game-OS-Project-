#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "grid.h"
#include "Pathways.h"

// Mutex for thread safety
pthread_mutex_t lock;

//int currentPositionA = 0; 
// Player A's position

struct PlayerArgs{
     int *currPosition;
     char tokenChar;
};

// Dice roll function
int rollDice() {
    return (rand() % 6) + 1; 
}

void movePlayerWithPathway(char tokenChar){
    if (tokenChar == 'a'){
       
       //for red tokens
       RedPathUH();
       YellowPathUp();
       YellowMiddle();
       YellowPathDown();
       GreenPathForward();
       GreenMiddle();
       GreenPathDown();
       BluePathDown();
       BlueMiddle();
       BluePathUp();
       RedPathDH();
       RedMiddle();
       RedInnerHome();
    
    }else if (tokenChar == 'b'){
      //for yellow tokens
      YellowPathDown();
      GreenPathForward();
      GreenMiddle();
      GreenPathDown();
      BluePathDown();
      BlueMiddle();
      BluePathUp();
      RedPathDH();
      RedMiddle();
      RedPathUH();
      YellowPathUp();
      //have to end in yellow home
      //need home inner path
      YellowMiddle();
      
    } else if (tokenChar == 'c'){
      //for blue tokens
      BluePathUp();
      RedPathDH();
      RedMiddle();
      RedPathUH();
      YellowPathUp();
      YellowMiddle();
      YellowPathDown();
      GreenPathForward();
      GreenMiddle();
      GreenPathDown();
      BluePathDown();
      //have to add blue inner path
      BlueMiddle();
    
    }else if (tokenChar == 'd'){
      //for green tokens
      GreenPathDown();
      BluePathDown();
      BlueMiddle();
      BluePathUp();
      RedPathDH();
      RedMiddle();
      RedPathUH();
      YellowPathUp();
      YellowMiddle();
      YellowPathDown();
      GreenPathForward();
      //have to add green inner path
      GreenMiddle();
      
    }
}

// Move token for Player A along the pathway
void moveToken(int *currPosition, char tokenChar, int steps) {
    pthread_mutex_lock(&lock);
    
    // Check if the token is at the starting position
    if (*currPosition == -1 && steps == 6) {
        // Set to starting position (assumed to be 0, modify if needed)
        if (tokenChar == 'a')
        {
            *currPosition = 0;
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        else if (tokenChar == 'b')
        {
            *currPosition = 12;
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        else if (tokenChar == 'c')
        {
            *currPosition = 37;
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        else if (tokenChar == 'd')
        {
            *currPosition = 24;
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        
    } else {
        if (*currPosition >= pathwayLength || *currPosition < -1) {
            printf("Error: Invalid position for Player %c.\n", tokenChar);
            pthread_mutex_unlock(&lock); // Ensure unlock before returning
            return;
        }
        
        // Clear the current position only if it's not in the home area
        int currentRow = pathway[*currPosition][0];
        int currentCol = pathway[*currPosition][1];

        // Clear the current position
        grid[currentRow][currentCol] = '.'; // Reset to pathway

        // Calculate new position (circular movement along pathway)
        *currPosition = (*currPosition + steps) % pathwayLength;
        
        // Place token at the new position
        int newRow = pathway[*currPosition][0];
        int newCol = pathway[*currPosition][1];
        grid[newRow][newCol] = tokenChar; // Place token at the new position
        
        printf("Player %c moved to position (%d, %d)\n", tokenChar, newRow, newCol);
    }
    
    pthread_mutex_unlock(&lock);
}


// Thread function for Player A's game loop
void* gameThread(void* arg) {
    struct PlayerArgs *playerArgs = (struct PlayerArgs*)arg;
    char tokenChar = playerArgs->tokenChar;
    int *currPosition = playerArgs->currPosition;
    
    movePlayerWithPathway(tokenChar);
   
    while (1) {
        printf("Press Enter to roll the dice for Player %c...", tokenChar);
        getchar(); // Wait for input

        int diceRoll = rollDice();
        printf("\nPlayer %c rolled a %d!\n", tokenChar, diceRoll);

        if (*currPosition==-1 && diceRoll!=6) {
            // If in home area, do not overwrite with '.'
            // Instead, keep the token representation
            printf("Player %c is in their home area and cannot move.\n", tokenChar);
        }
        else {
            // Move Player's token
            moveToken(currPosition, tokenChar, diceRoll);
        }

        // Display updated grid
        displayGrid(); 
        
         // Check for game end (example condition: reaching position 0 again)
        if (*currPosition == 0 && diceRoll > 0) {
            printf("Player %c has completed the pathway!\n", tokenChar);
            break; 
        }
            
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB, threadC, threadD;

    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);

    initializePathway();
    
    initializeGrid(); 

    // Place Player A's token at the starting position
    int currPositionA = -1;
    grid[1][1] = 'a';
    
    // Place Player B's token at the starting position
    //have to change starting position
    int currPositionB = 0-1;
    grid[1][11] = 'b';
    
    // Place Player C's token at the starting position (similar to others)
    int currPositionC = -1; // Starting position for C
    grid[12][1] = 'c';

    // Place Player D's token at the starting position (similar to others)
    int currPositionD = -1; // Starting position for D
    grid[11][11] = 'd';
    
    // Start Player A's thread
    //char tokenA = 'A';
    
    struct PlayerArgs tokenA = {&currPositionA, 'a'};
    struct PlayerArgs tokenB = {&currPositionB, 'b'};
    struct PlayerArgs tokenC = {&currPositionC, 'c'}; 
    struct PlayerArgs tokenD = {&currPositionD, 'd'};
     
    pthread_create(&threadA, NULL, gameThread, &tokenA);
    pthread_create(&threadB, NULL, gameThread, &tokenB);
    pthread_create(&threadC, NULL, gameThread, &tokenC); 
    pthread_create(&threadD, NULL, gameThread, &tokenD);

    // Wait for thread to finish
    pthread_join(threadA, NULL); 
    pthread_join(threadB, NULL); 
    pthread_join(threadC, NULL); 
    pthread_join(threadD, NULL);
    
    pthread_mutex_destroy(&lock); // Clean up mutex

    return 0;
}

