CC=clang
CFLAGS=-Isrc -fsanitize=address -fsanitize=undefined -Wall -Werror 
LDFLAGS= -fsanitize=address -fsanitize=undefined
source_files := $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c) $(wildcard src/*/*/*/*/*.c) $(wildcard src/*/*/*/*/*/*.c)
header_files := $(wildcard src/*.h) $(wildcardsrc/ */*.h) $(wildcard src/*/*/*.h) $(wildcard src/*/*/*/*.h) $(wildcard src/*/*/*/*/*.h) $(wildcard src/*/*/*/*/*/*.h)

object_files := $(source_files:.c=.o)

%.o: %.c
	$(CC) -c -g -o $@ $< $(CFLAGS)

build: $(object_files)
	@mkdir -p bin
	$(CC) -o bin/PenisLang $^ $(LDFLAGS)

run : build
	./bin/PenisLang example.dik

clean:
	rm -f bin/*
	rm -f $(object_files)