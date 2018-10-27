FLAGS=-Wall -std=c99
CC=gcc

all: bloom_filter.o PMurHash.o main.o hash.o parse_file.o parse_args.o
	$(CC) $(FLAGS) $^ -o main

PMurHash.o: lib/PMurHash.c
	$(CC) $(FLAGS) -c lib/PMurHash.c -o PMurHash.o

bloom_filter.o: bloom_filter.c
	$(CC) $(FLAGS) -c bloom_filter.c -o bloom_filter.o

main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o

hash.o: hash.c
	$(CC) $(FLAGS) -c hash.c -o hash.o

parse_file.o: parse_file.c
	$(CC) $(FLAGS) -c parse_file.c -o parse_file.o

parse_args.o: parse_args.c
	$(CC) $(FLAGS) -c parse_args.c -o parse_args.o