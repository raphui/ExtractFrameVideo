SRC:= main.c
OBJ:= main.o
CC:= gcc
LIBS:= -lvlc

tool: $(OBJ)
	$(CC) $(OBJ) -o tool $(LIBS)

$(OBJ): $(SRC)
	$(CC) -c $(SRC) -o $(OBJ)

clean:
	rm -rf *.o
