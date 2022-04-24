#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid = getpid();
	pid_t ppid = getppid();

	printf("PID: %i\nPPID: %i\n", pid, ppid);

	return 0;
}

