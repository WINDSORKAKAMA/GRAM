#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int count = 0;

// Creating a stack
struct stack {
  int items[MAX];							// buffer that can hold numbers
  int top;									// show the top of the stack
};
typedef struct stack st;					// st can be used to declare structures of type stack

void createEmptyStack(st *s) {				// takes argument as a pointer to stack
  s->top = -1;								// top=-1 signaling that the stack is empty
}

// Check if the stack is full
int isfull(st *s) {							
  if (s->top == MAX - 1)					// if is equal to 9, the stack is full
    return 1;								// signifies that the stack is full
  else
    return 0;								// signifies that the stack is not full
}

// Check if the stack is empty
int isempty(st *s) {					
  if (s->top == -1)							// if top==1 , the stack is empty
    return 1;								// signifies that stack is empty
  else
    return 0;								// signifies that stck is not empty
}

// Add elements into stack
void push(st *s, int newitem) {				// takes a stack pointer and an integer as arguments
  if (isfull(s)) {							// check whether stack is full and print a message if true
    printf("STACK FULL");
  } else {									
    s->top++;								// otherwise, increment top by 1
    s->items[s->top] = newitem;				// place the new item in the next free index of items[]
  }
  count++;									// count the number of push operations
}

// Remove element from stack
void pop(st *s) {
  if (isempty(s)) {
    printf("\n STACK EMPTY \n");					// check whether stack is empty and print a message if true
  } else {
    printf("Item popped= %d", s->items[s->top]);	// print the item to be popped
    s->top--;										// otherwise, decrement top by 1 to allow overriding 
    												    // the "popped" element in the next push operation
  }
  count--;											// count the number of pop operations
  printf("\n");								
}

// Print elements of stack
void printStack(st *s) {
  printf("Stack: ");
  for (int i = 0; i < count; i++) {				// print out all stack elements
    printf("%d ", s->items[i]);
  }
  printf("\n");
}

// Driver code
int main() {
  int ch;
  st *s = (st *)malloc(sizeof(st));				// dynamically allocate memory for s which is a pointer to st

  createEmptyStack(s);							// create a new stack using s

  push(s, 1);									// push 1 to stack s
  push(s, 2);									// push 2 to stack s
  push(s, 3);									// push 3 to stack s
  push(s, 4);									// push 4 to stack s

  printStack(s);								// print 1, 2 3 and 4

  pop(s);										// pop 4 from the stack

  printf("\nAfter popping out\n");				// print 1, 2 and 3
  printStack(s);							// print elements ot the stack
  
  free(s);									// I deallocated the memory  for s which the writer forgot to do		
}



/* 
	This stack program uses a function, createEmptyStack() to create a stack
	The push operation may be borrowed
	The pop operation doesn't delete any element but instead allows for overriding the "popped" element
	ALSO, the pop operation prints out some text, which is not what I want
o	In your version, /0 should signify empty area such that you can track how full or empty it is
*/