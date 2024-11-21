/* Дописать комментарии ко всем непонятным местам.
   1 Повысить надёжность при записи текста исходящего соообщения.
   2 Как формируется уникальный ключ для разделяемой памяти.
   3 Переделать на работу с несколькими терминалами,
    каждое сообщение начинать с номера терминала, 
    номер терминала передавать в параметре при запуске.*/
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define SHM_KEY_BASE 0xDEADBABE
#define SHM_MAXSIZE 1 << 20
#define DELAY (10*1000)
#define OFFSET 100

#define SHMEM_SIZE 4096

int main()
{
	printf(
		"--------------------\n"
		"SHM-Chat 0.1\n"
		"--------------------\n"
		"To send message just type it and press Enter. Another instance of SHM-Chat receives and displays it.\n"
		"--------------------\n"
		"stdin: %s\n"
		"stdout: %s\n"
		"--------------------\n"
		"Enter any number (chat is among instances with the same number):"
	, ttyname(fileno(stdin)), ttyname(fileno(stdout)));

	// This way of obtaining a unique shmem key is bad.
	int shm_key;
	scanf("%d", shm_key);
	shm_key += SHM_KEY_BASE;

	printf("--------------------\n\n");
	
	// check if more than one instance already running
	int shmid_test = shmget(shm_key, SHMEM_SIZE, 0777);		
	struct shmid_ds buf;
	shmctl(shmid_test, IPC_STAT, &buf);

	if (buf.shm_nattch > 2 && buf.shm_nattch < 0xFF)
	{
		printf("Only tet-a-tet chat is supported! Now exiting...\n",
		        buf.shm_nattch);
		exit(1);
	}

	pid_t childpid;
	if ((childpid = fork()) == -1)
	{
		perror("fork error");
	}
	
	if(childpid == 0)
	{
		// child process: prints incoming messages
		usleep(DELAY);
		int shmid = shmget(shm_key, SHMEM_SIZE, 0777);
		char* mem = (char*)shmat(shmid, NULL, 0);
		mem[0] = 0;

		// If a change is detected???
		for(;)
		{
			if (mem[0] != 0 && strcmp( mem, ttyname( fileno(stdout) ) ) != 0)
			{
				printf("--> %s\n", mem + OFFSET);
				mem[0] = 0;
			}
			usleep(DELAY);
		}
	} else
	{
		// parent process: scans outcoming messages
		int shmid = shmget(shm_key, SHMEM_SIZE, IPC_CREAT | 0777);
		char* mem = (char*)shmat(shmid, NULL, 0);
		usleep(20 * 1000);

		for(;;)
		{
			gets(mem + OFFSET);
			ttyname_r(fileno(stdin), mem, 20);
			usleep(DELAY);
		}
	}
}
