CPPFLAGS = -Wall -Wextra -O1 -std=c++17 -g

output: main.o
	@echo "Linking final executable..."
	g++ $(CPPFLAGS) main.o -o output

main.o: main.cpp
	@g++ $(CPPFLAGS) -c main.cpp

clean:
	rm *.o output

# message.o: message.cpp message.h
# 	g++ -c message.cpp
# target: files whose change triggers execution of the command
#	the command
# target: dependencies
#	action