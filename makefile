CC = g++
CFLAGS = -c -Wall

target: run

run: tic_tac_toe.exe
	./tic_tac_toe.exe

tic_tac_toe.exe: obj obj/main.o obj/tic_tac_toe.o
	${CC} -o tic_tac_toe.exe obj/main.o obj/tic_tac_toe.o

obj:
	mkdir obj

obj/main.o: src/main.cpp inc/tic_tac_toe.hh
	${CC} ${CFLAGS} -o obj/main.o src/main.cpp

obj/tic_tac_toe.o: src/tic_tac_toe.cpp
	${CC} ${CFLAGS} -o obj/tic_tac_toe.o src/tic_tac_toe.cpp