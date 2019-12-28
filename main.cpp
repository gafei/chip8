#include <iostream>
#include "chip8cpu.h"
#include <GLUT/glut.h> // use OpenGL for now. Possibly use Metal in the future?


chip8 myChip8;

int main(int argc, char **argv)
{

	// init the graphics renderer and register input callbacks
	//setUpGrahics();
	//setUpInput();

	//Init the chip8 system and load the game into memory

	myChip8.init();
	myChip8.loadGame("pong");

	// The actual emulation loop

	for(;;)
	{

		// Emulate one CPU cycle
		myChip8.emulateCycle();

		//If the draw flag is set, update the screen
		if(myChip8.drawFlag)
		{
			drawGraphics();
		}

		// Store keypress state, during press and release
		myChip8.setKeys();


	}

	return 0;
}
