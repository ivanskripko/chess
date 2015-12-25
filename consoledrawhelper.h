#ifndef CONSOLEDRAWHELPER_H_
#define CONSOLEDRAWHELPER_H_

#include "drawhelper.h"
#include "piece.h"
#include "board.h"

// класс для консольного вывода доски на экран
class ConsoleDrawHelper : public DrawHelper {
public:
	void draw (const Board& board) const; // нарисовать доску
	void giveMessage (const char* message) const; // вывести сообщение
protected:
	void drawPiece (int w, const Piece& piece) const; // нарисовать отдельную фигуру
};

#endif