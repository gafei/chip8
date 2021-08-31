#include "chip8.h"

void chip8::init()
{
	//init registers and memory once
	pc = 0x200; //program counter starts at 0x200
	opcode = 0; //reset current opcode
	I = 0; // reset index register
	sp = 0; //resets stack pointer

	//clear the display



	//clear the stack
	//clear registers V0-VF
	//Clear memory

	// Load fontset
	// Font set starts at 0x50 (aka 80)

	//for (int i = 0; i <80 ; ++i)
	//{
//		memory[i] = exit
//		chip8_fontset[i];
//	}

	//reset memory timers



}

void chip8::loadRom()
{
	// load the program rom
	
	int bufferSize = 4096;
	int buffer[bufferSize];
	    //const char *filePath = "C:\\Users\\UrName\\Desktop\\testFile.bin";  

	FILE *fp;
	fp = fopen("chip8-master/roms/pong.rom", "rb");
	if (fp ==NULL)
	{
		std::cout <<"Couldn't open ROM.\n";
	}
	else{
		std::cout <<"ROM Opened successfully.\n";
	}

// An unsigned char can store 1 Bytes (8bits) of data (0-255)
	typedef unsigned char BYTE;

	BYTE *fileBuf;          // Pointer to our buffered data
	fileBuf = new BYTE[4096];

		// Read the file in to the buffer
	    fread(fileBuf, 4096, 1, fp);

	for (int i = 0; i <4096; i++){
		printf("%02x ", fileBuf[i]);
	}


	//fread(fp, )


	// start filling the memory at location 0x200 == 512
	//for(int i = 0; i < bufferSize; ++i){
//		memory[i + 512] = buffer[i];
//	}	

}



// Every cycle, the method emulateCycle is called, which emulates one cycle of the 
// chip8 cpu. Each cycle will fetch, decode, and execute an opcode.

void chip8::emulateCycle()
{

	// Fetch Opcode
	// This is determined from the program counter
	// One OPCODE is 2 bytes long
	// Need to fetch two bytes and merge them to get a opcode
	// This merges both bytes and stores them in an unsigned short
	opcode = memory[pc] << 8 | memory [pc +1]; // shift pc left by 8, then OR with [pc + 1]

	// Decode Opcode
	switch (opcode & 0xF000)
	{
		switch(opcode & 0x000F)
		{
			case 0x00E0: // 0x00E0: Clears the screen, CLS	
			// Clear the screen

			break;

			case 0x00EE: // 0x00EE: Returns from a subroutine, RET
				pc = stack[sp]; // sets the pc to the address at top of stack;
				--sp; //subtracts 1 from stack pointer.
			break;

			default:
				std::cout << "Unknown opcode [0x0000]: 0x" << opcode << "\n";

		}

		case 0xA000: // ANNN: Sets I to the address NNN, SYS addr
		// Execute opcode
			I = opcode & 0x0FFF;
			pc+=2;
		break;

		// insert more opcodes here



		case 0x1000: // Jump to location nnn. JP addr
			pc = opcode & 0x0FFF; 
		break;

		case 0x2000: // Call subroutine at nnn. 
			stack[sp] = pc; // puts the program counter at the top of the stack  
			++sp; //increment the stack pointer
			pc = opcode & 0x0FFF; // set PC to nnn.
		break;

		case 0xD000:
		{

			// Fetch the position and height of the sprite
			unsigned short x = V[(opcode & 0x0F00) >> 8 ];
			unsigned short y = V[(opcode & 0x00F0) >> 4 ];
			unsigned short height = opcode & 0x000F; // Pixel value
			unsigned short pixel;

			V[0xF] = 0; // Reset register VF	
			for (int yline = 0; yline < height; yline ++) // Loop over each row
			{
				pixel = memory[I + yline]; // Fetch the pixel value from the memory starting at location I 
				for (int xline = 0; xline < 8; xline++) // Loop over 8 bits of one row
				{
					if((pixel & (0x80 >> xline )) !=0 ) // Check if the current evaulated pixel is set to 1
					{ // 0x80 >> xline scans through the byte, one bit a a time 
						if (gfx[(x + xline + ((yline) * 64))]  == 1) // check if the pixel on the display is set to 1. 
							V[0xF] = 1; // if the value is 1, we need to register the collision by setting the VF register
						gfx[x + xline + ((y + yline) * 64)] ^= 1; // set the pixel value by using XOR		
					}
			}
		}

		//drawFlag = true; // we changed our gfx[] array and need to update the screen
		pc +=2; // update the program counter to move to the next opcode

		
	}
	break;


	case 0x8004: // ADD Vx and Vy, If result is greater than 8 bits, VF is set to 1
		if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]))
    		V[0xF] = 1; //carry
  		else
			V[0xF] = 0;
			V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
			pc += 2;          
		break;

	case 0xE000:
		switch(opcode & 0x00FF)
		{
			//EX9E : Skips the next instruction
			// if the key stored in VX is pressed

			case 0x009E:
				if (key[V[(opcode & 0x0F00) >> 8]] !=0)
					pc+=4;
				else
					pc+=2;
				break;


		}




		default:
		printf("Unknown opcode:0x%X\n", opcode);


	// Execute Opcode

	// Update timers

	if (delay_timer > 0){
		--delay_timer;
	}
 
	if(sound_timer > 0)
	{
		if(sound_timer == 1)
			printf("BEEP!\n");
			--sound_timer;
	}
}
}