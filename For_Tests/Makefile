CFLAGS = -W -Wall -Werror
CC = g++

all : udp

udp : cli_udp ser_udp

cli_udp : cli_udp.o
	$(CC) $(CFLAGS) cli_udp.o -o cli_udp

cli_udp.o : cli_udp.cpp
	$(CC) $(CFLAGS) -c cli_udp.cpp -o cli_udp.o

ser_udp : ser_udp.o
	$(CC) $(CFLAGS) ser_udp.o -o ser_udp

ser_udp.o : ser_udp.cpp
	$(CC) $(CFLAGS) -c ser_udp.cpp -o ser_udp.o



clean :
	rm *.o cli_udp ser_udp
