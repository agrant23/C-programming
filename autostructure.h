#ifndef AUTOSTRUCTURE_H_INCLUDED
#define AUTOSTRUCTURE_H_INCLUDED

typedef struct {
      char grid [50][50];
      int requested_size;
      double initial_probability;
      int necessary_neighbors;
      int current_generation;
      int max_generations;
      int requested_mod;
} automaton;

#endif // AUTOSTRUCTURE_H_INCLUDED
