//***************************************************************************//
//
//***************************************************************************//

//Pre-Processor Includes and Directives
#include<iostream>
#include<fstream>

//Accessing Namespace Standard
using namespace std;

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
instruc_extract()
{
}

instruc_execute()
{
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
