# Bloom Filter

by Fischer Jemison. Uses PMurHash by Austin Appleby.

## Building

Run `make` to build. Requires GCC and is only tested with GCC 7.

## Running

Run with `./main -d $dict_file -i $input_file -i $out_3 $out_5 where $dict file is a newline-separated list of bad passwords, $input_file is a newline separated list of passwords to test, and $out_3 and $out_5 are the output files for the 3 and 5 hash bloom filters, respectively.

Provided with the repository are `dictionary.txt` and `input.txt`, two known-good files you can use for testing.