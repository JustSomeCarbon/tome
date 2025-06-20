CC = gcc
CFLAGS = -Wall

all: scry gate

scry: scry.c scry.h
	$(CC) $(CFLAGS) -o scry scry.c

gate: gate.c gate.h
	$(CC) $(CFLAGS) -o gate gate.c

clean:
	rm scry gate
