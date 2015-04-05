CFLAGS=-g 
CXXFLAGS=-g -std=c++11 -fsanitize=address

all: test


test: test.o matrix.o
	g++ $(CXXFLAGS) -o $@ $^

%.o: %.asm
	yasm -f elf64 -g dwarf2 -o $@ $^ 



