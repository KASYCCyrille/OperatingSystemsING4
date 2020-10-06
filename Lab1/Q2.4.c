#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t	pid, pid2;

	pid = fork();

	if (pid == 0)
	{
		printf("I'm the 1 child %i - PID: %i\n", getpid(), pid);
	
		pid = fork();
		if (pid != 0)
			printf("1Child process %i, created grand-child process %i\n", getpid(), pid);
		else
			printf("I'm the grand-child %i - PID: %i\n", getpid(), pid);
	}
	else
	{
		printf("I'm the parent %i - Created child process PID: %i\n", getpid(), pid);

		pid = fork();
		if (pid != 0)
			printf("I'm the parent %i - Created child process PID: %i\n", getpid(), pid);
		else
		{
			printf("I'm the 2 child %i - PID: %i\n", getpid(), pid);

			/* If we wanted to create a second grand-child process
			pid = fork();
			if (pid != 0)
				printf("2Child process %i created grand-child process %i\n", getpid(), pid);
			else
				printf("I'm the grand-child %i - PID: %i\n", getpid(), pid);
			*/
		}
	}
	return (0);
}
