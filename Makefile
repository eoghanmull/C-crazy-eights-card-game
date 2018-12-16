# Makefile for cardGame program
# Used to compile, link and run program
# Also used for debug and memory leak checks 
# uses both a libaray and main module

# Authors:
#	Eoghan Mulcahy
#	Ciarán O' Mara
# Last change of date: 22/12/2016

# Variables comp, exec, db and mem
# Store rules for a given task
comp = cardGame lib.o 
exec = exe
db = d_b
mem = mem_Check
game = cardGame
# runs the compiled executable
run:$(comp) $(exec)

#debugs the compiled executable
debug:$(comp) $(db)

#runs valgrind to check memory leaks etc
memCheck:$(comp) $(mem)

#compiles the file
compile:$(comp)

#links the library and the main file
cardGame: main.c lib.o
	gcc -Wall -std=c11 -ggdb -o cardGame main.c lib.o 

#compiles the library file
lib.o: lib.c
	gcc -Wall -std=c11 -ggdb -c lib.c

#the debug rule for steping through the code looking for errors
d_b: 
	./cardGame 1

#executes the program
exe:
	./cardGame 0

#rule for running the valgrind tool with some flags 
mem_Check: cardGame
	valgrind --tool=memcheck --leak-check=full ./cardGame 0

#clean rule for removing o files and executables
clean: 
	rm $(game) *.o *~

#recipes target dependancies
