#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main (void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1){
		fprintf(stderr, "gettimeofday failed.\n");
		return 1;
	}
	unsigned int ui;
	ui = (unsigned int)tv.tv_sec * (unsigned int)tv.tv_usec + (unsigned int)tv.tv_sec + (unsigned int)tv.tv_usec;
	srand(ui);
	for (int i = 0; i < 1000; i++){
		printf("%d:%ld\n", i, rand());
	}

	return 0;
}
