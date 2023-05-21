CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

SRC = blablacar.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = blablacar

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXECUTABLE)
