// currently has no way to interact with the underlying stack
// thus the squiggles on the values in the push operation
// this was mearly adopted as a driver for stackexample.c

#include "header.h"

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
