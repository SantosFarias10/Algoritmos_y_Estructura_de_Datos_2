CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99

CC = gcc

SRC = main.c strfuncs.c

OBJS = $(SRC:.c=.o)

all: str

clean:
	rm -f str *.o 

objetos:
	$(CC) $(CFLAGS) -c $(SRC)

str: $(OBJS)
	$(CC) $(Cflags) -o $@ *.o

.PHONY: clean