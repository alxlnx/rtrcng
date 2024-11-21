#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
/* Программа посылающая себе сигнал на уничтожение.*/
/* Дописать игнорирование данного сигнала.*/
int main (void)
{
	pid_t dpid = getpid();

	//signal(SIGINT, SIG_IGN);
	struct sigaction act = { 0 };
	act.sa_handler = SIG_IGN;

	sigaction(SIGINT, &act, NULL);

	if (kill (dpid, SIGINT) == -1) {
	  	fprintf (stderr, "Cannot send signal\n");
	  	return 1;
	}

	puts("Made it past the kill()");

	return 0;
}
