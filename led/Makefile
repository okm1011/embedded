all:exe.elf

exe.elf: libMyPeri.a ledtest.o
	 arm-linux-gnueabi-gcc ledtest.o -l MyPeri -L. -o exe.elf

libMyPeri.a: led.o
	 arm-linux-gnueabi-ar rc libMyPeri.a led.o

led.o: led.c led.h
	arm-linux-gnueabi-gcc -c -o led.o led.c

ledtest.o: ledtest.c led.h
	arm-linux-gnueabi-gcc ledtest.c -c
clean :
	rm -rf *.o *.a


