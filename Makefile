TARGET = Open_Source_File_Browser
OBJS = main.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS=
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Open Browser
PSP_EBOOT_ICON= ICON0.PNG
#PSP_EBOOT_PIC1 = PIC1.PNG
#PSP_EBOOT_SFO= PARAM.SFO

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak