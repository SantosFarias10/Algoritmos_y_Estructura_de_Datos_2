CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99
CNAME = checkpal

all: compilar

obj:
	gcc $(CFLAGS) -c *.c

compilar: obj
	gcc $(CFLAGS) *.o -o $(CNAME)

valgrind: $(CNAME)
	valgrind --leak-check=full -s ./$(CNAME)

eliminar:
	rm -f *.o $(CNAME)

.PHONY: eliminar