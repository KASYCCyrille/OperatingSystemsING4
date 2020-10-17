#include <stdio.h>
#include <unistd.h>

int main (void)
{
	int i = 5;
	if(!fork())
	{
		execl("/usr/bin/firefox", "firefox", (char*)NULL);

		i++;
		printf("%d\n", i);
	}
	else
	{
		printf("Process id: %i\n", getpid());
	}
}
