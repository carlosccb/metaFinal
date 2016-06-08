OS := $(shell uname)

ifeq ($(OS),Darwin)
   CC = clang++
   FLAGS = -Wall  -lm -std=c++14
else ifeq ($(OS),Linux)
   CC = g++-5
   FLAGS = -lm -std=c++14
endif

FLAGS := $(FLAGS) -O3

all:
	$(CC) -o main main.cpp $(FLAGS)

auto:
	$(CC) -o main_auto main_auto.cpp $(FLAGS)

debug: FLAGS := $(FLAGS) -g
debug:
	$(CC) -o main main.cpp $(FLAGS)
	$(CC) -o main_auto main_auto.cpp $(FLAGS)

uco: CC = g++
uco: all

clean:
	if [ -f main ]; then rm main; fi;
	if [ -f main_auto ]; then rm main_auto; fi;
	if [ -d main.dSYM ]; then rm -r main.dSYM; fi;
	if [ -d main_auto.dSYM ]; then rm -r main_auto.dSYM; fi;

update: clean
update: all
