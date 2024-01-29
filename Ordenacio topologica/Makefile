all: main

main: main.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o main main.cc

compile_commands.json:
	bear -- make all

clean:
	rm main compile_commands.json
