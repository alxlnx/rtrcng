#define _XOPEN_SOURCE 700
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*Восстановить нормальное поведение программы через 5 принятых сигналов.*/
sig_atomic_t sig_occured = 0;

void sig_handler (int snum)
{
	sig_occured++;
}

int main (void)
{
	struct sigaction act;
	sigemptyset (&act.sa_mask);
	act.sa_handler = &sig_handler;
	act.sa_flags = 0;

	if (sigaction (SIGINT, &act, NULL) == -1) 
	{
		fprintf (stderr, "sigaction() error\n");
		return 1;
	}

	while (5) 
	{
		if (sig_occured >= 5) 
		{
			fprintf (stderr, "signal...\n");
			sig_occured = 0;
		}
	}
	
	return 0;
}
