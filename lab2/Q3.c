#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY 4567
#define PERMS 0660

#define A 10
#define B 5
#define C 10
#define D 5
#define E 10
#define F 5

int main(void) 
{
	int 	id, pid, status;
	int		*tab;

	id = shmget(KEY, 4*sizeof(int), IPC_CREAT | PERMS);	
	tab = (int *) shmat(id, NULL, 0);
	if (!(pid = fork()))
	{
		tab[1] = (C - D);
		tab[0] = (A + B);
		exit(0);
	} 
	else 
	{
		while(1)
		{
			waitpid(pid, &status, WUNTRACED);
			if (WIFEXITED(status))
			{
				if (!(pid = fork()))
				{
					tab[2] = (E + F);
					tab[3] = tab[0] * tab[1];
					exit(0);
				}
				else
				{
					while(1)
					{
						waitpid(pid, &status, WUNTRACED);
						if (WIFEXITED(status))
						{
							printf("%d", tab[3] + tab[2]);
							shmctl(id, IPC_RMID, NULL);
							exit(0);
						}
					}
				}
			}
		}
	}
}
