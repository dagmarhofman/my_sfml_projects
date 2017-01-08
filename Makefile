all:
	g++ -c map.cpp 
	g++ -c main.cpp 
	g++ -c game.cpp
	g++ -o iosilver map.o game.o main.o -lsfml-graphics -lsfml-window -lsfml-system
