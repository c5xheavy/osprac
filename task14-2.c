#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
  printf("\nReceive signal %d, ", nsig);
  if (nsig == 2) {
    printf("CTRL-C pressed\n");
  }
  if (nsig == 3) {
    printf("CTRL-4 pressed\n");
  }
}

int main(void) {

  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);

  while(1);

  return 0;
}
