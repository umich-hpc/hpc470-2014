#include <stdio.h>

main()
{
	int i, n = 1000000;
	float sum;

	sum = 0.0;
	for (i = 0; i < n; i++)
		sum += (float)i/n;

	printf("sum = %f\n", sum);

	sum = 0.0;
	for (i = n-1; i >= 0; i--)
		sum += (float)i/n;

	printf("sum = %f\n", sum);
}
