CPPFLAGS = -Wall -Wextra -O1 -std=c++17 -g
CFLAGS = -Wall -Wextra -O1 -g

output: main.o
	@echo "Linking final executable..."
	gcc $(CFLAGS) main.o -o output

main.o: main.c
	@gcc $(CFLAGS) -c main.c

clean:
	rm *.o output

# message.o: message.cpp message.h
# 	g++ -c message.cpp
# target: files whose change triggers execution of the command
#	the command
# target: dependencies
#	action

# gcc -c = compile, do not link