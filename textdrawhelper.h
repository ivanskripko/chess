#ifndef TEXTDRAWHELPER_H_
#define TEXTDRAWHELPER_H_

#include "drawhelper.h"
#include "piece.h"
#include "board.h"

// класс для текстового вывода информации о расположении фигур
class TextDrawHelper : public DrawHelper {
public:
	void draw (const Board& board) const; // нарисовать доску
	void giveMessage (const char* message) const; // вывести сообщение
protected:
	void drawPiece (int x, int y, const Piece& piece) const; // нарисовать отдельную фигуру
};

#endif