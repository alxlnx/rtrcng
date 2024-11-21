/* Создать программу для запуска на двух терминалах 
для обмена сообщениями между ними через файл
 - один передаёт(записывает файл) второй получает, 
можно чтобы он ещё и рассчитывал чего либо (например возводил строку, если это число, в квадрат). 
Что будет, если запустить более двух териналов на запись и на чтение? */

// Fork two times
// One fork reads, one fork writes
// Launch that in two terminals

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  pid_t pid, ppid, chpidR, chpidW;
  int child_num = 0;

  const size_t BUFF_SIZE = 100;
  char read_buff[BUFF_SIZE];
  char read_buff_prev[BUFF_SIZE];

  char* fname = argv[1];

  // Fork two times
  chpidR = fork();
  chpidW = fork();
  pid = getpid();

  if (chpidR == -1)
  {
    printf("Can't fork the process: %d", pid);
  }
  if (chpidW == -1)
  {
    printf("Can't fork the process: %d", pid);
  }

  FILE* fpW = NULL;
  FILE* fpR = NULL;
  // Open the file in necessary moodes
  if (chpidW == 0)
  {
    fpW = fopen(fname, "w");
    if (fpW == NULL)
    {
      printf("Error: can't open file %s", fname);
      exit(1);
    }
  }
  if (chpidR == 0)
  {
    fpR = fopen(fname, "r");
    if (fpR == NULL)
    {
      printf("Error: can't open file %s", fname);
      exit(1);
    }
  }

  // The main program loop:
  while(1)
  {    
    if (chpidW == 0)
    {
      // Read from stdin and write to the file
      pid = getpid();
     
      //char buff[100];
      //fgets(buff, 100, stdin);
      char* buff = "Sometning here";

      size_t w = fwrite(buff, sizeof(buff[0]), strlen(buff), fpW);
      
      // printf("Wrote %zu out of %d", w, 100);
    }
    else if (chpidR == 0)
    {
      char string[100];
      size_t r = fread(string, sizeof(string[0]), 100, fpR);
      
      printf("Read: %s", string);
      
    }
  }


  // Writing is very weird as soon as you add sleep(1) somewhere.
  // Read doesn't seem to work too.
}
