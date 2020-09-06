SFMLPATH=C:/users/josep/code/SFML

main: pong.hpp 
	g++ pong.cpp -o bin/pong -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -Wall

drawing:
	g++ tests/drawing.cpp -o test -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -lsfml-graphics -lsfml-window -lsfml-system
db:
	g++ -g pong.cpp -o bin/pongdb -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -Wall

clean:
	rm bin/*.exe