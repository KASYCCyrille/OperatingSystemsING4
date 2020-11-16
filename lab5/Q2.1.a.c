#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

#define KEY 4567
#define PERMS 0660


void	increment(int *ptr)
{
	int i, j;
	
	i = *ptr;
	j = -1;
	while (++j < 10)
	{
		i++;
		if(j == 5)
		{
			*ptr = i;
			wait(NULL);
		}
	}
	*ptr = i;
}


void	decrement(int *ptr)
{
	int i, j;

	i = *ptr;
	j = -1;
	while (++j < 10)
	{
		i--;
		if(j == 5)
		{
			*ptr = i;
			wait(NULL);
		}
	}
	*ptr = i;
}

void	setAt(int *ptr, int value)
{
	*ptr = value;
}

int main(void)
{
	int		id, *ptr;
	int		id_sem;
	sem_t	*sem, *sem1, *sem2;

	id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
	ptr = (int *) shmat(id, NULL, 0);
	*ptr = 65;

	id_sem = shmget(4568, sizeof(sem_t), IPC_CREAT | PERMS);
	sem = (sem_t *) shmat(id_sem, NULL, 0);

	sem_init(sem, 1, 0);

	if (fork() == 0)
	{
		printf("Increment value before: %d\n", *ptr);
		increment(ptr);
		printf("Increment value after: %d\n", *ptr);
		sem_post(sem);
	}
	else
	{
		sem_wait(sem);
		sem_init(sem, 1, 0);
		if (fork () == 0)
		{
			printf("SetAt value before: %d\n", *ptr);
			setAt(ptr, 42);
			printf("SetAt value after: %d\n", *ptr);
			sem_post(sem);
		}
		else
		{
			sem_wait(sem);
			printf("Decrement value before: %d\n", *ptr);
			decrement(ptr);
			printf("Decrement value after: %d\n", *ptr);
		}
	}
}
