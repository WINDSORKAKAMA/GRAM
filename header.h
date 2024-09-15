// use in stack.c and newram.c
#if !defined (GLOBAL)
#define GLOBAL 0

	#include <string.h>					    // include strcmp()
    #include <stdio.h>              
	#define RAM_SIZE 8704

typedef union{
    unsigned long l;                            // perform the operations and stores int data_in
    double f;                                   // stores float data_in
}memory;

extern st RAM[RAM_SIZE];

extern int* address;							// hexadecimal value of address global to the whole program
												// calculate the address of a variable in hexadecimal
												// note that "+1" was used instead of "++" in 
												// CALC_ADDR to prevent side effects

    // input variables store data given by users
    typedef union{
        long *i64;                              // stores 64 bit int
        int *i32;                               // stores 32 bit int 
        short *i16;                             // stores 16 bit int and 16 bit char
        char *i8;                               // stores 8 bit int and 8 bit char

        double *f64;                            // stores 64 bit float
        float *f32;                             // stores 32 bit float
    }input;
#endif


// used by utils.c
#if !defined(INCLUDE_UTILS) 						// aka #ifndef INCLUDE
#define INCLUDE_UTILS 1								// the following code is used by utils.h

	#include <stdlib.h>                             // include strol() for conversion into a decimal no.

	void reset(int* currentaddr, int* index, int);  // free all memory 
	
	int getdecdigit(char);  						// get the decimal value of a hexadecimal digit
	extern int htod(char*, int);    	        	// get the decimal equivalent of a hexadecimal number
	
	extern char placehexdig(int, char*);
	extern char* dtohc(int);
	extern long dtoh(int);					        // calculate the decimal equivalent of a decimal number
	
	extern int blockstatus(int*); 			        // calculate the number of free blocks
#endif


// Used by stack.c
#ifndef INLCUDE_STACK
#define INCLUDE_STACK 2

	// stack datatype
	typedef struct stack{
		memory *stkptr;								    // pointer to memory, used to point to RAM
		int top;									    // show the top of the blocks used by the stack
	}st;
	
	extern void createEmptyStack(st *s);
	
	extern int isFull(st*);
	extern int isEmpty(st*);
	
	extern memory printStack(st*);

    // used by calcRem();
    #define EIGHT_BYTES 0x40
    #define SEVEN_BYTES 0x38
    #define SIX_BYTES 0x30
    #define FIVE_BYTES 0x28
    #define FOUR_BYTES 0x20
    #define THREE_BYTES 0x18
    #define TWO_BYTES 0x10
    #define ONE_BYTES 0x8

    extern void calcRem(int, int *);

    extern void push(st*, int, char*, input);

    // used by pop()
    #define BYTE_MAX 0xFF
    #define TWO_BYTE_MAX 0xFFFF
    #define FOUR_BYTE_MAX 0xFFFFFFFF   
    #define EIGHT_BYTE_MAX 0xFFFFFFFFFFFFFFFF

    extern void pop(st*, int, char*);
#endif


#ifndef HELP
    #define HELP "The array static const int sizeloc[18] stores the following numbers: 97, 98, 99, 100, 101, 102, 103,\
    104, 195, 197, 199, 201, 203, 205, 207, 394, 410, 804\n\
    The above are the decimal equivalents for the binary address size codes in sizeloc[] within push().\nIn sizeloc[],\n\
    The first 8 each represent 8 bit int or 8 bit char\n\
    The next 7 each represent 16 bit int or 16 bit char\n\
    The next 2, 394 or 410 can represent 32 bit int or single precision float\n\
    The last number, 804 can represent 64 bit int or double precision float\n\
    The idea is that you can use these magic numbers to represent the size of part of an 8 byte address\n\
    while also shrinking the size of the function returning the size left.\n\
    I actually opted for a funtion to denote size used since it will always be less than 8 bytes.\n\
    Thus, easing calculation of size left.\
    When storing data_in, check whether the current address has enough space left for it.\n\
    If the size left is not enough to store the new data_in, skip to the next 8 byte address and store it there.\n\n\
    You may later optimize this algorithm.\n\n\
    Also, you may store size and assign a sizeloc number to a struct variable to enable the system to\
    optimize memory usage that is, by assigning data_in that fits into this memory\n\
    Also, later, you may think of upgrading the system to support functions and arrays."
#endif


#if !defined(NEW_FEATURES)
    #define NEW_FEATURES "The original address numbering system used letters a through h to represent\
    address sizes. according to the following rules:\n8 bit integers and characters are represented using\
    a0, b0, c0, ..., h0.\n16 bit integers and wide characters are represented using ab, bc, cd, ..., gh.\n\
    32 bit integers and single precision floating point decimals are represented using abcd and efgh.\n\
    64 bit integers and double precision floating point decimals are represented by abcdefgh.\n\
    The original system planned to add these at the beginning of the address after\
    \"0x\" but this was deemed too complex. Thus a new system was made.\
    The new system uses the sum-of-integer method to get the numeric equivalents of the letter arrangements above.\n\"
#endif


#ifndef VERSION   
    #define VERSION "0.2.1"
#endif
