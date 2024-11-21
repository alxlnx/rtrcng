#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define _XOPEN_SOURCE 700

#define FIFO_PERMBITS 0666

/* Make a named pipe for the client and the server to communicate through (FIFO) */
/* Перая программа создаёт или удаляет трубу.*/
int main()
{
  char fname[] = "fifo";
  umask(0);

  if ( mkfifo(fname, FIFO_PERMBITS) < 0 )
  {
    printf("Error: can't create fifo, errno: %d\n", errno);
    exit(1);
  }

  
  /* Make another pipe */

  char fname2[] = "fifo_back";
  umask(0);

  if ( mkfifo(fname2, FIFO_PERMBITS) < 0 )
  {
    printf("Error: can't create fifo_back, errno: %d\n", errno);
    exit(1);
  }


  return 0;
}