#include "Mandelbrot.h"

void Mandelbrot::gen_fractal()
{
	const unsigned int height = get_height();
	const unsigned int width = get_width();
	const unsigned int NPIXELS=width*height;
	const int STARTSUBSAMPLEX=-1*SUBSAMPLEX;
	const int STARTSUBSAMPLEY=-1*SUBSAMPLEY;
	const double MAX = MAXITER;
	const double log2=log(2.0);
	const double subsampleXFactor=1/(width*TOTALSUBSAMPLESX);
	const double subsampleYFactor=1/(NPIXELS*TOTALSUBSAMPLESY);
	const double subsampleXStartOffset=STARTSUBSAMPLEX*subsampleXFactor;
	const double subsampleYStartOffset=STARTSUBSAMPLEY*subsampleYFactor;
	const float colorScalar=1/255;
	const float escape_radius=2<<16;
	const double sinFactor=MAX/escape_radius;
	unsigned int position,bitmapPosition;
	double subsample_x,subsample_y;
	double z_r,z_i,z_temp,n,position_c_r,position_c_i,c_r,c_i,r,g,b,rTotal,gTotal,bTotal;
	float modulus;
	#pragma omp parallel for private(position,bitmapPosition,subsample_x,subsample_y,n,z_r,z_i,z_temp,position_c_r,position_c_i,c_i,c_r,r,g,b,rTotal,gTotal,bTotal,modulus)
	for(position=0;position<NPIXELS;position++)
	{
		position_c_r=position%width; //simplest way to get x
		position_c_i=position-c_r; //simplest way to get y
		position_c_i = (position_c_i/NPIXELS)*3 - 1.5;
		position_c_r = (position_c_r/width)*3 - 2.25;
		c_r = position_c_r + subsampleXStartOffset;
		c_i = position_c_i + subsampleYStartOffset;
		rTotal=BLACK;
		gTotal=BLACK;
		bTotal=BLACK;
		for(subsample_y=STARTSUBSAMPLEY;subsample_y<SUBSAMPLEY;subsample_y++)
		{
			for(subsample_x=STARTSUBSAMPLEX;subsample_x<SUBSAMPLEX;subsample_x++)
			{
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
					z_temp= log(n+1.5-log( log(modulus) / log2 ) / log2);
					//z_temp=z_temp/(MAX);//z_temp=(mu/MAX);
					z_temp*=abs(sin(sinFactor*z_r/n)); //Makes image a lot more interesting swap n and MAX for interesting results
					z_temp=abs(z_temp);
					if(z_temp<1)
						z_temp=pow(z_temp,-1);
					r=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.4));
					if(r<1)
						r*=MAXCOLOR;
					g=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.7));
					if(g<1)
						g*=MAXCOLOR;
					b=MAXCOLOR-MAXCOLOR*(pow(z_temp,-0.6));
					if(b<1)
						b*=MAXCOLOR;
					rTotal+=r;
					gTotal+=g;
					bTotal+=b;
				}
				c_r+=subsampleXFactor;
			}
			c_i+=subsampleYFactor;
		}
		rTotal/=TOTALSUBSAMPLES;
		gTotal/=TOTALSUBSAMPLES;
		bTotal/=TOTALSUBSAMPLES;
		bitmapPosition=4*position;
		color(&bitmapPosition,&rTotal,&gTotal,&bTotal);
	}

}   
