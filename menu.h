#ifndef MENU_H_
#define MENU_H_

#include "game.h"

// абстрактный класс Menu
class Menu 
{
public:
	virtual void draw (int menuLevel, Game& game) const = 0; // непосредственно отрисовка меню
};

// класс Консольного меню, который отвечает за отображение меню на экран
class ConsoleMenu : public Menu 
{
public:
	void draw (int menuLevel, Game& game) const;

private:
	void showInstructions() const; // показать инструкции

	void showSettings(int menuLevel, Game& game) const; // меню настроек

	void pressAnyKey() const; // нажмите любую клавишу...

	void clearScreen() const; // очистка экрана

	void showAdvice() const; // показать совет на экран
};

#endif