#include <stdio.h>
#include <stdlib.h>
#include "automaton.h"
#include "autostructure.h"

void maintain_file (FILE **, int);

int main()
{
    FILE *out_file = NULL;
    automaton a;
    int i = 0;

    maintain_file(&out_file, 1);

    create_automaton_parameters(&a);
    create_initial_state(&a);

    fprintf(out_file, "\n\t");
    fprintf(out_file, "Initial State");
    write_current_state (a, out_file);
    fprintf(out_file, "\n\n");

    for (i = 1; i < a.max_generations; i++)
    {
        create_new_generation(&a);
        if(a.requested_mod != 1){
            if (i % a.requested_mod == 0){
                fprintf(out_file, "\n\t");
                fprintf(out_file, "Generation %d", i);
                write_current_state(a, out_file);
                fprintf(out_file, "\n\n");
            }
        }
        else{
            if (i % a.requested_mod == 0){
                fprintf(out_file, "\n\t");
                fprintf(out_file, "Generation %d", i + 1);
                write_current_state(a, out_file);
                fprintf(out_file, "\n\n");
            }
        }
    }

    if ((i - 1) % a.requested_mod != 0){
        fprintf(out_file, "\n\t");
        fprintf(out_file, "Generation %d", (i));
        write_current_state(a, out_file);
    }

    maintain_file(&out_file, 0);

    return 0;
}

void maintain_file (FILE **path, int argument)
{
    char pathname[256];

    if(argument == 1)
    {
        printf("Enter the path and file name: ");
        get_string(pathname, 255);

        while((*path = fopen(pathname, "w")) == NULL)
        {
            printf("\nTry another file path: ");
            get_string(pathname, 255);
        }
    }
    else
        fclose(*path);
}
