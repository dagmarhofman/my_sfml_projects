all:
	g++ -c map.cpp 
	g++ -c main.cpp 
	g++ -c game.cpp
	g++ -c player.cpp
	g++ -o iosilver player.o map.o game.o main.o -lsfml-graphics -lsfml-window -lsfml-system
