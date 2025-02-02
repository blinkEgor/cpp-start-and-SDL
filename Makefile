all: main

main: main.cpp
	g++ main.cpp WindowManager.cpp GameState.cpp -o main -lSDL2

run: main
	./main

clean:
	rm -f main