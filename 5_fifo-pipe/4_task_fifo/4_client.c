/* Третья программа (клиент) читает с терминала число и пихает его в трубу.*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#define _XOPEN_SOURCE 700

int main()
{
  char fname[] = "fifo";

  printf("Please, enter a decimal number: ");
  char input[100];
  fgets(input, sizeof(input), stdin);
  printf("Read from cmd: %s\n", input);

  int fd = open(fname, O_WRONLY);
  if (fd < 0)
  {
    printf("Error: can\'t open fifo for WRITING, errno: %d\n", errno);
    exit(1);
  } else
  {
    printf("FIFO opened, fd: %d\n", fd);
  }

  int size = write(fd, input, sizeof(input));

  printf("Written size: %d\n", size);
  if(size != sizeof(input))
  {
    /* Если записалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
    printf("Can\'t write all string to FIFO\n");
    exit(1);
  }

  if (close(fd) < 0)
  {
    printf("Error: can\'t close FIFO\n");
    exit(1);
  }



  /* Дополнительно усовершенствовать задачу,
   создать вторую трубу для обратной связи.
   (третья программа печатает число - результат)*/
  puts("");
  char fname2[] = "fifo_back";
  int fd2 = open(fname2, O_RDONLY);
  if (fd < 0)
  {
    printf("Error: can\'t open fifo_back for READING, errno: %d\n", errno);
    exit(1);
  } else
  {
    printf("FIFO opened, fd: %d\n", fd);
  }

  char buff[100];
  size = read(fd2, buff, sizeof(buff));
  printf("Read bytes: %d\n", size);
  if(size < 0)
  {
    /* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
    printf("Can\'t read from FIFO_back\n");
    exit(1);
  }

  /* Печатаем прочитанную строку */
  printf("Buff: %s\n", buff);

  /* Calculate and print the result*/
  int n = atoi(buff);
  printf( "f(n): %d\n", n );

  close(fd2);

  return 0;
}