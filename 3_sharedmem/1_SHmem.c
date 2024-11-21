/* Программа для записи текста исходного файла в разделяемую память, 
   проверить совместно с 2 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
 /* Предполагаем, что размер исходного файла < SIZE */
#define SIZE 65535

int main()
{
/* Указатель на разделяемую память */
char *memory; 
/* Временный указатель для записи фрагментов файла */
char *p = (char *)malloc(SIZE); 
/* IPC дескриптор для области разделяемой памяти */
int shmid;
/* Переменные для файлового дескриптора и количества прочитанных байт */
int fd, nread; 
FILE* file;

 /* Имя файла, использующееся для генерации ключа и чтения исходного текста.
 Файл с таким именем должен существовать в текущей директории */
char pathname[] = "key_gen.txt";
/* IPC ключ */ 
key_t key;

/* Генерируем IPC ключ из имени файла и номера экземпляра области разделяемой памяти 0 */
if((key = ftok(pathname,0)) < 0)  // Get a unique key number. Uses the inode num.
{
  printf("Can\'t generate key\n");
  free(p);
  exit(-1);
}

/* Пытаемся создать разделяемую память для сгенерированного ключа */
if((shmid = shmget(key, SIZE, 0666|IPC_CREAT)) < 0)
{
  printf("Can\'t create shared memory\n");
  free(p);
  exit(-1);
}

/* Пытаемся отобразить разделяемую память в адресное пространство текущего процесса */ 
if((memory = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) // Now get the memory address
{
  printf("Can't attach shared memory\n");
  free(p);
  exit(-1);
}

/* Открываем файл только на чтение*/ 
// if((fd = open(pathname,O_RDONLY)) < 0)
// { 
//   printf("Can't open source file\n"); 
//   (void)shmdt(memory); 
//   exit(-1); 
// } 
if( (file = fopen(pathname, "r")) == NULL )
{
  printf("Can't open source file\n"); 
  (void)shmdt(memory); 
  free(p);
  exit(-1);
}

/* Читаем файл порциями по 1kb до тех пор, пока не достигнем конца файла 
или не возникнет ошибка */
// while((nread = read(fd, p, 1024)) > 0)
// { 
//   p += nread; 
// }
nread = fread(p, 1, 1024, file);

if(ferror(file)) 
{
  puts("Eror reading source file\n");
  (void)shmdt(memory); 
  free(p);
  exit(-1); 
}

/* Закрываем файл */ 
// (void)close(fd); 
fclose(file);

/* Если возникла ошибка - завершаем работу */ 
// if(nread < 0)
// { 
//   printf("Error reading source file\n"); 
//   (void)shmdt(memory); 
//   exit(-1); 
// } 

/* После всего считанного текста вставляем признак конца строки,
чтобы впоследствии распечатать все одним printf'ом */
p[nread] = '\0';

/* Печатаем содержимое буфера.*/
printf ("%s\n", p);

strcpy(memory, p);

// while(1);

/* Отсоединяем разделяемую память и завершаем работу */ 
// This does not, however, free the memory, it will stay occupied until a sys reboot happens.
// This memory is properly freed in 2_SHmem.c
if(shmdt(memory) < 0)
{
  printf("Can't detach shared memory\n");
  free(p);
  exit(-1);
}

return 0;
}