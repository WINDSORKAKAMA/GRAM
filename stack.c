// create an emty stack
#include "header.h"
// #include <string.h> dont forget to add this for string comparisons
// create an empty stack
void createEmptyStack(st *s) {	
 	s->top=-1;			
}

// Check if the stack is full
int isFull(st *s) {							
	if (s->top == RAM_SIZE-1)		
		return 1;
	else
		return 0;																	
}

// Check if the stack is empty
int isEmpty(st *s) {					

	if (s->top == -1)
		return 1;
	else
		return 0;
}

#define EIGHT_BYTES 0x40
#define SEVEN_BYTES 0x38
#define SIX_BYTES 0x30
#define FIVE_BYTES 0x28
#define FOUR_BYTES 0x20
#define THREE_BYTES 0x18
#define TWO_BYTES 0x10
#define ONE_BYTES 0x8

void calcRem(int currentaddr, int *sizec){
    // for more info, go to HELP near the end in header.h
    static const int bin_const[]={0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0xC3, 
                                0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xCF, 0x18A, 0x19A, 0x324};

    if(currentaddr&bin_const[17]||currentaddr&bin_const[16]||
        currentaddr&bin_const[7]||currentaddr&bin_const[14])
        *sizec = EIGHT_BYTES-EIGHT_BYTES;

    else if(currentaddr&bin_const[6]||currentaddr&bin_const[13])
        *sizec = EIGHT_BYTES-SEVEN_BYTES;

    else if(currentaddr&bin_const[5]||currentaddr&bin_const[12])
        *sizec = EIGHT_BYTES-SIX_BYTES;

    else if(currentaddr&bin_const[4]||currentaddr&bin_const[11])
        *sizec = EIGHT_BYTES-FIVE_BYTES;

    else if(currentaddr&bin_const[3]||currentaddr&bin_const[10]||
        currentaddr&bin_const[9]||currentaddr&bin_const[15])
        *sizec = EIGHT_BYTES-FOUR_BYTES;

    else if(currentaddr&bin_const[2]||currentaddr&bin_const[9])
        *sizec = EIGHT_BYTES-THREE_BYTES;

    else if(currentaddr&bin_const[1]||currentaddr&bin_const[8])
        *sizec = EIGHT_BYTES-TWO_BYTES;

    else if(currentaddr&bin_const[0])
        *sizec = EIGHT_BYTES-ONE_BYTES;

    else
        *sizec = EIGHT_BYTES;
}

// push new elements to RAM
void push(st* ptr, int currentaddr, char* data_type, input data_in){
    // size counter - stores the size of the data_in in use in current block
    static int sizec;

    void calcRem(currentaddr, &sizec);

    // input data into the desired format -> the type should be declared in the inputs struct
    long store = ptr->stkptr->l;
    ptr->stkptr->l >>= sizec;
    currentaddr <<= 10;				            // multiply address by 2^10 to fit int the size code,
                                                // which is anywhere from 7 to 10 bits wide

    if(isfull(ptr))
		printf("Stack Overflow");

    else{
        int size;
        if(strcmp(*data_type, "i64") == 0){
            ptr->stkptr->l=data_in.i64;
            size=8;
        }

        else if (strcmp(*data_type, "f64") == 0){
            size=8;
            ptr->stkptr->f = *data_in.f64;
        }

        else if(strcmp(*data_type, "i32") == 0){
            size=4;
            ptr->stkptr->l = *data_in.i32;
        }

        else if (strcmp(*data_type, "f32") == 0){
            size=4;
            ptr->stkptr->l = *data_in.f32;
        }

        else if(strcmp(*data_type, "i16") == 0){
            size=2;
            ptr->stkptr->l = *data_in.i16;
        }

        else if(strcmp(*data_type, "i8") == 0){
            size=1;
            ptr->stkptr->l = *data_in.i8;
        }

        else
            printf("Error!");

        if (size>sizec){
            RAM[ptr->top++]=*ptr->stkptr;
            sizec=EIGHT_BYTES;
        }

        ptr->stkptr->l <<= sizec;
        ptr->stkptr->l |= store;
        
        // calculate the new address using sizec and place in currentaddr
    }
}

/*
    pop(st* ptr, int* current_address,char* data_type){     // should use the data type to remove the data by some size
        ... ...                                        // this size should be less than or equal to the amount of the 
                                                       // RAM block space used
    }

    Theory:
    Preserve the last n bits
    Where n is a multiple of 8 between 8-64 
 */
// pop element off the stack and return memory to RAM


// print elements of ram
memory printStack(st* s){
	for(int i=0; i<RAM_SIZE; i++)
		s->stkptr=&RAM[i++];

	return *s->stkptr;
}