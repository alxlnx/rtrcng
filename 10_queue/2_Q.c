//написать программу получающую в качестве параметров два номера. Первый номер это 
//номер для получения сообщений, второй номер для передачи сообщений. Можно  
//запустить несколько экземпляров такой программы и они все будут обмениваться  
//сообщениями между собой по номерам.
//Всё это нужно реализовать через одну очередь. 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define MESSAGE_LENGTH 255

int main(int argc, char* arg[])
{
  /* Parse input */
  if (argc > 3)
  {
    fprintf(stderr, "Error: too many input arguments");
    exit(1);
  } else if (argc < 3)
  {
    fprintf(stderr, "Error: too few input arguments, submit two");
    exit(1);
  }
  long rcv_num = atoi(arg[1]);
  long snd_num = atoi(arg[2]);
  // printf("%d, %d", rcv_num, snd_num);

  /* Setup msg queue */
  int msqid;
  char pathname[]="2_Q.c";
  key_t  key;
  struct mymsgbuf
  {
    long mtype;
    char mtext[MESSAGE_LENGTH];
  } mybuf;
    
  key = ftok(pathname, 0);
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
  {
    fprintf(stderr, "Error: msgget() %d", errno);
  }
  // msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
  
  /* Fork this process */
  int pid = fork();
  if (pid < 0)
  {
    fprintf(stderr, "Error: fork() %d", errno);
  } else if (pid == 0)
  {
    /* Child process.
      один из процессов проверяет очередь на предмет наличия в ней сообщений,
      адресованных данному терминалу и выводит их на экран
    */
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
      fprintf(stderr, "Error: msgget() %d", errno);
    }

    int rcv_len;
    for(;;)
    {
      if (( rcv_len = msgrcv(msqid, (struct msgbuf *) &mybuf, MESSAGE_LENGTH, rcv_num, 0)) < 0)
      {
        printf("Can\'t receive message from queue, %d\n", errno);
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(1);
      }
      
      printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mtext);
    }
  } else 
  {
    /* Parent here, with pid set to child id 
       второй процесс ожидает ввода с клавиатуры и отправляет сообщения,
       встретив символ перевода строки 
    */
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
      fprintf(stderr, "Error: msgget() %d", errno);
    }

    char input_string[MESSAGE_LENGTH];
    for (;;)
    {
      // scanf("%[^\n]", input_string);
      // scanf("%s\n", input_string);
      // scanf fucking sucks for this
      fgets(input_string, sizeof(input_string), stdin);
        
      mybuf.mtype = snd_num;
      strcpy(mybuf.mtext, input_string);
      // fprintf(stderr, "Sent %s", mybuf.mtext);
      if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.mtext), 0) < 0)
      {
        printf("Can\'t send message to queue %d\n", errno);
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(1);
      }

    }
  }
}