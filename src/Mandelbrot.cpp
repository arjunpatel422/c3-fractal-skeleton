#include "Mandelbrot.h"

void Mandelbrot::gen_fractal()
{
	const int height = get_height();
	const int width = get_width();
	const int NPIXELS=width*height;
	const double MAX = MAXITER;
	const double log2=log(2.0);
	const float colorScalar=1/255;
	int position;
	double z_r,z_i,z_temp,n,c_r,c_i,r,g,b;
	float escape_radius=2<<16;
	float modulus;
	#pragma omp parallel for private(position,n,z_r,z_i,z_temp,c_r,c_i,r,g,b,modulus)
	for(position=0;position<NPIXELS;position++)
	{
		c_r=position%width; //simplest way to get x
		c_i=position-c_r; //simplest way to get y
		c_i = (c_i/NPIXELS)*3 - 1.5;
		c_r = (c_r/width)*3 - 2.25;
		z_r = 0.0;
		z_i = 0.0;
		n = 0;  //iterator
		modulus=0.0;
		while (modulus< escape_radius && n < MAX)
		{
			z_temp = z_r;
			z_r = pow(z_r,2) - pow(z_i,2) + c_r;
			z_i = z_i*z_temp*2 + c_i;
			n++;
			modulus=(pow(z_r,2) + pow(z_i,2));
		}
		modulus=sqrt(modulus);//-(log(log(modulus)))/log2;
		if (n < MAX ) 
		{
			z_temp= n+1.5-log( log(modulus) / log2 ) / log2;
			//z_temp=z_temp/(MAX);//z_temp=(mu/MAX);
			z_temp*=abs(sin(MAX*z_r/(n*escape_radius))); //Makes image a lot more interesting swap n and MAX for interesting results
			r=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.2));
			g=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.7));
			b=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.6));
		}
		else //if not converging to infinity (COLOR BLACK) */
		{
			r=BLACK;
			g=BLACK;
			b=BLACK;
		}
		color(&position,&r,&g,&b);
	}

}   
