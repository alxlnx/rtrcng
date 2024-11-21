/* Пример программы для изменения пользовательского контекста (запуска новой программы) в порожденном процессе. */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
pid_t pid, ppid, chpid;
int result;
 
if (argc < 2) 
{
	fprintf (stderr, "Too few arguments\n");
	return 1;
}	

chpid = fork();
 
if (chpid == -1)
{ 
  /* Ошибка */
  printf("Can\'t fork a child process\n");
 
} 
else if (chpid > 0)
{
  pid = getpid();
  ppid = getppid();

  printf("pid = %d, ppid = %d \n", (int)pid, (int)ppid); 
} 
else 
{
  //result = execl("/bin/cat", "/bin/cat", "exec.c", NULL);
  char prog_name[] = "/home/alx/repos/rtrcng/4_signals/3_signal-child"; 
  result = execl(prog_name, prog_name, argv[1], NULL);

  if(result < 0)
  {
    /* Если возникла ошибка, то попадаем сюда*/
    printf("Error on program start\n");
    exit(-1);
  }
 
}

return 0;
}

