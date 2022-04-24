#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t process_id = fork();
	if (process_id < 0) {
		printf("Error has caused by creating new process\n");
	}
	else {
		pid_t pid = getpid();
		pid_t ppid = getppid();
		if (process_id == 0) {
			printf("Process-child:\n\tPID: %i\n\tPPID: %i\n", pid, ppid);
		} else {
			printf("Process-parent:\n\tPID: %i\n\tPPID: %i\n\tChildPID: %i\n", pid, ppid, process_id);
		}
	}
	return 0;
}

