#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	for (int i = 0; i < 1000; i++){
		printf("%d:%ld\n", i, random());
	}

	return 0;
}
