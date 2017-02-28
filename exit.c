#include "assist.h"

int globvar = 6;

int main (void)
{
	pid_t pid;
	int i;
	int var;
	char buf[1000];
	var = 88;
	printf("before vfork\n");
	if ((pid = fork()) == -1) p_err("fork err.");
	else if (pid == 0){
		globvar++;
		var++;
		_exit(0);
		//fclose(stdout);
		//return 0;
	}
	i = printf("pid = %ld. glob = %d, var = %d\n", (long)getpid(), globvar, var);
	sprintf(buf, "%d\n", i);
	write(STDOUT_FILENO, buf, strlen(buf));
}
