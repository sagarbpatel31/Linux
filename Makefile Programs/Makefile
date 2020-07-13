CC = gcc
CFLAGS = -Wall
SRC=$(wildcard *.c *.h)
sampleMake4: compile
	@./$@
compile: ${SRC}
	@$(CC) $(CFLAGS) $^ -o sampleMake4
clean: 
	rm -rf *.o sampleMake4 || true
