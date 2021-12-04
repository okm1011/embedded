all:exe.elf

exe.elf: libMyPeri.a testAll.o
	 arm-linux-gnueabi-gcc testAll.o -l MyPeri -L. -o exe.elf -lpthread

libMyPeri.a: button.o led.o buzzer.o colorLED.o fnd.o textLCD.o temperature.o accelMagGyro.o
	 arm-linux-gnueabi-ar rc libMyPeri.a button.o led.o buzzer.o colorLED.o fnd.o textLCD.o temperature.o accelMagGyro.o

accelMagGyro.o: accelMagGyro.c accelMagGyro.h
	arm-linux-gnueabi-gcc -c -o accelMagGyro.o accelMagGyro.c
temperature.o: temperature.c temperature.h
	arm-linux-gnueabi-gcc -c -o temperature.o temperature.c
buzzer.o:buzzer.c buzzer.h
	arm-linux-gnueabi-gcc -c -o buzzer.o buzzer.c
led.o: led.c led.h
	arm-linux-gnueabi-gcc -c -o led.o led.c
button.o: button.c button.h
	 arm-linux-gnueabi-gcc -c -o button.o button.c -lpthread
colorLED.o: colorLED.c colorLED.h
	 arm-linux-gnueabi-gcc -c -o colorLED.o colorLED.c 
fnd.o: fnd.c fnd.h
	 arm-linux-gnueabi-gcc -c -o fnd.o fnd.c 
textLCD.o: textLCD.c textLCD.h
	 arm-linux-gnueabi-gcc -c -o textLCD.o textLCD.c 
testAll.o: testAll.c button.h led.h buzzer.h colorLED.h fnd.h textLCD.h
	 arm-linux-gnueabi-gcc testAll.c -c -lpthread
clean :
	 rm -rf *.o *.a


