#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#define SEED 35791246

int main(int argc, char* argv[])
{
	long long niter = 1000000000;			
	int myid;							//hold's process's rank id
	int nodenum;

	MPI_Init(&argc, &argv);						//Start MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);				//get rank of node's process
	MPI_Comm_size(MPI_COMM_WORLD, &nodenum);

	if (argc > 1)
	{
		niter = atoll(argv[1]);
		if (niter <= 0)
		{
			if (myid == 0)
				printf("Invalid number of iterations specified\n");
			MPI_Finalize();
			exit(1);
		}
	}

	niter /= (nodenum-1);

	if (myid == 0)							//if root process
	{
		long long finalcount = 0;
		long long finalniter = 0;
		double pi;						//holds approx value of pi
		int i;
		long long count;

		printf("Using %lld = %.1e iterations per rank on %d of %d ranks\n", niter, (float)niter, nodenum-1, nodenum);

		for(i=1; i<nodenum; ++i)
		{
			MPI_Recv(&count, nodenum, MPI_LONG_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("rank 0 received count=%lld from rank %d\n", count, i);

			finalcount += count;
			finalniter += niter;
		}

		printf("finalcount=%lld, finaliter=%lld\n", finalcount, finalniter);

		pi = ((double)finalcount/(double)finalniter)*4.0;	//p = 4(m/n)
		printf("Pi: %.16f\n", pi);				//Print the calculated value of pi
		
	}
	else								//if not root process
	{
		double x,y;						//x,y value for the random coordinate
		long long ii, count=0;					//Count holds all the number of how many good coordinates

		srand(SEED*myid*time(NULL));				//Give rand() an unique seed value

		for (ii=1; ii<=niter; ++ii)				//main loop
		{
			x = ((double)rand())/RAND_MAX;			//gets a random x coordinate
			y = ((double)rand())/RAND_MAX;			//gets a random y coordinate
			if (x*x+y*y <= 1)				//Checks to see if number in inside unit circle
				count++;				//if it is, consider it a valid random point
		}

		MPI_Send(&count, 1, MPI_LONG_LONG, 0, myid, MPI_COMM_WORLD);
	}

	MPI_Finalize();							//Close the MPI instance
	return 0;
}
