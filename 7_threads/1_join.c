#include <stdio.h>
#include <pthread.h>
//-lpthread или -pthread  для успешной компиляции добавтить одну из этих опций
//Добавить вызов any_func в основную нить выполнения, чтобы распечатать 2009

void* any_func (void* arg)
{
  /* Cast void* arg to int* arg, then dereference it. */
  int a = *(int *) arg; 
  
  a++;
  return (void*) a;
  //return (void*) &a;
}

int main (void)
{
  pthread_t thread;
  int parg = 2007, pdata;
	
  if (pthread_create (&thread, NULL, &any_func, &parg) != 0) 
  {
    fprintf (stderr, "Error\n");
	  return 1;
  }
  printf("thread id: %lu \n", thread);
  printf("thread id: %lu \n", pthread_self());

  pthread_join (thread, (void *) &pdata);
  printf ("%d\n", pdata);

  return 0;
}
