#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv) 
{
	int id;
	int i;
	int *ptr;

	/*
	** Print the Shared Memory Segments stored on the computer
	*/
	system("ipcs -m");
	
	/*
	** Declare a new shared segment in the memory. 
	** That segment have the size of an int, and its permission are set so the 
	** "owner" and the users that are in the same group (6 = 4 + 2) can write
	** and read on it (first and second column filled) but not execute (0 on the
	** last column). 
	** Then shmget return the shmid of that declared segment which will allow us
	** to write/read it (a bit like files descriptors let us do with files).
	*/
	id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
	system("ipcs -m");
	
	/*
	** Get the memory address of the shared segment so the program can access it.
	*/
	ptr = (int *) shmat(id, NULL, 0);
	*ptr = 54;
	i = 54;
	if (fork() == 0) {
		/*
		** Change the values stored inside the local variable (i) and inside the
		** shared one (through *ptr), from the child process,  and then print them.
		*/
		(*ptr)++;
		i++;
		printf("H - Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
		exit(0);
	} 
	else 
	{
		/*
		** That just put the program in IDLE mode so the child process execute first.
		*/
		wait(NULL);
		printf("B - Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
		
		/*
		** Free the shared segment declared earlier
		*/
		shmctl(id, IPC_RMID, NULL);
	}
}
