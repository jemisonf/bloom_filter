#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Functions used for parsing an input file into an array of c strings

struct lines {
    int num_lines;
    char** lines;
};


struct lines* parse_lines(const char* filename); 

void free_lines(struct lines *);

int get_line_count(const char* filename);

void readline(FILE * fp, char* line);