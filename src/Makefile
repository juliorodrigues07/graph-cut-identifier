all: graph_cut.o
	gcc graph_cut.o main.c -o main

graph_cut.o: utilities.h
	gcc -c graph_cut.c

clean:
	rm -rf *.o