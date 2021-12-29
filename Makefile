CC = gcc
AR = ar
FLAGS =-Wall - g 
OBJECTS = main.o nodes.o algo.o

all: graph
graph: $(OBJECTS) 
	$(CC) $(FLAGS) -o graph $(OJBJECTS)
main.o: main.c algo.h 
	$(CC) $(FLAGS) -c main.c
nodes.o: nodes.c nodes.h 
	$(CC) $(FLAGS) -c nodes.c
algo.o: algo.c algo.h nodes.h
	$(CC) $(FLAGS) -c algo.c
.PHONY: clean
clean:
	rm -f connections *.o 