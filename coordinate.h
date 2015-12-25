#ifndef COORDINATE_H_
#define COORDINATE_H_

// Класс, который содержит в себе координаты Х и У, возможно, было проще сделать структуру без методов
class Coordinate 
{
private:
	int myX;
	int myY;

public:
	Coordinate()
	{
		myX = -1;
		myY = -1;
	}

	Coordinate(int x, int y) 
	{
		myX = x;
		myY = y;
	}

	int getX() const
	{
		return myX;
	}

	int getY() const
	{
		return myY;
	}

	void setX(int x) 
	{
		myX = x;
	}

	void setY(int y) 
	{
		myY = y;
	}
};

#endif