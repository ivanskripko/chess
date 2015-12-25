chess: board.o consoledrawhelper.o game.o gamerules.o main.o menu.o piece.o textdrawhelper.o
	g++ board.o consoledrawhelper.o game.o gamerules.o main.o menu.o piece.o textdrawhelper.o -o chess
board.o: board.cpp board.h piece.h
	g++ -c board.cpp
consoledrawhelper.o: consoledrawhelper.h piece.h board.h consoledrawhelper.cpp
	g++ -c consoledrawhelper.cpp
game.o: piece.h board.h drawhelper.h textdrawhelper.h consoledrawhelper.h inputhelper.h gamerules.h coordinate.h game.h game.cpp
	g++ -c game.cpp
gamerules.o: board.h piece.h gamerules.h gamerules.cpp
	g++ -c gamerules.cpp
main.o: menu.h game.h main.cpp
	g++ -c main.cpp
menu.o: game.h menu.h menu.cpp
	g++ -c menu.cpp
piece.o: piece.h piece.cpp
	g++ -c piece.cpp
textdrawhelper.o: textdrawhelper.h board.h piece.h textdrawhelper.cpp
	g++ -c textdrawhelper.cpp
clean:
	rm -rf *.o	