OS := $(shell uname)

ifeq ($(OS),Darwin)
   CC = clang++
   FLAGS = -Wall -I/usr/local/include/  -L /usr/local/lib/ -lgsl -lgslcblas -lm -std=c++14 -O3
else ifeq ($(OS),Linux)
   CC = g++-5
   FLAGS = -lm -std=c++14
endif

DEBUG = -g

all:
	$(CC) -o main main.cpp $(FLAGS)

debug: FLAGS := $(FLAGS) -g
debug: all

clean:
	rm mainFinal
