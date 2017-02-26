#include "assist.h"
#include "random_number.h"

int main (void)
{
	for (int i = 0; i < 1000; i++){
		long int  num;
		if (get_random_number(&num)) err("get_random_number err.");
		printf("random number:%ld\n", num);
	}
}
