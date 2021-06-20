CC = gcc
CFLAGS = -Wall -O0
OBJECTS = main.o fiber.o
TARGET = main

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
