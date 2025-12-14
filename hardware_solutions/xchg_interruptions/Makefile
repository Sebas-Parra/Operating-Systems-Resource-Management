# Makefile para compilar el ejemplo de XCHG

CC = gcc
CFLAGS = -Wall -pthread -std=c11
TARGET = xchg
SRC = xchg.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
