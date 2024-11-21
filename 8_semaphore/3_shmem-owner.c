#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHMEM_SIZE	4096
#define SH_MESSAGE	"Hello World!\n"

#define SEM_KEY		2007
#define SHM_KEY		2007
// Написать комментарии, отладить работу

union semnum 
{
	int val; /* Value for SETVAL */
	struct semid_ds * buf; /* Buffer for IPC_STAT, IPC_SET */
	unsigned short * array; /* Array for GETALL, SETALL */
} sem_arg;


int main (void)
{
  char pathname[]="1_sem.c";
  key_t key;
  key = ftok(pathname, 0);

	int shm_id, sem_id;
	char* shm_buf; /* shared mem buffer */
	int shm_size;  /* shared mem size */

	struct shmid_ds ds; /* DS describing the shared mem */
	struct sembuf sb[1]; /* Operation descriptions for semaphores */
	unsigned short sem_vals[1]; /*  */
	
	//shm_id = shmget (key, SHMEM_SIZE,
	//		IPC_CREAT | IPC_EXCL | 0600);
  shm_id = shmget (key, SHMEM_SIZE,
			            IPC_CREAT | 0600);

	if (shm_id == -1) 
	{
		fprintf (stderr, "shmget() error\n");
		return 1;
	}

	// sem_id = semget (key, 1,
	// 		0600 | IPC_CREAT | IPC_EXCL);
  sem_id = semget (key, 1,
	 		0600 | IPC_CREAT);

	if (sem_id == -1)
	{
		fprintf (stderr, "semget() error\n");
		return 1;
	}

	printf ("Semaphore: %d\n", sem_id);
	sem_vals[0] = 1;
	sem_arg.array = sem_vals;

  /* Perform an op on the semaphore set */
	if (semctl (sem_id, 0, SETALL, sem_arg) == -1)
	{
		fprintf (stderr, "semctl() error\n");
		return 1;
	}

  /* Allocate shared memory */
	shm_buf = (char *) shmat (shm_id, NULL, 0);
	if (shm_buf == (char *) -1)
	{
		fprintf (stderr, "shmat() error\n");
		return 1;
	}

  /* Copy infromation about shm_id to smhid_ds buf */
	shmctl (shm_id, IPC_STAT, &ds);
	
	shm_size = ds.shm_segsz;
	if (shm_size < strlen (SH_MESSAGE))
	{
		fprintf (stderr, "error: segsize=%d\n", shm_size);
		return 1;
	}
	
	strcpy (shm_buf, SH_MESSAGE);

	printf ("ID: %d\n", shm_id);
	
	sb[0].sem_num = 0; /* Peform on 0th sem in the set */
	sb[0].sem_flg = SEM_UNDO; /* UNDO once done */
	sb[0].sem_op = -1; /* subs 1 from semval => semval = 0 */
	semop (sem_id, sb, 1);

	sb[0].sem_op = -1; /* hangs here until 1 is added to semval in shmsem-user.c */
	semop (sem_id, sb, 1);

	semctl (sem_id, 0, IPC_RMID, sem_arg); /* Remove the semaphore set */
	shmdt (shm_buf); /* Detach the memory segment */
	shmctl (shm_id, IPC_RMID, NULL); /* Remove the shared memory */

	return 0;
}
