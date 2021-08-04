TARGET = PBP_Depack
OBJS = depack.o 

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

USE_KERNEL_LIBC=0
USE_KERNEL_LIBS=0

LIBDIR =
LDFLAGS = -mno-crt0 -nostartfiles
LIBS = -lstdc++ -lpspkernel


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
