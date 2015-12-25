#ifndef DRAWHELPER_H_
#define DRAWHELPER_H_

#include "board.h"

// абстрактный класс для вывода информации на экран
class DrawHelper { 
public:
	virtual void draw (const Board& board) const = 0; // нарисовать доску
	virtual void giveMessage (const char* message) const = 0; // вывести сообщение пользователю
};

#endif