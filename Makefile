all:
	g++ -Isrc/include -Lsrc/lib -o bin/run.exe *.cpp -lmingw32 -lSDL2main -lSDL2