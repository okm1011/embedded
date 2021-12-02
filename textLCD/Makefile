all:exe.elf

exe.elf: libMyPeri.a textLCDtest.o
	 arm-linux-gnueabi-gcc textLCDtest.o -l MyPeri -L. -o exe.elf

libMyPeri.a: textLCD.o
	 arm-linux-gnueabi-ar rc libMyPeri.a textLCD.o

textLCD.o: textLCD.c textLCD.h
	arm-linux-gnueabi-gcc -c -o textLCD.o textLCD.c

textLCDtest.o: textLCDtest.c textLCD.h
	arm-linux-gnueabi-gcc textLCDtest.c -c
clean :
	rm -rf *.o *.a


