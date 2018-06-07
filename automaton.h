#include "autostructure.h"

#ifndef AUTOMATON_H_INCLUDED
#define AUTOMATON_H_INCLUDED

void get_string(char *, int);
void create_automaton_parameters (automaton *);
void create_initial_state (automaton *);
double get_random_value ();
void write_current_state (automaton, FILE *);
char new_cell_state(char, char, char, char, int);
void create_new_generation (automaton *);
void copy_cell_grid (char [][50], char [][50], int);

#endif // AUTOMATON_H_INCLUDED
