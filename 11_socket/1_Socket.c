#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char **argv)
/* Полюбоваться на созданный сокет man 2 socket man 2 bind*/
{
	int sock;
	struct sockaddr_un saddr;

	if (argc < 2) 
	{
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}

	sock = socket (AF_UNIX, SOCK_STREAM, 0);
  // descriptor
	if (sock == -1) 
	{
		fprintf (stderr, "socket() error\n");
		return 1;
	}

	saddr.sun_family = AF_UNIX;
	/* Присвоить массив в структуре нельзя, но можно скопировать содержимое.*/ 
  strcpy(&saddr.sun_path, argv[1]);

  puts(saddr.sun_path);
  
	if (bind (sock, (struct sockaddr *) &saddr,	SUN_LEN (&saddr)) == -1) 
  // maybe sizeof(saddr)
	{
		fprintf (stderr, "bind() error %d\n", errno);
		return 1;
	}

	fprintf (stderr, "Press <Enter> to continue...");
	fgetc (stdin);

	int cl = close (sock);
  /* Зачем нужна эта команда */
	int un = unlink (argv[1]);
	return 0;
}
