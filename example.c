// test to see if char is signed or unsigned on this machine
#include <stdio.h>
#include <limits.h>

int main(void){
    if(CHAR_MIN<0)
        printf("char is signed\n");

    else
        printf("char is unsigned\n");
}