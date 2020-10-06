#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <unistd.h>

#define KEY 4567
#define PERMS 0660

#define A 10
#define B 5
#define C 10
#define D 5
#define E 10
#define F 5
#define G 5
#define H 5

clock_t times(struct tms *buf);

int main(void) 
{
	int 			id, pid, pid2, status, iterateur;
	int				*tab;
	struct tms 		start, end;
	struct rusage	rstart, rend;

	times(&start);
	getrusage(RUSAGE_SELF, &rstart);
	for (iterateur = 0; iterateur < 100; iterateur++)
	{
		id = shmget(KEY, 6*sizeof(int), IPC_CREAT | PERMS);	
		tab = (int *) shmat(id, NULL, 0);
		if (!(pid = fork()))
		{
			if (!(pid2 = fork()))
			{
				tab[0] = A + B;
				tab[3] = G + H;
				exit(0);
			}
			else
			{
				while(1)
				{
					waitpid(pid2, &status, WUNTRACED);
					if (WIFEXITED(status))
					{
						tab[5] = tab[0] + tab[3];
						exit(0);
					}
				}
			}
		} 
		else 
		{
			if (!(pid2 = fork()))
			{
				tab[1] = C * D;
				tab[2] = E - F;
				exit(0);
			}
			else
			{
				waitpid(pid2, &status, WUNTRACED);
				if (WIFEXITED(status))
				{
					if (!(pid2 = fork()))
					{
						tab[4] = tab[1] / tab[2];
						exit(0);
					}
					else
					{
						waitpid(pid2, &status, WUNTRACED);
						if (WIFEXITED(status))
						{
							waitpid(pid, &status, WUNTRACED);
							if (WIFEXITED(status))
							{
								printf("%d - %d\n", iterateur, tab[5] - tab[4]);
								shmctl(id, IPC_RMID, NULL);
							}
						}
					}
				}
			}
		}
	}
	times(&end);
	getrusage(RUSAGE_CHILDREN, &rend);
	
	printf("\n  Fork usage:\nTime: %ldusec\nNb swap: %ld\nNb block read: %ld\nNb block write: %ld\nNb message sent: %ld\nNb message get: %ld\nNb signal get: %ld\n",
		   ( 
			   (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec)
		   ),
		   (rend.ru_nswap - rstart.ru_nswap),
		   (rend.ru_inblock - rstart.ru_inblock),
		   (rend.ru_oublock - rstart.ru_oublock),
		   (rend.ru_msgsnd - rstart.ru_msgsnd),
		   (rend.ru_msgrcv - rstart.ru_msgrcv),
		   (rend.ru_nsignals - rstart.ru_nsignals)
		);
}
