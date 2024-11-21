/* Проверить совместную работу с 4.
   Написать комментарии, В ТОМ ЧИСЛЕ К ПАРАМЕТРАМ!*/
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

#define SHMEM_SIZE	4096
#define SH_MESSAGE	"Poglad Kota!\n"

int main (void)
{
	int shm_id;
	char* shm_buf;
	int shm_size;
	struct shmid_ds ds;
	
	// Get shared memory of size SHMEM_SIZE
	/* IPC_PRIVATE here is a special key value:
		Make a new shared memory segment (regardless of if IPC_CREAT is set)
		And ignore all but 9 LSBits of shmflg, which set permissions.
		So IPC_CREAT and IPC_EXCL are redundant here.
	*/
	shm_id = shmget (IPC_PRIVATE,
	                 SHMEM_SIZE,
			             IPC_CREAT | IPC_EXCL | 0600);

	if (shm_id == -1) 
	{
		fprintf (stderr, "shmget() error\n");
		exit(-1);
	}

	/* Attach the shared memory
		 The last number here is shmflg, it can be set to make the attached segment read-only */
	shm_buf = (char *) shmat (shm_id,
	                          NULL,
	                          0);
	if (shm_buf == (char *)-1)
	{
		fprintf (stderr, "shmat() error\n");
		return 1;
	}

	// Perform a control operation on the shared mem segment shm_id
	/* IPC_STAT: Copy information from the kernel data structure 
	associated with shmid into the shmid_ds structure pointed to by buf (ds).
	*/
	shmctl (shm_id,
	        IPC_STAT,
	        &ds);
	
	shm_size = ds.shm_segsz;
	if (shm_size < strlen (SH_MESSAGE)) 
	{
		fprintf (stderr, "error: segsize=%d\n", shm_size);
		return 1;
	}
	
	// Write the message into the shared memory
	strcpy (shm_buf,
	        SH_MESSAGE);

	printf ("ID: %d\n", shm_id);
	// printf ("Press <Enter> to exit...");	
	// fgetc (stdin);

	printf("Current attaches:	%d\n", ds.shm_nattch);
	shmdt (shm_buf);
	shmctl (shm_id, IPC_STAT, &ds);
	printf("Current attaches:	%d\n", ds.shm_nattch);
	// Mark the memory segment to be destroyed, the buff argument is ignored (so NULL here)
	// Actual removal is going to happen when last process detaches the segment
	// shmctl (shm_id,
	//         IPC_RMID,
	//         NULL);

	//printf ("Press <Enter> to exit...");	
	//fgetc (stdin);

	return 0;
}
