word: main.o fn.o 
	gcc main.o fn.o -o word.out -lncurses
main.o: main.c
	gcc -c main.c
fn.o: fn.c
	gcc -c fn.c
clean:
	rm -f main.o fn.o