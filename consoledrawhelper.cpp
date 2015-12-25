#include "consoledrawhelper.h"
#include "piece.h"
#include "board.h"
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

void ConsoleDrawHelper::draw (const Board& board) const
{
	const int w = 3;

	cout << endl;

	char c = 'a';
	for (int i = 0; i < Chess::BoardSize; ++i) {
		cout << setw(w) << char(c + i);
	}

	cout << endl;

	for (int i = 0; i < Chess::BoardSize; ++i) {
		cout << i + 1;

		for (int j = 0; j < Chess::BoardSize; ++j) {		
			Piece piece = board.getPiece(i, j);
			drawPiece(w, piece);
		}

		cout << endl;
	}
}

void ConsoleDrawHelper::drawPiece (int w, const Piece& piece) const
{
	if (piece.getType() == Piece::EMPTY) {
		cout << setw(w) << ".";
	} else {
		cout << setw(w-1) << piece.getLetter() << (piece.getColor() == Chess::WHITE ? 'w' : 'b');				
	}
}

void ConsoleDrawHelper::giveMessage(const char* message) const
{
	cout << message << endl;
}