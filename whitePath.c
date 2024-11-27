#include <stdio.h>
#include "Pathways.h"

int pathway[MaxPathwayLength][2];
int pathwayLength = sizeof(pathway) / sizeof(pathway[0]);
int pathIndex = 0;

// Initialize pathway to avoid uninitialized memory issues
void initializePathway() {
    for (int i = 0; i < MaxPathwayLength; i++) {
        pathway[i][0] = -1; // -1 indicates unused
        pathway[i][1] = -1;
    }
}

// Upper horizontal red path
void RedPathUH() {
    for (int j = 1; j <= 5; j++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = 6; // Row is constant
        pathway[pathIndex][1] = j; // Column varies
        pathIndex++;
    }
}

// Red path downward
void RedPathDH() {
    for (int j = 5; j >= 1; j--) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = 8; // Row is constant
        pathway[pathIndex][1] = j; // Column varies
        pathIndex++;
    }
}

// Red middle path
void RedMiddle() {
    int redMiddle[][2] = {{8, 0}, {7, 0}};
    for (int k = 0; k < 2; k++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = redMiddle[k][0];
        pathway[pathIndex][1] = redMiddle[k][1];
        pathIndex++;
    }
}

// Yellow path upward
void YellowPathUp() {
    for (int i = 5; i >= 2; i--) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = i; // Row varies
        pathway[pathIndex][1] = 6; // Column is constant
        pathIndex++;
    }
}

// Yellow middle area path
void YellowMiddle() {
    int yellowMiddle[][2] = {{1, 6}, {0, 7}, {0, 8}};
    for (int k = 0; k < 3; k++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = yellowMiddle[k][0];
        pathway[pathIndex][1] = yellowMiddle[k][1];
        pathIndex++;
    }
}

// Yellow path downward
void YellowPathDown() {
    for (int i = 1; i <= 5; i++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = i; // Row varies
        pathway[pathIndex][1] = 8; // Column is constant
        pathIndex++;
    }
}

// Green path forward
void GreenPathForward() {
    for (int j = 10; j <= 13; j++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = 6; // Row is constant
        pathway[pathIndex][1] = j; // Column varies
        pathIndex++;
    }
}

// Green middle area path
void GreenMiddle() {
    int greenMiddle[][2] = {{6, 14}, {7, 14}, {8, 14}};
    for (int k = 0; k < 3; k++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = greenMiddle[k][0];
        pathway[pathIndex][1] = greenMiddle[k][1];
        pathIndex++;
    }
}

// Green path downward
void GreenPathDown() {
    for (int j = 13; j >= 9; j--) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = 8; // Row is constant
        pathway[pathIndex][1] = j; // Column varies
        pathIndex++;
    }
}

// Blue path downward
void BluePathDown() {
    for (int i = 10; i <= 13; i++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = i; // Row varies
        pathway[pathIndex][1] = 8; // Column is constant
        pathIndex++;
    }
}

// Blue middle area path
void BlueMiddle() {
    int blueMiddle[][2] = {{14, 8}, {14, 7}, {14, 6}};
    for (int k = 0; k < 3; k++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = blueMiddle[k][0];
        pathway[pathIndex][1] = blueMiddle[k][1];
        pathIndex++;
    }
}

// Blue path upward
void BluePathUp() {
    for (int i = 13; i >= 9; i--) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = i; // Row varies
        pathway[pathIndex][1] = 6; // Column is constant
        pathIndex++;
    }
}

// Red inner home path
void RedInnerHome() {
    for (int j = 1; j <= 5; j++) {
        if (pathIndex >= MaxPathwayLength) {
            printf("Error: Exceeded maximum pathway size.\n");
            return;
        }
        pathway[pathIndex][0] = 7; // Row is constant
        pathway[pathIndex][1] = j; // Column varies
        pathIndex++;
    }
}

