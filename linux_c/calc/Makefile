calcul: libcalcul.a
	gcc main.c show.c -o calcul -L. -lcalcul
libcalcul.a: add.o ded.o div.o mult.o libcalc.h 
	ar -rc libcalcul.a add.o ded.o div.o mult.o
	rm -f ded.o add.o mult.o div.o
add.o:
	gcc -c add.c
ded.o:
	gcc -c ded.c
div.o:
	gcc -c div.c
mult.o:
	gcc -c mult.c
clen:
	rm -f libcalcul.a calcul