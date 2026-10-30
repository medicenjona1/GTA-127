3RDPARTY = 0

PRX_DIR = .
TARGET = GTAClient
OBJS = src/main.o

# Banderas de compilación Cell PPU
CFLAGS = -O2 -Wall -mcpu=cell
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
PRX_LDFLAGS = -Wl,-q -Wl,--export-dynamic

# Definición de PSL1GHT
ifeq ($(strip $(PSL1GHT)),)
    PSL1GHT := $(PS3DEV)
endif

# Inclusión de las reglas base de PSL1GHT
ifneq ($(wildcard $(PSL1GHT)/ppu/share/psl1ght/makefile.base),)
    include $(PSL1GHT)/ppu/share/psl1ght/makefile.base
else ifneq ($(wildcard $(PSL1GHT)/share/psl1ght/makefile.base),)
    include $(PSL1GHT)/share/psl1ght/makefile.base
else ifneq ($(wildcard $(PS3DEV)/ppu/share/psl1ght/makefile.base),)
    include $(PS3DEV)/ppu/share/psl1ght/makefile.base
else ifneq ($(wildcard $(PS3DEV)/share/psl1ght/makefile.base),)
    include $(PS3DEV)/share/psl1ght/makefile.base
else
    PSL1GHT_BASE := $(shell find / -iname "*makefile.base*" 2>/dev/null | head -n 1)
    ifneq ($(PSL1GHT_BASE),)
        include $(PSL1GHT_BASE)
    else
        $(error No se encontro Makefile.base de PSL1GHT en el entorno)
    endif
endif
