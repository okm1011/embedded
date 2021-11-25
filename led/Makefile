all:led.elf

led.elf:ledtest.o libMyperi.a
	arm-linux-gnueabi-gcc ledtest.o -l Myperi -L. -o led.elf
ledtest.o:ledtest.c led.h
	arm-linux-gnueabi-gcc ledtest.c -c
libMyperi.a:led.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o
led.o:led.c led.h
	arm-linux-gnueabi-gcc --static -c -o led.o led.c
clean:
	arm-linux-gnueabi-rm -rf *.o.*.a.*,elf
