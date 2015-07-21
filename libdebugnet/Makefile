TARGET_LIB = libdebugnet.a
OBJS       = source/debugnet.o 
INCLUDES   = include
PREFIX  = arm-none-eabi
CC      = $(PREFIX)-gcc
AR      = $(PREFIX)-ar
CFLAGS  = -O2 -Wall -specs=psp2.specs -I$(INCLUDES) 
ASFLAGS = $(CFLAGS)

all: $(TARGET_LIB)


$(TARGET_LIB): $(OBJS)
	$(AR) -rc $@ $^ 

clean:
	@rm -rf $(TARGET_LIB) $(OBJS)

install: $(TARGET_LIB)
	@cp $(TARGET_LIB) $(PSP2SDK)/lib
	@cp include/debugnet.h $(PSP2SDK)/include
	@echo "Installed!"