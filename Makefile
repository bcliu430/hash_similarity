CC=gcc
CFLAGS=-Wall -Werror
DEBUG=-g
BIN1=helloworld
BIN2=gen_rand
BIN3=datetime
BIN4=greenlet
PAGE=1
IP=172.30.13.48

all: main.o
	$(CC) $(CFLAGS) main.c -o hashsim

run: all
	sudo ./hashsim $(BIN1) $(BIN2) $(PAGE)
	sudo ./hashsim $(BIN1) $(BIN3) $(PAGE)
	sudo ./hashsim $(BIN1) $(BIN4) $(PAGE)
	sudo ./hashsim $(BIN2) $(BIN3) $(PAGE)
	sudo ./hashsim $(BIN2) $(BIN4) $(PAGE)
	sudo ./hashsim $(BIN3) $(BIN4) $(PAGE)

clean:
	sudo rm *.o hashsim

install:
	scp main.c Makefile $(IP):~
