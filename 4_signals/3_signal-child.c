#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

/* Дочерний процесс, анализирующий год и возвращающий различные сигналы,
 * в зависимости от его високосности.
 */
int main (int argc, char ** argv)
{
	pid_t pid = getpid();
	printf("signal-child PID: %d\n", pid);
	pid_t ppid = getppid();
	printf("signal-child parent PID: %d\n", ppid);

	int year;
	if (argc < 2) 
	{
		fprintf (stderr, "child: too few arguments\n");
		return 2;
	}

	year = atoi (argv[1]);

	if (year <= 0)
		return 2;
/*Объяснить как считаем условие*/
	if ( ((year%4 == 0) && (year%100 != 0)) ||
			(year%400 == 0) ) 
	{
		kill (getppid(), SIGUSR1);
		return 0;
	}
	else 
	{
		kill (getppid(), SIGUSR2);
		return 0;
	}

	return 0;
}
