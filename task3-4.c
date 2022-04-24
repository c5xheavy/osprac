#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[])
{
	pid_t process_id = fork();
	if (process_id < 0) {
		printf("Error has caused by creating new process\n");
		exit(-1);
	} else if (process_id == 0) {
		printf("Child\nCalling task1-1.c\n");
		(void) execle("/bin/cat", "/bin/cat", "task1-1.c", 0, envp);
		printf("Error has caused by calling program\n");
		exit(-1);
	} else {
		printf("Parent\n");
	}
	return 0;
}

