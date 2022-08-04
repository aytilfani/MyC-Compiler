all :	ex1 ex2 ex3 ex4 ex5 ex6 ex7

pcode : PCode.c PCode.h
	gcc -c PCode.c

ex1 :	pcode pcode-ex1.c
	gcc -o ex1 pcode-ex1.c PCode.o

ex2 :	pcode pcode-ex2.c
	gcc -o ex2 pcode-ex2.c PCode.o

ex3 :	pcode pcode-ex3.c
	gcc -o ex3 pcode-ex3.c PCode.o

ex4 :	pcode pcode-ex4.c
	gcc -o ex4 pcode-ex4.c PCode.o

ex5 :	pcode pcode-ex5.c
	gcc -o ex5 pcode-ex5.c PCode.o

ex6 :	pcode pcode-ex6.c
	gcc -o ex6 pcode-ex6.c PCode.o

ex7 :	pcode pcode-ex7.c
	gcc -o ex7 pcode-ex7.c PCode.o

clean :
	rm -f ex* *.o
