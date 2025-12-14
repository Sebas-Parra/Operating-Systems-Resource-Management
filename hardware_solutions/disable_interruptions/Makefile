# Makefile para compilar el ejemplo de deshabilitar interrupciones

CC = gcc
CFLAGS = -Wall -pthread
TARGET = deshabilitar_interrupciones
SRC = deshabilitar_interrupciones.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
