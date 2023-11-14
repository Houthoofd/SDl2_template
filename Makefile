all:
	g++ -Isrc/include -Lsrc/lib -o run.exe *.cpp -lmingw32 -lSDL2main -lSDL2