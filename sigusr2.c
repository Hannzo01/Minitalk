#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0) //child process
	{

	}
	else //parent process
	{
		int x;
		printf("what os the result of 3 x 5 :")
		scanf("%d", &x);
	}

	return (0);
}