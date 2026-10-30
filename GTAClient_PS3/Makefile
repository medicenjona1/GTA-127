3RDPARTY = 0

PRX_DIR = .
TARGET = GTAClient
OBJS = src/main.o

# Banderas de compilación
CFLAGS = -O2 -Wall -mcpu=cell
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
PRX_LDFLAGS = -Wl,-q -Wl,--export-dynamic

# Detección automática de la ruta de PSL1GHT
ifneq ($(wildcard $(PS3DEV)/portlibs/ppu/share/psl1ght/makefile.base),)
    include $(PS3DEV)/portlibs/ppu/share/psl1ght/makefile.base
else ifneq ($(wildcard $(PS3DEV)/share/psl1ght/makefile.base),)
    include $(PS3DEV)/share/psl1ght/makefile.base
else ifneq ($(wildcard $(PSL1GHT)/share/psl1ght/makefile.base),)
    include $(PSL1GHT)/share/psl1ght/makefile.base
else ifneq ($(wildcard $(PSL1GHT)/makefile.base),)
    include $(PSL1GHT)/makefile.base
else
    include $(PS3DEV)/psl1ght/makefile.base
endif
