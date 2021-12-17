all:exe.elf

exe.elf: libMyPeri.a testAll.o libjpeg.a libmylib.a 
	arm-linux-gnueabi-gcc testAll.o -o exe.elf -lpthread -l MyPeri -L. -l mylib -L. -l jpeg -L.

testAll.o: testAll.c bitmap.h jpgAnimation.h
	arm-linux-gnueabi-gcc testAll.c -c -lpthread

libMyPeri.a: button.o led.o buzzer.o colorLED.o fnd.o textLCD.o temperature.o accelMagGyro.o touch.o bitmap.o jpgAnimation.o
	 arm-linux-gnueabi-ar rc libMyPeri.a button.o led.o buzzer.o colorLED.o fnd.o textLCD.o temperature.o accelMagGyro.o touch.o bitmap.o jpgAnimation.o

jpgAnimation.o: jpgAnimation.c jpgAnimation.h libjpeg.a libmylib.a 
	arm-linux-gnueabi-gcc -c -o jpgAnimation.o jpgAnimation.c -l mylib -L. -l jpeg -L.
bitmap.o: bitmap.c bitmap.h
	arm-linux-gnueabi-gcc -c -o bitmap.o bitmap.c
touch.o: touch.c touch.h
	arm-linux-gnueabi-gcc -c -o touch.o touch.c
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

clean :
	 rm -rf *.o *.a

