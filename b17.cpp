//***************************************************************************//
//
//***************************************************************************//

//Pre-Processor Includes and Directives
#include<iostream>
#include<fstream>

//Accessing Namespace Standard
using namespace std;

enum AddrMode {Direct, Indirect, Indexed, Indirect, IndexedIndirect };


                          //Description                        |Addr Modes
                          //-----------------------------------+-------------
enum Operation{HALT = 0,  //Stop Execution                     |Ignored
               NOP  = 1,  //Do Nothing                         |Ignored
               LD   = 16, //Load Accumulator from memory       |All
               ST   = 17, //Store the accumulator in memory    |Not Immidiate
               EM   = 18, //Exchange the accumulator with mem  |Not Immidiate
               LDX  = 24, //Not Implimented                    |
	       STX  = 25, //Not Implimented                    |
               EMX  = 26, //Not Implimented                    |
               ADD  = 32, //Add memory to the accumulator      |All
               SUB  = 33, //Subtr mem from accumulator         |All
               CLR  = 34, //Clear Accumulator                  |Ignored
               COM  = 35, //Compliment Accumulator             |Ignored
               AND  = 36, //AND mem to accumulator             |All
               OR   = 37, //OR mem to accumulator              |All
               XOR  = 38, //XOR mem to accumulator             |All
               ADDX = 40, //Not Implimented                    |
               SUBX = 41, //Not Implimented                    |
               CLRX = 42, //Not Implimented                    |
               J    = 48, //Jump to memory address             |not immidiate
               JZ   = 49, //If accumulator is zero: jump       |not immidiate
               JN   = 50, //If accumulator is negative: jump   |not immidiate
               JP   = 51};//If accumulator is positive: jump   |not immidiate

//Function Prototypes

//Enumerated Types
enum register { MAR ,       //Memory Address Reg - Address of the mem location
                            // to load or store
                IC ,        //Instruction Counter - instruction to be fetched
                X0 ,        //Index Register - Used for calculations
                X1 ,        //Index Register - Used for calculations
                X2 ,        //Index Register - Used for calculations
                X3 ,        //Index Register - Used for calculations
                ABUS ,      //Address Bus - Used when moving addresses
                MDR ,       //Memory Data Reg - Data to write into,
                            // or recently read
                AC ,        //Accumulator
                ALU ,       //Arithmetic-Logic Unit - Performs Computations
                IR ,        //Instruction Register - contains current instruct
                DBUS };     //Data Bus - Used when moving data and instructs

//Global Variables
int reg[12] = { 0 };            //All Registers, index with Enums
int mem[4096] = { 0 };          //Global memory, 24 bits per word

struct Instruction
{
  int operandAddr;
  Operation operation;
  AddrMode mode;
};

//***********************************MAIN************************************//
//***************************************************************************//


main( int argc, char* argv )
{
    //Local Variable Declaration

    //Verify Object file to simulate was passed, exit if no args
    if( argc == 1 )
    {
        cout << "No Object file passed to simulate. Exiting..." << endl;
        return 1;
    }

    //Begin Simulations Loop (Runs all command line Arguments )
    //Open Command Line Object file
}

//Breaks apart the word into the ADDRESS, OPERATION and ADDRESSING MODE
instruc_extract( Instruction &to_extract, int location )
{
}

int instruc_execute( )
{
  Instruction instruct;
  instruc_extract( instruct, reg[IC] );
  //Impliment HALT
  if( instruct.operation == HALT )
  {
    return -1;//Stop Execution loop:
  }
  //Impliment NOP
  else if( instruct.operation == NOP )
  {
    //Do nothing
  }
  //Impliment CLR
  else if( instruct.operation == CLR )
  {
    reg[AC] = 0;
  }
  //Impliment COM
  else if( instruct.operation == COM )
  {
    reg[ALU] = ^reg[AC];
    reg[AC] = ^reg[ALU];
  }
  //Impliment Instructions That accept all addressing modes
  else if( instruct.operation == LD  ||
           instruct.operation == ADD ||
           instruct.operation == SUB ||
           instruct.operation == AND ||
           instruct.operation == OR  ||
           instruct.operation == XOR )
  {
    //Do operand fetching for the instruction
    if( mode == Direct )
    {
      reg[DBUS] = instruct.operandAddr;
    }
    else if( mode == Immidiate )
    {
      reg[ABUS] = instruct.operandAddr;
      reg[DBUS] = mem[reg[ABUS]];
      reg[MDR]  = reg[DBUS];
    }
    else if( mode <= IndexedIndirect )
    {
      return -3; //Unsupported Addressing Modes
    }

    if( instruct.operation == LD )
    {
      reg[AC] = reg[DBUS];
    }
  }
  else
  {
    return -2; //Illegal Addressing Mode
  }

  
}


//Gives a null terminated string of the instruction being exected (e.g. ADD)
instruc_abbrv()
{
}

instruc_print()
{
}



//Reads the specified object file into memory
//Returns: byte in memory for IC (Program Start Location)
int read_file( char *file )
{
}

//Fetch next instruction to instruction register
//Increments IC to next instruction
fill_IR()
{
}
