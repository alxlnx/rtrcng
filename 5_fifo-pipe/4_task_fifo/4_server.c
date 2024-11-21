/* Вторая программа(сервер) получает из трубы значение, возводит в квадрат
и печатает его.*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#define _XOPEN_SOURCE 700

long long f(long long n)
{
  return n*n;
}

int main()
{
  char fname[] = "fifo";

  int fd = open(fname, O_RDONLY);
  if (fd < 0)
  {
    printf("Error: can't open fifo for READING, errno: %d\n", errno);
    exit(1);
  } else
  {
    printf("FIFO opened, fd: %d\n", fd);
  }

  char buff[100];
  int size = read(fd, buff, sizeof(buff));
  printf("Read bytes: %d\n", size);
  if(size < 0)
  {
    /* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
    printf("Can\'t read from FIFO\n");
    exit(1);
  }

  /* Печатаем прочитанную строку */
  printf("Buff: %s\n", buff);

  /* Input validity check (lazy) */
  if (isdigit(buff[0]) == 0)
  {
    printf("Error: invalid input, not a number\n");
    exit(1);
  }

  /* Calculate and print the result */
  int n = atoi(buff);
  printf( "f(n): %lld\n", f(n) );

  close(fd);

  puts("");
  /* Send the result to the client */
  char fname2[] = "fifo_back";

  int fd2 = open(fname2, O_WRONLY);
  if (fd2 < 0)
  {
    printf("Error: can\'t open fifo for WRITING, errno: %d\n", errno);
    exit(1);
  } else
  {
    printf("FIFO opened, fd: %d\n", fd2);
  }

  char output[100];
  snprintf( output, sizeof(output), "%lld", f(n) );
  size = write(fd2, output, sizeof(output));

  printf("Written size: %d\n", size);
  if(size != sizeof(output))
  {
    /* Если записалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
    printf("Can\'t write all string to FIFO_back\n");
    exit(1);
  }

  if (close(fd2) < 0)
  {
    printf("Error: can\'t close FIFO_back\n");
    exit(1);
  }

  return 0;
}