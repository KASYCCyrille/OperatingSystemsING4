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
	int		id_sem[2];
	sem_t	*sem1, *sem2;

	id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
	ptr = (int *) shmat(id, NULL, 0);
	*ptr = 65;

	id_sem[0] = shmget(4568, sizeof(sem_t), IPC_CREAT | PERMS);
	id_sem[1] = shmget(4569, sizeof(sem_t), IPC_CREAT | PERMS);
	sem1 = (sem_t *) shmat(id_sem[0], NULL, 0);
	sem2 = (sem_t *) shmat(id_sem[1], NULL, 0);

	sem_init(sem1, 1, 0);
	if (fork() == 0)
	{
		printf("Increment value before: %d\n", *ptr);
		increment(ptr);
		printf("Increment value after: %d\n", *ptr);
		sem_post(sem1);
	}
	else
	{
		sem_wait(sem1);
		sem_init(sem1, 1, 0);
		sem_init(sem2, 1, 0);
		if (fork () == 0)
		{
			sem_wait(sem1);
			printf("SetAt value before: %d\n", *ptr);
			setAt(ptr, 42);
			printf("SetAt value after: %d\n", *ptr);
			sem_post(sem2);
		}
		else
		{
			sem_wait(sem2);
			printf("Decrement value before: %d\n", *ptr);
			decrement(ptr);
			printf("Decrement value after: %d\n", *ptr);
			sem_post(sem1);


			shmctl(id, IPC_RMID, NULL);
			shmctl(id_sem[0], IPC_RMID, NULL);
			shmctl(id_sem[1], IPC_RMID, NULL);
		}
	}
}
