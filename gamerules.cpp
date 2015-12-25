#include "board.h"
#include "piece.h"
#include "gamerules.h"

bool GameRules::isCheck(const Board& board, Chess::Color who) const
{	
	// Находим короля и смотрим, может ли его атаковать каждая из вражеских фигур
	Coordinate c = findTheKing(board, who);
	Chess::Color oponentColor = (who == Chess::WHITE ? Chess::BLACK : Chess::WHITE);

	int x = c.getX();
	int y = c.getY();

	for (int i = 0; i < Chess::BoardSize; ++i) {
		for (int j = 0; j < Chess::BoardSize; ++j) {
			if (board.getPiece(i, j).getColor() == oponentColor) {
				if (isChessPieceCanMove(board, i, j, x, y) 
					&& isPathClear(board, i, j, x, y)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool GameRules::isCheckMate(const Board& board, Chess::Color who) const 
{	
	// короля атакуют и он не может сходить сделать ход
	return isCheck(board, who) && isStaleMate(board, who);
}

bool GameRules::isStaleMate(const Board& board, Chess::Color who) const 
{
	// Проверякм все соседние клетки от короля (сможет ли король на них сходить)
	Coordinate c = findTheKing(board, who);
	Chess::Color oponentColor = (who == Chess::WHITE ? Chess::BLACK : Chess::WHITE);

	Coordinate coordinates[8];
	fillPossibleKingMoves(coordinates, c); // находим все потенциальные ходы короля

	int posMovesNum = 8;

	// далее пробегаемся по всем потенциальным ходам и отбрасываем, те куда сходить не получится
	for (int k = 0; k < 8; ++k) {
		int x = coordinates[k].getX();
		int y = coordinates[k].getY();

		// Проверякм, что не в пределах доски или не пустая клетка 
		// (для простоты, хотя там может быть вражеская, которую можно съесть)
		if (isInBounds(x, y, 0, 0)) {
			if (board.getPiece(x, y).getType() != Piece::EMPTY)	{
				--posMovesNum;
				continue;	
			}
		} else {
			--posMovesNum;
			continue;
		}
		
		// смотрим, что вражеские фигуры тоже не могут атаковать потенциальную клетку
		for (int i = 0; i < Chess::BoardSize; ++i) {
			for (int j = 0; j < Chess::BoardSize; ++j) {
				if (board.getPiece(i, j).getColor() == oponentColor) {
					if (isChessPieceCanMove(board, i, j, x, y) 
						&& isPathClear(board, i, j, x, y)) {
						--posMovesNum;
					}
				}
			}
		}
	}

	if (posMovesNum < 1) {
		return true;
	}

	return false;
}

bool GameRules::canMove(const Board& board, Chess::Color who, int x0, int y0, int x1, int y1) const
{
	return 	isInBounds(x0, y0, x1, y1) &&
			!isTheKing(board, x1, y1) &&
			isCorrectPieceColor(board, who, x0, y0) &&
			isColorDifferent(board, x0, y0, x1, y1) &&
			isChessPieceCanMove(board, x0, y0, x1, y1) &&
			isPathClear(board, x0, y0, x1, y1);
}

bool GameRules::isInBounds(int x0, int y0, int x1, int y1) const
{
	return (x0 > -1 && x0 < Chess::BoardSize 
		&& x1 > -1 && x1 < Chess::BoardSize 
		&& y0 > -1 && y0 < Chess::BoardSize 
		&& y1 > -1 && y1 < Chess::BoardSize);
}

bool GameRules::isTheKing(const Board& board, int x, int y) const
{
	Piece piece = board.getPiece(x,y);
	return piece.getType() == Piece::KING;
}

bool GameRules::isCorrectPieceColor(const Board& board, Chess::Color who, int x, int y) const
{
	Piece piece = board.getPiece(x, y);
	return piece.getColor() == who;
}

bool GameRules::isColorDifferent(const Board& board, int x0, int y0, int x1, int y1) const
{
	Chess::Color col1 = board.getPiece(x0, y0).getColor();
	Chess::Color col2 = board.getPiece(x1, y1).getColor();
	return col1 != col2;
}

// каждая фигура может ходить строго определенным образом
bool GameRules::isChessPieceCanMove(const Board& board, int x0, int y0, int x1, int y1) const
{
	Piece piece = board.getPiece(x0, y0);
	switch (piece.getType()) 
	{
	case Piece::KING:
		if ((x1 == x0-1 && y1 == y0) || (x1 == x0-1 && y1 == y0+1) || (x1 == x0 && y1 == y0+1) || 
			(x1 == x0+1 && y1 == y0+1) || (x1 == x0+1 && y1 == y0) || (x1 == x0+1 && y1 == y0 - 1) ||
			(x1 == x0 && y1 == y0 - 1) || (x1 == x0-1 && y1 == y0 - 1)) {
			
			return true;				
		}
		break;
	case Piece::QUEEN:			
		if ( (x1 != x0 && y1 == y0) || (x1 == x0 && y1 != y0) || (x1 - x0 == y1 - y0) || (x1 - x0 == -(y1 - y0)))		
			return true;
		break;
	case Piece::ROOK:
		if ( (x1 != x0 && y1 == y0) || (x1 == x0 && y1 != y0) ) {
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

// все клетки между двумя точками должны быть пустыми (не относится к коню)
bool GameRules::isPathClear(const Board& board, int x0, int  y0, int  x1, int y1) const
{
	int minX = (x0 < x1 ? x0 : x1);
	int minY = (y0 < y1 ? y0 : y1);
	int maxX = (x0 > x1 ? x0 : x1);
	int maxY = (y0 > y1 ? y0 : y1);

	if (x0 != x1) {
		if (y0 != y1) {
			if ((x0 > x1 && y0 > y1) || (x0 < x1 && y0 < y1)) {
				int j = minY+1;			
				for (int i = minX +1; i < maxX; ++i) {
						if (board.getPiece(i,j).getType() != Piece::EMPTY) {
							return false;
						}
					++j;
				}				
			} else {
				int j = minY+1;			
				for (int i = maxX - 1; i > minX; --i) {
						if (board.getPiece(i,j).getType() != Piece::EMPTY) {
							return false;
						}
					++j;
				}
			}
		} else {
			for (int i = minX+1; i < maxX; ++i) {
				if (board.getPiece(i,y0).getType() != Piece::EMPTY) {
					return false;
				}
			}
		}
	} else {
		for (int j = minY+1; j < maxY; ++j) {
			if (board.getPiece(x0,j).getType() != Piece::EMPTY) {
					return false;
			}
		}
	}

	return true;
}

// пробегаемся по всей доске, пока не наткнемся на короля нужного цвета
Coordinate GameRules::findTheKing(const Board& board, Chess::Color who) const
{	
	Coordinate c;
	for (int i = 0; i < Chess::BoardSize; ++i) {
		for (int j = 0; j < Chess::BoardSize; ++j) {
			if (isTheKing(board, i, j) && isCorrectPieceColor(board, who, i, j)) {
				c.setX(i);
				c.setY(j);
				break;
			}
		}
	}
	return c;
}

// находим все возможные ходы короля (для Пата и Мата)
void GameRules::fillPossibleKingMoves(Coordinate* arr, Coordinate kingCoordinate) const
{
	int x = kingCoordinate.getX();
	int y = kingCoordinate.getY();

	arr[0].setX(x-1);
	arr[0].setY(y);

	arr[1].setX(x-1);
	arr[1].setY(y-1);

	arr[2].setX(x);
	arr[2].setY(y-1);

	arr[3].setX(x+1);
	arr[3].setY(y);

	arr[4].setX(x+1);
	arr[4].setY(y+1);

	arr[5].setX(x);
	arr[5].setY(y+1);

	arr[6].setX(x-1);
	arr[6].setY(y+1);	

	arr[7].setX(x+1);
	arr[7].setY(y-1);
}