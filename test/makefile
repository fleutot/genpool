CC = gcc
CFLAGS = -std=c99 -g -Wall -Werror -O3 -Wno-unused-function -I../genome/

SRC = ../genome/genome.c ../genome/randomizer.c ../genome/linkedlist/linkedlist.c ../genome/machine/machine.c ../genpool.c genpool_test.c
OBJ = $(SRC:.c=.o)
TARGET = genpool_test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ../*.o *.o $(TARGET)

test: $(TARGET)
	./$(TARGET)
