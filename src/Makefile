PROJECT = myproject

DEVICE = stm32f103c8t6
OOCD_FILE = board/stm32f1discovery.cfg

BUILD_DIR = bin
SHARED_DIR = ../lib

CFILES = main.c
CFILES += bootloader/bootloader.c

# Uncomment if you plan to use api example in main.c
# CFILES += api/api.c
# AFILES += api/api-asm.S

# Device path used by stm32flash utility to burn bootloader.
STM32FLASH_DEVICE=/dev/ttyUSB0

# Mountpath of firmware to override when bootloader is running.
FIRMWARE_BIN_PATH=/media/${USER}/STM32F103C8/FIRMWARE.BIN

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk

# include $(OPENCM3_DIR)/mk/genlink-rules.mk
$(LDSCRIPT): $(OPENCM3_DIR)/ld/linker.ld.S $(OPENCM3_DIR)/ld/devices.data
	$(Q)$(CPP) $(ARCH_FLAGS) $(shell $(OPENCM3_DIR)/scripts/genlink.py $(DEVICES_DATA) $(DEVICE) DEFS|sed s/_ROM_OFF=0x08000000/_ROM_OFF=0x08001000/g) -P -E $< -o $@

mscflash: $(BUILD_DIR)/$(PROJECT).bin
	@printf "  MSCFLASH\t$<\n"
	@cp $< $(FIRMWARE_BIN_PATH) && echo flash done...

bootloaderflash:
	# Set UART RX to pin A9
	# Set UART TX to pin A10
	# Set BOOT0 jumper to 1
	# Set BOOT1 jumper to 0
	@sudo ../lib/bootloader/stm32flash ${STM32FLASH_DEVICE} -u # Disable the flash write-protection
	@sudo ../lib/bootloader/stm32flash ${STM32FLASH_DEVICE} -o # Erase only
	@sudo ../lib/bootloader/stm32flash ${STM32FLASH_DEVICE} -v -g 0x08000000 -w ../lib/bootloader/bootloader.bin # Flash and start execution at specified address

