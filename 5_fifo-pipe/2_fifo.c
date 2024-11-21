/* Программа для чтения из  FIFO */
/* Для отладки использовать утилиту strace: strace -e trace=open,read ./имя программы */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _XOPEN_SOURCE 700

int main()
{
int fd;
size_t size;
char resstring[25];
char name[]="/home/alx/repos/rtrcng/5_fifo-pipe/fifo";

/* Открываем FIFO на чтение.*/ // missing () here will cause fd = 0 so it's gonna read from your terminal
if( (fd = open(name, O_RDONLY)) < 0)
{
  /* Если открыть FIFO не удалось, 
  печатаем об этом сообщение и прекращаем работу */
  printf("Can\'t open FIFO for reading\n");
  exit(-1);
} else
{
  puts("FIFO opened");
  printf("FIFO's fd: %d\n", fd);
}


/* Пробуем прочитать из FIFO 20 байт в массив,
т.е. заполнить весь доступный буфер */
size = read(fd, resstring, sizeof(resstring));
printf("Read bytes: \n", size);
if(size < 0)
{
  /* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
  printf("Can\'t read string\n");
  exit(-1);
}

/* Печатаем прочитанную строку */
printf("Resstring: %s\n", resstring);
// Зачем ??
close(fd);
return 0;
} 
