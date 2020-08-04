SFMLPATH=E:/code/SFML

main: pong.hpp 
	g++ pong.cpp -o pong -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -Wall

drawing:
	g++ tests/drawing.cpp -o test -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.exe