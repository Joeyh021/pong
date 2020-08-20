SFMLPATH=C:/users/josep/code/SFML

main: pong.hpp 
	g++ pong.cpp -o bin/pong -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -Wall

drawing:
	g++ tests/drawing.cpp -o test -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm bin/*.exe