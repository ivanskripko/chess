#include <iostream>
#include <cstdlib>
#include "game.h"
#include "menu.h"

using std::cout;
using std::endl;

void ConsoleMenu::draw (int menuLevel, Game& game) const
{	
	do {		
		clearScreen();

		switch (menuLevel)
		{
		case 0:
			cout << "Добро пожаловать в игру Шахматы." << endl;
			cout << "1. Продолжить игру." << endl;
			cout << "2. Новая игра." << endl;
			cout << "3. Сохранить игру." << endl;
			cout << "4. Загрузить игру." << endl;
			cout << "5. Руководство пользователя." << endl;
			cout << "6. Настройки." << endl;
			cout << "7. Выход." << endl;

			cout << "\nВыберите пункт меню: ";
			cin >> menuLevel;

			if (menuLevel == 7) return;
			break;
		case 1:
			cout << "Продолжение игры: " << endl;
			showAdvice();
			game.continueGame();
			menuLevel = 0;
			break;
		case 2:
			cout << "Новая игра: " << endl;
			showAdvice();
			game.newGame();
			menuLevel = 0;
			break;
		case 3:
			cout << "Сохранение игры..." << endl;
			if (game.saveToFile("save_file.txt")) {
				cout << "Сохранение выполненно успешно." << endl;
			} else {
				cout << "Сохранение выполнить не удалось." << endl;
			}
			pressAnyKey();
			menuLevel = 0;
			break;
		case 4:
			cout << "Загрузка игры..." << endl;
			if (game.loadFromFile("save_file.txt")) {
				cout << "Загрузка выполнена успешно." << endl;
			} else {
				cout << "Загрузку выполнить не удалось." << endl;
			}
			pressAnyKey();
			menuLevel = 0;
			break;
		case 5:
			showInstructions();
			pressAnyKey();				
			menuLevel = 0;
			break;			
		case 6:
			cout << "Настройки: " << endl;
			cout << "1. Изменить способ ввода." << endl;
			cout << "2. Изменить способ отображения шахмат." << endl;
			cout << "3. В главное меню." << endl;
			cin >> menuLevel;
			showSettings(menuLevel, game);
			menuLevel = 0;
			break;
		default:
			menuLevel = 0;
			break;
		}
	} while (1);
}

void ConsoleMenu::showInstructions() const
{		
	cout << "Инструкция пользователя: " << endl;
	cout << "\nФигуры: " << endl;
	cout << "Pawn - Пешка, обозначается P" << endl;
	cout << "Knight - Конь, обозначается H" << endl;
	cout << "Bishop - Слон, обозначается B" << endl;
	cout << "Rook - Ладья, обозначается R" << endl;
	cout << "Queen - Королева, обозначается Q" << endl;
	cout << "King - Король, обозначается K" << endl;
	cout << "\nЧтобы совершить ход используйте буквы и цифры, обозначающие клетки доски." << endl;
	cout << "Например: e2 e4" << endl;
	cout << "\nЧтобы выйти в главное меню, наберите во время игры exit" << endl;
}

void ConsoleMenu::showSettings(int menuLevel, Game& game) const
{
	bool isSuccessful = false;
	switch(menuLevel)		
	{
		case 1:
			clearScreen();
			cout << "Выберите способ ввода: " << endl;
			cout << "1. Ввод через консоль." << endl;			
			cin >> menuLevel;
			if (menuLevel == 1) {
				game.changeInputHelper(menuLevel);
				isSuccessful = true;
			}
			break;				
		case 2:
			clearScreen();
			cout << "Выберите способ отображения шахмат: " << endl;
			cout << "1. Вывод в текстовом формате." << endl;
			cout << "2. Вывод в псевдографическом режиме." << endl;
			cin >> menuLevel;
			if (menuLevel == 1 || menuLevel == 2) {
				game.changeDrawHelper(menuLevel);
				isSuccessful = true;
			}
			break;
		case 3:
			return;
		default:
			break;
	}
	if (isSuccessful) {
		cout << "Значение установленно." << endl;
	} else {
		cout << "Ошибочное значение." << endl;
	}
	pressAnyKey();
}

void ConsoleMenu::pressAnyKey() const 
{
	cout << "\nНажмите любую клавишу для продолжения..." << endl;
	cin.get();
	cin.get();
}

void ConsoleMenu::clearScreen() const
{
	system("clear");
}

void ConsoleMenu::showAdvice() const
{
	cout << "\nВы можете выйти в главное меню, набрав exit в поле ввода." << endl;
}