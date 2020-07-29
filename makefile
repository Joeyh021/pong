SFMLPATH=E:/code/SFML


drawing:
	g++ tests/drawing.cpp -o test -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.exe