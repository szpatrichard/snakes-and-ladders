#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Structure representing a square (node in a list) */
typedef struct Node
{
    int index;
    int has_ladder;
    int has_snake;
    int is_final;
    struct Node *next;
    struct Node *skip_to;
} * Square;

/* Initialise the gameboard (list of squares) */
Square initialise_gameboard(void);
/* Randomise the size of gameboard */
int gameboard_size(void);
/* Add a square to the gameboard */
void append_square(Square *head, int index);
/* Add ladders and snakes to the gameboard */
void add_ladders_and_snakes(Square *node);
/* Traverse through the gameboard */
Square traverse(Square node, int index);
/* Print the gameboard */
void print_gameboard(Square node);
/* Print the game report */
void print_report();
/* Save the current move for game report */
void save_move(int source_square, int destination_square, int ladder, int snake);
/* Simulate the throw of a dice */
int roll_dice(void);
/* Start the game */
void start(void);
