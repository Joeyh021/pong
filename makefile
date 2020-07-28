SFMLPATH=E:/code/SFML

test: 
	g++ test.cpp -o test -I$(SFMLPATH)/include -L$(SFMLPATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm test