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
#define B 10
#define C 5
#define D 5

int main(void) 
{
	int 	id;
	int		*tab;

	id = shmget(KEY, 2*sizeof(int), IPC_CREAT | PERMS);	
	tab = (int *) shmat(id, NULL, 0);
	
	if (!fork())
	{
		tab[0] = (A + B);
		exit(0);
	} 
	else 
	{
		if(!fork())
		{
			tab[1] = (C + D);
		}
		else
		{
			wait(NULL);
			printf("%d", tab[0] - tab[1]);
			shmctl(id, IPC_RMID, NULL);
		}
	}
}
