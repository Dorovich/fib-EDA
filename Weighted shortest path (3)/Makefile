all: compile_commands.json main solution

main: main.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o main main.cc

solution: solution.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o solution solution.cc

compile_commands.json: main.cc
	bear -- make main

clean:
	rm main compile_commands.json
