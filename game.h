#ifndef GAME_H_
#define GAME_H_ 

#include "piece.h"
#include "board.h"
#include "drawhelper.h"
#include "inputhelper.h"
#include "gamerules.h"
#include <string>

using std::string;

// основной класс игры
class Game {
private:
	Board board; // игровое поле
	Chess::Color whoMoves; // кто на данный момент ходит
	DrawHelper* dh; // отрисовщик
	InputHelper* ih; // класс, отвечающий за ввод
	GameRules rules; // игровые правила

public:
	Game();

	~Game();

	bool saveToFile(string fileName); // сохранение в файл

	bool loadFromFile(string fileName); // загрузка из файла

	void changeInputHelper (int choice); // смена способа ввода (динамически)

	void changeDrawHelper (int choice); // смена способа отображения (динамически)

	void continueGame(); // продолжить игру

	void newGame(); // начать новую игру

private:
	Game(const Game& g);

	void removeAllPieces(); // удалить все фигуры с поля

	void changePlayer (); // сменить игрока, т.е. поменять того кто ходит

	void setWhoMoves(Chess::Color color); // установить цвет того, кто ходит

	void run(); // основной игровой цикл

	void refreshView(); // отобразить поле на экран

	bool doNextMove(); // сделать следующий ход

};

#endif
