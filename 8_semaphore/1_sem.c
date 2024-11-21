#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Написать комментарии, отладить работу
int main(int argc, char *argv[], char *envp[])
{
  int   semid;
  char pathname[]="1_sem.c";
  key_t key;
  struct sembuf mybuf;
  
  key = ftok(pathname, 0);

  const int num_of_sem = 1;
  const int permbits = 0666;

  if((semid = semget(key, num_of_sem, permbits | IPC_CREAT)) < 0)
  {
    printf("Can\'t create semaphore set\n");
    exit(-1);
  }
  
  // semctl(semid, 0, )

  /* Specify operation to be performed on the semaphore */
  mybuf.sem_num = 0;  // number of sem to run the op on
  mybuf.sem_op  = 1; // -1 will fail since semaphores are probably init with semval = 0 => |sem_op|>semval => sleep until...
  mybuf.sem_flg = SEM_UNDO;
  
  // semget and semid refer to a semaphore SET, each semaphore in left unitialized
  const int operations_len = 1; // since there is only mybuf
  if(semop(semid, &mybuf, operations_len) < 0)
  {
    printf("Can\'t wait for condition\n");
    exit(-1);
  }  
    
  printf("The condition is present\n");
  return 0;
}