/* Программа, осуществляющая двунаправленную связь через pipe
между процессом-родителем и процессом-ребенком */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//  WATCH THE BUFFER SIZE!!!

int main()
{
int fd0[2], fd1[2], result;
/* [0] - READ, [1] - WRITE */

size_t size;
char resstring[80];

/* Создаем два pip'а */
if(pipe(fd0) < 0)
{
  printf("Can\'t create pipe\n");
  exit(-1);
}

if(pipe(fd1) < 0)
{
  printf("Can\'t create pipe\n");
  exit(-1);
}

/* Порождаем новый процесс */
result = fork();

if(result < 0)
{
  /* Если создать процесс не удалось, сообщаем обэтом и завершаем работу */
  printf("Can\'t fork child\n");
  exit(-1);
} 
else if (result > 0) 
{
  /* Мы находимся в родительском процессе. Закрываем ненужные потоки данных */
  close(fd0[0]); // WRITE, close child read
  close(fd1[1]); // READ, close child write

  /* Пишем в первый pipe и читаем из второго */
  char msg[] = "Привет, дитя!";
  size = write(fd0[1], msg, sizeof(msg));
  if(size != sizeof(msg))
  {
    printf("Parent: can\'t write all string\n");
    exit(-1);
  }

  size = read(fd1[0], resstring, 80);
  if(size < 0)
  {
    printf("Parent: can\'t read string\n");
    exit(-1);
  }
  printf("Parent: %s\n", resstring); 
  close(fd1[1]);
  close(fd1[0]);
  printf("Parent exit\n");
} 
else 
{
  /* Мы находимся в порожденном процессе. Закрываем ненужные потоки данных */
  close(fd0[1]);
  close(fd1[0]);
  /* Читаем из первого pip'а и пишем во второй */
  size = read(fd0[0], resstring, 10);
  if(size < 0)
  {
    printf("Child: can\'t read string\n");
    exit(-1);
  }
  
  printf("Child: %s\n",resstring);
  size = write(fd1[1], "Ну привет, папик!", 80);
  if(size != 80)
  {
    printf("Child: can\'t write all string\n");
    exit(-1);
  }

  close(fd0[0]);
  close(fd1[1]);
}

return 0;
} 
