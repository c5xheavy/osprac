#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	for (int i = 0; i < argc; ++i) {
		printf("{argv} %s\n", argv[i]);
	}
	for (int i = 0; envp[i] != 0; ++i) {
		printf("{envp} %s\n", envp[i]);
	}
	return 0;
}

