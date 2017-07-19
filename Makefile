CC=gcc
CFLAGS=-Wall -Werror
DEBUG=-g
BIN1=redis_noload
BIN2=redis_withload
BIN3=nginx_noload
BIN4=nginx_withload
PAGE=1

all: main.o
	$(CC) $(CFLAGS) main.c -o hashsim

run: all
	sudo ./hashsim $(BIN1) $(BIN3) $(PAGE)
	sudo ./hashsim $(BIN1) $(BIN4) $(PAGE)
	sudo ./hashsim $(BIN2) $(BIN3) $(PAGE)
	sudo ./hashsim $(BIN2) $(BIN4) $(PAGE)

clean:
	sudo rm *.o hashsim
