# Makefile para compilar el ejemplo de Test-and-Set

CC = gcc
CFLAGS = -Wall -pthread -std=c11
TARGET = test_and_set
SRC = test_and_set.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
