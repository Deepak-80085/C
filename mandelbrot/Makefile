CC = gcc
CFLAGS = -Wall -Wextra -O2 -lm
SRC_DIR = src
TARGET = mandelbrot

$(TARGET): $(SRC_DIR)/mandelbrot.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) 