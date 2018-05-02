.PHONY: clean wipeout

EXEC = fasta_project
C_FLAGS = -Wall -Wextra -g
CC = gcc $(C_FLAGS)

SRC = $(wildcard src/*.c)
OBJ = ${SRC:.c=.o}

all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(EXEC)

clean:
	rm -rf $(OBJ)

wipeout: clean
	rm -rf $(EXEC)
