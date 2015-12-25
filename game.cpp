#include "piece.h"
#include "board.h"
#include "drawhelper.h"
#include "textdrawhelper.h"
#include "consoledrawhelper.h"
#include "inputhelper.h"
#include "gamerules.h"
#include "coordinate.h"
#include "game.h"
#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;

Game::Game() 
{
	whoMoves = Chess::WHITE;
	dh = new ConsoleDrawHelper;
	ih = new ConsoleInputHelper;
}

Game::~Game() 
{
	delete dh;
	delete ih;
}

bool Game::saveToFile(string fileName) 
{
	ofstream saveFile;
	saveFile.open(fileName.c_str(), ios::out);

	if (!saveFile.is_open()) {
		string error = "Error! Cannot open " + fileName + " file.";
		dh->giveMessage(error.c_str());
		return false; 
	}

	for (int i = 0; i < Chess::BoardSize; ++i) {
		for (int j = 0; j < Chess::BoardSize; ++j) {
			Piece piece = board.getPiece(i, j);
			if (piece.getType() != Piece::EMPTY) {
				saveFile << piece.getType() << ' ' 
				<< piece.getColor() << ' ' 
				<< i << ' ' 
				<< j << '\n';
			}
		}
	}

	saveFile.close();
	return true;
}

bool Game::loadFromFile(string fileName) 
{
	ifstream loadFile;
	loadFile.open(fileName.c_str(), ios::in);

	if (!loadFile.is_open()) {
		string error = "Error! Cannot open " + fileName + " file.";
		dh->giveMessage(error.c_str());
		return false; 
	}

	removeAllPieces();

	int c = 0; 
	int x = 0;
	int y = 0;
	while (loadFile >> c) {
		if (c == EOF) break;
		Piece::Type type = (Piece::Type)c;
		loadFile >> c;
		Chess::Color color = (Chess::Color)c;
		loadFile >> x;
		loadFile >> y;
		board.addPiece(type, color, x, y);
	}

	loadFile.close();
	return true;
}

void Game::changeInputHelper (int choice)
{
	switch(choice)
	{
		case 1:
			delete ih;
			ih = new ConsoleInputHelper;
			break;	
		default:
			break;		
	}
}

void Game::changeDrawHelper (int choice)
{
	switch(choice)
	{
		case 1:
			delete dh;
			dh = new TextDrawHelper;
			break;
		case 2:
			delete dh;
			dh = new ConsoleDrawHelper;
			break;
		default:
			break;
	}
}

void Game::continueGame() 
{
	run();
}

void Game::newGame() 
{
	removeAllPieces();
	board.addPiece(Piece::ROOK, Chess::WHITE, 0, 0);
	board.addPiece(Piece::ROOK, Chess::WHITE, 0, 7);
	board.addPiece(Piece::KING, Chess::WHITE, 0, 4);
	board.addPiece(Piece::QUEEN, Chess::WHITE, 0, 3);

	board.addPiece(Piece::KING, Chess::BLACK, 7, 4);
	board.addPiece(Piece::QUEEN, Chess::BLACK, 7, 3);
	board.addPiece(Piece::ROOK, Chess::BLACK, 7, 0);
	board.addPiece(Piece::ROOK, Chess::BLACK, 7, 7);

	setWhoMoves(Chess::WHITE);
	run();
}

void Game::removeAllPieces() 
{
	for (int i = 0; i < Chess::BoardSize; ++i) {
		for (int j = 0; j < Chess::BoardSize; ++j) {
			board.removePiece(i,j);
		}
	}
}

void Game::changePlayer ()
{
	whoMoves = (whoMoves == Chess::BLACK ? Chess::WHITE : Chess::BLACK);
}

void Game::setWhoMoves(Chess::Color color)
{
	whoMoves = color;
}

void Game::run() 
{
	do {
		refreshView();
		if (rules.isCheck(board, whoMoves)) {
			string message = "Шах ";
			if (rules.isCheckMate(board, whoMoves)) { 
				message += "и мат!";
				dh->giveMessage(message.c_str());
				ih->getUserInput();
				break; // если шах и мат выходим
			}
			dh->giveMessage(message.c_str());				
		} else if (rules.isStaleMate(board, whoMoves)) {
			string message = "Пат! ";
			dh->giveMessage(message.c_str());
			ih->getUserInput();
			break; // если пат, тогда тоже выходим из цикла
		}		
		string turn = "Ходят ";
		turn += (whoMoves == Chess::WHITE ? "белые: " : "черные: ");		
		dh->giveMessage(turn.c_str());			
	} while (doNextMove());
}

void Game::refreshView() 
{
	dh->draw(board);		
}

bool Game::doNextMove()
{
	string s = ih->getUserInput();

	if (s == "exit") return false; // если пользователь ввел exit тогда выходим в главное меню

	// в ином случае заполняем координаты откуда и куда, проверяем возможность хода и делаем ход
	Coordinate from = ih->getUserMove(s);
	s = ih->getUserInput();		
	Coordinate to = ih->getUserMove(s);
	if (rules.canMove(board, whoMoves, from.getX(), from.getY(), to.getX(), to.getY())) {
		board.movePiece(from.getX(), from.getY(), to.getX(), to.getY());
		changePlayer();			
	} else {
		s = "Ход не верный. Попробуйте ещё раз.";
		dh->giveMessage(s.c_str());
	}
	return true;
}