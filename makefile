build:
	bear -- clang++ -ggdb -std=c++20 -pedantic-errors -Wshadow -Wall -Wextra -Wsign-conversion -Weffc++ -lncurses main.cpp include/program/*.cpp -o main
