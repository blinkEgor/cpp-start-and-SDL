all: main

main: main.cpp
	g++ main.cpp -o main -lSDL2

run: main
	./main

clean:
	rm -f main