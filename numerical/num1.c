#include <stdio.h>

main()
{
	int i, n = 1000000;
	float sum = 0.0;

	for (i = 0; i < n; i++)
		sum += 0.1;

	printf("sum = %f\n", sum);
}
