#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	printf("before\n");
	usleep(1000);
	printf("after\n");
}