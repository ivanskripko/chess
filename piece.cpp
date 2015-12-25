#include "piece.h"

char Piece::getLetter() const
{
	switch(myType)
	{
		case EMPTY:
			return '0';
		case PAWN:
			return 'P';
		case KNIGHT:
			return 'H';
		case BISHOP:
			return 'B';
		case ROOK:
			return 'R';
		case QUEEN:
			return 'Q';
		case KING:
			return 'K';			
	}
}