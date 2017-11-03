#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "sums.h"

int main(int argc, char** argv)
{
    if(argc == 1) /* usage */
    {
        fprintf(stderr, "usage: %s file1 [...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int num_files = argc - 1;

    for(unsigned int i=0;i<num_files;i++)
    {
        pid_t pid = fork();

        if(pid == 0) /* child */
        {
            FILE* in = fopen(argv[i+1], "r");

            char* output_path = calloc(strlen(argv[i+1]) + 5, sizeof(char));
            sprintf(output_path, "%s.out", argv[i+1]);
            FILE* out = fopen(output_path, "w");
            free(output_path);

            sumfile(in, out);

            fclose(in);
            fclose(out);

            return EXIT_SUCCESS;
        }
        else if(pid == -1) /* handle error */
        {
            perror("fork");
            return EXIT_FAILURE;
        }
    }

    /* reap child processes */
    for(unsigned int i=0;i<num_files;i++)
    {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

