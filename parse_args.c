#include "parse_args.h"

struct args * parse_args(int argc, char* argv[]) {
    int ctr = 1;
    struct args * a = malloc(sizeof(struct args));
    while (ctr < argc) {
        if (!strcmp(argv[ctr], "-d")) {
           strcpy(a->dictionary, argv[ctr + 1]); 
           ctr += 2;
        }
        if (!strcmp(argv[ctr], "-i")) {
            strcpy(a->input_file, argv[ctr + 1]);
            ctr += 2;
        }
        if (!strcmp(argv[ctr], "-o")) {
            strcpy(a->output_files[0], argv[ctr + 1]);
            strcpy(a->output_files[1], argv[ctr + 2]);
            ctr += 3;
        }
    }
    return a;
}