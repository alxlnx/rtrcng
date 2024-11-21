/* 
  Создать программу(программы) для последовательного вычетания 1 двумя процессами
  из некоторого числа, записанного в разделяемой памяти.
  Очерёдность работы процессов регулируем при помощи семафора.
  Ход выполнения следующий:
  Открываем два терминала и запускаем в них созданную(ые) программы
  В одном из них вводим некоторое число.
  После чего обе программы начинают выводить по очереди уменьшенное на 1,
  полученное значение.
  Предусмотреть задержки для наглядности.

*/

#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define INPUT_SIZE 1024
#define SHMEM_SIZE 4096
#define AVAL 1
#define BVAL 2

/* Data structure for operating on semaphores */
union semnum 
{
	int val; /* Value for SETVAL */
	struct semid_ds * buf; /* Buffer for IPC_STAT, IPC_SET */
	unsigned short * array; /* Array for GETALL, SETALL */
} sem_arg;

/* This program will read a number from the terminal & get shmem & create sem set*/
int main(void)
{ 
  /* ---- Create shared memory ---- */
  /* Get a unique key */
  char pathname[]="cccc.c";
  key_t key;
  key = ftok(pathname, 0);

  /* Create shared memory */
  int shm_id = shmget(key, SHMEM_SIZE, IPC_CREAT | 0666);
  if (shm_id < 0)
	{
		fprintf (stderr, "shmget() error\n");
		return 1;
	}

  /* ---- Create a semaphore ---- */
  int sem_id = semget (key, 1,
	 		0666);
	if (sem_id == -1)
	{
		fprintf (stderr, "semget() error\n");
		exit(1);
	}

  unsigned short sem_vals[1]; /* Value to use with semnum.array */
	sem_arg.array = sem_vals;
  //printf ("Semaphore: %d\n", sem_id);

  char b_buff[100];
  int n = 1;
  /* ---- MAIN LOOP ---- */
  while(n>0) {
    /* Check the semaphore value to see whose turn it is */
    if ( semctl(sem_id, 0, GETALL, sem_arg) < 0 )
    {
		  fprintf (stderr, "semctl() GETALL error\n");
      printf("Errno = %d\n", errno);
		  exit(1);
	  }
    int sem_value = sem_arg.array[0];
    // printf("b: semval = %d\n", sem_value);
    sleep(1);
    if (sem_value == AVAL)
    /* Their turn */
    {
    } else if (sem_value == BVAL)
    // Our turn 
    {
      /* Get the value from memory */
      char* shm_buf = (char *) shmat (shm_id, NULL, 0);
      if (shm_buf == (char *)-1)
      {
        fprintf (stderr, "shmat() error\n");
        exit(1);
      }
      strcpy (b_buff, shm_buf);
      n = atoi(b_buff);
      /* Decrease it by 1 */
      n--;
      /* Put back in memory */
      snprintf( b_buff, sizeof(b_buff), "%d", n );
      strcpy(shm_buf, b_buff);
      /* Detach the memory */
      shmdt(shm_buf);
      /* Change the semaphore value */
      sem_vals[0] = AVAL;
      sem_arg.array = sem_vals;
      if (semctl(sem_id, 0, SETALL, sem_arg) < 0)
      {
        fprintf (stderr, "semctl() error on SETALL\n");
        return 1;
      }
      printf("b: n = %d\n", n);
    } else 
    {
      fprintf(stderr, "semval error, invalid value encountered");
      exit(1);
    }
  }
} 
