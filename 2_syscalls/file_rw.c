/* Программа, иллюстрирующая использование системных вызовов open(), read() и close() для чтения информации из файла */

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
int fd;
size_t size;
char string[60];

char* fname = argv[1];	// argv[0] is always the program name

/* Попытаемся открыть файл с именем в первом параметре выззова только
для операций чтения */

// if((fd = open(fname, O_RDONLY)) < 0)
// {
//   /* Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу */
//   printf("Can\'t open file\n");
//   exit(-1);
// }

FILE* fp = NULL;
fp = fopen(fname, "r");
if (!fp) 
{
	printf("Error while reading file: %s", fname);
}

/* Читаем фаил пока не кончится и печатаем */
//ssize_t read_num = fread(fd, string, 60);
ssize_t read_num = fread(string, 1, 60, fp);
printf("%s\n", string); /* Печатаем прочитанное*/

/*  Записываем файл под новым именем */


/* Закрываем файл */
// if(close(fd) < 0)
// {
//   printf("Can\'t close file\n");
// }
if (fclose(fp) == EOF) 
{
	printf("Error when closing the file");
}

/*  Открываем файл в редакторе */
if ( execl("/usr/bin/xed", "/usr/bin/xed", fname, NULL) < 0 )
{
	printf("Error\n");
}

return 0;
} 
