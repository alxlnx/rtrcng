/* разобраться как работает, написать комментарии,
   в том числе ко всем параметрам. */
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int shm_id;
	char* shm_buf;
	int shm_size;
	struct shmid_ds ds;
	// doesn't work if declared in a diff. order?
	
	if (argc < 2) 
	{
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}

	shm_id = atoi(argv[1]);
	
	shm_buf = (char *) shmat (shm_id, NULL, 0);
	if (shm_buf == (char *) -1) 
	{
		fprintf (stderr, "shmat() error\n");
		return 1;
	}

	printf ("Message: %s\n", shm_buf);

	shmctl(shm_id, IPC_STAT, &ds);
	printf("Number of current attaches:	%d\n", ds.shm_nattch);
	// Detach the shared memory segment
	if (shmdt (shm_buf) < 0)
	{
		printf("Can't detach shared memory\n");
  	exit(-1);
	}

	

	shmctl(shm_id, IPC_STAT, &ds);
	printf("Number of current attaches:	%d\n", ds.shm_nattch);

	shmctl (shm_id,
	         IPC_RMID,
	         NULL);

	return 0;
}
