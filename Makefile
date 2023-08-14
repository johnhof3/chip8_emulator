# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Sources and objects
SRCS = main.c chip8_cpu.c chip8_graphics.c chip8_input.c chip8_sound.c chip8_util.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = chip8_interpreter

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
