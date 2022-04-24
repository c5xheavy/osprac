#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>


// S = 0
//
// For N
//
//  Parent:
//  write()
//  A(S,2)
//  Z(S)
//  read()
//
//  Child:
//  D(S,1)
//  read()
//  write()
//  D(S,1)
//

int main()
{
  int fd[2], result;
  size_t size;
  char  message[16];

  char pathname[] = "task9-3.c";
  key_t key;
  struct sembuf mybuf;
  int semid;

  int N;
  scanf("%d", &N);

  if (pipe(fd) < 0) {
    printf("[error]\tcan\'t open pipe\n");
    exit(-1);
  }

  if ((key = ftok(pathname, 0)) < 0) {
    printf("[error]\tcan\'t generate key\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("[error]\tcan\'t get semaphore set\n");
    exit(-1);
  }

  result = fork();
  if (result < 0) {
    printf("[error]\tcan\'t fork child\n");
    exit(-1);
  }

  for (int i = 0; i < N; ++i) {
    if (result > 0) {
      size = write(fd[1], "Parent", 16);
      if (size != 16) {
        printf("[parent error]\tcan\'t write all string to pipe\n");
        exit(-1);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op = 2;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("[parent error]\tcan\'t wait for condition\n");
        exit(-1);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op = 0;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("[parent error]\tcan\'t wait for condition\n");
        exit(-1);
      }

      size = read(fd[0], message, 16);
      if (size != 16) {
        printf("[parent error]\tcan\'t read string from pipe\n");
        exit(-1);
      }

      printf("[parent success %d]\tread from pipe: %s\n", i, message);
    } else {

      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("[parent error]\tcan\'t wait for condition\n");
        exit(-1);
      }

      size = read(fd[0], message, 16);
      if (size != 16) {
        printf("[child error]\tcan\'t read string from pipe\n");
        exit(-1);
      }

      printf("[child success %d]\tread from pipe: %s\n", i, message);

      size = write(fd[1], "Child", 16);
      if (size != 16) {
        printf("[child error]\tcan\'t write all string to pipe\n");
        exit(-1);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("[parent error]\tcan\'t wait for condition\n");
        exit(-1);
      }
    }
  }

  if (close(fd[0]) < 0) {
    printf("[error]\tcan\'t close reading side of pipe\n");
    exit(-1);
  }

  if (close(fd[1]) < 0) {
    printf("[error]\tcan\'t close writing side of pipe\n"); 
    exit(-1);
  }

  return 0;
}
