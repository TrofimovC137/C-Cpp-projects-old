all: main

main: main.o filework.o
	gcc -o main main.o filework.o
	
main.o: main.c
	gcc -c main.c
	
filework.o: filework.c
	gcc -c filework.c
	
clean:
	rm *.o
