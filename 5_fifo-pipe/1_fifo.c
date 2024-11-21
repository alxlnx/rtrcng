/* Программа для записи в FIFO*/
/* Для отладки использовать утилиту strace: strace -e trace=open,read ./имя программы */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE 700

int main()
{
int fd;
size_t size;
char name[]="/home/alx/repos/rtrcng/5_fifo-pipe/fifo";

/* Обнуляем маску создания файлов текущего процесса для того, чтобы
права доступа у создаваемого FIFO точно соотвествовали параметру вызова mknod() */
(void)umask(0);

/* Попытаемся создать FIFO с именем  aaa.fifo в текущей директории,
если FIFO уже существует, то этот if нужно удалить !!! или добавить анализ.  */
// if(mknod(name, S_IFIFO | 0666, 0) < 0)
// if (mkfifo(name, 0666) < 0)
// {
//   /* Если создать FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
//   printf("Can\'t create FIFO\n");
//   exit(-1);
// }
mkfifo(name, 0666);

/* Открываем FIFO на запись.*/
if ( (fd = open(name, O_WRONLY)) < 0)
{
  /* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
  printf("Can\'t open FIFO for writing\n");
  exit(-1);
} else 
{
  puts("FIFO opened");
  printf("FIFO's fd: %d\n", fd);
}

/* Пробуем записать в FIFO ?? байт, т.е. всю строку "Погладь Кота!"
вместе с ... */
size = write(fd, "Погладь Кота!", strlen("Погладь Кота!")+1);
printf("Written size: %d\n", size);
if(size != sizeof("Погладь Кота!"))
{
  /* Если записалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
  printf("Can\'t write all string to FIFO\n");
  exit(-1);
}

if (close(fd) < 0)
{
  printf("Can\'t close FIFO\n");
  exit(-1);
}

return 0;
} 
