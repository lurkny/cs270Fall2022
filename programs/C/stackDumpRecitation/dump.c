/*
 * dumpStack prints a memory dump starting at the top of the stack 
 * for a fixed number of locations.
 * For each memory location, dumpStack prints a line containing 
 * the memory address and its contents in both Hexadecimal and decimal.
 */
 
#include <stdio.h>

int depth = 0; // number of memory locations to print in stack dump

void dumpStack(char *label) {

    unsigned int *tos = (unsigned int *) &tos;  
    /*
    *  pointer tos (top of stack) is initialized to point to
    *  itself, literally the memory location at the top of the
    *  stack when this function is called.
    *  it's cast to (unsigned int*) to avoid an incompatable type
    *  warning; gcc thinks we're making it a double pointer
    *  by mistake. we're not, but we need to tell it that.
    */
    for(int i = 0; i < depth; i++){ 
    printf("Top of stack: %s\n       Address: %p  Hexadecimal %x      Decimal %d\n", label, &tos, *tos, *tos );
    // @todo complete the function.
    tos++;
	}

   
   
}

// Do not change the code below this comment 

int fact(int n, int parm2) {
    // the extra parameter and local variables are 
    // sentinel values to help analyze the stack.
    int local1 = -1;
    int local2 = 0x55555555;

    // base case
    if (n < 1) {
        dumpStack("at the base case for fact(n)");
        return 1;
    }

    // capture the return value for the stack dump
    local1 = n * fact(n-1,1-n); 

    return local1; 
}

int main(int argc, char *argv[]){

    // declare and initialize locals, initialize global
    int f = 65535;
    int n = 4;
    depth = 100;

    // obtain n,depth from command line?

    f = fact(n,-n);  

    return f;
}

