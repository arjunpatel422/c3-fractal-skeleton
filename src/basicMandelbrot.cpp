#include "Mandelbrot.h"

void Mandelbrot::gen_fractal()
{
	const int height = get_height();
	const int width = get_width();
	const int NPIXELS=width*height;
	const double MAX = 1000;
	int position,r,g,b;
	double z_r,z_i,n,c_r,c_i,temp;
	#pragma omp parallel for private(position,n,z_r,z_i,c_r,c_i,temp,r,g,b)
	for(position=0;position<NPIXELS;position++)
	{
		c_r=position%width; //simplest way to get x
		c_i=position-c_r; //simplest way to get y
		c_i = (c_i/NPIXELS)*3 - 1.5;
		c_r = (c_r/width)*3 - 2.25;
		z_r = 0.0;
		z_i = 0.0;
		n = 0;  //iterator
		while (z_r*z_r + z_i*z_i < 4 && n < MAX)
		{
			temp = z_r;
			z_r = z_r*z_r - z_i*z_i + c_r;
			z_i = z_i*temp*2 + c_i;
			n++;
		}
		if (n > MAX ) /* if not converging to infinity (COLOR BLACK) */
		{
			r=BLACK;
			g=BLACK;
			b=BLACK;
		}
		else
		{
			temp=(n/MAX);
			r=MAXCOLOR-MAXCOLOR*(pow(temp,-0.9));
			g=MAXCOLOR-MAXCOLOR*(pow(temp,-0.3));
			b=MAXCOLOR-MAXCOLOR*(pow(temp,-0.2));
		}
		color(&position,&r,&g,&b);
	}

}   
