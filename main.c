/*  Patrik Richard Szilagyi R00198735
    MTU SOFT7019 C Programming Module
    Assignment 2 "Snakes and Ladders"
*/

#include "game.h"

int size;

Square create_gameboard()
{
    /* Create the head of the gameboard */
    Square head = NULL;
    /* Set the size of the gameboard */
    size = gameboard_size();
    /* Add the squares to the gameboard */
    for (int i = 1; i <= size; i++)
        append_square(&head, i);
    /* Return the head */
    return head;
}

void append_square(Square *head, int index)
{
    /* Allocate memory to node */
    Square new_node = (Square)malloc(sizeof(struct Node));
    Square last_node = *head;
    /* Set the attributes of the square */
    new_node->index = index;
    new_node->is_ladder = 0;
    new_node->is_snake = 0;
    /* Make next node empty */
    new_node->next = NULL;
    /* If head is empty then add new node as head */
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    /* Traverse until the last node */
    while (last_node->next != NULL)
        last_node = last_node->next;
    /* Append new node to list */
    last_node->next = new_node;
    return;
}

void print_gameboard(Square node)
{
    printf("Gameboard size: %d\nSTART->", size);
    /* Loop until the value of node is empty */
    while (node != NULL)
    {
        printf("%d->", node->index);
        /* Make next node the current node */
        node = node->next;
    }
    printf("END\n");
}

int gameboard_size()
{
    const int MIN = 32, MAX = 64;
    return (rand() % (MAX - MIN + 1)) + MIN;
}

int roll_dice()
{
    const int SIDES = 6;
    return (rand() % ((SIDES - 1) + 1)) + 1;
}

void start()
{
    Square start = create_gameboard();
    print_gameboard(start);
    int dice = roll_dice();
    printf("Dice: %d\n", dice);

    // int player_pos = 0;
    // printf("Position: %d\n", gb->list[1]->index);
    // while (player_pos >= 0)
    // {
    //     printf("Player position: %d\n", player_pos);
    //     if (player_pos >= size)
    //     {
    //         printf("You won!\n");
    //         break;
    //     }
    // Set player position
    //     player_pos = gb->list[player_pos + dice]->index;
    // }
}

void main()
{
    srandom(time(NULL));
    start();
}
