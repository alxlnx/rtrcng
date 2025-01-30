#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN		4096
#define HTTP_PORT	80
/* Получить и распечатать какую либо страничку из интернета man 3 gethostbyname */
int main (int argc, char ** argv)
{
	int sock, count;
	char buf[BUF_LEN];
	struct hostent* host;
  
	struct sockaddr_in addr;
	
	if (argc < 2) 
	{
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}

	//buf = (char *) malloc (BUF_LEN);
	if (buf == NULL) 
	{
		fprintf (stderr, "malloc() error\n");
		return 1;
	}

	sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock == -1) 
	{
		fprintf (stderr, "socket() error\n");
		return 1;
	}

	addr.sin_family = AF_INET;

  /* Get the host */
  // memset(&hints, 0, sizeof(hints));

	printf("Resolving hostname...\n\n");
	host = gethostbyname(argv[1]);
	puts(argv[1]);
  
  // struct in_addr **address_list = (struct in_addr **)host->h_addr_list;
  // for(int i = 0; address_list[i] != NULL; i++)
  // {
  //    printf("%lld\n", address_list[i]->s_addr);
  // }
  // write (1, host->h_addr_list[0], 10);

	if (host == NULL)
	{
		fprintf (stderr, "Unknown server %d\n", h_errno);
		return 1;
	}

	/* addr.sin_addr = * (struct in_addr*) 
				host->h_addr_list[0]; */

	printf("Assigning HTTP_PORT\n");
	addr.sin_port = HTTP_PORT;
	printf("Assigned HTTP_PORT\n");

	printf("Connecting...\n");
	// printf("fkdfdfkdf\n");
	printf("%d", 22);
	if (connect (sock, (struct sockaddr*) &addr, sizeof (addr)) == -1) 
	{
		fprintf (stderr, "connect() error %d\n", errno);
		return 1;
	}
	printf("Connected");
  // printf("%lld", addr.sin_addr.s_addr);

	char sendline[BUF_LEN + 1];
	char* poststr = "Connection: close";
	snprintf(sendline, 4096, 
     "GET / HTTP/1.0\r\n"  // POST or GET, both tested and works. Both HTTP 1.0 HTTP 1.1 works, but sometimes 
     "Host: %s\r\n"     // but sometimes HTTP 1.0 works better in localhost type
     "Content-type: application/x-www-form-urlencoded\r\n"
     "Content-length: %d\r\n\r\n"
     "%s\r\n", argv[1], (unsigned int)strlen(poststr), poststr);


	strcpy(buf, "GET / HTTP/2\r\nHost: example.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:132.0) Gecko/20100101 Firefox/132.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest: document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: cross-site\r\nIf-Modified-Since: Thu, 17 Oct 2019 07:18:26 GMT\r\nIf-None-Match: \"3147526947+gzip\"\r\nPriority: u=0, i");

	// strcpy (buf, "GET /");
  // strcat (buf, " HTTP/2\r\nHost: ");
  // strcat (buf, "example.com");
  // strcat (buf, "\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:50.0) Gecko/20100101 Firefox/50.0");
  // strcat(buf, "\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
  // strcat (buf, "\nAccept-Language: en-US,en;q=0.5\r\n\r\n");
  // //strcat (buf, "\nAccept-Encoding: gzip, deflate");
	// // strcat (buf, "\r\nContent-Length: 960\r\n");
  // strcat (buf, "\r\nConnection: close\r\n");
  // strcat (buf, "\r\n");
	
	puts(buf);
	int written = write(sock, buf, strlen (buf));
	printf("%d\n", written);
  puts("Successful write");
	puts(buf);

	char* readline = (char*)malloc(BUF_LEN);
	count = 0;
	count = read(sock, readline, 1);

	printf("%d", count);
	/*while ((count = read(sock, readline, BUF_LEN)) > 0)
  {
    printf("Read %d bytes\n", count);
    //buf[count] = '\0';
		// write (1, buf, count);
		write(STDOUT_FILENO, readline, count);
    //fputs(buf, stdout);
  }*/
	// write(STDOUT_FILENO, readline, count);

	close (sock);
	free (buf);
	return 0;
}
