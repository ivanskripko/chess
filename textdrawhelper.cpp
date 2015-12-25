#include <iostream>
#include "textdrawhelper.h"
#include "board.h"
#include "piece.h"

using std::cout;
using std::endl;

void TextDrawHelper::draw (const Board& board) const
{
	cout << "\nИгровое поле: " << endl;
	for (int i = 0; i < Chess::BoardSize; ++i) {
		for (int j = 0; j < Chess::BoardSize; ++j) {
			Piece piece = board.getPiece(i, j);
			drawPiece(i, j, piece);
		}
	}	
}

void TextDrawHelper::drawPiece (int x, int y, const Piece& piece) const
{
	if (piece.getType() != Piece::EMPTY) {
		cout << (piece.getColor() == Chess::WHITE ? 'W' : 'B')
			<< piece.getLetter() 
			<< char ('a' + y) 
			<< x + 1
			<< endl;
	}
}

void TextDrawHelper::giveMessage(const char* message) const
{
	cout << message << endl;
}
