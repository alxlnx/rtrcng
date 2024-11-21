/*
Написать программу мирно считающую факториал, а по сигналу выводящую на терминал
текущее время счёта и промежуточный результат.
Сигнал выдавать из другого терминала, командой терминала.
*/
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

long long res = 1;
long elapsed = 0;

long long factorial(long n)
// Return n! NO overflow detection.
{
  while (n >= 1)
  {
    res *= n;
    --n;
    sleep(2);
    elapsed++;
  }
  return res;
}

void sig_handler(int snum)
{
  printf("Current calculation is: %lld\n", res);
  printf("Elapsed time: %ld s\n", elapsed);
}

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    printf("Error: not enough input arguments\n");
    exit(1);
  }

  long n = atoi( argv[1] );

  /* Handle the signal */
  struct sigaction act;
  sigemptyset (&act.sa_mask);
  act.sa_handler = &sig_handler;
	act.sa_flags = 0;

  if (sigaction (SIGUSR1, &act, NULL) == -1) 
	{
		fprintf (stderr, "sigaction() error\n");
		exit(1);
	}

  /* Print the pid for interaction */
  printf("Procces pid: %d\n", (int)getpid());

  /* Calculate the result */
  printf("%lld", factorial(n));

  return 0;
}