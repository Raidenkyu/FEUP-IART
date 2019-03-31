SRC = src/*.cpp

all:
	g++ -Wall -std=c++11 $(SRC) -o run

debug:
	g++ -g -Wall -std=c++11 $(SRC) -o run

clean:
	rm run
