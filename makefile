LIBS 	= 
CFLAGS	= -Wall -I inc
LDFLAGS	= -rcs
CC	= gcc   # compiler name
LD	= ar

TARGET	= libcfg.a

OBJ := $(patsubst %.c,%.o,$(wildcard src/*.c))

all: $(TARGET) 


$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
	
src/%.o : src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm -f $(TARGET)  $(OBJ) #This way is cleaner than your clean

install:
	cp libcfg.a /lib/
	cp inc/cfg.h /usr/include/

uninstall:
	rm /lib/libcfg.a
	cp /usr/include/cfg.h
