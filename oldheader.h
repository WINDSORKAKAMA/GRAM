// use in stack.c and newram.c
#if !defined (GLOBAL)
#define GLOBAL 0

	#include <string.h>						// include strcmp()
	#include <stdbool.h>					// include bool

	#define RAM_SIZE 8704

	#define	_BIT_MAX_08 0xFF				// 2^8-1 
	#define	_BIT_MAX_16 0xFFFF				// 2^16-1 
	#define _BIT_MAX_24 0xFFFFFF			// 2^24-1 
	#define _BIT_MAX_32 0xFFFFFFFF       	// 2^32-1  
	#define _BIT_MAX_40 0xFFFFFFFFFF		// 2^40-1 
	#define _BIT_MAX_48 0xFFFFFFFFFFFF		// 2^48-1 
	#define _BIT_MAX_56 0xFFFFFFFFFFFFFF	// 2^56-1 
	#define _BIT_MAX_64 0xFFFFFFFFFFFFFFFF	// 2^64-1

	#define BYTE_MAX 8
	#define TWO_BYTE_MAX 16
	#define	THREE_BYTE_MAX 24
	#define FOUR_BYTE_MAX 32
	#define FIVE_BYTE_MAX 40
	#define SIX_BYTE_MAX 48
	#define SEVEN_BYTE_MAX 56
	#define EIGHT_BYTE_MAX 64

	typedef struct{
		union{
			double f64;						// used to store 64 bit float o bouble precision
			float f32;						// used to store 32 bit float or single precision float
			
			long i64;

			union{
				long i64;					// used to store 64 bit signed integer
				unsigned long u64;			// used to store signed 64 bit unsigned integer

				int i32;					// used to store 32 bit signed integer
				unsigned u32;				// used to store 32 bit unsigned integer

				short i16;					// used to store 16 bit signed integer
				unsigned short u16;         // used to store 16 bit unsigned integer or double size char aka wchar_t

				char c8;					// used to store signed char or 8 bit signed integer
				unsigned uc8;				// used to store unsigned char 8 bit unsigned integer
			};
		};

		union{
			double* fptr;				// used to point to either a 32 or 64 bit float
			long* iunptr;				// can be used to point to any member of integer union
			char* str;					// can be used as string replacement
		};
	}memory;

	unsigned char getinput(char usrinput){


	}

	typedef struct registers{
		union{								// data register containing pointers to the data
			long *ip;						// pointer to integer
			double* fp;						// pointer to float
			char* cp;						// pointer to characters				

			double** pfp;					//	pointer to pointer to float
			long** pip;						//	pointer to pointer to int
			char** sp;						//	pointer to pointer to char
		};

		// initialization bytes containing 1 for in use and 0 for not in use
		bool byte_1;		// first byte  
		bool byte_2;		// second byte
		bool byte_3;		// third byte
		bool byte_4;		// fourth byte
		bool byte_5;		// fifth byte
		bool byte_6;		// sixth byte
		bool byte_7;		// seventh byte
		bool  byte_8;		// eighth byte
	}reg;

	/*
	extern bitstore=INIT_BIT;			// (0x0 + 1) = 1, (1 * 2) = 2, (2 ^ 2) = 4

	#define MIN_LOOP_TIMES 1			// if you want to get 2^1 
	#define	BYTE_MAX 8					// if you want to get 2^8
	#define	TWO_BYTE_MAX 16				// if you want to get 2^16
	#define FOUR_BYTE_MAX 32            // if you want to get 2^32
	#define MAX_LOOP_TIMES 64			// if you want to get 2^64

			unsigned char store=mem->u64&_56_BIT_MAX;
			mem->u64=0;
			mem->u64=mem->uc8;
			mem->64=mem->64|store;
	*/ 

	// increment index when nth bit is full for nth data size
	/*
	
	*/int checkRem(memory* mem, char* addr){ // *addr is the current address
		if(mem->i64==NULL||mem->u64==NULL){
			// code for transorming the indexes
			return sizeof(mem->u64)*_BIT_MAX_08;
		}
		else{
			for(int i=0; i<sizeof(*addr); i++){
				if(addr[i++]=='a'&&addr[++i]=='0'){
					char store=mem->i64;							// quantize to store only the last 8 bits
					//(mem->u64>>BYTE_MAX)=mem->uc8;					
					//(mem->u64<<BYTE_MAX)+=store;
					 
					mem->u64>>=BYTE_MAX;							// shift to the next free byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=BYTE_MAX;							// shift it to the previous byte
					mem->u64|=store;								// fill the previous byte with the original data
																	// as well as the new byte having new data
					
					return EIGHT_BYTE_MAX-TWO_BYTE_MAX;
				}
				else if(addr[i++]=='b'||addr[++i]=='0'){
					short store=mem->i64;							// quantize to store only the last 16 bits
					mem->u64>>=TWO_BYTE_MAX;						// shift to the next free byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=TWO_BYTE_MAX;						// shift it to the previous 2 bytes
					mem->u64|=store;								// fill the previous 2 bytes with the original data
																	// as well as the new byte containing the new data
					
					return EIGHT_BYTE_MAX-THREE_BYTE_MAX;
				}
				else if(addr[i++]=='c'||addr[++i]=='0'){
					int store=mem->i64;								// quantize to store only the last 24 bits
					mem->u64>>=THREE_BYTE_MAX;						// shift to the next free byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=THREE_BYTE_MAX;						// shift it to the previous 3 bytes
					mem->u64|=store;								// fill the previous 3 bytes with the original data
																	// as well as the new byte containing the new data
					
					return EIGHT_BYTE_MAX-FOUR_BYTE_MAX;
				}
				else if(addr[i++]=='d'||addr[++i]=='0'){
					int store=mem->i64;								// quantize to store only the last 32 bits
					mem->u64=mem->u64>>FOUR_BYTE_MAX;				// shift to the next free byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64=mem->u64<<FOUR_BYTE_MAX;				// shift it to the previous 4 bytes
					mem->u64=mem->u64|store;						// fill the previous 4 bytes with the original data
																	// as well as the new byte containing the new data
					
					return EIGHT_BYTE_MAX-FIVE_BYTE_MAX;
				}
				else if(addr[i++]=='e' && addr[++i]=='0'){
					long store=mem->i64;							// quantize to store only the last 40 bits
					mem->u64>>=FIVE_BYTE_MAX;						// shift to the next free byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=FIVE_BYTE_MAX;						// shift it to the last 5 bytes
					mem->u64|=store;								// fill the last 5 bytes with the original data
																	// as well as the new byte containing the new data
					
					return EIGHT_BYTE_MAX-SIX_BYTE_MAX;	
				}
				else if(addr[++i]='f'&&addr[i++]=='0'){
					long store=mem->i64;							// quantize to store only the last 48 bits
					mem->u64>>=SIX_BYTE_MAX;						// shift to the last byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=SIX_BYTE_MAX;						// shift it left by 6 bytes
					mem->u64|=store;								// fill the last 6 bytes with the original data
																	// as well as the the last containing the new data
					
					return EIGHT_BYTE_MAX-SEVEN_BYTE_MAX;			
				}
				else if(addr[i++]=='g'&&addr[++i]=='0'){
					long store=mem->i64;							// quantize to store only the last 7 bits
					mem->u64>>=SIX_BYTE_MAX;						// shift to the last byte
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=SIX_BYTE_MAX;						// shift it left by 7 bytes
					mem->u64|=store;								// fill the last 7 bytes with the original data
																	// as well as the the last containing the new data

					return EIGHT_BYTE_MAX-EIGHT_BYTE_MAX;			// address is full
				}
				else if(addr[i++]=='a'||addr[++i]=='b'){
					long store=mem->i64;							// quantize to store only the last 16 bits
					mem->u64>>=TWO_BYTE_MAX;						// shift to the next 2 bytes
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=TWO_BYTE_MAX;						// shift it to the previous 2 bytes
					mem->u64|=store;								// fill the byte with the original data
																	// as well as the 2 new bytes containing new data
					
					return EIGHT_BYTE_MAX-FOUR_BYTE_MAX;
				}
				else if(addr[i++]=='b'||addr[++i]=='c'){
					long store=mem->i64;							// quantize to store only the last 32 bits
					mem->u64>>=TWO_BYTE_MAX;						// shift to the next 2 bytes
					mem->u64=mem->uc8;								// place data in memory
					mem->u64<<=TWO_BYTE_MAX;						// shift it to the previous 4 bytes
					mem->u64|=store;								// fill the last 4 bytes with the original data
																	// as well as the 2 new bytes containing new data
					
					return EIGHT_BYTE_MAX-FOUR_BYTE_MAX;
				}
				else if(addr[i++]=='c'||addr[++i]=='d'){
					
				}
				else if(addr[i++]=='d'||addr[++i]=='e'){
					
				}
				else if(addr[i++]=='e'||addr[++i]=='f'){
					
				}
				else if(addr[i++]=='f'||addr[++i]=='g'){
					
				}
				else if(addr[i++]=='g'||addr[++i]=='h'){
					
				}
				// full
				if(addr[i++]=='e'||addr[++i]=='h'){
					
				}
			}
		}
	}
	void index(int size, reg* data, memory* place){
		if(size=8){
			
			data->byte_8=1;
			data->byte_7=data->byte_6=data->byte_5=data->byte_4=data->byte_3=data->byte_2=data->byte_1=0;
		}
		if(size=4){
			data->byte_4=1;
			data->byte_8=data->byte_7=data->byte_6=data->byte_5=data->byte_3=data->byte_2=data->byte_1=0;
		}
		if(size=2){
			data->byte_2=1;
			data->byte_8=data->byte_7=data->byte_6=data->byte_5=data->byte_4=data->byte_3=data->byte_1=0;
		}
		if(size=1){
			data->byte_1=1;
			data->byte_8=data->byte_7=data->byte_6=data->byte_5=data->byte_4=data->byte_3=data->byte_2=0;
		}
		else{					// if not empty, check how much is left

		}
	}
	// place data in the address and return size left
	int placeData(memory* place, reg* data, char* size){
		//place->
		int s;
		if(strcmp(size, "u64")==0||strcmp(size, "i64")==0){
			// if empty
			s=8;
			index(s,data);
			// else; go to next index
		}
		else if(strcmp(size, "u32")==0||strcmp(size, "i32")==0){ 
			// if empty
			s=4;
			index(s,data);
			//else if byte 4 is already intitialized; fill byte 8
		}
		else if(strcmp(size, "i16")==0||strcmp(size, "u16")==0){
			// if empty
			s=2;
			index(s,data);
		}
		else if(strcmp(size, "uc8")==0||strcmp(size, "c8")==0){
			// if empty
			s=1;
			index(s,data);
		}
		else if (strcmp(size, "f32")==0){
			s=4;
			index(s,data);
		}
		else if (strcmp(size, "f64")==0){
			s=8;
			index(s,data);
		}
		else
			printf("Syntax Error: <Type> <Data>");
	}

	extern memory RAM[RAM_SIZE];
	
#endif

// used by utils.c
#if !defined(INCLUDE_UTILS) 						// aka #ifndef INCLUDE
#define INCLUDE_UTILS 1								// the following code is used by utils.h

	#include <stdio.h>
	#include <stdlib.h>								// include strol() for conversion into a decimal no.

		
	extern memory* sptr; 							// status pointer for returning the number of free cells in the 
													//current address and adresses in the block
	
	extern memory* cmplptr; 						// complex pointer for functions and arrays
	
	void reset(int depth, int rows, int columns);	// free all memory
	
	int getdecdigit(char set);						// get the decimal value of a hexadecimal digit
	extern int htod(char* input, int digitno);		// get the decimal equivalent of a hexadecimal number
	
	extern char placehexdig(int input, char* key);
	extern char* dtohc(int dec_num);
	extern long dtoh(int decnum);					// calculate the decimal equivalent of a decimal number
	
	extern int blockstatus(int* address); 			// calculate the number of free blocks
	
	extern int* address;							// hexadecimal value of address global to the whole program
													// calculate the address of a variable in hexadecimal
													// note that "+1" was used instead of "++" in 
													// CALC_ADDR to prevent side effects
#endif

// Used by stack.c
#ifndef INLCUDE_STACK
#define INCLUDE_STACK 2

	// stack datatype
	typedef struct stack{
		memory *stkptr;								// pointer to memory, used to point to RAM
		int top;									// show the top of the blocks used by the stack
	}st;
	
	extern void createEmptyStack(st *s);
	
	extern int isFull(st *s);
	extern void increaseIndex(st *s);
	extern void push(st *s);
	
	extern int isEmpty(st *s);
	extern void decreaseIndex(st *s);
	extern void pop(st *s);
	
	extern st* printStack(st *s);
#endif