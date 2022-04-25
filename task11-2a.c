#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int msqid;
  char pathname[] = "task11-2a.c";

  key_t  key;
  int i, len, maxlen;

  struct
  {
    long mtype;
    struct {
        short sinfo;
        float finfo;
    } info;
  } mybuf;

  if ((key = ftok(pathname, 0)) < 0) {
    printf("[error task11-2a.c]\tCan\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("[error task11-2a.c]\tCan\'t get msqid\n");
    exit(-1);
  }

  for (i = 1; i <= 5; i++) {
    mybuf.mtype = 1;
    mybuf.info.sinfo = i;
    mybuf.info.finfo = i + 0.5;
    len = sizeof(mybuf.info);

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("[error task11-2a.c]\tCan\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }
  }

  for (i = 1; i <= 5; i++) {
    maxlen = sizeof(mybuf.info);

    if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) < 0) {
      printf("[error task11-2a.c]\tCan\'t receive message from queue\n");
      exit(-1);
    }

    printf("[success task11-2a.c]\tmessage type = %ld, sinfo = %i, finfo = %f\n", mybuf.mtype, mybuf.info.sinfo, mybuf.info.finfo);
  }
  
  msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

  return 0;
}

