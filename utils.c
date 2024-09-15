#include "header.h"

int getdecdigit(char set){
	if(set>='0'&&set<='9'){									// e.g if set='1', number=49-48 
		return set-'0';										// i.e set=1 since '0'=48 and '1'='0'+1=49
	}
	else if(set>='A'&&set<='E'){							// e.g if set='B', number=66-65+10 
		return set-'A'+10;									// i.e set=1+10 thus set=11 since 'A'=65 and 'B'='A'+1=66
	}
	else if(set>='a'&&set<='e'){							// e.g if set='b', number=98-97+10 
		return set-'a'+10;									// i.e set=1+10 thus set=11 since 'a'=97 and 'b'='a'+1=98
	}
	else
		return -1;											// non hex digit was inputed
}
int htod(char* input, int digitno){
	int result=0;
	int power=1;
	
	while (digitno > 0) {
		--digitno;  											// Decrement digitno once at the start of each iteration
		result += (power * gethexdigit(*(input + digitno)));  	// Process current digit
		power *= 16;  											// Adjust power for the next higher place value (move to the next digit)
	}
	return result;
}
int calhexrem(int dividend) {
	return dividend % 16;
}

char placehexdig(int input, const char* key) {
	static const short constval1 = 'A' - 10;  // Uppercase hex values
	static const short constval2 = '0';       // Numeric digits 0-9
	static const short constval3 = 'a' - 10;  // Lowercase hex values

	if (input >= 0 && input <= 9) {
		return input + constval2;
	} 
	else if (input >= 10 && input <= 15) {
		if (strcmp(key, "lower") == 0 || strcmp(key, "lc") == 0 || strcmp(key, "l") == 0 || strcmp(key, "lowercase") == 0) {
			return input + constval3;
		}
		else if (strcmp(key, "upper") == 0 || strcmp(key, "uc") == 0 || strcmp(key, "U") == 0 || strcmp(key, "uppercase") == 0) {
			return input + constval1;
		}
	}
	return -1;  // Error condition if input is out of range
}

char* dtohc(int dec_num) {
	// Allocating space for up to 8 hex digits + null terminator (for a 32-bit number)
	char* hexnum = malloc(9 * sizeof(char));
	int index = 0;

	if (dec_num == 0) {
		hexnum[index++] = placehexdig(0, "upper");
	}
	else {
		while (dec_num > 0) {
			int dec_rem = calhexrem(dec_num);  // Remainder when dividing by 16
			hexnum[index++] = placehexdig(dec_rem, "upper");  // Use uppercase by default
			dec_num /= 16;  // Divide number by 16 for the next iteration
		}
	}

	hexnum[index] = '\0';  // Null-terminate the string

	// Reverse the string to get the correct hexadecimal representation
	for (int i = 0; i < index / 2; i++) {
		char temp = hexnum[i];
		hexnum[i] = hexnum[index - i - 1];
		hexnum[index - i - 1] = temp;
	}

	return hexnum;
}

long dtoh(int decnum) {
	char* hex_str = dtohc(decnum);  // Get the hex string
	char* endptr;

	long int value = strtol(hex_str, &endptr, 16);  // Convert the hex string to a long integer

	// Check if the entire string was successfully converted
	if (*endptr == '\0') {
		free(hex_str);  // Free allocated memory after use
		return value;
	}
	else {
		free(hex_str);  // Free allocated memory before returning error
		return -1;  // Return error code for conversion failure
	}
}

int calcAddr(int address){
	st* mST;
	return address=mST->top+1;
}

void blockstatus(int address){
	
}

// delete all contents in RAM
void reset(){ 
	st* s=(st*)malloc(sizeof(s));
	s->stkptr=&RAM[0];
	int depth=0;
	while(depth<RAM_SIZE){
		pop(s);
		// assign RAM[depth++]='\0'; within pop() in stack.c
	}
	free(s);
}
