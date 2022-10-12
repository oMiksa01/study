CC = gcc
CFLAGS = -c -g
PREFIX = ./bin

labs: lab_1.o lab_2.o lab_3.o course_work.o
	$(CC) lab_1.o -o $(PREFIX)/lab_1
	$(CC) lab_2.o -o $(PREFIX)/lab_2
	$(CC) lab_3.o -o $(PREFIX)/lab_3
	$(CC) course_work.o -o $(PREFIX)/course_work
	rm -f *.o
lab_1.o: lab_1.c
	$(CC) $(CFLAGS) lab_1.c
lab_2.o: lab_2.c
	$(CC) $(CFLAGS) lab_2.c
lab_3.o: lab_3.c
	$(CC) $(CFLAGS) lab_3.c
course_work.o: course_work.c
	$(CC) $(CFLAGS) course_work.c
clear:
	rm -f *.o $(PREFIX)/*