// potential new features to add to stack.c

#include "header.h"

#define BYTE_MAX 0xFF
#define TWO_BYTE_MAX 0xFFFF
#define FOUR_BYTE_MAX 0xFFFFFFFF   
#define EIGHT_BYTE_MAX 0xFFFFFFFFFFFFFFFF

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

// note to self: generate a function that can modify currentaddr to update it after every push() or pop() operation

void pop(st* ptr, int currentaddr, char* data_type){
    if(isEmpty(ptr))
        printf("\n !!!Stack Error \n");

    else{
        // stores minimum size of the datatype
        int typesize; 

        // stores the size remaining memory in the current address
        int size;

        calcRem(currentaddr, &size);

        if(strcmp(*data_type, "i64")==0||(strcmp(*data_type, "f64") == 0))
            typesize=EIGHT_BYTES;

        else if(strcmp(*data_type, "i32") == 0||strcmp(*data_type, "f32") == 0)
            typesize=FOUR_BYTES;


        else if(strcmp(*data_type, "i16") == 0)
            typesize=TWO_BYTES;

        else if(strcmp(*data_type, "i8") == 0)
            typesize=ONE_BYTES;

        else
            printf("Error!");

        if(size<=typesize){
            size+=typesize;

            if(typesize==8)
                ptr->stkptr->l&=EIGHT_BYTES-size-EIGHT_BYTE_MAX;

            else if(typesize==4)
                ptr->stkptr->l&=EIGHT_BYTES-size-FOUR_BYTE_MAX;

            else if(typesize==2)
                ptr->stkptr->l&=EIGHT_BYTES-size-TWO_BYTE_MAX;
            
            else if(typesize==1)
                ptr->stkptr->l&=EIGHT_BYTES-size-BYTE_MAX;
        }
        
        else
            RAM[ptr->top--]=*ptr->stkptr;
    }
}

/*
OLD VERSION
void pop(st *s, st data){
	s->stkptr=&data;
	if(isEmpty(s))
		printf("\n !!!Stack Error \n");
	else {
		//*s->stkptr='\0'; // Error
		RAM[s->top--]=*s->stkptr;
	}
}
*/

/*
    pop(st* ptr, int* current_address, char* data_type){     // should use the data type to remove the data by some typesize
        ... ...                                              // this typesize should be less than or equal to the amount of the 
                                                             // RAM block space used
    }

    Theory:
    Preserve the last n bits
    Where n is a multiple of 8 
    *ptr->stkptr->l&=N_BYTE_MAX                               // preserve a certain no of bits
    
    recalculate *sizec                                        // note to self: transfer the *sizec calculation to a  separate function
                                                              // make bin_const a static global const int array
                                                              // so as to calculate the current address outside of push() i.e within pop()

 */