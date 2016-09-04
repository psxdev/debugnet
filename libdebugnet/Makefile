TARGET_LIB = libdebugnet.a
OBJS       = source/debugnet.o 
INCLUDES   = include
PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
AR      = $(PREFIX)-ar
CFLAGS  = -Wl,-q -Wall -O3 -I$(INCLUDES)
ASFLAGS = $(CFLAGS)

all: $(TARGET_LIB)


$(TARGET_LIB): $(OBJS)
	$(AR) -rc $@ $^ 

clean:
	@rm -rf $(TARGET_LIB) $(OBJS)

install: $(TARGET_LIB)
	@cp $(TARGET_LIB) $(VITASDK)/arm-vita-eabi/lib
	@cp include/debugnet.h $(VITASDK)/arm-vita-eabi/include
	@echo "Installed!"
