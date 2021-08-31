#include <iostream>

class chip8{

public:
    //The chip 8 has 35 opcodes which are two bytes long
    // opcode is 16 bits, so we'll use a 'short' data type
    unsigned short opcode;
    //The chip 8 has 4K memory total
    unsigned char memory[4096];
    // CPU registers. The Chip 8 has 15, 8 bit general purpose registers
    // named V0, V1, up to VE. The 16th register is used for the carry flag.
    // 8 bits is one byte, therefore we can use a 'char'  :) 
    unsigned char V[16];

    // Define an index register "I"
    // address register I is also 16 bits, so we'll use a 'short' data type
    unsigned short I;

    // Define program counter
    // Program counter values can be 0x000 to 0xFFF
    // 0x000-0x1FF, chip 8 interpreter (contains font of emu)
    // 0x050-0x0A0, used for built in 4x5 pixel font set (0-F)
    // 0x200-0xFFF, used for Program ROM and work RAM
    unsigned short pc;

    // Define the graphics system
    // The chip 8 has one instruction that draws sprites to the screen
    // Drawing is done in XOR mode, and if a pixel is turned off as a result
    // of drawing, the VF register is set. This is used for collision detection.

    // The graphics ofthe chip 8 are black and white and the screen has a total of 
    // 2048 pixels, (64 x 32). This can easily be implemented using an array
    // that holds the pixel state (1 or 0):

    unsigned char gfx[64 * 32];

    // interrupts and hardware registers. The chip 8 has none, but there are 
    // two timing registeres that count to 60 Hz. When set above 0, they will count 
    // down to zero. 
    // The system's buzzer sounds whenever the sound timer reaches zero.
    unsigned char delay_timer;
    unsigned char sound_timer;

    // The chip8 has opcodes that allow the pgoram to jump to 
    // a certain address or call a subroutine.
    // A stack needs to be implemented as part of the interpreter.
    // The stack is sued to remember current location before a "jump" is performed.
    // Before a jump or a call to a subroutine is perfomed, the program counter must 
    // be stored in the stack.
    // There are 16 slots in the stack. You'll need a stack pointer to remember the location.
    unsigned short stack[16];
    unsigned short sp;

    // The chip 8 has a hex based keypad that points to (0x0-0xF).
    // We'll use an array to store the current state of the key.

    unsigned char key[16];

    // This is the chip 8 font set. 
    // Each number or character is 4 pixels wide by 5 pixels high

    unsigned char chip8_fontset[80] = {

    // 0xF0 = 1111 0000 MSB first.
    // 0x90 = 1001 0000
    // 0x90 = 1001 0000
    // 0xF0 = 1111 0000

    // The ones represent the digit, in this case 0.

    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F


    };

    void init();
    void loadRom();
    void emulateCycle();
    void fetch();
    void decode();
    void execute();
    void setKeys();
    void drawGraphics();



	
};
















