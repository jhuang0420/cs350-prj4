all: matmul

matmul: main.o matmul.o
	gcc -o matmul main.o matmul.o -pthread

matmul.o:
	gcc -c matmul.c 

main.o:
	gcc -c main.c

clean:
	rm -f matmul *.o
