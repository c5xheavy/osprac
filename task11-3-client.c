#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int msqid;
    char pathname[] = "task11-3-server.c";
    
    key_t key;
    int len, maxlen;

    struct mymsgbuf1 {
        long mtype;
        struct {
            pid_t client_pid;
	    double client_request;
        } request;
    } request_buf;

    struct mymsgbuf2 {
        long mtype;
        struct {
	    double server_response;
        } response;
    } response_buf;

    double input;
    scanf("%lf", &input);

    if ((key = ftok(pathname, 0)) < 0) {
        printf("[error task11-3-client.c]\tCan't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("[error task11-3-client.c]\tCan't get msqid\n");
        exit(-1);
    }

    request_buf.mtype = 1;
    request_buf.request.client_pid = getpid();
    request_buf.request.client_request = input;
    len = sizeof(request_buf.request);

    if (msgsnd(msqid, (struct msgbuf *) &request_buf, len, 0) < 0) {
        printf("[error task11-3-client.c]\tCan't send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    maxlen = sizeof(response_buf.response);
    if (len = msgrcv(msqid, (struct msgbuf *) &response_buf, maxlen, getpid(), 0) < 0) {
        printf("[error task11-3-client.c]\tCan't receive message from queue\n");
        exit(-1);
    }

    printf("[success task11-3-client.c]\n\tmessage type = %d\n\trequest = %lf\n\tresponse = %lf\n", request_buf.request.client_pid, request_buf.request.client_request, response_buf.response.server_response);

    return 0;
}
