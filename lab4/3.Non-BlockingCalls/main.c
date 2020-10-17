#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

int main() 
{
	int i;
	char buf[100];

	//fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);				/* Change the flags of the standard input (stdin) so reading from id doesn't block the rest of the program. */
	for (i = 0; i < 10; i++) 
	{
		int nb;
		nb = read(STDIN_FILENO, buf, 100); 					/* Read the next 100 characters that will be written on stdin (or until the user hit enter) */
		printf("nwrites = %d\terror = %d\n", nb, errno); 	/* Write in the standard output the number of characters read during the previous operation, and the error number if there is one. */
	}
}
