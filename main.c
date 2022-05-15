/*  Patrik Richard Szilagyi R00198735
    Snakes and Ladders
*/

#include "game.h"

int player_pos, size, total_ladders, total_snakes;

Square initialise_gameboard()
{
    /* Create the head of the gameboard */
    Square head = NULL;
    /* Set size of the gameboard */
    // size = 32;
    size = gameboard_size();
    /* Add the squares to the gameboard */
    for (int i = 1; i <= size; i++)
        append_square(&head, i);
    add_ladders_and_snakes(&head);
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
    new_node->has_ladder = 0;
    new_node->has_snake = 0;
    new_node->is_final = 0;
    new_node->skip_to = NULL;
    if (new_node->index == size)
        new_node->is_final = 1;
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

void add_ladders_and_snakes(Square *head)
{
    const int MIN_LENGTH = 1, MAX_LENGTH = 10;

    /* Ladders */
    for (int i = 0; i < total_ladders; i++)
    {
        /* Length of ladder */
        int length = (random() % (MAX_LENGTH - MIN_LENGTH + 1)) + MIN_LENGTH;

        /* Position of ladder */
        const int MIN_POS = 2, MAX_POS = size - length;
        int pos = (random() % (MAX_POS - MIN_POS + 1)) + MIN_POS;

        /* Traverse to the nodes at the position */
        Square source = traverse(*head, pos);

        /* Ladder located at node */
        while (source->has_ladder)
        {
            pos = (random() % (MAX_POS - MIN_POS + 1)) + MIN_POS;
            source = traverse(*head, pos);
        }

        Square destination = traverse(source, pos + length);

        /* Add the ladder */
        if (!source->has_ladder)
        {
            source->skip_to = destination;
            source->has_ladder = 1;
            destination->has_ladder = 1;
        }
    }

    /* Snakes */
    for (int i = 0; i < total_snakes; i++)
    {
        /* Length of snake */
        int length = (random() % (MAX_LENGTH - MIN_LENGTH + 1)) + MIN_LENGTH;

        /* Position of snake */
        const int MIN_POS = length + 1, MAX_POS = size - 1;
        // printf("%d %d %d %d\n", length, MIN_POS, MAX_POS, size);
        int pos = (random() % (MAX_POS - MIN_POS + 1)) + MIN_POS;

        /* Traverse to the nodes at the position */
        Square source = traverse(*head, pos);

        /* Snake or ladder located at node */
        while (source->has_snake || source->has_ladder)
        {
            pos = (random() % (MAX_POS - MIN_POS + 1)) + MIN_POS;
            source = traverse(*head, pos);
        }

        Square destination = traverse(*head, pos - length);

        /* Add the snake */
        if (!source->has_snake || !source->has_ladder)
        {
            source->skip_to = destination;
            source->has_snake = 1;
            destination->has_snake = 1;
        }
    }
}

Square traverse(Square node, int index)
{
    while (node->index != index)
        node = node->next;
    return node;
}

void print_gameboard(Square node)
{
    printf("Gameboard size: %d\tLadders: %d\tSnakes: %d\n", size, total_ladders, total_snakes);
    /* Loop until the value of node is empty */
    while (node != NULL)
    {
        for (int i = 1; i <= size; i++)
        {
            printf("[%d", node->index);
            if (node->skip_to)
                printf("-%d]\t", node->skip_to->index);
            else
                printf("]\t");
            /* Make next node the current node */
            node = node->next;
            if (i % 6 == 0)
                printf("\n");
        }
    }
    printf("\n\n");
}

void print_report()
{
    printf("\nGame Report\n");
    FILE *f = fopen("report.txt", "r");

    if (f == NULL)
    {
        printf("Could not open file. :(\n");
        exit(-1);
    }

    int length = 64;
    char str[length];
    int move = 1;

    while (fgets(str, length, f))
    {
        char *token = strtok(str, " ");

        printf("Move %d: ", move);
        while (token != NULL)
        {
            printf("%s ", token);
            token = strtok(NULL, " ");
        }
        move++;
    }

    fclose(f);
}

void save_move(int source_square, int destination_square, int ladder, int snake)
{
    FILE *f = fopen("report.txt", "a");
    fprintf(f, "%d %d %d %d\n", source_square, destination_square, ladder, snake);
    fclose(f);
}

int gameboard_size()
{
    const int MIN = 32, MAX = 64;
    return (random() % (MAX - MIN + 1)) + MIN;
}

int roll_dice()
{
    const int SIDES = 6;
    return (random() % ((SIDES - 1) + 1)) + 1;
}

void start()
{
    FILE *f = fopen("report.txt", "w+");
    int player_pos = 0;
    Square sq = initialise_gameboard();
    print_gameboard(sq);

    while (1)
    {
        int dice = roll_dice();
        int previous_pos = player_pos;
        player_pos += dice;

        /* Player is at the end of gameboard */
        if (player_pos >= size)
        {
            printf("You won!\n");
            print_report();
            break;
        }

        /* Move player to square */
        Square pos = traverse(sq, player_pos);

        /* Save the move */
        save_move(previous_pos, player_pos, 0, 0);

        printf("Rolled a %d and moved to %d.\n", dice, pos->index);

        /* As long as the square contains a snake or a ladder then skip to the other end */
        while (pos->skip_to)
        {
            /* The new position */
            player_pos = pos->skip_to->index;
            printf("Skipped to %d.\n", player_pos);

            /* Save move after moving through a ladder */
            if (player_pos > pos->index)
            {
                save_move(pos->index, player_pos, 1, 0);
            }

            /* Save move after moving through a snake */
            if (player_pos < pos->index)
            {
                save_move(pos->index, player_pos, 0, 1);
            }

            /* Move player to square */
            pos = traverse(sq, player_pos);
        }
    }

    fclose(f);
}

void main(int argc, char *argv[])
{
    srandom(time(NULL));
    if (argc == 3)
    {
        total_ladders = atoi(argv[1]);
        total_snakes = atoi(argv[2]);
        /* Total amount of ladders and snakes that can be placed on the gameboard */
        int limit = 15;

        if (total_ladders < 0 || total_ladders > limit || total_snakes < 0 || total_ladders > limit)
        {
            printf("Only positive values up to %d are allowed!\n", limit);
            return;
        }
        start();
    }
    else
    {
        printf("Number of ladders and snakes not correctly provided!\n");
        return;
    }
}
