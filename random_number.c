#include "random_number.h"

//get number between 0 and 1
int get_random_number (double* num)
{
	time_t cur_time = time(NULL);
	if (cur_time == (time_t)-1) return 1;
	srandom((unsigned int)cur_time);
	long int temp_num = random();
	char state[LONG_BITS + 1];
	int ret;
	if ((ret = snprintf(state, sizeof(state), "%ld", temp_num)) == -1 || ret + 1 > sizeof(state)) return 2;
	if (cur_time == (time_t)-1) return 1;
	initstate((unsigned int)cur_time, state, sizeof(state) - 1);
	if (setstate(state) == NULL) return 3;
	if (cur_time == (time_t)-1) return 1;
	srandom(cur_time);
	*num = 1.0 * random() / (RAND_MAX + 1);

	return 0;
}
