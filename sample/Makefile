#
# Copyright (c) 2015 Antonio Jose Ramos Marquez aka bigboss (@psxdev)
#





TARGET		:= debugnetsample

OBJS= main.o

LIBS=-ldebugnet -lSceNet_stub -lSceNetCtl_stub 

PREFIX   = arm-vita-eabi
AS	     = $(PREFIX)-as
CC       = $(PREFIX)-gcc
CXX		 = $(PREFIX)-g++
READELF  = $(PREFIX)-readelf
OBJDUMP  = $(PREFIX)-objdump
CFLAGS   = -Wl,-q  $(DEFINES) $(INCDIR) -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -ffunction-sections
CXXFLAGS = $(CFLAGS) -fno-unwind-tables -fno-rtti -fno-exceptions -Wno-deprecated -Wno-comment -Wno-sequence-point
ASFLAGS  = $(CFLAGS) --gc-sections

all: $(TARGET).velf

$(TARGET).velf: $(TARGET).elf
#advice from xyzz strip before create elf
	arm-vita-eabi-strip -g $<
#i put db.json there use your location 
	vita-elf-create  $< $@ $(VITASDK)/bin/db.json

$(TARGET).elf: $(OBJS)
	$(CC)   $^  $(CFLAGS) $(LIBS) -o $@ 

clean:
	@rm -rf $(TARGET).elf $(TARGET).velf $(OBJS) $(DATA)/*.h
		
