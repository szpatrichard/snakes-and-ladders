/*  Patrik Richard Szilagyi R00198735
    MTU SOFT7019 - C Programming Module
    Assignment 2 - "Snakes and Ladders" */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Square *create_square(int);
struct Gameboard *create_gameboard();
void generate_gameboard(struct Gameboard *);
void add_edge(struct Gameboard *, int, int);
void print_gameboard(struct Gameboard *);
void gameboard_size(void);
void roll_dice(void);

int dice, size;

// Structure representing a square
struct Square
{
    int index;
    struct Square *next;
};

// Structure representing a gameboard
struct Gameboard
{
    int size;
    struct Square **list;
};

// Create a square
struct Square *create_square(int i)
{
    struct Square *square = malloc(sizeof(struct Square));
    square->index = i;
    square->next = NULL;
    return square;
}

// Create a gameboard
struct Gameboard *create_gameboard()
{
    struct Gameboard *gameboard = malloc(sizeof(struct Gameboard));
    gameboard_size();
    gameboard->size = size;
    gameboard->list = malloc(gameboard->size * sizeof(struct Square *));
    for (int i = 0; i < gameboard->size; i++)
        gameboard->list[i] = NULL;
    return gameboard;
}

// Fill gameboard with squares
void generate_gameboard(struct Gameboard *gameboard)
{
    for (int i = 0; i <= size; i++)
    {
        add_edge(gameboard, i, i + 1);
    }
}

// Add an edge to gameboard
void add_edge(struct Gameboard *gameboard, int source, int destination)
{
    // Add edge from source to destination
    struct Square *new_square = create_square(destination);
    new_square->next = gameboard->list[source];
    // source -> new_square in gameboard
    gameboard->list[source] = new_square;
}

// Print the gameboard
void print_gameboard(struct Gameboard *gameboard)
{
    for (int i = 0; i < gameboard->size; i++)
    {
        struct Square *temp = gameboard->list[i];
        printf("%d: ", i);
        while (temp)
        {
            printf("%d ", temp->index);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Randomise the size of gameboard
void gameboard_size()
{
    const int min = 32, max = 64;
    size = (rand() % (max - min + 1)) + min;
    printf("Gameboard size: %d\n", size);
}

// Simulate the throw of a dice
void roll_dice()
{
    const int sides = 6;
    dice = (rand() % ((sides - 1) + 1)) + 1;
    printf("Dice: %d\n", dice);
}

void main()
{
    srandom(time(NULL));
    struct Gameboard *gb = create_gameboard();
    generate_gameboard(gb);
    add_edge(gb, 10, 15);
    print_gameboard(gb);
    roll_dice();
}
