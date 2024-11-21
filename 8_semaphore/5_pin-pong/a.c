#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
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
  /* Read the number to decrase */
  printf("Enter a POSITIVE decimal number: ");

  char input[INPUT_SIZE];
  fgets(input, sizeof(input), stdin);
  int n = atoi(input);

  /* Check input validity */
  if (n < 0)
  {
    fprintf(stderr, "Error: input number less than 0\n");
    exit(1);
  }

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

  /* ---- Put the entered number in memory ---- */
  /* Allocate shared memory */
	char* shm_buf = (char *) shmat (shm_id, NULL, 0);
	if (shm_buf == (char *)-1)
	{
		fprintf (stderr, "shmat() error\n");
		exit(1);
	}

  /* Convert the number to string, put in memory & detach it */
  // Maybe no need to convert to char here?
  char output[100];
  snprintf( output, sizeof(output), "%d", n );
	strcpy (shm_buf, output);
  shmdt(shm_buf);


  /* ---- Create a semaphore ---- */
  int sem_id = semget (key, 1,
	 		0666 | IPC_CREAT);
	if (sem_id == -1)
	{
		fprintf (stderr, "semget() error\n");
		exit(1);
	}

  //printf ("Semaphore: %d\n", sem_id);
  
  /* If the semaphore value is set to AVAL, then **a** is to decrease the number & write it into shmem
     If set to BVAL, then **b** is to ...
     Otherwise we have an error.
   */
  
  /* Initialize the semval of the semaphore */
  unsigned short sem_vals[1]; /*  */
  sem_vals[0] = AVAL;
	sem_arg.array = sem_vals;

  if (semctl(sem_id, 0, SETALL, sem_arg) < 0)
  {
    fprintf (stderr, "semctl() error on SETALL\n");
		return 1;
  }

  char a_buff[100];
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
    // printf("a: semval = %d\n", sem_value);
    
    sleep(1);
    if (sem_value == AVAL)
    /* Our turn */
    {
      /* Get the value from memory */
      char* shm_buf = (char *) shmat (shm_id, NULL, 0);
      if (shm_buf == (char *)-1)
      {
        fprintf (stderr, "shmat() error\n");
        exit(1);
      }
      strcpy (a_buff, shm_buf);
      n = atoi(a_buff);
      /* Decrease it by 1 */
      n--;
      /* Put back in memory */
      snprintf( a_buff, sizeof(a_buff), "%d", n );
      strcpy(shm_buf, a_buff);
      /* Detach the memory */
      shmdt(shm_buf);
      /* Change the semaphore value */
      sem_vals[0] = BVAL;
      sem_arg.array = sem_vals;
      if (semctl(sem_id, 0, SETALL, sem_arg) < 0)
      {
        fprintf (stderr, "semctl() error on SETALL\n");
        return 1;
      }
      if (n != -1) 
      {
        printf("a: n = %d\n", n);
      }
    } else if (sem_value == BVAL)
    {
      // Their turn
    } else 
    {
      fprintf(stderr, "semval error, invalid value encountered");
      exit(1);
    }
  }

	shmctl (shm_id, IPC_RMID, NULL); /* Remove the shared memory */
} 
