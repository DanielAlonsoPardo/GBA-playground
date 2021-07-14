SRC_DIR := src
OBJ_DIR := obj

CC := arm-none-eabi-gcc
OPTIMIZE := -O2
DEBUG := -g
CFLAGS  := -mthumb-interwork -mthumb -Wall
LDFLAGS := -mthumb-interwork -mthumb -specs=gba.specs 

SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS := $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


rom: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.elf $(LDFLAGS) $(DEBUG)
	arm-none-eabi-objcopy -v -O binary main.elf main.gba
	gbafix main.gba

$(OBJECTS): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG)

clean:
	rm -f *.elf *.o *.gba
	rm -fr obj/
