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
DEPENDENCY_FILES := $(OBJECTS:%.o=%.d)
ASSEMBLY_FILES := $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.s)

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


compile_without_fixing: main.elf

include $(DEPENDENCY_FILES)

#Compile and run
run: main.gba
	mgba-qt main.gba

#Generate verbose assembly files
assembly: $(ASSEMBLY_FILES)

#Generate dependency files (so that makefile takes all .h files into account when compiling)
#  This doesnt ever need to be called manually
dependencies: $(DEPENDENCY_FILES)

#Run the executable and use gdb to debug it.
#Runs the mgba-qt emulator with its debugger server running,
#  puts in your clipboard the commands needed to connect to said server from a gdb client,
#  then opens up a gdb client.
#  Just paste and enter to begin debugging.
debug: main.elf
	mgba-qt main.elf -g &
	(echo "target remote 0.0.0.0:2345"; echo "file main.elf"; echo "y") | xclip -selection clipboard
	arm-none-eabi-gdb

clean:
	rm -f *.elf *.o *.gba *.sav *.s
	rm -fr obj/

###########################################

main.elf: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.elf $(LDFLAGS) $(DEBUG)

main.gba: main.elf
	arm-none-eabi-objcopy -v -O binary main.elf main.gba
	gbafix main.gba

$(OBJECTS): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG)

#Dependency files
#  Uses the compiler to generate dependencies for a given .o target,
#  then adds those dependencies to '.o', '.s' and '.d' files.
$(DEPENDENCY_FILES): $(OBJ_DIR)%.d : $(SRC_DIR)%.c
	@set -e; rm -f $@; \
	mkdir -p $(@D); \
	$(CC) -MM $(CFLAGS) $< -MF $@.$$$$; \
	sed 's,\(.*\)\.o[ :]*,$(@D)/\1.o $(@D)/\1.d $(@D)/\1.s : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(ASSEMBLY_FILES): $(OBJ_DIR)%.s : $(SRC_DIR)%.c
	mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG) -S -fverbose-asm

