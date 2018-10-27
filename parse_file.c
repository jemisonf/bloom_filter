#include "parse_file.h"

int get_line_count(const char* filename) {
    FILE* fp = fopen(filename, "r");
    char c = getc(fp);
    int num_lines = 0;
    while (c != EOF) {
        if (c == '\n' || c == EOF)
            num_lines++;
        c = getc(fp);
    }
    fclose(fp);
    return num_lines;
}
char* get_blank_string(int size) {
    char* str = malloc(size * sizeof(char));
    memset(str, 0, size * sizeof(char));
    return str;
}

void readline(FILE * fp, char* line) {
    memset(line, 0, 10000 * sizeof(char));
    char c = getc(fp);
    int counter = 0;
    while(c != '\n' && c != EOF) {
        line[counter] = c;
        c = getc(fp);
        counter++;
    }
}

struct lines* parse_lines(const char* filename) {
    assert(access(filename, F_OK) != -1);
    struct lines * self = malloc(sizeof(struct lines));
    printf("Getting num lines\n");
    self->num_lines = get_line_count(filename);
    printf("Getting lines\n");
    // self->lines = readlines(self->num_lines, filename);
    printf("got lines\n");
    return self;
}