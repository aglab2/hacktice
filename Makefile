SRC_DIR = src
OBJ_DIR = obj
TOOL_DIR = Hacktice

# Alter these 4 variables according to your need
CPP_FILES = main savestate text_manager input_viewer level_reset cfg level_conv strings string_conv wallkick_frame distance levitate speed timer checkpoint action interaction music death death_floor version

# If _start will have more elements, adjust this variable 
PAYLOAD_HEADER_SIZE = 48

# ROM to inject into for convenient testing
ROM = sr8.z64

INCLUDE_PATH = sm64-api/sm64
LIBRARY_PATH = sm64-api/ld

# 0x7f2000
ROM_OFFSET = 8331264

SRC_FILES = $(patsubst %, $(SRC_DIR)/%.c, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))

PAYLOAD = $(OBJ_DIR)/payload
PAYLOAD_HEADER = $(TOOL_DIR)/payload_header
PAYLOAD_DATA = $(TOOL_DIR)/payload_data

CC = clang
AR = llvm-ar
LD = ld.lld
CFLAGS = -flto -Wall -Wdouble-promotion -Oz -mfix4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -I $(INCLUDE_PATH)/libc -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -DTARGET_N64 -mfpxx

all: $(OBJ_DIR) $(ROM) $(PAYLOAD_HEADER) $(PAYLOAD_DATA)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(PAYLOAD): $(OBJ_FILES)
	$(LD) -o $@ -L. -L $(LIBRARY_PATH) --oformat binary -T ldscript -M $^

$(ROM): $(PAYLOAD)
	dd bs=1 seek=$(ROM_OFFSET) if=$^ of=$@ conv=notrunc

$(PAYLOAD_HEADER): $(PAYLOAD)
	dd bs=48 count=1 if=$^ of=$@ conv=notrunc

$(PAYLOAD_DATA): $(PAYLOAD)
	dd bs=1 skip=48 if=$^ of=$@ conv=notrunc

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(PAYLOAD_HEADER)
	rm -f $(PAYLOAD_DATA)

.PHONY: all clean $(ROM)
