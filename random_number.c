#include "random_number.h"
#include <limits.h>

//get number between 0 and 1
int get_random_number (long int *num)
{
	struct timespec ts;
	unsigned int rand;
	double multiple;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) return 1;
	rand = ts.tv_sec * ts.tv_nsec + ts.tv_sec + ts.tv_nsec;
	srandom(rand);
	multiple = 1.0 * random() / (RAND_MAX + 1LL);
	*num = multiple * LONG_MAX;

	return 0;
}
