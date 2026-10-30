3RDPARTY = 0

PRX_DIR = .
TARGET = GTAClient
OBJS = src/main.o

# Banderas de compilación para PS3
CFLAGS = -O2 -Wall -mcpu=cell
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
PRX_LDFLAGS = -Wl,-q -Wl,--export-dynamic

# Entorno ps3dev / PSL1GHT
include $(PS3DEV)/psl1ght/makefile.base
