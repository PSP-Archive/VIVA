TARGET = isoloader
OBJS =\
\
k/UMD_K.o\
\
isoloader.o 

CFLAGS = -O2 -Os -G0 -Wall -fshort-wchar -fno-pic -mno-check-zero-division 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

USE_KERNEL_LIBC=0
USE_KERNEL_LIBS=0

INCDIR = ../../include
LIBDIR = ../../lib
LIBS =\
\
-lmad -lpspaudiolib -lpspaudio \
-lpspsystemctrl_user -lpspumd -lpsppower \
-lpsprtc -lpspdebug -lpspwlan \
-lpsphprm \
-lpspgu -lpng -ljpeg -lpspge -lz -lm -lpspgum -lpspaudiocodec -lpspaudiolib -lpspsystemctrl_user -lpspkubridge\
-lstdc++


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
