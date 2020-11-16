#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

#define PERMS 0660

int main(void)
{
	int		id_sem[4], fd;
	sem_t	*sem1, *sem2, *sem3, *sem4;

	id_sem[0] = shmget(4568, sizeof(sem_t), IPC_CREAT | PERMS);
	id_sem[1] = shmget(4569, sizeof(sem_t), IPC_CREAT | PERMS);
	id_sem[2] = shmget(4570, sizeof(sem_t), IPC_CREAT | PERMS);
	id_sem[3] = shmget(4571, sizeof(sem_t), IPC_CREAT | PERMS);
	sem1 = (sem_t *) shmat(id_sem[0], NULL, 0);
	sem2 = (sem_t *) shmat(id_sem[1], NULL, 0);
	sem3 = (sem_t *) shmat(id_sem[2], NULL, 0);
	sem4 = (sem_t *) shmat(id_sem[3], NULL, 0);
	sem_init(sem1, 1, 0);
	sem_init(sem2, 1, 0);
	sem_init(sem3, 1, 0);
	sem_init(sem4, 1, 0);

	if (fork() == 0)
	{
		if (fork() == 0)
		{
			// Added the wait to test if the first fork was executed lastelym it sill run in the good order
			wait(NULL);
			printf("Creating test.txt and changing its permissions\n");
			if ((fd = open("./test.txt", O_WRONLY | O_CREAT )) == -1)
				exit(0);
			write(fd, "Hello World!\n", 13);
			close(fd);
			// Added the sleep in the code to be sure that the process were over. Could have used waitpid instead.
			sleep(1);
			sem_post(sem1);
			execl("/usr/bin/chmod", "chmod", "777", "./test.txt", (char*)NULL);			
		}
		else
		{
			sem_wait(sem1);
			sleep(1);
			sem_post(sem2);	
			execl("/usr/bin/ls", "ls", "-l", "./test.txt", (char*)NULL);			
		}
	}
	else
	{
		if (fork () == 0)
		{
			sem_wait(sem2);
			sleep(1);
			sem_post(sem3);	
			execl("/usr/bin/hexdump", "hexdump", "-C", "./test.txt", (char*)NULL);
		}
		else
		{
			if (fork () == 0)
			{
				sem_wait(sem3);
				sleep(1);
				printf("Deleting test.txt\n");
				sleep(1);
				sem_post(sem4);
				execl("/usr/bin/rm", "rm", "-f", "./test.txt", (char*)NULL);
			}
			else
			{
				sem_wait(sem4);
				exit(1);
			}
		}
	}
}
