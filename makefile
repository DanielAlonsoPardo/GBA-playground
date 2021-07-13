all: main.c geometry.o
	arm-none-eabi-gcc -c main.c -mthumb-interwork -mthumb -O2 -o main.o
	arm-none-eabi-gcc    main.o geometry.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf
	arm-none-eabi-objcopy -v -O binary main.elf main.gba
	gbafix main.gba
	make clean

geometry.o: lib/geometry.h lib/geometry.c
	arm-none-eabi-gcc -c lib/geometry.c -mthumb-interwork -mthumb -O2 -o geometry.o


clean:
	rm -f *.elf *.o
