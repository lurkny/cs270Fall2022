#include <stdio.h>

int main() {
    int i;  	// an integer value
    int *pi;	// a pointer to an integer value
    
    i = -1;
    pi = &i ;	// set pi to the address of i
    
    printf("i: %d, pi: %p > *pi: %d\n", i, pi, *pi);
    
    // place additional code here
    int **ppi;
    ppi = &pi;
    printf("i: %d, pi: %p > *pi: %d, ppi: %p > **ppi: %d \n", i, pi, *pi, ppi, **ppi);
    //Using a pointer to loop over array
    int memory[] = {1,2,3,4,5,6,7,8,9};
    int *pm;

    pm = memory;  // &memory[0] is an alternative.
    for (int i=0; i<9; i++) {
        printf("pm: %p > *pm: %d\n", pm, *pm);
        pm++;
    }
  char *cp;
    cp = (char *) pm;
   memory[0] = 0x12345678; 
    for (int i=0; i<36; i++) {
      printf ("cp: %p > *cp: 0x%02X\n", cp, *cp);
      cp++;
      }
    return 0;    
} 
