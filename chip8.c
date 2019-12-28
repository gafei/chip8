#include "chip8.h"

void chip8::init()
{
	//init registers and memory once
	pc = 0x200; //program counter starts at 0x200
	opcode = 0; //reset current opcode
	I = 0; // reset index register
	sp = 0; //reset stack pointer

	//clear the display
	//clear the stack
	//clear registers V0-VF
	//Clear memory

	// Load fontset

	fot (int i = 0; i <80 ; ++i)
	{
		memory[i] = chip8_fontset[i];
	}

	//reset memory timers



}

void chip8::loadROM()
{



	// load the program rom

}



// Every cycle, the method emulateCycle is called, which emulates one cycle of the 
// chip8 cpu. Each cycle will fetch, decode, and execute an opcode.

void chip8::emulateCycle()
{

	// Fetch Opcode
	// Decode Opcode
	// Execute Opcode

	// Update timers
}

void chip8::fetch()
{

	// in a fetch, the system will fetch one opcode 
	// from memory at the location specified by the program counter
	// In our chip8 emulator, data is stored in an array
	// where each address contains a byte. 
	// As one opcode is 2 bytes long, we will need to fetch two
	// successive bytes and merge them to get the actual opcode

	// Assumes the below:

	memory[pc] == 0xA2;
	memory[pc + 1] == 0xF0


}

void chip8::decode()
{

}

void chip::execute()
{

}

