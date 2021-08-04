TARGET = VIVA
BUILD_PRX = 1

PSP_FW_VERSION = 352

OBJS =\
\
../VIVA_Modules/ISOLoader/ISOLoader.o\
../VIVA_Modules/ISOLoader/k/UMD_K.o\
\
../VIVA_Modules/PBP-Depacker/PBPDepack.o\
\
framerate.o\
GL.o\
icon.o\
main.o


CFLAGS = -O3 -frename-registers -ffast-math -fomit-frame-pointer -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

INCDIR = ../include
LIBDIR = ../lib
LIBS += -lglut -lGLU -lGL -lm -lc -lpspgu -lpspge -lz -lm -lpspgum -lpsputility -lpspdebug -lpspge -lpspdisplay -lpspctrl -lpspsdk -lpspvfpu -lpsplibc -lpspuser -lpspkernel -lpsprtc -lpsppower -lstdc++ -lz -lpspgum -lpng -ljpeg\
-lpspvshbridge\
\
-lmad -lpspaudiolib -lpspaudio \
-lpspsystemctrl_user -lpspumd -lpsppower \
-lpsprtc -lpspdebug -lpspwlan \
-lpsphprm \
-lpspgu -lpng -ljpeg -lpspge -lz -lm -lpspgum -lpspaudiocodec -lpspaudiolib -lpspsystemctrl_user -lpspkubridge\
-lstdc++

#
# way to many libraries added to make a quick fix for external modules failing to load
#

LDFLAGS += -mno-crt0

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak