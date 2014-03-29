#include "Buddhabrot.h"
using namespace std;

void Buddhabrot::gen_fractal()
{
	// Real (-2.5, 1)
	// Imaginary (-1, 1)
	const unsigned int height = get_height();
	const unsigned int width = get_width();
	const double randWidthFactor=3.5;
	const double randHeightFactor=2.0;
	const unsigned int widthFactor=width/3.5;
	const unsigned int heightFactor=height/2;
	const unsigned int NPIXELS=width*height;
	const unsigned int totalIterations=NPIXELS*3;
	const double max_iter=MAXITER;
	//const double max_iterPlus1=MAXITER+1;
	const double escape_radius=4;
	const double sinFactor=escape_radius/max_iter;
	double maxValue=0;
    // Initialize a bucket array (one integer for each pixel) (this is the outer bucket array)
	vector<int> outerPixelBucket(NPIXELS);
	#pragma omp parallel
	{	
		unsigned int position,tempX,tempY,bitmapPosition;
		vector<int> innerPixelBucket(NPIXELS,0);
		double z_r,z_i,z_temp,n,c_r,c_i,modulus,r,g,b;
		#pragma omp for
		for(position=0;position<NPIXELS;position++)
			outerPixelBucket[position]=0;
		// iterate over the following
		//several thousand times (at least more times than # of pixels)
		#pragma omp for
		for (position = 0; position<totalIterations; position++)
		{
			// Create a temporary bucket array (one integer for each pixel
			//
			vector<int> tempBucket(NPIXELS,0);
			// Let C be a random point in the complex plane
			//
			c_r = rand() *randWidthFactor / RAND_MAX + -2.5;
			c_i = rand() * randHeightFactor / RAND_MAX + -1.0;
			// Trace the orbit of C, incrementing the temporary bucket 	that z falls in for each iteration
			z_r = 0.0;
			z_i = 0.0;
			n = 0;  //iterator
			modulus=0.0;
			while (modulus< escape_radius && n < max_iter)
			{
				z_temp = z_r;
				z_r = pow(z_r,2) - pow(z_i,2) + c_r;
				z_i = z_i*z_temp*2 + c_i;
				tempX=(2.5 + z_r) * widthFactor;
				tempY=(1 + z_i) * heightFactor;
				if (tempX < m_width && tempY < m_height)
					tempBucket[tempY*m_width + tempX] ++;
				n++;
				modulus=(pow(z_r,2) + pow(z_i,2));
			}
			// If Z is in the mandelbrot set, discard the temporary bucket

			// Else, merge the temporary bucket with the outer bucket array
			if (n <max_iter) 
			{
				for(tempX=0;tempX<NPIXELS;tempX++)
					innerPixelBucket[tempX]+=tempBucket[tempX];
			}
		// Parallelizing is not required, but will save you a lot of time.
		}
		for(position=0;position<NPIXELS;position++)
		{
			#pragma omp atomic
			outerPixelBucket[position]+=innerPixelBucket[position];
		}
		// Normalize the global bucket array by dividing each value	by the maximum value
		// Color each pixel however you wish
		//
		// Parallelizing this function is tricky. It helps to have a list of temporary bucket arrays
		// Which are merged after the computation has finished.
		
		#pragma omp single
		{
			for (position= 0; position<NPIXELS;position++)
			{
				if(outerPixelBucket[position]>maxValue)
					maxValue=outerPixelBucket[position];
			}
			maxValue=pow(maxValue,-1);
		}
		#pragma omp for
		for(position=0;position<NPIXELS;position++)
		{
			z_temp=(maxValue*outerPixelBucket[position]);
			r=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.4));
			g=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.7));
			b=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.6)); 
			bitmapPosition=position*4;
			color(&bitmapPosition,&r,&g,&b);
		}
	}
}
    

