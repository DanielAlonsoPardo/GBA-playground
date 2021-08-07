SRC_DIR := src
OBJ_DIR := obj

CC := arm-none-eabi-gcc
OPTIMIZE := -O2
DEBUG := -g
CFLAGS  := -mthumb-interwork -mthumb -Wall
LDFLAGS := -mthumb-interwork -mthumb -specs=gba.specs -lm
#possibly only link -lm on certain files?

SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS := $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
ASSEMBLY_FILES := $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.s)

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

main.gba: main.elf
	arm-none-eabi-objcopy -v -O binary main.elf main.gba
	gbafix main.gba

main.elf: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.elf $(LDFLAGS) $(DEBUG)

$(OBJECTS): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG)

$(ASSEMBLY_FILES): $(OBJ_DIR)%.s : $(SRC_DIR)%.c
	mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG) -S -fverbose-asm

exec: main.gba
	mgba-qt main.gba

debug: main.elf
	mgba-qt main.elf -g &
	(echo "target remote 0.0.0.0:2345"; echo "file main.elf"; echo "y") | xclip -selection clipboard
	arm-none-eabi-gdb

clean:
	rm -f *.elf *.o *.gba *.sav *.s
	rm -fr obj/

assembly: $(ASSEMBLY_FILES)
