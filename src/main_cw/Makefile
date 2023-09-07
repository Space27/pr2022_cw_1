CC=gcc
CFLAGS=-c -Wall

all: cw_exe clean

cw_exe: main.o error.o memory.o print.o processing.o read.o structs.o user_tips.o
	$(CC) main.o error.o memory.o print.o processing.o read.o structs.o user_tips.o -o cw_exe

main.o: main.c print.h user_tips.h structs.h error.h processing.h
	$(CC) $(CFLAGS) main.c

error.o: error.c error.h memory.h structs.h
	$(CC) $(CFLAGS) error.c

memory.o: memory.c memory.h structs.h
	$(CC) $(CFLAGS) memory.c

print.o: print.c print.h structs.h
	$(CC) $(CFLAGS) print.c

read.o: read.c read.h structs.h memory.h processing.h
	$(CC) $(CFLAGS) read.c

structs.o: structs.c structs.h
	$(CC) $(CFLAGS) structs.c

user_tips.o: user_tips.c user_tips.h read.h error.h
	$(CC) $(CFLAGS) user_tips.c

processing.o: processing.c processing.h structs.h memory.h
	$(CC) $(CFLAGS) processing.c

clean:
	rm *.o