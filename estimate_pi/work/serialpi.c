#include <stdio.h>
#include <time.h>
#include <stdlib.h>

main(int argc, char* argv[])
{
	long long niter = 1000000000;
	double x,y;						//x,y value for the random coordinate
	long long i;
        long long count=0;					//Count holds all the number of how many good coordinates
	double z;						//Used to check if x^2+y^2<=1
	double pi;						//holds approx value of pi
	time_t t;
	
	printf("niter: %lld = %.1e\n", niter, (float)niter);			
	srand48(((unsigned)time(&t)));				//Give rand() a seed value

	for (i=1; i<=niter; ++i)				//main loop
	{
		x = (double)drand48();//RAND_MAX;		//gets a random x coordinate
		y = (double)drand48();//RAND_MAX;		//gets a random y coordinate
		z = ((x*x)+(y*y));				//Checks to see if number in inside unit circle
		if (z<=1)
		{
			++count;				//if it is, consider it a valid random point	
		}	
	}			
	pi = ((double)count/(double)niter)*4.0;			//p = 4(m/n)
	printf("Pi: %f\n", pi);			
}
