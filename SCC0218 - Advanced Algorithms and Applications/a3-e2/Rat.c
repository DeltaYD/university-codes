#include <stdio.h>
#include <stdlib.h>
#include "Rat.h"

int cheese = 0;
int gN;
int **maze;
int **trail;

void squareMaze(int N){

    //  Allocate global matrix (I'm dumb, so this is why this thing exists)
    trail = (int**)malloc(sizeof(int*) * N);
    maze = (int**)malloc(sizeof(int*) * N);
    for(int count = 0; count < N; count++){
        trail[count] = (int*)calloc(N, sizeof(int));
        maze[count] = (int*)malloc(sizeof(int) * N);
    }

    //  Set global variable
    gN = N;
    
    //  Obtain labyrinth
    for(int count = 0; count < N; count++){
        for(int kount = 0; kount <N; kount++){
            scanf("%d", &maze[count][kount]);
        }
    }

    //  Call the algorithm
    recMaze(0, 0);

    //  Print results
    printf("%d", cheese);

    //  Free memory space
    for(int count = 0; count < N; count++){
        free(trail[count]);
        free(maze[count]);
    }
    free(trail);
    free(maze);

    return;
}

//  Main code
void recMaze(int x, int y){
    //  Occupy our current track
    trail[x][y] = 1;

    //  If we arrive at cheese, say that we did and consider it a path
    if(x == (gN - 1) && y == (gN - 1)){
        cheese++;
    } else{
        //  Up
        if(x - 1 >= 0 && maze[x - 1][y] == 0 && trail[x - 1][y] != 1){
            recMaze( x - 1, y);
        }
        //  Left
        if(y + 1 <= (gN - 1) && maze[x][y + 1] == 0 && trail[x][y + 1] != 1){
            recMaze(x, y + 1);
        }
        //  Down
        if(x + 1 <= (gN - 1) && maze[x + 1][y] == 0 && trail[x + 1][y] != 1){
            recMaze(x + 1, y);
        }
        //  Right
        if(y - 1 >= 0 && maze[x][y - 1] == 0 && trail[x][y - 1] != 1){
            recMaze(x, y - 1);
        }
    }

    //  This path is available again
    trail[x][y] = 0;

    //  Return to previous spot in the maze
    return;
}