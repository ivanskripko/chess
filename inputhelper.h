#ifndef USERINPUT_H_
#define USERINPUT_H_

#include <iostream>
#include <string>
#include "coordinate.h"

using std::string;
using std::cin;

// абстрактный класс, который отвечает за ввод пользователя
class InputHelper
{
public:
	virtual Coordinate getUserMove(string& s) const = 0; // метод, который переводит из строки в координаты
	virtual string getUserInput() const = 0; // метод, который получает ввод пользователя и переводит в строку
};

// класс для консольного ввода
class ConsoleInputHelper : public InputHelper
{
public:
	string getUserInput() const 
	{
		string s;
		cin >> s;
		return s;
	}	
	
	Coordinate getUserMove(string& s) const
	{
		int x = -1;
		int y = -1;

		if (s.length() >= 2) {
			y = s.at(0) - 'a';
			x = s.at(1) - '0' - 1;
		}

		Coordinate c(x, y);

		return c;
	}
};

#endif