#include "board.h"
#include "piece.h"

Board::Board()
{
	p = new Piece*[Chess::BoardSize];

	for (int i = 0; i < Chess::BoardSize; ++i) {
		p[i] = new Piece[Chess::BoardSize];
	}
}

Board::~Board()
{
	for (int i = 0; i < Chess::BoardSize; ++i) {
		delete [] p[i];
	}

	delete [] p;
}

void Board::addPiece(Piece::Type type, Chess::Color color, int x, int y) 
{
	p[x][y].setType(type);
	p[x][y].setColor(color);
}

void Board::removePiece(int x, int y)
{
	p[x][y].setType(Piece::EMPTY);
	p[x][y].setColor(Chess::EMPTY);
}

void Board::movePiece(int x0, int y0, int x1, int y1)
{
	p[x1][y1] = p[x0][y0];
	removePiece(x0, y0);
}

Piece Board::getPiece(int x, int y) const
{
	return p[x][y];
}