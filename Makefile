CC	= gcc
LIBS	= -lSDL2main -lSDL2 -lSDL2_image
INC	= -I ./include
FLAGS	= -Wall -g
OBJ	= *.o
SRC	= src/main.c	\
	  src/screen.c	\
	  src/player.c

compile :
	$(CC) -c $(SRC)


link :
	$(CC) $(OBJ) $(INC) $(LIBS) $(FLAGS) -o Plateformer

clear :
	rm $(OBJ)
