#include "menu.h"
#include "game.h"

int main () 
{	
	Game g;
	Menu* menu = new ConsoleMenu;
	
	menu->draw(0, g);
		
	delete menu;
	return 0;
}
