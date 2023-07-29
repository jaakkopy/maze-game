CPP_SRC=$(wildcard *.cpp)
HPP_SRC=$(wildcard *.cpp)
INCL=-lraylib -lm -Wall -Wextra
CC=g++

main: $(CPP_SRC) $(HPP_SRC)
	$(CC) -o main $(CPP_SRC) $(INCL)