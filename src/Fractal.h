#ifndef _FRACTAL_H
#define _FRACTAL_H

#include<string>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<omp.h>
#include "lodepng.h"

using namespace std;	

const int MAXITER = 1100;
const int SUBSAMPLING = 20;
const int SUBSAMPLEX=4;
const int SUBSAMPLEY=4;
const int TOTALSUBSAMPLESX=SUBSAMPLEX*2;
const int TOTALSUBSAMPLESY=SUBSAMPLEY*2;
const int TOTALSUBSAMPLES=TOTALSUBSAMPLESX*TOTALSUBSAMPLESY;
const int BLACK=0;
const int MAXCOLOR=255;

class Fractal
{
    public:
        Fractal(unsigned int height, unsigned int width);
		Fractal(double x);
		~Fractal();
        virtual void gen_fractal() = 0;
        bool save_file(string filepath) const;
		unsigned int get_width() const;
		unsigned int get_height() const;
		virtual void color(unsigned int* bitmapPosition, const double* r, const double* g, const double* b);
    protected:
        unsigned char *m_bitmap;
		unsigned int m_height;
		unsigned int m_width;
};

#endif // FRACTAL_H
