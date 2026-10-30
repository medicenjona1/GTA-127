TARGET      := GTAClient
BUILD_PRX   := 1
PRX_DIR     := .

OBJS        := src/main.o

CFLAGS      := -O2 -Wall -mcpu=cell
CXXFLAGS    := -O2 -Wall -mcpu=cell -std=gnu++11 -fno-exceptions -fno-rtti
PRX_LDFLAGS := -Wl,-q -Wl,--export-dynamic

# Localización de makefile.base en PSL1GHT
PSL1GHT_BASE := $(wildcard $(PS3DEV)/ppu/share/psl1ght/makefile.base)
ifeq ($(PSL1GHT_BASE),)
    PSL1GHT_BASE := $(wildcard $(PS3DEV)/portlibs/ppu/share/psl1ght/makefile.base)
endif
ifeq ($(PSL1GHT_BASE),)
    PSL1GHT_BASE := $(shell find / -iname "makefile.base" 2>/dev/null | head -n 1)
endif

ifneq ($(PSL1GHT_BASE),)
    include $(PSL1GHT_BASE)
endif

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).sprx $(TARGET).prx
