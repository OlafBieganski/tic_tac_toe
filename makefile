CC = g++
CFLAGS = -c -Wall

target: run

run: tic_tac_toe.exe
	./tic_tac_toe.exe

tic_tac_toe.exe: obj/main.o
	${CC} ${CFLAGS} obj/main.o

obj/main.o: main.cpp
	${CC} ${CFLAGS} main.cpp