#include "Mandelbrot.h"

void Mandelbrot::color(int x, int y, int r, int g, int b)
{
   m_bitmap[4*(x*m_height + y)] = r;
   m_bitmap[4*(x*m_height + y) + 1] = g;
   m_bitmap[4*(x*m_height + y) + 2] = b;
   m_bitmap[4*(x*m_height + y) + y*4 + 3] = 255;
}


void Mandelbrot::gen_fractal()
{
	int height = get_height();
	int width = get_width();
	int MAX = 1000;
	int i,j,n;
	double z_r,z_i,a,b,c_r,c_i,temp;
	//iterate through rows
	#pragma omp parallel for private(i,j,n,z_r,z_i,a,b,c_r,c_i,temp)
	for (i = 1; i < height; i++)
	{
		b=i;
		a=1;
		//columns
		for (j = 1; j < width; j++)
		{
			z_r = 0.0;
			z_i = 0.0;
		
			//scale pixels

			c_r = (a/height)*3 - 2.25;
			c_i = (b/width)*3 - 1.5;
	
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
			 color(i,j,0,0,0);
			}
			else
			{
			 color(i,j,(255-(pow((double)n/(double)MAX,-0.9)*255)),(255-(pow((double)n/(double)MAX,-0.8)*255)),(255-(pow((double)n/(double)MAX,-0.7)*255)));
			}
			a++;
		}

	}

}   
