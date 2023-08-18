complex.o : complex.cpp complex.h
	g++ -c complex.cpp

Button.o : Button.cpp Button.h
	g++ -c Button.cpp

Mandelbrot.o : Mandelbrot.cpp Mandelbrot.h
	g++ -c Mandelbrot.cpp

main.o : main.cpp
	g++ -c main.cpp

mandelbrot : main.o complex.o Button.o Mandelbrot.o
	g++ main.o complex.o Button.o Mandelbrot.o -o mandelbrot -lsfml-graphics -lsfml-window -lsfml-system
