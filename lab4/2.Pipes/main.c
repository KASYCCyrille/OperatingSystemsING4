#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int		pipefd[2];
	pid_t	cpid;
	char	buf;

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) {		/* Child reads from pipe */
		close(pipefd[1]); 	/* Close unused write end */
		wait(NULL);
		
		dup2(pipefd[0], 0);
		execl("/bin/more", "more", (char*)NULL);
	}
	else {					/* Parent writes argv[1] to pipe */
		close(pipefd[0]);	/* Close unused read end */
		dup2(pipefd[1], 1);
		execl("/bin/ps", "ps", "aux", (char*)NULL);
	}
}
