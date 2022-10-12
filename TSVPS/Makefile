CC = gcc
CFLAGS = -c -g
PREFIX = ./bin

labs: selection_sort.o bubble_sort.o merge_sort.o dejkstra.o floyd.o bellman_ford.o backpack.o kraskall.o
	$(CC) selection_sort.o -o $(PREFIX)/selection_sort
	$(CC) bubble_sort.o -o $(PREFIX)/bubble_sort
	$(CC) merge_sort.o -o $(PREFIX)/merge_sort
	$(CC) dejkstra.o -o $(PREFIX)/dejkstra
	$(CC) floyd.o -o $(PREFIX)/floyd
	$(CC) bellman_ford.o -o $(PREFIX)/bellman_ford
	$(CC) backpack.o -o $(PREFIX)/backpack
	$(CC) kraskall.o -o $(PREFIX)/kraskall
	rm -f *.o
selection_sort.o: selection_sort.c
	$(CC) $(CFLAGS) selection_sort.c
bubble_sort.o: bubble_sort.c
	$(CC) $(CFLAGS) bubble_sort.c
merge_sort.o: merge_sort.c
	$(CC) $(CFLAGS) merge_sort.c
dejkstra.o: dejkstra.c
	$(CC) $(CFLAGS) dejkstra.c
floyd.o: floyd.c
	$(CC) $(CFLAGS) floyd.c
bellman_ford.o: bellman_ford.c
	$(CC) $(CFLAGS) bellman_ford.c
backpack.o: backpack.c
	$(CC) $(CFLAGS) backpack.c
kraskall.o: kraskall.c
	$(CC) $(CFLAGS) kraskall.c
clear:
	rm -f *.o $(PREFIX)/*