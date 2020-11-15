#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY 4567
#define PERMS 0660

int main(void)
{
	int id, j, i, *ptr;

	id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
	ptr = (int *) shmat(id, NULL, 0);
	*ptr = 65;
	j = -1;
	if (fork() == 0)
	{
		i = *ptr;
		while (++j < 10)
		{
			i++;
			if(j == 5)
			{
				*ptr = i;
				sleep(1);
			}
		}
		printf("Children value before: %d\n", *ptr);
		*ptr = i;
		printf("Children value after: %d\n", *ptr);
	}
	else
	{
		i = *ptr;
		while (++j < 10)
		{
			i--;
			if(j == 5)
			{
				*ptr = i;
				sleep(1);
			}
		}
		printf("Parent value before: %d\n", *ptr);
		*ptr = i;
		printf("Parent value after: %d\n", *ptr);
	}
}
