all : final.elf

final.elf : main.o 1.o
	gcc main.o 1.o -o final.elf
main.o : main.c MyProject.h
	gcc main.c -c
1.o : 1.c MyProject.h
	gcc 1.c -c

clean : 
	rm -rf *.o

