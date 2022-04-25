#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Structure representing a square (node in a list) */
typedef struct Node
{
    int index;
    int is_ladder;
    int is_snake;
    struct Node *next;
} * Square;

/* Create the gameboard (list of squares) */
Square create_gameboard();
/* Add a square to the gameboard */
void append_square(Square *head, int index);
/* Randomise the size of gameboard */
int gameboard_size(void);
/* Print the gameboard */
void print_gameboard(Square node);
/* Simulate the throw of a dice */
int roll_dice(void);
/* Start the game */
void start();
