# Makefile for two programs

# compiler
CC = g++

# compiler flags
CFLAGS =-Wall 
# Point the compiler to the include directorys for sfml
PATH1 = -I /usr/local/SFML-2.5.1/include
# Point the compiler to the directory with all of the libraries for sfml
SFMLFLAGS = -L /usr/local/2.5.1_2/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


all:main

# Create the main program. And point it to each of the object files created from the later sections
main: main.o attack.o blueslime.o redslime.o enemy.o player.o tree.o
	$(CC) $(CFLAGS) $(PATH1) -o main main.o  attack.o blueslime.o redslime.o enemy.o player.o tree.o $(SFMLFLAGS)


# Create the main.o file, pointing it to each of the header files used in main after which, build the lines of code to compile it
main.o: main.cpp attack.h  blueslime.h redslime.h enemy.h player.h tree.h
	$(CC) $(CFLAGS) -c  main.cpp $(PATH1)
# Create the attack.o file, pointing it to attack.cpp and its requirement attack.h
attack.o: attack.cpp attack.h
	$(CC) $(CFLAGS) -c attack.cpp $(PATH1)
# Create the enemy.o file, pointing it to enemy.cpp and enemy.h
enemy.o: enemy.cpp enemy.h
	$(CC) $(CFLAGS) -c enemy.cpp $(PATH1)
# Create blueslime.o and point it to its requirements, enemy.h and blueslime.h and then build it
blueslime.o: blueslime.cpp blueslime.h enemy.h
	$(CC) $(CFLAGS) -c blueslime.cpp $(PATH1)

# Create redslime.o and point it to its requirements, enemy.h and redslime.h and then build it
redslime.o: redslime.cpp redslime.h enemy.h
	$(CC) $(CFLAGS) -c redslime.cpp $(PATH1)

# Create the player.o file, and point it to its cpp and .h files. then compile it
player.o: player.cpp  player.h
	$(CC) $(CFLAGS) -c player.cpp $(PATH1)

# build the tree.o file, and point it to its .cpp and .h files. then compile it
tree.o: tree.cpp tree.h
	$(CC) $(CFLAGS) -c tree.cpp $(PATH1)

# Run the command
run:main.o
	./main

clean:
	rm main attack.o blueslime.o redslime.o enemy.o player.o tree.o

