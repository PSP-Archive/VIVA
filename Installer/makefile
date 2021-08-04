TARGET = VIVA_flash_patch
BUILD_PRX = 1

OBJS =\
main.o


CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lpspdebug

LDFLAGS += -mno-crt0

EXTRA_TARGETS   = EBOOT.PBP
PSP_EBOOT_TITLE = VIVA Flash Patcher

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
