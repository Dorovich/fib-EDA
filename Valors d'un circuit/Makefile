all: compile_commands.json main

main: main.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o main main.cc

compile_commands.json: main.cc
	bear -- make main

clean:
	rm main compile_commands.json
