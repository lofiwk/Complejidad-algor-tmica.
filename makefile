CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = Workbench/inverted_index
SRC = Workbench/inverted_index.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
