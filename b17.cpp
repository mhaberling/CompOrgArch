//***************************************************************************//
//
//***************************************************************************//

//Pre-Processor Includes and Directives
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <cstring>

//Accessing Namespace Standard
using namespace std;

enum AddrMode {Direct, 
               Immidiate, 
               Indexed, 
               Indirect, 
               IndexedIndirect,
               Illegal};

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
               J    = 48, //Jump to memory address             |Not immidiate
               JZ   = 49, //If accumulator is zero: jump       |Not immidiate
               JN   = 50, //If accumulator is negative: jump   |Not immidiate
               JP   = 51  //If accumulator is positive: jump   |Not immidiate
               };
//Function Prototypes

//Enumerated Types
enum Register { MAR ,       //Memory Address Reg - Address of the mem location
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

int instruc_execute();

bool OppNotImplimented  ( Operation toTest );
bool IgnoredAddrOpp     ( Operation toTest );
bool AllAddrOpp         ( Operation toTest );
bool NotImmidiateAddrOpp( Operation toTest );
int read_file( char *file );

//***********************************MAIN************************************//
//***************************************************************************//


main( int argc, char* argv[] )
{
    reg[IC] = read_file( argv[1] ); //X0 now contains program start
    if( reg[IC] == -1 )
    {
        cout << "Object File is improperly formated or does not exist.\n"
             << "Exiting..." << endl;
        return -1;
    }
    cout << "Starting on Instruction Address: " << std::hex << reg[IC] << endl;

    while( instruc_execute() == 0 )
      cout << "Instruc Executed!" << endl;
}

//***************************************************************************//
// int instruc_extract()                                                     //
//                                                                           //
// Author: Jason Anderson                                                    //
//                                                                           //
// Description: Instruct extract takes what is in a memory location and      //
//		breaks it down into the address (bits 23-12), instruction    //
//		(bits 11-6) and mode (bits 5-2).  It then sets the           //
//		corresponding variable in the instruction structure to the   //
//		correct value.                                               //
//                                                                           //
// Returns  None                                                             //
//                                                                           //
//***************************************************************************//
void instruc_extract( Instruction &to_extract, int location )
{
  int addrMask[12][2] = {{8388608, 2048},
                         {4194304, 1024},
                         {2097152, 512},
                         {1048576, 256},
                         {524288, 128},
                         {262144, 64},
                         {131072, 32},
                         {65536, 16},
                         {32768, 8},
                         {16384, 4},
                         {8192, 2},
                         {4096, 1}};

  int instrMask[6][2] = {{2048,32},
                         {1024,16},
                         {512,8},
                         {256,4},
                         {128,2},
                         {64,1}};

  int modeMask[4][2]  = {{32,8},
                         {16,4},
                         {8,2},
                         {4,1}};

  int address = 0;
  int instruction = 0;
  int mode = 0;

  for(int i = 0; i < 12; i++)
    if(location >= addrMask[i][0])
    {
      location -= addrMask[i][0];
      address += addrMask[i][1];
    }

  for(int i = 0; i < 6; i++)
    if(location >= instrMask[i][0])
    {
      location -= instrMask[i][0];
      instruction += instrMask[i][1];
    }

  for(int i = 0; i < 4; i++)
    if(location >= modeMask[i][0])
    {
      location -= modeMask[i][0];
      mode += modeMask[i][1];
    }

  to_extract.operandAddr = address;
  to_extract.operation = Operation(instruction);
  to_extract.mode = AddrMode(mode);
}


//Gives a null terminated string of the instruction being exected (e.g. ADD)
void instruc_abbrv()
{
}

void instruc_print()
{
}



//Reads the specified object file into memory
//Returns: byte in memory for IC (Program Start Location)
int read_file( char *file )
{
  //Local Variable Declaration
  fstream fin;                //File containing program to be read

  //Open File specified on command line
  fin.open( file );
 
  //Failed to open file to be read, exit program
  if( !fin )
  {
    return -1;
  }

  //int mem[4096], global virtual memory

  while( !fin.eof() )
  {  
    fin >> hex >> reg[MAR];
        //Should error check to verify we got a number back
    if( fin.eof() ) //End of file flag tripped, last address read is start
    {
      return reg[MAR];
    }

        //Get and store counter
    fin >> dec >> reg[X3];

        //Read counter(reg[AC]) times and store it sequentially in memory
    for( reg[AC] = 0; reg[AC] < reg[X3]; reg[AC]++ )
    {
      fin >> hex >> reg[MDR];
      mem[ reg[MAR]+reg[AC] ] = reg[MDR];
    }
  }

    return reg[MAR];
}


//Fetch next instruction to instruction register
//Increments IC to next instruction
//void fill_IR()
//{
//}

//***************************************************************************//
// int instruc_execute()                                                     //
//                                                                           //
// Author: Marcus Haberling                                                  //
//                                                                           //
// Description: Instruct execute takes the instruction stored in memory as   //
//              specified in the Instruction Counter register (IC). It then  //
//              executes the operation and alters the gloabal register array //
//              to reflect the operation. It also returns error codes if the //
//              HALT instruction is called, if the addressing mode is not    //
//              implimented, the instruction is not implimented, or if the   //
//              addressing mode is not allowed by the instruction.           //
//                                                                           //
// Returns  0: Operation executed                                            //
//         -1: Halt operation executed                                       //
//         -2: Operation not implimented                                     //
//         -3: Address mode not implimented by the simulator                 //
//         -4: Illegal addressing mode for the operation                     //
//         -5: This should never happen. What did you do?                    //
//                                                                           //
//***************************************************************************//
int instruc_execute( )
{
  Instruction instr;
  instruc_extract( instr, reg[IC] );
  cout<< "Extracted Instruction" << endl 
      << instr.operandAddr << endl 
      << instr.operation << endl << instr.mode << endl;
  reg[IC]++;

  if( OppNotImplimented( instr.operation ) )
  {
    cout << "Operation not implimented by virtual machine." << endl;
    return -2;
  }
  else if ( IgnoredAddrOpp ( instr.operation ) )
  {
    switch( instr.operation )
    {
    case NOP:
      break;
    case HALT:
      cout << "Program Execution Halted" << endl;
      return -1;
      break;
    case CLR:
      reg[AC] = 0;
      break;
    case COM:
      reg[AC] = ~reg[AC];
      break;
    }
    return 0;
  }
  else if ( AllAddrOpp( instr.operation ) )
  {
    if( instr.mode == Direct  )
    {
      reg[ABUS] = instr.operandAddr;
      reg[MDR]  = mem[reg[ABUS]];
      reg[ALU]  = reg[MDR]; 
    }
    else if ( instr.mode == Immidiate )
    {
      reg[ALU] = instr.operandAddr;
    }
    else if ( instr.mode >= Indexed && instr.mode <= IndexedIndirect )
    {
      cout << "Address Mode not implimented." << endl;
      return -3;
    }
    else
    {
      cout << "Illegal Addressing Mode" << endl;
      return -4;
    } 
    switch( instr.operation )
    {
      case LD:
        reg[AC] = reg[ALU];
        break;
      case ADD:
        reg[AC] = reg[AC] + reg[ALU];
        break;
      case SUB:
        reg[AC] = reg[AC] - reg[ALU];
        break;
      case AND:
	reg[AC] = reg[AC] & reg[ALU];
        break;
      case OR:
	reg[AC] = reg[AC] | reg[ALU];
	break;
      case XOR:
	reg[AC] = reg[AC] ^ reg[ALU];
	break;
    }
    return 0;
  }
  if ( NotImmidiateAddrOpp( instr.operation ) )
  {
    if( instr.mode == Direct  )
    {
      reg[ABUS] = instr.operandAddr;
      reg[MDR]  = mem[reg[ABUS]];
      reg[ALU]  = reg[MDR]; 
    }
    else if ( instr.mode >= Indexed && instr.mode <= IndexedIndirect )
    {
      cout << "Address Mode not implimented." << endl;
      return -3;
    }
    else
    {
      cout << "Illegal Addressing Mode" << endl;
      return -4;
    } 
    switch( instr.operation )
    {
      case ST:
	reg[ABUS] = reg[ALU];
	mem[reg[ABUS]] = reg[AC];
	break;
      case EM:
	reg[ABUS] = reg[ALU];
	reg[MDR]  = mem[reg[ABUS]];
	mem[reg[ABUS]] = reg[AC];
	reg[AC]   = reg[MDR];
	break;
      case J:
	reg[IC] = reg[ALU];
	break;
      case JZ:
	if( reg[AC] == 0 )
	  reg[IC] = reg[ALU];
	break;
      case JN:
	if( reg[AC] < 0 )
	  reg[IC] = reg[ALU];
	break;
      case JP:
	if( reg[AC] > 0 )
	  reg[IC] = reg[ALU];
	break;
    }
    return 0;
  }
  else
  {
    return -5; //This shouldn't be possible
  }
}

bool OppNotImplimented( Operation toTest )
{
  return ( toTest == LDX  ||
	   toTest == STX  ||
	   toTest == EMX  ||
	   toTest == ADDX ||
	   toTest == SUBX ||
	   toTest == CLRX
	   );
}

bool IgnoredAddrOpp( Operation toTest )
{
  return ( toTest == HALT ||
           toTest == NOP  ||
           toTest == CLR  ||
           toTest == COM 
	 );
}

bool AllAddrOpp( Operation toTest )
{
  return ( toTest == LD  ||
	   toTest == ADD ||
	   toTest == SUB ||
	   toTest == AND ||
	   toTest == OR  ||
	   toTest == XOR 
	 );
}

bool NotImmidiateAddrOpp( Operation toTest )
{
  return ( toTest == ST ||
	   toTest == EM ||
	   toTest == J  ||
	   toTest == JZ ||
	   toTest == JN ||
	   toTest == JP
	 );
}
