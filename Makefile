CXX = g++
CXXFLAGS = -W -Wall -Wno-unused-result -O3 -I algorithms -I mazetypes -I maze -std=c++17 -I G:\CppDev\SDL2\include -I G:\CppDev\SDL2_ttf\include
LDFLAGS = -L G:\CppDev\SDL2\lib\x64 -L G:\CppDev\SDL2_ttf\lib\x64 -lSDL2_ttf -lSDL2main -lSDL2

all: mazegen

mazegen: main.o bfs.o spanningtreealgo.o rectmaze.o dfs.o cellborder.o maze.o event_handler.o maze_handler.o sdl_utils.o renderer.o game.o
	$(CXX) -o $@ $^ $(LDFLAGS)

main.o: main.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

bfs.o: bfs.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

spanningtreealgo.o: spanningtreealgo.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

rectmaze.o: rectmaze.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

dfs.o: dfs.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

cellborder.o: cellborder.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

maze.o: maze.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

event_handler.o: event_handler.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

maze_handler.o: maze_handler.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

sdl_utils.o: sdl_utils.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

renderer.o: renderer.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

game.o: game.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f *.o mazegen
