.PHONY: clean wipeout

EXEC = projet_fasta
C_FLAGS = -Wall -Wextra -g
CC = gcc $(C_FLAGS)

SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}

all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(EXEC)

clean:
	rm -rf $(OBJ)

wipeout: clean
	rm -rf $(EXEC)
