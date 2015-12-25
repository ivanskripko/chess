#ifndef GAMERULES_H
#define GAMERULES_H

#include "board.h"
#include "piece.h"
#include "coordinate.h"

// класс содержащий игровые правила
class GameRules {
public:
	// проверка на шах (короля атакуют)
	bool isCheck(const Board& board, Chess::Color who) const;

	// проверка на шах и мат (король не может двигаться и его атакуют)
	bool isCheckMate(const Board& board, Chess::Color who) const;

	// проверка на пат (король не может двигаться, но его никто не атакует)
	bool isStaleMate(const Board& board, Chess::Color who) const;

	// проверка может ли указанный игрок сходить из одной клетки доски с другую
	bool canMove(const Board& board, Chess::Color who, int x0, int y0, int x1, int y1) const;

private:
	// проверка, являются ли указанные координаты в пределах доски
	bool isInBounds(int x0, int y0, int x1, int y1) const;

	// провека, является ли указанная фигура королем
	bool isTheKing(const Board& board, int x, int y) const;

	// проверка, что указанная фигура принадлежит тому, чей ход
	bool isCorrectPieceColor(const Board& board, Chess::Color who, int x, int y) const;

	// проверка, что мы ходим на фигуру другого цвета, а не своего
	bool isColorDifferent(const Board& board, int x0, int y0, int x1, int y1) const;

	// проверка, может ли указанная фигура ходить таким образом (только по диагонали, буквой Г и т.д.)
	bool isChessPieceCanMove(const Board& board, int x0, int y0, int x1, int y1) const;
	
	// проверка, есть ли между двумя фигурами препятствие, отдельные случаи для коня и пешки
	bool isPathClear(const Board& board, int x0, int  y0, int  x1, int y1) const;

	// находим короля и возвращаем его координаты
	Coordinate findTheKing(const Board& board, Chess::Color who) const;

	// находим все возможные ходы короля (для Пата и Мата)
	void fillPossibleKingMoves(Coordinate* arr, Coordinate kingCoordinate) const;
};

#endif