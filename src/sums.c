#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sums.h"

int sumline(const char* line)
{
    if(line == NULL) /* null guard */
    {
        return 0;
    }

    if(strlen(line) == 0) /* trivial case */
    {
        return 0;
    }

    int sum = 0;            /* running total */
    unsigned int pos = 0;   /* current position in line */
    char* elem = NULL;      /* pointer to temp string */

    for(unsigned int i=0;i<strlen(line);i++)
    {
        if((line[i] == ELEM_DELIM || line[i] == LINE_DELIM) && pos > 0)
        {
            elem = calloc(pos + 2, sizeof(char));   /* allocate element str */
            strncpy(elem, &line[i-pos], pos + 2);   /* copy element into str */
            sum += atoi(elem);                      /* add to sum */
            free(elem);                             /* free element string */
            pos = 0;                                /* reset position */
        }

        pos++; /* increment position */
    }

    return sum;
}

void sumfile(FILE* in, FILE* out)
{
    if(in == NULL || out == NULL)
    {
        return;
    }

    long in_size = 0; /* size of input file */

    /* determine size of input file */
    fseek(in, 0, SEEK_END);
    in_size = ftell(in);
    rewind(in);

    char* in_data = calloc(in_size, sizeof(char)); /* file data */
    int bytes_read = fread(in_data, sizeof(char), in_size, in); /* read in */
    unsigned int pos = 0;   /* position in the file */
    char* line = NULL;      /* pointer for storing line */

    for(int i=0;i<bytes_read;i++)
    {
        if(in_data[i] == LINE_DELIM && pos > 0)
        {
            line = calloc(pos + 2, sizeof(char));       /* allocate space */
            strncpy(line, &in_data[i-pos], pos + 1);    /* copy into string */
            fprintf(out, "%d\n", sumline(line));        /* write out */
            free(line);                                 /* free line string */
            pos = 0;                                    /* reset position */
        }

        pos++; /* increment position */
    }

    free(in_data);
}

