#include <stdlib.h>
#include <string.h>

struct args {
    char dictionary[256];
    char input_file[256];
    char output_files[2][256];
};

struct args * parse_args(int argc, char* argv[]);