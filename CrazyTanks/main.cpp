
//	The concept of C ++ information hiding and encapsulation is violated by public variables.
//	In the real programms i should use private variables and access functions instead. 
//	One exception to this rule is the data structure, with no behavior (equivalent to a C struct).
//	Another exception when you solve a test taks (for easy codereview without a lot of getSmth / setSmth)
 
#include "Game.h"

int main() {
	Game game;
	game.startTheGame();

	return 0;
}