# Compiler
CC = g++

all: bank deinit

bank: bank.o client.o init.o bank.h
	g++ bank.o client.o init.o bank.h -o bank

deinitializer: deinit.o
	g++ deinit.o -o deinit


clean:
	rm -f *.o bank deinit