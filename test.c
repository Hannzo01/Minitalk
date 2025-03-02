#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>


int main(int argc, char *argv[])
{
	int pid = fork();
	if (pid == 0)  //child process
	{
		while (1)
		{
			printf("test\n");
			fflush(stdout); // forces the buffer to be written to the output immediately.
			printf("text here\n");
			fflush(stdout); 
			usleep(5000);
		}
	}
	else // parent process
	{
		kill(pid, SIGKILL); //Kill the child process with SIGKILL (9)
		sleep(1);
		wait(NULL);
	}

	return (0);
}