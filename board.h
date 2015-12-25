#ifndef BOARD_H_
#define BOARD_H_ 

#include "piece.h"

// класс доска
class Board {
private:
	Piece** p; // динамический двумерный массив из фигур
public:
	Board();
	~Board();	
	void addPiece(Piece::Type type, Chess::Color color, int x, int y); // добавить фигуру
	void removePiece(int x, int y); // убрать фигуру
	void movePiece(int x0, int y0, int x1, int y1); // переместить фигуру
	Piece getPiece(int x, int y) const; // получить фигуру, которая расположенна по указанным координатам
private:
	Board(const Board& b);
};

#endif