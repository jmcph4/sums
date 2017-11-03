#ifndef SUMS_H_
#define SUMS_H_

#include <stdio.h>

#define ELEM_DELIM ' '
#define LINE_DELIM '\n'

int sumline(const char* line);
void sumfile(FILE* in, FILE* out);

#endif /* SUMS_H_ */

