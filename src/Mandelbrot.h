#ifndef _MANDELBROT_H
#define _MANDELBROT_H

#include <cmath>
#include <cstdlib>
#include "Fractal.h"

class Mandelbrot : public Fractal
{
	public:
	Mandelbrot(int height, int width):Fractal(height, width) {}
    Mandelbrot(double x):Fractal(x) {}
	void gen_fractal();
};

#endif
