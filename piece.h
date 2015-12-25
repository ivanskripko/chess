#ifndef PIECE_H_
#define PIECE_H_

// в этой структуре просто храним цвета и размер доски. Поля public
struct Chess
{
	enum Color {EMPTY, WHITE, BLACK};
	static const int BoardSize = 8;
};

// класс пешка, у которой есть тип (включая пустую) и цвет
class Piece
{
public:
	enum Type {EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
private:
	Chess::Color myColor;
	Type myType;
public:
	Piece() : myColor(Chess::EMPTY), myType(EMPTY)
	{		
	}

	Piece(Chess::Color color, Type type) : myColor(color), myType(type)
	{		
	}

	Piece(const Piece& p) : myColor(p.myColor), myType(p.myType)
	{		
	}

	~Piece()
	{		
	}
	
	Chess::Color getColor() const
	{
		return myColor;
	}

	void setColor(Chess::Color color) 
	{
		myColor = color;
	}

	Type getType() const
	{
		return myType;
	}

	void setType(Type type) 
	{
		myType = type;
	}

	// каждая фигура обозначается каким-либо символом. Данный метод возвращает этот символ
	char getLetter() const; 
	
};

#endif