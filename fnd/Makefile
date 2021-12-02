all:exe.elf

exe.elf: libMyPeri.a fndtest.o
	 arm-linux-gnueabi-gcc fndtest.o -l MyPeri -L. -o exe.elf

libMyPeri.a: fnd.o
	 arm-linux-gnueabi-ar rc libMyPeri.a fnd.o

fnd.o: fnd.c fnd.h
	arm-linux-gnueabi-gcc -c -o fnd.o fnd.c

fndtest.o: fndtest.c fnd.h
	arm-linux-gnueabi-gcc fndtest.c -c
clean :
	 rm -rf *.o *.a

