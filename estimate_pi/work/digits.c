#include <stdio.h>

main()
{
	int d;

	printf("  12345678901234567890\n");
	for (d=3; d<8; d+=4) {
		printf("%.64Lf\n", (long double)1/d);
		printf("%.64lf\n", (double)1/d);
		printf("%.64f\n", (float)1/d);
	}
}
