#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)
{
  pthread_t thid;
  thid = pthread_self();

  a = a + 1;

  printf("[thread %lu] calculation result: %d\n", thid, a);
  return NULL;
}

int main()
{
  pthread_t main_thid, thid1, thid2;
  int result;

  result = pthread_create(&thid1, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("[error] on first thread create, fault code: %d\n", result);
    exit(-1);
  }

  printf("[thread %lu] created\n", thid1);

  result = pthread_create(&thid2, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("[error] on second thread create, fault code: %d\n", result);
    exit(-1);
  }

  printf("[thread %lu] created\n", thid2);

  main_thid = pthread_self();

  a = a + 1;

  printf("[thread %lu] calculation result: %d\n", main_thid, a);

  pthread_join(thid1, (void **)NULL);
  pthread_join(thid2, (void **)NULL);

  return 0;
}
