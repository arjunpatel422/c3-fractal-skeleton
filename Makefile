all: mandelbrotgen buddhabrotgen

mandelbrotgen:	objs/Fractal.o objs/Buddhabrot.o objs/Mandelbrot.o objs/mandelbrotgen.o objs/lodepng.o
	g++ -fopenmp -g -o mandelbrotgen objs/Fractal.o  objs/Mandelbrot.o objs/mandelbrotgen.o objs/lodepng.o -ansi -pedantic -Wall -Wextra -O3
	
buddhabrotgen: objs/Fractal.o objs/Buddhabrot.o objs/Mandelbrot.o objs/buddhabrotgen.o objs/lodepng.o
	g++ -fopenmp -g -o buddhabrotgen objs/Fractal.o objs/Buddhabrot.o  objs/buddhabrotgen.o objs/lodepng.o -ansi -pedantic -Wall -Wextra -O3

configure:
	mkdir objs
	
smallmandelbrot:
	./mandelbrotgen 1 mandelbrot.png

mediummandelbrot:
	./mandelbrotgen 3 mandelbrot.png

largemandelbrot:
	./mandelbrotgen 5 mandelbrot.png
	
smallbuddhabrot:
	./buddhabrotgen 1 buddhabrot.png

mediumbuddhabrot:
	./buddhabrotgen 3 buddhabrot.png

largebuddhabrot:
	./buddhabrotgen 5 buddhabrot.png

objs/Fractal.o: src/Fractal.cpp
	g++ -fopenmp -g -c -o objs/Fractal.o src/Fractal.cpp

objs/Mandelbrot.o: src/Mandelbrot.cpp 
	g++ -fopenmp -g -c -o objs/Mandelbrot.o src/Mandelbrot.cpp

objs/mandelbrotgen.o: src/mandelbrotgen.cpp
	g++ -fopenmp -g -c -o objs/mandelbrotgen.o src/mandelbrotgen.cpp
	
objs/buddhabrotgen.o: src/buddhabrotgen.cpp
	g++ -fopenmp -g -c -o objs/buddhabrotgen.o src/buddhabrotgen.cpp

objs/Buddhabrot.o: src/Buddhabrot.cpp
	g++ -fopenmp -g -c -o objs/Buddhabrot.o src/Buddhabrot.cpp

objs/lodepng.o: src/lodepng.cpp
	g++ -fopenmp -g -c -o objs/lodepng.o src/lodepng.cpp

clean:
	rm objs/*.o mandelbrotgen buddhabrotgen
