#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "automaton.h"
#include "autostructure.h"

void get_string (char *holder, int max_length)
{
    char buffer[256];

    gets(buffer);

    while (strlen(buffer) > max_length)
    {
        printf("Sorry, input is too long. Please enter less than %i characters: ", max_length + 1);
        gets(buffer);
    }
    strcpy(holder, buffer);
}

void create_automaton_parameters (automaton *auto_ptr)
{
    printf("Enter the number of rows and columns: ");
    scanf("%d", &auto_ptr->requested_size);

    while ((*auto_ptr).requested_size < 5 || (*auto_ptr).requested_size > 50)
    {
        printf("Sorry, that input was invalid.\n");
        printf("\nEnter the number of rows and columns: ");
        scanf("%d", &auto_ptr->requested_size);
    }

    printf("\nEnter the initial probability of survival: ");
    scanf("%lf", &(auto_ptr)->initial_probability);

    while ((*auto_ptr).initial_probability < 0 || (*auto_ptr).initial_probability > 1)
    {
        printf("Sorry, that input was invalid.\n");
        printf("\nEnter the initial probability of survival: ");
        scanf("%lf", &(auto_ptr)->initial_probability);
    }

    printf("\nEnter the number of necessary members: ");
    scanf("%d", &(auto_ptr)->necessary_neighbors);

    while ((*auto_ptr).necessary_neighbors < 1 || (*auto_ptr).necessary_neighbors > 4)
    {
        printf("Sorry, that input was invalid.\n");
        printf("\nEnter the number of necessary members: ");
        scanf("%d", &(auto_ptr)->necessary_neighbors);
    }

    printf("\nHow frequent are the generations? ");
    scanf("%d", &(auto_ptr)->requested_mod);
    printf("\nEnter the max number of generations: ");
    scanf("%d", &(auto_ptr)->max_generations);
}

void create_initial_state (automaton *auto_ptr)
{
    int i = 0, j = 0;
    double x = 0.0;

    srand((unsigned) time(NULL));

    for (i = 0; i < (*auto_ptr).requested_size; i++)
    {
        for (j = 0; j < (*auto_ptr).requested_size; j++)
        {
            x = get_random_value();

            if (x <= (*auto_ptr).initial_probability)
            {
                (auto_ptr)->grid[i][j] = '*';
            }
            else
                {
                    (auto_ptr)->grid[i][j] = ' ';
                }
        }
    }
}

double get_random_value ()
{
    double a = 1.0, random_num = 0.0;

    random_num = ((double)rand() / (double)(RAND_MAX)) * a;

    return random_num;
}

void write_current_state (automaton a, FILE *out_file)
{
    int i = 0, j = 0;

    fprintf(out_file, "\n\t");

    for (i = 0; i < a.requested_size; i++)
    {
        fprintf(out_file, "____");
    }
    fprintf(out_file, "_");
    fprintf(out_file, "\n");

    for (i = 0; i < a.requested_size; i++)
    {
        fprintf(out_file, "\t");

        for (j = 0; j < a.requested_size; j++)
        {
            if (a.grid[i][j] == '*')
                {
                    fprintf(out_file, "| %c ", 42);
                }
                else
                    {
                        fprintf(out_file, "| %c ", 32);
                    }
        }
        fprintf(out_file, "|\n");
        fprintf(out_file, "\t");

        for (j = 0; j < a.requested_size; j++)
        {
            fprintf(out_file, "____");
        }
        fprintf(out_file, "_");
        fprintf(out_file, "\n");
    }
}

char new_cell_state(char up, char down, char left, char right, int n)
{
    int sum = 0;

    if (up == '*')
        sum += 1;

    if (down == '*')
        sum += 1;

    if (left == '*')
        sum += 1;

    if (right == '*')
        sum += 1;

    if (sum == n)
    {
        return '*';
    }
    else
        return ' ';
}

void create_new_generation (automaton *auto_ptr)
{
    int i = 0, j = 0;
    char new_gen[50][50];

    copy_cell_grid((*auto_ptr).grid, new_gen, (*auto_ptr).requested_size);

    for (i = 0; i < (*auto_ptr).requested_size; i++)
    {
        for (j = 0; j < (*auto_ptr).requested_size; j++)
        {
            if (i > 0 && i < ((*auto_ptr).requested_size - 1) && j > 0 && j < ((*auto_ptr).requested_size - 1))
            {
                (*auto_ptr).grid[i][j] = new_cell_state(new_gen[i + 1][j], new_gen[i - 1][j], new_gen[i][j - 1], new_gen[i][j + 1], (*auto_ptr).necessary_neighbors);
            }
            //CORNERS
            else
                if (i == 0 && j == 0) //Top Left//
                {
                    (*auto_ptr).grid[i][j] = new_cell_state(new_gen[(*auto_ptr).requested_size - 1][j], new_gen[i - 1][j], new_gen[i][(*auto_ptr).requested_size - 1], new_gen[i][j + 1], (*auto_ptr).necessary_neighbors);
                }
                else
                    if (i == 0 && j == ((*auto_ptr).requested_size - 1)) //Top Right//
                    {
                        (*auto_ptr).grid[i][j] = new_cell_state(new_gen[(*auto_ptr).requested_size - 1][j], new_gen[i - 1][j], new_gen[i][j - 1], new_gen[i][0], (*auto_ptr).necessary_neighbors);
                    }
                    else
                        if (i == ((*auto_ptr).requested_size - 1) && j == 0) //Bottom Left//
                        {
                            (*auto_ptr).grid[i][j] = new_cell_state(new_gen[0][j], new_gen[i - 1][j], new_gen[i][(*auto_ptr).requested_size - 1], new_gen[i][j + 1], (*auto_ptr).necessary_neighbors);
                        }
                        else
                            if (i == ((*auto_ptr).requested_size - 1) && j == ((*auto_ptr).requested_size - 1)) //Bottom Right//
                            {
                                (*auto_ptr).grid[i][j] = new_cell_state(new_gen[i + 1][j], new_gen[0][j], new_gen[i][j - 1], new_gen[i][0], (*auto_ptr).necessary_neighbors);
                            }
            //EDGES
                            else
                                if (i == 0 && j > 0 && j < ((*auto_ptr).requested_size - 1)) //Top Horizontal//
                                {
                                    (*auto_ptr).grid[i][j] = new_cell_state(new_gen[i + 1][j], new_gen[(*auto_ptr).requested_size - 1][j], new_gen[i][j - 1], new_gen[i][j + 1], (*auto_ptr).necessary_neighbors);
                                }
                                else
                                    if (j == 0 && i > 0 && i < ((*auto_ptr).requested_size - 1)) //Left Vertical//
                                    {
                                        (*auto_ptr).grid[i][j] = new_cell_state(new_gen[i + 1][j], new_gen[i - 1][j], new_gen[i][(*auto_ptr).requested_size - 1], new_gen[i][j + 1], (*auto_ptr).necessary_neighbors);
                                    }
                                    else
                                        if (i == ((*auto_ptr).requested_size - 1) && j > 0 && j < ((*auto_ptr).requested_size - 1)) //Bottom Horizontal//
                                        {
                                            (*auto_ptr).grid[i][j] = new_cell_state(new_gen[0][j], new_gen[i - 1][j], new_gen[i][j - 1], new_gen[i][j + 1], (*auto_ptr).necessary_neighbors);
                                        }
                                        else
                                            if (j == ((*auto_ptr).requested_size - 1) && i > 0 && i < ((*auto_ptr).requested_size - 1)) //Right Vertical//
                                            {
                                                (*auto_ptr).grid[i][j] = new_cell_state(new_gen[i + 1][j], new_gen[i - 1][j], new_gen[i][j - 1], new_gen[i][0], (*auto_ptr).necessary_neighbors);
                                            }
        }
    }
}

void copy_cell_grid (char old_gen[][50], char new_gen[][50], int size)
{
    int i = 0, j = 0;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            new_gen[i][j] = old_gen[i][j];
        }
    }
}
