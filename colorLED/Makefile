all:exe.elf
        
exe.elf: libMyPeri.a colorLEDtest.o
	 arm-linux-gnueabi-gcc colorLEDtest.o -l MyPeri -L. -o exe.elf

libMyPeri.a: colorLED.o
	 arm-linux-gnueabi-ar rc libMyPeri.a colorLED.o

colorLED.o: colorLED.c colorLED.h
	arm-linux-gnueabi-gcc -c -o colorLED.o colorLED.c

colorLEDtest.o: colorLEDtest.c colorLED.h
	arm-linux-gnueabi-gcc colorLEDtest.c -c
clean :
	rm -rf *.o *.a



