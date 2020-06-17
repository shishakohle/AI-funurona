/* TODO:
 * some comments on this project
 */

#include "game.h"

int main(void)
{
	Game meinSpiel;
	bool anotherGame = true;

	do
	{
		anotherGame = true;
		anotherGame = meinSpiel.start();
	}while(anotherGame);
	
	return 0;
}

