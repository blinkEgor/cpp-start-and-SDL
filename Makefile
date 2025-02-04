all: main

main: src/main.cpp
	g++ src/main.cpp src/Graphics/WindowManager.cpp src/Game/GameState.cpp -o main -lSDL2

run: main
	./main

clean:
	rm -f main