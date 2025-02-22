#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

/* Программа запускает дочерний процесс, который анализирует чиcло (год),
 * введённое как параметр и возвращает различные сигналы,
 * в зависимости от его високосности.*/
/* 0 - no signal, 1 - SIGUSR1, 2 - SIGUSR2 */
sig_atomic_t sig_status = 0;

void handle_usr1 (int s_num)
{
	sig_status = 1;
}

void handle_usr2 (int s_num)
{
	sig_status = 2;
}

int main (int argc, char ** argv)
{
	pid_t pid = getpid();
	printf("signal-parent PID: %d\n", pid);

	struct sigaction act_usr1, act_usr2;
	sigemptyset (&act_usr1.sa_mask);
	sigemptyset (&act_usr2.sa_mask);
	act_usr1.sa_flags = 0;
	act_usr2.sa_flags = 0;
	act_usr1.sa_handler = &handle_usr1;
	act_usr2.sa_handler = &handle_usr2;

	if (sigaction (SIGUSR1, &act_usr1, NULL) == -1) 
	{
		fprintf (stderr, "sigaction (act_usr1) error\n");
		return 1;
	}

	if (sigaction (SIGUSR2, &act_usr2, NULL) == -1) 
	// this had acr_usr1 all along
	{
		fprintf (stderr, "sigaction (act_usr2) error\n");
		return 1;
	}


	if (argc < 2) 
	{
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}	

	pid_t chpid = fork();
	printf("signal-parent child PID: %d\n", chpid);
	if (chpid == 0)
	//Child's code
	{
		pid_t pid = getppid();
		printf("signal-parent parent PID: %d\n", pid);

		char prog_name[] = "/home/alx/repos/rtrcng/4_signals/3_signal-child"; 
		int result = execl (prog_name, prog_name, argv[1], NULL);
		if (result < 0)
		{
			fprintf (stderr, "execl() error\n");
			return 1;
		}
	} else
	{
		pid_t pid = getpid();
		printf("signal-parent PID: %d\n", pid);
	}

	//char prog_name[] = "/home/alx/repos/rtrcng/4_signals/3_signal-child"; 
	//int result = execl (prog_name, prog_name, argv[1], NULL);
	// THIS HAS PARENT PID = PID OF THE SHELL signal-parent IS BEING RUN FROM


	while (1) 
	{
		
		if (sig_status == 1) 
		{
			printf ("%s: leap year\n", argv[1]);
			return 0;
		}

		if (sig_status == 2) 
		{
			printf ("%s: not leap year\n", argv[1]);
			return 0;
		}
	}
	
	return 0;
}
