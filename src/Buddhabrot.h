#ifndef _BUDDHABROT_H
#define _BUDDHABROT_H
#include <cmath>
#include <cstdlib>
#include "Fractal.h"

class Buddhabrot : public Fractal
{
	public:
	Buddhabrot(int height, int width):Fractal(height, width) {}	
    Buddhabrot(double x):Fractal(x) {}
	void gen_fractal();
};
#endif
