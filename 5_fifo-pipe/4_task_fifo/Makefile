CPPFLAGS = -Wall -Wextra -O1 -std=c++17 -g
CFLAGS = -Wall -Wextra -O0 -g

all: 4_pipe.c 4_client.c 4_server.c
	@gcc $(CFLAGS) 4_pipe.c -o pipe
	@gcc $(CFLAGS) 4_client.c -o client
	@gcc $(CFLAGS) 4_server.c -o server

pipe: 4_pipe.c
	@gcc $(CFLAGS) 4_pipe.c -o pipe

client: 4_client.c
	@gcc $(CFLAGS) 4_client.c -o client

server: 4_server.c
	@gcc $(CFLAGS) 4_server.c -o server

clean:
	rm client pipe server fifo fifo_back

# message.o: message.cpp message.h
# 	g++ -c message.cpp
# target: files whose change triggers execution of the command
#	the command
# target: dependencies
#	action

# gcc -c = compile, do not link