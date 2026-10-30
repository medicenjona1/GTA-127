3RDPARTY = 0

PRX_DIR = .
TARGET = GTAClient
OBJS = src/main.o

# Banderas de compilación para Cell PPU
CFLAGS = -O2 -Wall -mcpu=cell
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
PRX_LDFLAGS = -Wl,-q -Wl,--export-dynamic

# Localización automática de makefile.base en el sistema
PSL1GHT_BASE := $(shell find /usr -name "makefile.base" 2>/dev/null | head -n 1)

ifneq ($(PSL1GHT_BASE),)
    include $(PSL1GHT_BASE)
else
    $(error No se encontro makefile.base de PSL1GHT en el contenedor)
endif
