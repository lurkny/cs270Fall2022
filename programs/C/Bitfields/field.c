#include "field.h"

#include <stdio.h>

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author <b>Brody Larson</b>
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit(int value, int position) {
  //for some reason this returns the value at the position that 1 is
  //so bit 2 in 00000000000000000001001000111100 would return 4, which is the decimal for the number that the 1 at that position represents.
  int temp = value &= (1 << position);
  if (temp != 0) {
    return 1;
  }
  return 0;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit(int value, int position) {
  int temp = value |= (1 << position);
  return temp;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit(int value, int position) {
  int temp = value &= ~(1 << position);

  return temp;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField(int value, int hi, int lo, bool isSigned) {
  if (isSigned == true) {
    int MSB = getBit(value, hi);
    if (MSB == 1) {
      value = value >> lo;
      int full = 0xFFFFFFFF;
      for (int i = 0; i < (hi - lo) + 1; i++) {
        full = clearBit(full, i);
      }
      for (int i = 0; i < (hi - lo) + 1; i++) {
        if (getBit(value, i) != 0) {
          value = clearBit(value, i);
        } else {
          value = setBit(value, i);
        }
      }
      int last = full |= value;
      return last + 1;
    }
  }
  //bitshift to get the bits we want in the right place
  value = value >> lo;
  //mask with everything set to 0
  int empty = 0x00000000;
  //looping through and setting the bits that we want to keep to 1
  for (int i = 0; i < (hi - lo) + 1; i++) {
    empty = setBit(empty, i);
  }

  //using AND to compare the mask where the digits I want to keep are 1 and everything else is 0.
  int last = value &= empty;

  return last;

}
