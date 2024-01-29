all: compile_commands.json main solution_1 solution_2 solution_1_copy

main: main.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o main main.cc

solution_1: solution_1.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o solution_1 solution_1.cc
	
solution_2: solution_2.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o solution_2 solution_2.cc

solution_1_copy: solution_1_copy.cc
	g++ -O3 -Wall -D_GLIBCXX_DEBUG -std=c++11 -o solution_1_copy solution_1_copy.cc

compile_commands.json: main.cc
	bear -- make main

clean:
	rm main compile_commands.json
