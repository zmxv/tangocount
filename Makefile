CC = gcc
CFLAGS = -O3 -ffast-math -Wall -Wextra
DEBUG_CFLAGS = -g -O0 -Wall -Wextra
TARGET = tangocount
SOURCE = tangocount.c

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

debug: $(SOURCE)
	$(CC) $(DEBUG_CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)